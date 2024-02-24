#include "NodeMainEntry.h"
#include <DriveHandler03.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

SingleMotorLinearDrive* DH3 = NULL;
//extern char driveHandlerThread[];

void DriveHandler03_entry(void)
{
    int drive_homed_,i,max_moves;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_03]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
    drive_homed_ = 0;
//    DH3 = getDriveHandler(DRIVE_HANDLER_INDEX_03);
    DH3 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_03];
    if(DH3->homed==DRIVESTATENOTHOMED){
        DH3->DriveStartHoming();
    }
    max_moves = MAX_MOVE_COUNT;
    while (DH3)
    {
        DH3->DriveHandler();
        if(DH3->homed==HOMING_HOMED && drive_homed_==0){
            printf("Drive Homed\n");
            tx_thread_sleep(1000);
            for(i=0;i<max_moves;i++){
                the_move.pos = 1600+i*500;
                the_move.frequency = 2500+ i*200;
                DH3->DriveMoveAdd(the_move);
            }
//            for(i=max_moves;i>0;i--){
//                the_move.pos = 10000+i*8;
//                the_move.frequency = 5000+ i*6;
//                DH3->DriveAddMove(the_move);
//            }
            drive_homed_ = 1;
            DH3->DriveCycleStart();
        }
        tx_thread_relinquish();
    }
}
