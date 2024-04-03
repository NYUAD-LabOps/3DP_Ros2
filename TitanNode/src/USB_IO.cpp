/*
 * USB_IO.c
 *
 *  Created on: Jan 5, 2024
 *      Author: Michael Davis
 */
#include "USB_IO.h"

extern TX_EVENT_FLAGS_GROUP g_usb_plug_events;

usbIO::usbIO()
{
}

usbIO::~usbIO()
{
    USBCloseMedia();
}

void usbIO::InitUSB()
{
    int titan_ini_open;
    sprintf(default_ini_file,DEFAULT_INI_FILE);
    USBOpenMedia();
    usb_init = 1;
    printf("USB Init Done.\n");
    titan_ini_open = USBTitanINIOpen();
    if(titan_ini_open==0){
        printf("Titan INI Opened.\n");
    }else{
        printf("Titan INI Open failed.\n");
    }
}

void usbIO::initGlobalsBlockUSB()
{
    UINT status = 0;
    ULONG block_size = sizeof(struct machineGlobalsUSB);
    ULONG block_allocation_size = block_size + 4;
    ULONG general_size_of = 0;
    CHAR *memory_ptr = NULL;
    CHAR globals[8] = "globals";
    globals[7] = 0;

    status = tx_block_pool_create(&my_poolUSB, globals, block_size, (VOID *) BASE_MEMORY_ADDRESS_USB, block_allocation_size);

    switch(status){
    case TX_SUCCESS: // (0x00) Successful memory block pool creation.
        printf("BPC - success\n");
        break;
    case TX_POOL_ERROR: //  (0x02) Invalid memory block pool pointer. Either the pointer is NULL or the pool is already created.
        printf("BPC - Pool Error\n");
        break;
    case TX_PTR_ERROR: // (0x03) Invalid starting address of the pool.
        printf("BPC - PTR error\n");
        break;
    case TX_SIZE_ERROR: // (0x05) Size of pool is invalid.
        printf("BPC - size error\n");
        break;
    case TX_CALLER_ERROR:  // (0x13) Invalid caller of this service.
        printf("BPC - caller error\n");
        break;
    default:
        break;
    }

    status = tx_block_allocate (&my_poolUSB, (VOID **) &memory_ptr, TX_NO_WAIT);
    switch(status){
        case TX_SUCCESS: //  (0x00) Successful memory block allocation.
                machineGlobalsBlockUSB = (struct machineGlobalsUSB *) memory_ptr;
                machineGlobalsBlockUSB->p_media = NULL;
                machineGlobalsBlockUSB->USB_media_open = 0;
                machineGlobalsBlockUSB->USBPlugIn = 0;
                memset(machineGlobalsBlockUSB->volume,0,32);
                general_size_of = sizeof(machineGlobalsBlockUSB->file_data);
                memset(&(machineGlobalsBlockUSB->file_data),0,general_size_of);
                printf("BPA - success\n");
                break;
        case TX_DELETED: //  (0x01) Memory block pool was deleted while thread was suspended.
            printf("BPA - deleted\n");
            break;
        case TX_NO_MEMORY: //  (0x10) Service was unable to allocate a block of memory within the specified time to wait.
            printf("BPA - no memory\n");
            break;
        case TX_WAIT_ABORTED: //  (0x1A) Suspension was aborted by another thread, timer or ISR.
            printf("BPA - wait aborted\n");
            break;
        case TX_POOL_ERROR: //  (0x02) Invalid memory block pool pointer.
            printf("BPA - pool error\n");
            break;
        case TX_PTR_ERROR: //  (0x03) Invalid pointer to destination pointer.
            printf("BPA - ptr error\n");
            break;
        case TX_WAIT_ERROR: //  (0x04) A wait option other than TX_NO_WAIT was specified on a call from a nonthread.    case TX_SUCCESS: // (0x00) Successful memory block pool creation.
            printf("BPA - Wait error\n");
            break;
        default:
            break;
    }

}

