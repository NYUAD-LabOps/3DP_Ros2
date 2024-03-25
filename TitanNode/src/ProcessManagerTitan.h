/*
 * ProcessManagerTitan.h
 *
 *  Created on: Jan 29, 2024
 *      Author: Windows
 */

#ifndef PROCESSMANAGERTITAN_H_
#define PROCESSMANAGERTITAN_H_

#include "SingleMotorLinearDrive.h"


typedef struct move_message_char{
    char drive[2];
    char type[2];
    char freq[7];
    char clock_cycle_target[7];
}move_msg_char;

typedef struct message_header_char{
    char ack[3];
    char move_count[2];
    char cycle_start[2];
}msg_hdr_char;

typedef struct move_msg_hdr_char{
    msg_hdr_char the_header;
    move_msg_char the_first_message;
}move_msg_hdr_char_ptr;



typedef struct move_message{
    int drive;
    int type;
    int freq;
    unsigned long clock_cycle_target;
}move_msg;

typedef struct message_header{
    char ack[3];
    int msg_length;
    int move_count;
    int cycle_start;
}msg_hdr;

typedef struct move_msg_hdr{
    msg_hdr the_header;
    move_msg the_first_message;
}move_msg_hdr_ptr;


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
