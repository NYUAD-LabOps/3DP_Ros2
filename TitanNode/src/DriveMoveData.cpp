/*
 * DriveMoveData.cpp
 *
 *  Created on: Mar 19, 2024
 *      Author: Windows
 */

#include <DriveMoveData.h>

DriveMoveData::DriveMoveData()
{
    head = 0;
    tail = 0;
    buffer_empty = true;
    buffer_full = false;
    move_index = 0;
    move_list = NULL;;
    blank_move.clock_cycle_count = 0;
    blank_move.clock_cycle_target = 0;
    blank_move.dir = IOPORT_LEVEL_LOW;
    blank_move.finished = false;
    blank_move.frequency = 0;
    blank_move.move_type = 0;
    blank_move.output = false;
    blank_move.posDelta = 0;
    blank_move.started = false;
    move_current = blank_move;
}

DriveMoveData::~DriveMoveData()
{
    // TODO Auto-generated destructor stub
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
    int tmp_head;
    if(buffer_full) return MOVE_ADD_FAIL_BUFFER_FULL;
    move_list[head] = new_move;
    tmp_head = head;
    tmp_head++;
    if(tmp_head>=MAX_MOVE_COUNT) tmp_head = 0;
    if(tmp_head==tail){
        head = tmp_head;
        buffer_full = true;
    }
    buffer_empty = false;
    return MOVE_ADD_SUCCESS;
}

move * DriveMoveData::DriveMoveGetBlankMove(void)
{
    return &blank_move;


}


