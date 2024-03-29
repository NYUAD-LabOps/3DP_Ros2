/*
 * DriveMoveData.cpp
 *
 *  Created on: Mar 19, 2024
 *      Author: Windows
 */

#include <DriveMoveData.h>

DriveMoveData::DriveMoveData()
{
    move_list = NULL;
    head = 0;
    tail = 0;
    buffer_empty = true;
    buffer_full = false;
    move_index = 0;
    blank_move.clock_cycle_count = 0;
    blank_move.clock_cycle_target = 0;
    blank_move.frequency = 0;
    blank_move.move_type = 0;
    move_current = blank_move;
    move_current_finished = true;
}

DriveMoveData::~DriveMoveData()
{
    // TODO Auto-generated destructor stub
}


void DriveMoveData::DriveMoveStop(void)
{
    head = 0;
    tail = 0;
    buffer_empty = true;
    buffer_full = false;
    move_index = 0;
    blank_move.clock_cycle_count = 0;
    blank_move.clock_cycle_target = 0;
    blank_move.frequency = 0;
    blank_move.move_type = 0;
    move_current = blank_move;
    move_current_finished = true;
}

void DriveMoveData::DriveMoveGetNext(void)
{

    if(buffer_empty) return;
    move_current = move_list[tail];
    tail++;
    if(tail>=MAX_MOVE_COUNT){
        tail = 0;
    }
    if(head==tail){
        buffer_empty = true;
    }
    buffer_full = false;
}

int DriveMoveData::DriveMoveAdd(move new_move)
{
    if(buffer_full) return MOVE_ADD_FAIL_BUFFER_FULL;
//    new_move.clock_cycle_count = 0;
    move_list[head] = new_move;
    head++;
    if(head>=MAX_MOVE_COUNT) head = 0;
    buffer_empty = false;
    if(head==tail){
        buffer_full = true;
    }
    return MOVE_ADD_SUCCESS;
}

move * DriveMoveData::DriveMoveGetBlankMove(void)
{
    return &blank_move;
}