char *usbIO::initUSBBufferPool(UINT size)
{
    CHAR *memory_ptr;
    UINT status;
    CHAR usb_byte_pool[14] = "usb_byte_pool";
    usb_byte_pool[13] = 0;
    ///Create pool
    status = tx_byte_pool_create(&USB_Byte_Pool, usb_byte_pool, (VOID *) 0x20060000, size + 128);

    ///Allocate bytes
    status = tx_byte_allocate (&USB_Byte_Pool, (VOID **) &memory_ptr, size, TX_NO_WAIT);
    if (status != TX_SUCCESS)
    {
        printf ("USB Buffer Init Failed.");
    }
    memset (memory_ptr, 0, size);
    return memory_ptr;
}


//callback function for USB_MSC_HOST
unsigned int usbIO::usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance)
{
    /* variable to hold the UX calls return values */
    UINT ux_return;

    UX_HOST_CLASS_STORAGE_MEDIA *p_ux_host_class_storage_media;

    // Check if host_class is for Mass Storage class.
    if (UX_SUCCESS
            == _ux_utility_memory_compare (_ux_system_host_class_storage_name, host_class,
                                           _ux_utility_string_length_get (_ux_system_host_class_storage_name)))
    {
        // Get the pointer to the media
        ux_return = ux_system_host_storage_fx_media_get ((UX_HOST_CLASS_STORAGE *)instance, &p_ux_host_class_storage_media, &g_fx_media0_ptr);

        if (ux_return != UX_SUCCESS)
        {
            /* This is a fairly simple error handling - it holds the
             application execution. In a more realistic scenarios
             a more robust and complex error handling solution should
             be provided. */
#ifdef SEMI_HOSTING
            if (DEBUGGER)
            {
                if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
                {
                    /* Debugger is connected */
                    /* Call this before any calls to printf() */
                    printf ("Could not get the pointer to the media, error:%d\n", ux_return);
                }
            }
#endif
//                   tx_thread_sleep(TX_WAIT_FOREVER);
        }
        else
        {
            //Check the usb_event type
            switch (usb_event)
            {
                case EVENT_USB_PLUG_IN:
                    // Notify the insertion of a USB Mass Storage device.
                    tx_event_flags_set (&g_usb_plug_events, EVENT_USB_PLUG_IN, TX_OR);
                    machineGlobalsBlockUSB->USBPlugIn = 1;
                break;
                case EVENT_USB_PLUG_OUT:
                    // Notify the removal of a USB Mass Storage device.
                    tx_event_flags_set (&g_usb_plug_events, EVENT_USB_PLUG_OUT, TX_OR);
                    machineGlobalsBlockUSB->USBPlugIn = 0;
                break;
                default:
                    //ignore this unsupported event
                break;
            }
        }
    }
    return UX_SUCCESS;
}

int usbIO::USBOpenMedia(void)
{
    UINT fx_return;
    int fx_return_int;
    char firstdir[9] = "firstdir";
    firstdir[8] = 0;
    ///Setup the byte pool for handling FileX operations.
    initGlobalsBlockUSB();
    tx_thread_sleep (1000);
    tx_thread_sleep (1000);
    fx_media_init_function0 ();
    tx_thread_sleep (1000);
    tx_thread_sleep (1000);
    machineGlobalsBlockUSB->p_media = g_fx_media0_ptr;
    fx_return = fx_media_volume_get (machineGlobalsBlockUSB->p_media, machineGlobalsBlockUSB->volume, FX_DIRECTORY_SECTOR);
    fx_return_int = (int)fx_return;
    switch(fx_return_int){
        case 0:  // FX_SUCCESS (0x00) Successful media volume get.
//            printf("FX_SUCCESS . . . USB media is open.\n");
            fx_directory_default_set (machineGlobalsBlockUSB->p_media, firstdir);
            printf("Set dir to firstdir\n");
//            machineGlobalsBlockUSB->USB_media_open = 1;
            break;
        case 17:  // FX_MEDIA_NOT_OPEN (0x11) Specified media is not open.
            printf("FX_MEDIA_NOT_OPEN . . . Specified media is not open.\n");
            break;
        case 4:  // FX_NOT_FOUND (0x04) Volume not found.
            printf("FX_NOT_FOUND . . . Volume not found.\n");
            break;
        case 144:  //FX_IO_ERROR(0x90) Driver I/O error.
            printf("FX_IO_ERROR . . . Driver I/O error.\n");
            break;
        case 24:  //  FX_PTR_ERROR (0x18) Invalid media or volume destination pointer.
            printf("FX_PTR_ERROR . . . invalid media or volume destination pointer.\n");
           break;
        case FX_CALLER_ERROR:  // (0x20) Caller is not a thread.
            printf("FX_CALLER_ERROR . . . caller is not a thread.\n");
            break;
        default:
            printf("FX_ . . . unknown fx_media_volume_get error.\n");
    }
    return fx_return_int;
}

