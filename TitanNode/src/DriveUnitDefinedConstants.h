/*
 * DriveUnitDefinedConstants.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Windows
 */

#ifndef DRIVEUNITDEFINEDCONSTANTS_H_
#define DRIVEUNITDEFINEDCONSTANTS_H_
#include <cstdint>
#include "stddef.h"
#include "DriveUnitDefineStructs.h"


constexpr size_t    USB_BLOCK_MEMORY_SIZE = sizeof(machineGlobalsUSB) + 4;
constexpr uintptr_t BASE_MEMORY_ADDRESS_USB = 0x20000000;
constexpr uintptr_t BASE_MEMORY_ADDRESS_MOVES = BASE_MEMORY_ADDRESS_USB + USB_BLOCK_MEMORY_SIZE;

//#define WIFI_PACKET_SIZE 53
#define WIFI_PACKET_SIZE 1000

#define CDC_COMMAND_GENERIC     1
#define CDC_FILE_TRANSFER       0

#define MAXERROR 1.0 /// %
#define MINPRECISION 1.0 /// %
#define ACCEL 1
///Number of steps between velocity adjustments.
#define ACCEL_STEP_INTERVAL 10
///Number of equal divisions used for acceleration processes.
#define ACCEL_DIV 4
///Number of OS ticks between acceleration steps.
#define ACCEL_STEP_TICKS 10
#define STEPX 45.472
#define STEPY 45.472
#define STEPZ 15
#define STEPA 45.472
#define STEPC 45.472
#define STEPT 45.472
//#define STEPZ 22.5
//#define STEPX 22.5
//#define STEPY 22.5
#define DEFAULTSPEED 1200
#define DEFAULTJERKSPEEDX 500
#define DEFAULTJERKSPEEDY 500
#define DEFAULTJERKSPEEDZ 500
#define HOME_BACKOFF 250 ///Time in milliseconds the motor runs when reversing away from limit.
#define MINV 100
#define MINPRECISION 1.0 /// %
#define MAXACCEL 2000 // mm/s^2
#define MAXSPEED 500.0 ///Was 110.0
#define ACCELPERTICK 120
#define HOME_BACKOFF 250 ///Time in milliseconds the motor runs when reversing away from limit.
#define HOME_BACKOFF_DISTANCE .3 ///Distance in millimeters to back off of limit.
#define SOFTLIMITFORWARD 700
#define SOFTLIMITREVERSE 0
#define HOMEVX 1200
#define HOMEVY 1200
#define HOMEVZ 1200
#define HOMEVA 1200
#define HOMEVC 1200
#define HOMEVT 1200
#define DEBOUNCE_TIME 75 //time in milliseconds for debouncing delay
#define ENCODERPULSESPERREVOLUTION  4000
#define STEPSPERREVOLUTION          1600
#define MAX_MOVE_COUNT              10
#define MOVE_ADD_SUCCESS             0
#define MOVE_ADD_FAIL_BUFFER_FULL   1


#define MOVE_TYPE_CLOCK_COUNT_NO_OUTPUT     0
#define MOVE_TYPE_CONTINUOUS_FWD            1
#define MOVE_TYPE_CONTINUOUS_REV            2
#define MOVE_TYPE_CLOCK_COUNT_FWD           3
#define MOVE_TYPE_CLOCK_COUNT_REV           4



#define UX_STORAGE_BUFFER_SIZE      (64*1024)
#define DEBUGTEMPERATURE 0
#define LIMITACTIVESTATE IOPORT_LEVEL_LOW
#define LIMITINACTIVESTATE IOPORT_LEVEL_HIGH

#define DRIVESTATENOTHOMED   0
#define DRIVESTATEHOMED     1

#define HOMING_NOT_HOMING   0
#define HOMING_NOT_HOMED    0
#define HOMING_GOTOHOME     1
#define HOMING_BACKOFF      2
#define HOMING_BACKINGOFF   3
#define HOMING_HOMED        4
#define HOMING_LIMIT_HIT    5

#define CYCLE_NONE          0
#define CYCLE_RUN           1
#define CYCLE_FEED_HOLD     2
#define CYCLE_MOVE_MANUAL   3


#define MAX_DRIVES  12
#define DRIVE_HANDLER_INDEX_01  0
#define DRIVE_HANDLER_INDEX_02  1
#define DRIVE_HANDLER_INDEX_03  2
#define DRIVE_HANDLER_INDEX_04  3
#define DRIVE_HANDLER_INDEX_05  4
#define DRIVE_HANDLER_INDEX_06  5
#define DRIVE_HANDLER_INDEX_07  6
#define DRIVE_HANDLER_INDEX_08  7
#define DRIVE_HANDLER_INDEX_09  8
#define DRIVE_HANDLER_INDEX_10  9
#define DRIVE_HANDLER_INDEX_11  10
#define DRIVE_HANDLER_INDEX_12  11


#define MAX_MOTOR_TIMERS    12
#define TIMER_INDEX_01 0
#define TIMER_INDEX_02 1
#define TIMER_INDEX_03 2
#define TIMER_INDEX_04 3
#define TIMER_INDEX_05 4
#define TIMER_INDEX_06 5
#define TIMER_INDEX_07 6
#define TIMER_INDEX_08 7
#define TIMER_INDEX_09 8
#define TIMER_INDEX_10 9
#define TIMER_INDEX_11 10
#define TIMER_INDEX_12 11



#define MAX_LIMIT_SWITCHES 10
#define LS_01   0
#define LS_02   1
#define LS_03   2
#define LS_04   3
#define LS_05   4
#define LS_06   5
#define LS_07   6
#define LS_08   7
#define LS_09   8
#define ESTOP   0

#define MAX_LINE_LENGTH 256
#define DEBUGGER 1
#define SEMI_HOSTING


#define     EVENT_USB_PLUG_IN           (1UL << 0)
#define     EVENT_USB_PLUG_OUT          (1UL << 1)


#define     UX_STORAGE_BUFFER_SIZE      (64*1024)

#define INI_SUCCESS            0
#define INI_FILE_NOT_FOUND    -1
#define INI_SECTION_NOT_FOUND -2
#define INI_KEY_NOT_FOUND     -3
#define INI_READ_ERROR        -4
#define MAX_LINE_LENGTH 256
#define SECTION_SUCCESS_FOUND   0
#define SECTION_NOT_FOUND       1


#define DEFAULT_INI_FILE    "titan.ini"



#endif /* DRIVEUNITDEFINEDCONSTANTS_H_ */
