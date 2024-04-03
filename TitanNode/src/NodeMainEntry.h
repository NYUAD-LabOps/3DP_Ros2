/*
 * NodeMainEntry.h
 *
 *  Created on: Jan 14, 2024
 *      Author: Windows
 */

#ifndef NODEMAINENTRY_H_
#define NODEMAINENTRY_H_
#include "SingleMotorLinearDrive.h"

//void ext_irq00_callback(external_irq_callback_args_t *p_args);
void genericOpenExtIRQ(external_irq_instance_t * external_irq);
//void genericTimerOpenandStart(timer_instance_t *gpt_timer);
//void genericTimerStart(timer_instance_t *gpt_timer);
//void genericTimerStop(timer_instance_t *gpt_timer);
timer_instance_t *get_Gpt_Timer_Index(int index);

//SingleMotorLinearDrive* getDriveHandler(int drive_index);
SingleMotorRotaryDrive* getDriveHandler(int drive_index);

void nmi_pin_callback_Node(bsp_grp_irq_t irq);

#endif /* NODEMAINENTRY_H_ */
