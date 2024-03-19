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
    int i;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_01]==NULL){
        tx_thread_sleep (5000);
//        tx_thread_relinquish();
    }
//    DH1 = getDriveHandler(DRIVE_HANDLER_INDEX_01);
    DH1 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_01];
    if(DH1->homed==DRIVESTATENOTHOMED){
        DH1->DriveStartHoming();
    }
    for(i=0;i<MAX_MOVE_COUNT;i++){
        the_move.started = false;
        the_move.finished = false;
        the_move.move_type = MOVE_TYPE_CLOCK_COUNT;
        the_move.clock_cycle_count = 0;
//        the_move.dir = DH1->dirFwd;
        if(i<6){
            the_move.dir = IOPORT_LEVEL_LOW;
            the_move.frequency = 1000*(5 - i);
            the_move.clock_cycle_target = 4800;
        }else{
            the_move.dir = IOPORT_LEVEL_HIGH;
            the_move.frequency = 1000*(i-5);
            the_move.clock_cycle_target = 4800;
        }
        the_move.posDelta = 0;
        the_move.output = true;
        DH1->move_data.DriveMoveAdd(the_move);
    }
    DH1->DriveCycleStart();
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
