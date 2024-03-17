/*
 * SingleMotorRotaryDrive.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Windows
 */

#ifndef SINGLEMOTORROTARYDRIVE_H_
#define SINGLEMOTORROTARYDRIVE_H_
#include <iostream>
#include <list>
#include "tx_api.h"
#include "hal_data.h"
#include "USB_IO.h"
#include "math.h"
#include "DriveUnitDefinedConstants.h"


#define BLOCK_SIZE_MOVE sizeof(move)

class SingleMotorRotaryDrive
{
public:
    char controlCode;
    ioport_level_t dir;
    ioport_level_t dirFwd;
    ioport_level_t dirHome;
    ioport_level_t dirFwd2;
    ioport_level_t dirHome2;
    ioport_level_t dirRev;
    ioport_level_t dirTarget;
    int drive_index;
    int drive_timer_index;
    TX_BLOCK_POOL move_block_pool;
    int move_count;
    int move_cycle;
    int move_generic;
    int move_index;
    int move_index_next;
    move *move_list;
    ioport_level_t mtrDisableState;
    ioport_level_t mtrEnableState;
    ioport_level_t mtrEnabledStatus;
    external_irq_instance_t * external_irq;
    int freqBase;
    int freqHome;
    int frequency;
    timer_instance_t *gpt_timer;
    ioport_level_t hasLimits;
    int homed;
    int homing;
    bool homing_in_progress;
    int init;
    ioport_level_t limit0State;
    ioport_level_t limit1State;
    int ls_index;
    int motor_count;
//    int move_count;
//    move move_current;
    int pos;
    int posBackOff;
    int posDelta;
    int posMax;
    int posSoftLimitForward;
    int posSoftLimitReverse;
    int posTarget;
    ioport_port_pin_t pinDir;
    ioport_port_pin_t pinDir2;
    ioport_port_pin_t pinEnable;
    ioport_port_pin_t pinEnable2;
    ioport_port_pin_t pinLimit0;
//    ioport_port_pin_t pinLimit02;
//    ioport_port_pin_t pinLimit1;
//    ioport_port_pin_t pinLimit12;
    ioport_port_pin_t pinStep;
    ioport_port_pin_t pinStep2;
    char referenced;
    char status[50];
    ioport_level_t stepState;
    usbIO* usb;

public:
    SingleMotorRotaryDrive(void);
    virtual ~SingleMotorRotaryDrive();
    void DriveCycleFeedHold();
    void DriveCycleNone();
    void DriveCycleStart();
    void DriveHandler(void);
    void DriveHandlerHoming(void);
//    void DriveHoming(void);
    void DriveHomingBackoff(void);
    void DriveMoveAdd(move new_move);
    void DriveMoveIncrementCurrent(void);
    void DriveMoveGeneric(void);
    void DriveMoveGenericStart(int freq,ioport_level_t dir);
    void DriveMoveGenericStop(void);
    move DriveMoveGetCurrent(void);
    void DriveSetMove(move the_move);
    void DriveStartHoming();
    void DriveStep(void);
    void DriveStepHandler(void);
    void DriveStepHandlerHoming(void);
    void DriveStop(void);
    void LimitHit(void);
    void OpenExtIRQ(void);
    void SetIrqInstance(external_irq_instance_t * ptr_external_irq);
    void SetDriveEnable(void);
    void SetDriveUnitIndex(int drive_unit_index);
    void SetDriveDir(ioport_level_t targetDir);
    void SetTimerFrequency(int new_frequency);
    void SetTimerPointer(timer_instance_t *gpt_timer);
    void SetupDriveUnit(ULONG block_size,void *block_pool_start,ULONG block_allocation_size);
    void SetUSBDrive(usbIO* ptr_usb_drive);
    void TimerOpen(void);
    void TimerStart(void);
    void TimerStop(void);
};

#endif /* SINGLEMOTORROTARYDRIVE_H_ */
