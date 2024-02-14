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
    while (DH1)
    {
        DH1->DriveHandler();
        if(DH1->homed==HOMING_HOMED && drive_homed_==0){
            printf("Drive Homed\n");
            tx_thread_sleep(1000);
            for(i=0;i<max_moves;i++){
                the_move.pos = 1600+i*500;
                the_move.frequency = 2500+ i*200;
                DH1->DriveMoveAdd(the_move);
            }
//            for(i=max_moves;i>0;i--){
//                the_move.pos = 10000+i*8;
//                the_move.frequency = 5000+ i*6;
//                DH1->DriveAddMove(the_move);
//            }
            drive_homed_ = 1;
            DH1->DriveCycleStart();
        }
        tx_thread_relinquish();
    }
}
