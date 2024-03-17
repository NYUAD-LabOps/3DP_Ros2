#include "NodeMainEntry.h"
#include "DriveHandler02.h"
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH2 = NULL;
//extern char driveHandlerThread[];

void DriveHandler02_entry(void)
{
    int drive_homed_,i,max_moves;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_02]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
    drive_homed_ = 0;
//    DH2 = getDriveHandler(DRIVE_HANDLER_INDEX_01);
    DH2 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_02];
    if(DH2->homed==DRIVESTATENOTHOMED){
        DH2->DriveStartHoming();
    }
    max_moves = MAX_MOVE_COUNT;
    while (DH2)
    {
        if(DH2->homing_in_progress){
            DH2->DriveHandlerHoming();
        }else{
            DH2->DriveHandler();
        }
        tx_thread_relinquish();
    }
}

