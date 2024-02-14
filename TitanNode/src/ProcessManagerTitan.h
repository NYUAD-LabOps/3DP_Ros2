/*
 * ProcessManagerTitan.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Windows
 */

#ifndef PROCESSMANAGERTITAN_H_
#define PROCESSMANAGERTITAN_H_

#include "SingleMotorLinearDrive.h"

class ProcessManagerTitan
{
public:
    SingleMotorLinearDrive *ptr_drive_handlers[MAX_DRIVES];
    SingleMotorLinearDrive *ptr_motor_timers[MAX_MOTOR_TIMERS];
    SingleMotorLinearDrive *ptr_limitswitches[MAX_LIMIT_SWITCHES];
    int drive_count;
    usbIO* usbDrive;
    unsigned char uartRx[WIFI_PACKET_SIZE];
    bool new_command;

public:
    ProcessManagerTitan();
    virtual ~ProcessManagerTitan();
    void ProcessManager_Main(void);
    void ProcessCommand(void);

};

#endif /* PROCESSMANAGERTITAN_H_ */
