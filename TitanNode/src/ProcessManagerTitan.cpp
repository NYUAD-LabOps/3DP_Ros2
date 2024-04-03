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
    message_count = 0;
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

    int i,size_header,size_move,parse_index;
    int drive_index;
    ParseMessageZeroStructures();
    ParseMessageExtractHeaderFromChar(uartRx);
    if (VerifyAck(&(message_header))==false) return;
    size_header = sizeof(msg_hdr_char);
    size_move = sizeof(move_msg_char);
    for(i=0;i<message_header.move_count;i++)
    {
        parse_index = i*size_move + size_header;
        ParseMessageExtractMoveFromChar(&uartRx[parse_index]);
        drive_index = move_message.drive;
        switch(a_move.move_type){
            case MOVE_TYPE_CLOCK_COUNT_NO_OUTPUT:
                ptr_drive_handlers[drive_index]->move_data->DriveMoveAdd(a_move);
                break;
            case MOVE_TYPE_HOME:
                ptr_drive_handlers[drive_index]->DriveStartHoming();
                break;
            case MOVE_TYPE_HOME_HOMING_BACK_OFF:
                ptr_drive_handlers[drive_index]->homing = HOMING_BACKOFF;
                ptr_drive_handlers[drive_index]->DriveStartHoming();
                break;
            case MOVE_TYPE_CONTINUOUS_FWD:
                ptr_drive_handlers[drive_index]->move_data->DriveMoveAdd(a_move);
                break;
            case MOVE_TYPE_CONTINUOUS_REV:
                ptr_drive_handlers[drive_index]->move_data->DriveMoveAdd(a_move);
                break;
            case MOVE_TYPE_CLOCK_COUNT_FWD:
                ptr_drive_handlers[drive_index]->move_data->DriveMoveAdd(a_move);
                break;
            case MOVE_TYPE_CLOCK_COUNT_REV:
                ptr_drive_handlers[drive_index]->move_data->DriveMoveAdd(a_move);
                break;
            case MOVE_TYPE_CLOCK_COUNT_STOP:
                ptr_drive_handlers[drive_index]->DriveMoveStop();
                break;
        }
        if(message_header.cycle_start>0){
            ptr_drive_handlers[drive_index]->DriveCycleStart();
        }
    }
}

bool ProcessManagerTitan::VerifyAck(msg_hdr *the_msg_hdr)
{
    if(the_msg_hdr == NULL) return false;
    if (the_msg_hdr->ack[0] == '@' && the_msg_hdr->ack[1] == '@' && the_msg_hdr->ack[2] == '@') return true;
    return false;
}

void ProcessManagerTitan::ParseMessageZeroStructures(void)
{
    message_count = 0;
    ParseMessageZeroStructureHeader();
    ParseMessageZeroStructureMoveMsgHeader();
    ParseMessageZeroStructureMoveQty(&a_move,1);
}

void ProcessManagerTitan::ParseMessageZeroStructureHeader(void)
{
    memset(&message_header,0,sizeof(msg_hdr));
}

void ProcessManagerTitan::ParseMessageZeroStructureMoveMsgHeader(void)
{
    memset(&move_message,0,sizeof(move_msg));
}

void ProcessManagerTitan::ParseMessageZeroStructureMoveQty(move *the_moves,int count)
{
    memset(the_moves,0,count * sizeof(move));
}

void ProcessManagerTitan::ParseMessageExtractHeaderFromChar(char *message_buffer)
{
    msg_hdr_char *char_msg_hdr = (msg_hdr_char *)(message_buffer);
    message_header.ack[0] = char_msg_hdr->ack[0];
    message_header.ack[1] = char_msg_hdr->ack[1];
    message_header.ack[2] = char_msg_hdr->ack[2];
    message_header.move_count = atoi(char_msg_hdr->move_count);
    message_header.cycle_start = atoi(char_msg_hdr->cycle_start);
}

void ProcessManagerTitan::ParseMessageExtractMoveFromChar(char *message_buffer)
{
    move_msg_char *char_move_msg = (move_msg_char *)(message_buffer);
    move_message.drive  = atoi(char_move_msg->drive);
    if(move_message.drive<0) move_message.drive = 0;
    if(move_message.drive>=drive_count) move_message.drive = 0;
    a_move.clock_cycle_target = atoi(char_move_msg->clock_cycle_target);
    a_move.clock_cycle_count = 0;
    a_move.frequency  = atoi(char_move_msg->freq);
    a_move.move_type  = atoi(char_move_msg->type);
}
