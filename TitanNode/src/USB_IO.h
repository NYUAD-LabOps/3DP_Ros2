/*
 * USB_IO.h
 *
 *  Created on: Jan 1, 2024
 *      Author: Windows
 */
//#include "USBMain_thread.h"

#ifndef USB_IO_H_
#define USB_IO_H_

#include <stdio.h>
#include "fx_api.h"
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#include "DriveUnitDefinedConstants.h"


class usbIO {
public:
    char default_ini_file[20];
    char default_ini_section[20];
    TX_BLOCK_POOL my_poolUSB;
    int usb_init = 0;
    static TX_BYTE_POOL USB_Byte_Pool;
    struct machineGlobalsUSB *machineGlobalsBlockUSB;

public:
    usbIO();
    ~usbIO();
    void SetDefaultIniFile(char* file_name);
    void SetDefaultIniSection(char* section_name);
    void InitUSB();
    int USBOpenMedia(void);
    int USBCloseMedia(void);
    int USBTitanINIOpen(void);
    void USBTitanINIClose(void);
    void USBTitanINIRewind(unsigned long pos);
    void initGlobalsBlockUSB(void);
    char *initUSBBufferPool(UINT size);
    int getIniValue(CHAR * file_name, CHAR* section, CHAR* key, CHAR* value);
    double getIniFValue(CHAR * file_name, CHAR* section, CHAR* key);
    int getIniIValue(CHAR * file_name, CHAR* section, CHAR* key);
    long getIniHextoLongValue(CHAR * file_name, CHAR* section, CHAR* key);
    int findKey(fileDataUSB* fileDataUSB_ptr, CHAR* key, CHAR* value);
    int findSection(fileDataUSB* fileDataUSB_ptr, CHAR* section);
    int readLine(fileDataUSB* fileDataUSB_ptr, CHAR* buffer);
    fileDataUSB *USBOpenFileRW(CHAR* filename);
    void USBCloseFileRW(fileDataUSB *myfile);
    void showFileError(INT status, CHAR *file_name, INT line_number);
    unsigned int usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance);
};

extern "C" {
extern void initialise_monitor_handles(void);
void USB_Device_UART_entry(void);
int USBDeviceDataWatch(void);
int USBDeviceDataWatchDownloadFile(void);
void serialHandler(char *uartRx);
void error_trap(char *msg, ULONG status);

}

#endif /* USB_IO_H_ */





