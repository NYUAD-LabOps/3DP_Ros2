#include "NodeMainEntry.h"
#include <DriveHandler01.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH1 = NULL;
//extern char driveHandlerThread[];

void DriveHandler01_entry(void)
{
    int drive_homed_,i,max_moves;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_01]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
    drive_homed_ = 0;
//    DH1 = getDriveHandler(DRIVE_HANDLER_INDEX_01);
    DH1 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_01];
    if(DH1->homed==DRIVESTATENOTHOMED){
        DH1->DriveStartHoming();
    }
    max_moves = MAX_MOVE_COUNT;
    for(i=0;i<max_moves;i++){
        the_move.clock_cycle_target = 5000+i*5000;
        the_move.clock_cycle_count = 0;
        the_move.output = true;
        the_move.frequency = 2500+ i*200;
        DH1->DriveMoveAdd(the_move);
    }
//    DH1->DriveCycleStart();
    while (DH1)
    {
        if(DH1->homing_in_progress){
            DH1->DriveHandlerHoming();
        }else{
            DH1->DriveHandler();
        }
        tx_thread_relinquish();
    }
}
