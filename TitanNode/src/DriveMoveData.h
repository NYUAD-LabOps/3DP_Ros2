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

/*
    switch(move_type){
        case MOVE_TYPE_CLOCK_COUNT_NO_OUTPUT:
            break;
        case MOVE_TYPE_HOME:
            break;
        case MOVE_TYPE_HOME_HOMING_BACK_OFF:
            break;
        case MOVE_TYPE_CONTINUOUS_FWD:
            break;
        case MOVE_TYPE_CONTINUOUS_REV:
            break;
        case MOVE_TYPE_CLOCK_COUNT_FWD:
            break;
        case MOVE_TYPE_CLOCK_COUNT_REV:
            break;
        case MOVE_TYPE_CLOCK_COUNT_STOP:
            break;
    }
*/

typedef struct move_instruction{
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
    bool move_current_finished;
//    move move_list[MAX_MOVE_COUNT];
    move *move_list;

public:
    DriveMoveData();
    virtual ~DriveMoveData();
    int DriveMoveAdd(move new_move);
    move *DriveMoveGetBlankMove(void);
    void DriveMoveGetNext(void);
    void DriveMoveStop(void);

};

#endif /* DRIVEMOVEDATA_H_ */
