#include "NodeMainEntry.h"
#include <DriveHandler05.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH5 = NULL;
//extern char driveHandlerThread[];

void DriveHandler05_entry(void)
{
    int drive_homed_,i,max_moves;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_05]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
    drive_homed_ = 0;
//    DH5 = getDriveHandler(DRIVE_HANDLER_INDEX_05);
    DH5 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_05];
    if(DH5->homed==DRIVESTATENOTHOMED){
        DH5->DriveStartHoming();
    }
    max_moves = MAX_MOVE_COUNT;
    while (DH5)
    {
        if(DH5->homing_in_progress){
            DH5->DriveHandlerHoming();
        }else{
            DH5->DriveHandler();
        }
        tx_thread_relinquish();
    }
}