int usbIO::USBCloseMedia(void)
{
    UINT fx_return;
    fx_return = fx_media_flush (machineGlobalsBlockUSB->p_media);
    fx_return = fx_media_close (machineGlobalsBlockUSB->p_media);
    return (int)fx_return;
}


int usbIO::USBTitanINIOpen(void)
{
    fileDataUSB *tmp_USB;
    tmp_USB = USBOpenFileRW(DEFAULT_INI_FILE);
    if(tmp_USB==NULL) return -1;
    machineGlobalsBlockUSB->file_data_titan_ini = tmp_USB;
    return 0;
}

void usbIO::USBTitanINIClose(void)
{
    fileDataUSB *titan_ini = machineGlobalsBlockUSB->file_data_titan_ini;
    fx_file_close(titan_ini->p_file);
    memset(titan_ini->p_file,0,sizeof(FX_FILE));
    free(titan_ini->p_file);
    titan_ini->file_open = 0;
}

void usbIO::USBTitanINIRewind(unsigned long pos)
{
    machineGlobalsBlockUSB->file_data_titan_ini->file_pos = pos;
    fx_file_seek(machineGlobalsBlockUSB->file_data_titan_ini->p_file,machineGlobalsBlockUSB->file_data_titan_ini->file_pos);
}



fileDataUSB *usbIO::USBOpenFileRW(CHAR* filename)
{
//    UCHAR line_buffer[MAX_LINE_LENGTH];
    UINT status;
    UINT i;
    FX_FILE *new_file;
    fileDataUSB *new_file_data;
    unsigned int FX_FILE_size = sizeof(FX_FILE);
    //
    // First find open usb file pointer structure
    //
    new_file_data = NULL;
    for(i=0;i<USB_FILE_MAX_COUNT;i++){
        if(machineGlobalsBlockUSB->file_data[i].file_open==0){
            new_file_data = &(machineGlobalsBlockUSB->file_data[i]);
            break;
        }
    }
    // Open the INI file
    new_file = (FX_FILE *)malloc(FX_FILE_size);
    if(new_file==NULL){
        return NULL;
    }
    new_file_data->p_file = new_file;
    status = fx_file_open(machineGlobalsBlockUSB->p_media, new_file_data->p_file, filename,FX_OPEN_FOR_READ | FX_OPEN_FOR_WRITE);
    switch(status){
        case FX_SUCCESS: // (0x00) Successful file open.
//            printf("FX_SUCCESS . . .\n");
            new_file_data->file_pos = 0;
            new_file_data->file_open = 1;
            fx_file_seek(new_file_data->p_file,new_file_data->file_pos);
            return new_file_data;
            break;
        case FX_MEDIA_NOT_OPEN: // (0x11) Specified media is not open.
            printf("FX_MEDIA_NOT_OPEN . . .\n");
            break;
        case FX_NOT_FOUND: // (0x04) Specified file was not found.
            printf("FX_FILE_NOT_FOUND . . .\n");
            break;
        case FX_NOT_A_FILE: // (0x05) Specified file name was a directory or volume.
            printf("FX_NOT_A_FILE . . .\n");
            break;
        case FX_FILE_CORRUPT: // (0x08) Specified file is corrupt and the open failed.
            printf("FX_FILE_CORRUPT . . .\n");
            break;
        case FX_ACCESS_ERROR: // (0x06) Specified file is already open or open type is invalid.
            printf("FX_ACCESS_ERROR . . .\n");
            break;
        case FX_MEDIA_INVALID: // (0x02) Invalid media.
            printf("FX_MEDIA_INVALID . . .\n");
            break;
        case FX_FAT_READ_ERROR: // (0x03) Unable to read FAT entry.
            printf("FX_FAT_READ_ERROR . . .\n");
            break;
        case FX_NO_MORE_SPACE: // (0x0A) No more space to complete the operation
            printf("FX_NO_MORE_SPACE . . .\n");
            break;
        case FX_IO_ERROR: // (0x90) Driver I/O error.
            printf("FX_IO_ERROR . . .\n");
            break;
        case FX_WRITE_PROTECT: // (0x23) Underlying media is write protected.
            printf("FX_WRITE_PROTECT . . .\n");
            break;
        case FX_PTR_ERROR: // (0x18) Invalid media or file pointer.
            printf("FX_PTR_ERROR . . .\n");
            break;
        case FX_CALLER_ERROR: // (0x20) Caller is not a thread.
            printf("FX_CALLER_ERROR . . .\n");
            break;
        default:
            printf("fx_file_open error opening file. . .default catch, returning\n");
    }
    return NULL;
}

