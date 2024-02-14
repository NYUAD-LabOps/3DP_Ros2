/*
 * ProcessManagerTitan.cpp
 *
 *  Created on: Jan 29, 2024
 *      Author: Windows
 */

#include <ProcessManagerTitan.h>

ProcessManagerTitan::ProcessManagerTitan()
{
    int i;
    for(i=0;i<MAX_DRIVES;i++){
        ptr_drive_handlers[i] = NULL;
    }
    for(i=0;i<MAX_MOTOR_TIMERS;i++){
        ptr_motor_timers[i] = NULL;
    }
    for(i=0;i<MAX_LIMIT_SWITCHES;i++){
        ptr_limitswitches[i] = NULL;
    }
    drive_count = 0;
    usbDrive = NULL;
    new_command = false;
}

ProcessManagerTitan::~ProcessManagerTitan()
{
    // TODO Auto-generated destructor stub
}

void ProcessManagerTitan::ProcessManager_Main(void)
{

}

void ProcessManagerTitan::ProcessCommand(void)
{
    int freq, drive_index, c_len;
    int i,x;
    ioport_level_t move_dir;
    char data[20];
    if (uartRx[0] == '@' && uartRx[1] == '@' && uartRx[2] == '@')
    {
        data[0] = uartRx[4];
        data[1] = uartRx[5];
        data[2] = 0;
        drive_index = atoi(data);
        switch(uartRx[3]){
            case 'H':
//                ptr_drive_handlers[drive_index]->homing = HOMING_GOTOHOME;
                ptr_drive_handlers[drive_index]->DriveStartHoming();
                break;
            case 'B':
                ptr_drive_handlers[drive_index]->homing = HOMING_BACKOFF;
                ptr_drive_handlers[drive_index]->DriveHoming();
                break;
            case 'M':
                c_len = strlen((const char *)uartRx);
                if(uartRx[6]=='F'){
                    move_dir = ptr_drive_handlers[drive_index]->dirFwd;
                }else{
                    move_dir = ptr_drive_handlers[drive_index]->dirRev;
                }
                x = 0;
                for(i=7;i<c_len;i++){
                    data[x] = uartRx[i];
                    x++;
                }
                data[x] = 0;
                freq = atoi(data);
                ptr_drive_handlers[drive_index]->DriveMoveGenericStart(freq, move_dir);
                break;
            case 'S':
                ptr_drive_handlers[drive_index]->DriveMoveGenericStop();
                break;
        }
    }
}


