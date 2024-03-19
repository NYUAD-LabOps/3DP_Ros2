/*
 * DriveMoveData.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Windows
 */

#ifndef DRIVEMOVEDATA_H_
#define DRIVEMOVEDATA_H_

#include "fx_api.h"
#include "DriveUnitDefinedConstants.h"


typedef struct move_instruction{
    bool output;
    bool finished;
    bool started;
    ioport_level_t dir;
    int posDelta;
    int frequency;
    int move_type;
    long clock_cycle_target;
    long clock_cycle_count;
}move;


class DriveMoveData
{
public:
    int head;
    int tail;
    bool buffer_empty;
    bool buffer_full;
    move blank_move;
    move move_current;
    int move_index;
    move *move_list;

public:
    DriveMoveData();
    virtual ~DriveMoveData();
    move *DriveMoveGetBlankMove(void);
    int DriveMoveAdd(move new_move);
    void DriveMoveGetNext(void);

};

#endif /* DRIVEMOVEDATA_H_ */