void usbIO::USBCloseFileRW(fileDataUSB *myfileData)
{
    if(myfileData!=NULL){
        fx_file_close(myfileData->p_file);
        memset(myfileData->p_file,0,sizeof(FX_FILE));
        free(myfileData->p_file);
        myfileData->file_open = 0;
    }
}

void usbIO::showFileError(INT status, CHAR *file_name, INT line_number){
    switch(status){
        case FX_SUCCESS: // (0x00) Successful file read.
            printf("FX_SUCCESS in file %s at line %d\n", file_name,line_number);
            break;
        case FX_NOT_OPEN: // (0x07) Specified file is not open.
            printf("FX_NOT_OPEN in file %s at line %d\n", file_name,line_number);
            break;
        case FX_FILE_CORRUPT: // (0x08) File is corrupted.
            printf("FX_FILE_CORRUPT in file %s at line %d\n", file_name,line_number);
            break;
        case FX_END_OF_FILE: // (0x09) End of file has been reached.
            printf("FX_END_OF_FILE in file %s at line %d\n", file_name,line_number);
            break;
        case FX_NO_MORE_SPACE: // (0x0A) No more space to complete the operation
            printf("FX_NO_MORE_SPACE in file %s at line %d\n", file_name,line_number);
            break;
        case FX_IO_ERROR: // (0x90) Driver I/O error.
            printf("FX_IO_ERROR in file %s at line %d\n", file_name,line_number);
            break;
        case FX_PTR_ERROR: // (0x18) Invalid file or buffer pointer.
            printf("FX_PTR_ERROR in file %s at line %d\n", file_name,line_number);
            break;
        case FX_CALLER_ERROR: // (0x20) Caller is not a thread.
            printf("FX_CALLER_ERROR in file %s at line %d\n", file_name,line_number);
            break;
        default:
            printf("fx_file_read_fail default catchin file %s at line %d\n", file_name,line_number);
    }

}

double usbIO::getIniFValue(CHAR * file_name, CHAR* section, CHAR* key){
    double ret_val;
    CHAR value_buffer[MAX_LINE_LENGTH];
    memset(value_buffer,0,MAX_LINE_LENGTH);
    getIniValue(file_name, section, key, value_buffer);
    ret_val = atof(value_buffer);
    return ret_val;
}

int usbIO::getIniIValue(CHAR * file_name, CHAR* section, CHAR* key){
    INT ret_val;
    CHAR value_buffer[MAX_LINE_LENGTH];
    memset(value_buffer,0,MAX_LINE_LENGTH);
    getIniValue(file_name, section, key, value_buffer);
    ret_val = atoi(value_buffer);
    return ret_val;
}



