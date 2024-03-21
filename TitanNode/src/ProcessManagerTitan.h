/*
 * ProcessManagerTitan.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Windows
 */

#ifndef PROCESSMANAGERTITAN_H_
#define PROCESSMANAGERTITAN_H_

#include "SingleMotorLinearDrive.h"


typedef struct move_message{
    char action[1];
    char drive[1];
    char dir[1];
    char type[1];
    char freq[6];
    char cycle_count[20];
}move_msg;

typedef struct message_header{
    char ack[3];
    char action[1];
    char msg_length[4];
    char move_count[4];
    char cycle_start[8];
}msg_hdr;


#define MSG_HDR_SIZE        sizeof(msg_hdr)
#define MSG_MOVE_SIZE       sizeof(move_msg)

class ProcessManagerTitan
{
public:
    msg_hdr     message_header;
    move_msg    move_message;
    move        a_move;
    int         message_count;
    SingleMotorLinearDrive *ptr_drive_handlers[MAX_DRIVES];
    SingleMotorLinearDrive *ptr_motor_timers[MAX_MOTOR_TIMERS];
    SingleMotorLinearDrive *ptr_limitswitches[MAX_LIMIT_SWITCHES];

    int drive_count;
    usbIO* usbDrive;
    char uartRx[WIFI_PACKET_SIZE];
    bool new_command;

public:
    ProcessManagerTitan();
    virtual ~ProcessManagerTitan();
    void ProcessManager_Main(void);
    void ProcessCommand(void);
    move * ParseMessage(char *message_buffer);
    bool VerifyAck(char *data_buffer);

};

#endif /* PROCESSMANAGERTITAN_H_ */
