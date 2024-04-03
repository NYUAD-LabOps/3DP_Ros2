#include "USB_CDC_Read.h"
#include "USB_IO.h"
#include "USB_IO.h"
#include "SingleMotorLinearDrive.h"
#include "ProcessManagerTitan.h"

//void USB_Device_UART_entry(void);

extern ProcessManagerTitan* ptr_ProcessManager;

extern int USB_Device_connected;

/* USB_CDC_Read entry function */
void USB_CDC_Read_entry(void)
{
    /* TODO: add your own code here */
    int datafound = 0;
    tx_thread_sleep(5000);
    printf("USB_Device startup next...\n");
    USB_Device_UART_entry();
    while(ptr_ProcessManager==0){
        tx_thread_sleep(100);
    }
    while(USB_Device_connected==0){
        tx_thread_sleep(100);
    }
    while (1)
    {
        datafound = USBDeviceDataWatch();
        switch(datafound){
            case CDC_COMMAND_GENERIC:
                ptr_ProcessManager->ProcessCommand();
                datafound = 0;
                break;
            case CDC_FILE_TRANSFER:
                datafound = USBDeviceDataWatchDownloadFile();
                break;
            default:
                break;
        }
        tx_thread_sleep (1);
    }
}