int usbIO::getIniValue(CHAR* file_name, CHAR* section, CHAR* key, CHAR* value) {
    fileDataUSB *titan_ini = machineGlobalsBlockUSB->file_data_titan_ini;
    fileDataUSB *file_data_ptr;
    int status;
    CHAR *theFile,*theSection;

    // Open the INI file.
    if(file_name==NULL){
        file_data_ptr = machineGlobalsBlockUSB->file_data_titan_ini;
        USBTitanINIRewind(0);
    }else{
        theFile = file_name;
        file_data_ptr = USBOpenFileRW(theFile);
    }
    if (file_data_ptr == NULL) {
        return INI_FILE_NOT_FOUND;
    }
    // Find the section.
    if(section==NULL){
        theSection = default_ini_section;
    }else{
        theSection = section;
    }
    status = findSection(file_data_ptr, theSection);
    if (status == INI_SUCCESS) {
        findKey(file_data_ptr, key, value);
    }
    if(file_name!=NULL){
        USBCloseFileRW(file_data_ptr);
    }
    return status;
}


int usbIO::findSection(fileDataUSB* file_data_ptr, CHAR* section) {
    char line[MAX_LINE_LENGTH]; // Adjust as necessary
    char section_header[MAX_LINE_LENGTH];
    int result, ret_val;
    int line_count = 0;
    sprintf(section_header, "[%s]", section);
    fx_file_seek(file_data_ptr->p_file, file_data_ptr->file_pos); // Reset file pointer to the start.
    ret_val = INI_SECTION_NOT_FOUND;
    while (1) {
        memset(line,0,MAX_LINE_LENGTH);
        result = readLine(file_data_ptr, line);
        if(result!=INI_SUCCESS && result!=FX_END_OF_FILE){
            ret_val = SECTION_NOT_FOUND;
            break;
        }
        line_count++;
        if(result == INI_SUCCESS){
            result = strcmp(line, section_header);
            if (result == 0) {
//                printf("Section found on line %i\n",line_count);
//                printf("Current file position: Line = %i, byte = %lu\n",line_count,file_data_ptr->file_pos);
                ret_val = SECTION_SUCCESS_FOUND;
                break;
            }
        }
    }
    return ret_val;
}

// Read a line from the file.
int usbIO::readLine(fileDataUSB* file_data_ptr, CHAR* buffer) {
    char ch;
    int i = 0;
    UINT ret_val;
    ULONG bytes_read;
    for(i=0;i<MAX_LINE_LENGTH;i++){
        //
        //  Read 1 byte from the file and verify it was read.
        //
        ret_val = fx_file_read(file_data_ptr->p_file, &ch, 1, &bytes_read);
        if (ret_val) {
            break;
        }
        file_data_ptr->file_pos++;
        if (ch == '\n') {
            buffer[i] = '\0';
            ret_val = INI_SUCCESS;
            break;
        } else if (ch != '\r') { // Ignore carriage returns.
            buffer[i] = ch;
        }
    }
    return (INT)ret_val;
}

int usbIO::findKey(fileDataUSB* file_data_ptr, CHAR* key, CHAR* value) {
    CHAR line[MAX_LINE_LENGTH]; // Adjust as necessary
    CHAR *tok_key, *tok_val;
    CHAR tok_delim[3] = " =";
    size_t len;
    while (1){
        memset(line,0,MAX_LINE_LENGTH);
        readLine(file_data_ptr, line);
        if (line[0] == '[') { // Next section reached without finding the key
            return INI_KEY_NOT_FOUND;
        }
        len = strlen(line);
        if(len==0) return INI_KEY_NOT_FOUND;
        // Find the equals sign separating the key and value.
        tok_key = strtok(line,tok_delim);
        tok_val = strtok(NULL,tok_delim);

        if(strcmp(tok_key,key)==0){
            len = strlen(tok_val);
            memcpy(value,tok_val,len);
            value[len] = 0;
            return INI_SUCCESS;
        }
    }
    return INI_KEY_NOT_FOUND;
}


long usbIO::getIniHextoLongValue(CHAR * file_name, CHAR* section, CHAR* key)
{
    LONG ret_val;
    CHAR value_buffer[MAX_LINE_LENGTH];
    memset(value_buffer,0,MAX_LINE_LENGTH);
    getIniValue(file_name, section, key, value_buffer);
    ret_val = strtol (value_buffer,NULL, 16);
    return ret_val;
}

void usbIO::SetDefaultIniFile(char* file_name)
{
    sprintf(default_ini_file,"%s",file_name);
}

void usbIO::SetDefaultIniSection(char* section_name)
{
    sprintf(default_ini_section,"%s",section_name);
}

