#include "NodeMainEntry.h"
#include <DriveHandler05.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

//SingleMotorLinearDrive* DH5 = NULL;
SingleMotorRotaryDrive* DH5 = NULL;
//extern char driveHandlerThread[];

void DriveHandler05_entry(void)
{
    int i;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_05]==NULL){
        tx_thread_sleep (5000);
    }
    DH5 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_05];
    while (DH5)
    {
/*
        if(DH5->homing_in_progress){
            DH5->DriveHandlerHoming();
        }else{
            DH5->DriveHandler();
        }
*/
        tx_thread_relinquish();
    }
}
