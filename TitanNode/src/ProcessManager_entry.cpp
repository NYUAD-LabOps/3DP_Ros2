#include "ProcessManager.h"
#include "USB_IO.h"
#include "SingleMotorLinearDrive.h"
#include "ProcessManagerTitan.h"
//usbIO* usbDrive = NULL;
//extern usbIO* usbDrive;
ProcessManagerTitan* ptr_ProcessManager = NULL;
//extern int numberOfDrives;

#define UX_BUFFER_SIZE (128)
#define CDCACM_FLAG ((ULONG)0x0001)

/* CDC-ACM reception data buffer. */
static char buffer[UX_BUFFER_SIZE];
char *uartRx;

int USB_Device_connected = 0;

/* A pointer to store CDC-ACM device instance. */
static UX_SLAVE_CLASS_CDC_ACM *g_cdc = (UX_SLAVE_CLASS_CDC_ACM*) UX_NULL;


/* USBX CDC-ACM Instance Activate User Callback Function */
VOID ux_cdc_device0_instance_activate(VOID *cdc_instance)
{
    /* Save the CDC instance.  */
    g_cdc = (UX_SLAVE_CLASS_CDC_ACM*) cdc_instance;
    tx_event_flags_set (&g_cdcacm_activate_event_flags0, CDCACM_FLAG, TX_OR);
}

/* USBX CDC-ACM Instance Deactivate User Callback Function */
VOID ux_cdc_device0_instance_deactivate(VOID *cdc_instance)
{
    SSP_PARAMETER_NOT_USED(cdc_instance);

    tx_event_flags_set (&g_cdcacm_activate_event_flags0, ~CDCACM_FLAG, TX_AND);
    g_cdc = (UX_SLAVE_CLASS_CDC_ACM*)UX_NULL;
}

void error_trap(char *msg, ULONG status)
{

    printf ("%s failed. error = %d\n", msg, (int) status);

    while (1)
    {

    }
}


void ProcessManager_entry(void)

{
    UINT size_of_usbDrive = sizeof(usbIO);
//    usbIO* usbDriveTmp;
    initialise_monitor_handles ();
    printf("size_of(usbIO) = %u\n\n",size_of_usbDrive);
    ptr_ProcessManager = new ProcessManagerTitan();
    uartRx = ptr_ProcessManager->uartRx;

    ptr_ProcessManager->usbDrive = new usbIO();
    ptr_ProcessManager->usbDrive->InitUSB();
    while(ptr_ProcessManager->drive_count==0){
        tx_thread_sleep (1);
    }
    while (1)
    {
        ptr_ProcessManager->ProcessManager_Main();
        tx_thread_sleep (1);
    }
}

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance)
{
    UINT ret_val = 0;
    ret_val = ptr_ProcessManager->usbDrive->usb_host_plug_event_notification(usb_event, host_class, instance);
    return ret_val;
}

/* UARTWIFI entry function */
void USB_Device_UART_entry()
{

    UINT fx_return;
//    UCHAR uartRx[WIFI_PACKET_SIZE];
    UCHAR controlCodeRxBuf[4];
    memset (controlCodeRxBuf, 0, 4);
//    int i;
//    i = 0;
//    memset (uartRx, 0, WIFI_PACKET_SIZE);

    ULONG status;
    ULONG actual_flags;
//    ULONG actual_length;

    //Call pre-programmed instructions.

 //   char preProgrammed[WIFI_PACKET_SIZE];

    tx_thread_sleep(1000);

    printf ("USBX_CDCACM_Device running???\n\n");

    /* Check if a CDC device is connected */
    status = tx_event_flags_get (&g_cdcacm_activate_event_flags0, CDCACM_FLAG, TX_OR, &actual_flags, TX_NO_WAIT);
    if (status && (status != TX_NO_EVENTS))
    {
        error_trap ("tx_event_flags_get 1", status);
    }

    /* Wait for a CDC device to be connected */
    while (!(actual_flags & CDCACM_FLAG))
    {

        printf ("Waiting for a CDC device to be connected...\n");

        /* 1. Wait for the CDCACM event flag */
        status = tx_event_flags_get (&g_cdcacm_activate_event_flags0, CDCACM_FLAG, TX_OR, &actual_flags,
        TX_WAIT_FOREVER);
        if (status)
        {
            error_trap ((char *)"tx_event_flags_get 2", status);
        }

        printf ("Event detected\n");

    }

    printf ("CDC device connected\n");\
    USB_Device_connected = 1;
}

extern char *uartRx;

int USBDeviceDataWatchDownloadFile(void)
{
    int status;
    return status;
}

int USBDeviceDataWatch(void)
{
    bool datafound = false;
    unsigned long status;
    unsigned long actual_length;
    move_msg_hdr_ptr *move_message_hdr;
    USB_Device_connected = 1;
    int i;
    for(i=0;i<WIFI_PACKET_SIZE;i++){
            uartRx[i] = 0;
    }
    status = ux_device_class_cdc_acm_read (g_cdc, (unsigned char *)uartRx, WIFI_PACKET_SIZE, &actual_length);
    move_message_hdr = (move_msg_hdr_ptr *)uartRx;
    printf("The data =>*** %s ***\n",uartRx);
    i = strlen((char *)uartRx);
    ux_device_class_cdc_acm_write (g_cdc, (unsigned char *)uartRx, i, &actual_length);

    if (status)
    {
        printf ("Device read fail");
    }else{
        datafound = 0;  // 1 = generic command data
    }
    if (uartRx[0] == '@' && uartRx[1] == '@' && uartRx[2] == '@')
    {
        switch(uartRx[3])
        {
            case 'F':
                datafound = CDC_FILE_TRANSFER;
                break;
            default:
                datafound = CDC_COMMAND_GENERIC;
                break;
        }
        status = ux_device_class_cdc_acm_write (g_cdc, (unsigned char *)uartRx, WIFI_PACKET_SIZE, &actual_length);
        return datafound;
    }
    printf ("%d characters read\n", (int) actual_length);
    return datafound;
}

void serialHandler(char *data_buffer)
{
    UINT status;
    ULONG actual_length;
    long long fileSize;
    fileSize = 0;
    UCHAR sendACK[WIFI_PACKET_SIZE];
    memset (sendACK, 0, WIFI_PACKET_SIZE);
    sendACK[0] = 'A';
    sendACK[1] = 'C';
    sendACK[2] = 'K';

    ///In the case of a file transfer, don't ACK until the gcode file is ready for writing.
    /// For all other messages, send ACK at the end of processReceivedMsg(), to indicate to the GUI
    /// that the message has been received, and the controller is ready for more.

    fileSize = 0;
    switch (uartRx[0])
    {
        default:
            ux_device_class_cdc_acm_write (g_cdc, sendACK, WIFI_PACKET_SIZE, &actual_length);
    }

}

