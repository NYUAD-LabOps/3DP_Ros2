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
    move the_move;
    char data[25];
    char m_type[2],m_freq[6];
    if (VerifyAck(uartRx))
    {
        data[0] = uartRx[4];
        data[1] = uartRx[5];
        data[2] = 0;
        drive_index = atoi(data);
        if(drive_index<0)drive_index = 0;
        if(drive_index>drive_count) drive_index = 0;
        switch(uartRx[3]){
            case 'H':
//                ptr_drive_handlers[drive_index]->homing = HOMING_GOTOHOME;
                ptr_drive_handlers[drive_index]->DriveStartHoming();
                break;
            case 'B':
                ptr_drive_handlers[drive_index]->homing = HOMING_BACKOFF;
                ptr_drive_handlers[drive_index]->DriveStartHoming();
                break;
            case 'M':
                the_move = *(ptr_drive_handlers[drive_index]->move_data.DriveMoveGetBlankMove());
                c_len = strlen((const char *)uartRx);
                if(uartRx[6]=='F'){
                    the_move.dir = ptr_drive_handlers[drive_index]->dirFwd;
                }else{
                    the_move.dir = ptr_drive_handlers[drive_index]->dirRev;
                }
                m_type[0] = uartRx[7];
                m_type[1] = 0;
                the_move.move_type = atoi(m_type);
                if(the_move.move_type){
                    the_move.output = true;
                }else{
                    the_move.output = false;
                }
                x = 0;
                for(i=8;i<13;i++){
                    data[x] = uartRx[i];
                    x++;
                }
                data[x] = 0;
                the_move.frequency = atoi(data);
                x = 0;
                for(i=13;i<c_len;i++){
                    data[x] = uartRx[i];
                    x++;
                }
                data[x] = 0;
                the_move.clock_cycle_target = atoi(data);
                ptr_drive_handlers[drive_index]->move_data.DriveMoveAdd(the_move);
                ptr_drive_handlers[drive_index]->DriveCycleStart();
                break;
            case 'S':
                ptr_drive_handlers[drive_index]->DriveMoveStop();
                break;
        }
    }
}

bool ProcessManagerTitan::VerifyAck(char *data_buffer)
{
    if (data_buffer[0] == '@' && data_buffer[1] == '@' && data_buffer[2] == '@') return true;
    return false;
}

move * ProcessManagerTitan::ParseMessage(char *message_buffer)
{
    return &a_move;
}

