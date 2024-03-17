#include "NodeMainEntry.h"
#include <DriveHandler06.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH6 = NULL;
//extern char driveHandlerThread[];

void DriveHandler06_entry(void)
{
    int drive_homed_,i,max_moves;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_06]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
    drive_homed_ = 0;
//    DH6 = getDriveHandler(DRIVE_HANDLER_INDEX_06);
    DH6 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_06];
    if(DH6->homed==DRIVESTATENOTHOMED){
        DH6->DriveStartHoming();
    }
    max_moves = MAX_MOVE_COUNT;
    while (DH6)
    {
        if(DH6->homing_in_progress){
            DH6->DriveHandlerHoming();
        }else{
            DH6->DriveHandler();
        }
        tx_thread_relinquish();
    }
}
