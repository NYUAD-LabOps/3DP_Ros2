#include "NodeMainEntry.h"
#include <DriveHandler04.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH4 = NULL;
//extern char driveHandlerThread[];

void DriveHandler04_entry(void)
{
    int i;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_04]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
//    DH4 = getDriveHandler(DRIVE_HANDLER_INDEX_04);
    DH4 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_04];
    while (DH4)
    {
        if(DH4->homing_in_progress){
            DH4->DriveHandlerHoming();
        }else{
            DH4->DriveHandler();
        }
        tx_thread_relinquish();
    }
}
