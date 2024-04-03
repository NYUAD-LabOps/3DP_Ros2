#include "NodeMainEntry.h"
#include <DriveHandler03.h>
#include "SingleMotorLinearDrive.h"
#include "NodeMainEntry.h"
#include "ProcessManagerTitan.h"
/* MotorHandler01 entry function */

extern ProcessManagerTitan* ptr_ProcessManager;

//SingleMotorLinearDrive* DH3 = NULL;
SingleMotorRotaryDrive* DH3 = NULL;
//extern char driveHandlerThread[];

void DriveHandler03_entry(void)
{
    int i;
    move the_move;
    tx_thread_sleep (5000);
    while(ptr_ProcessManager==NULL){
        tx_thread_sleep(100);
    }
    while(ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_03]==NULL){
        tx_thread_sleep (5000);
    }
    DH3 = ptr_ProcessManager->ptr_drive_handlers[DRIVE_HANDLER_INDEX_03];
    while (DH3)
    {
/*
        if(DH3->homing_in_progress){
            DH3->DriveHandlerHoming();
        }else{
            DH3->DriveHandler();
        }
*/
        tx_thread_relinquish();
    }
}
