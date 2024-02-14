/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_12;
#ifndef gpt_MTR_12_callback
void gpt_MTR_12_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_11;
#ifndef gpt_MTR_11_callback
void gpt_MTR_11_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_10;
#ifndef gpt_MTR_10_callback
void gpt_MTR_10_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_09;
#ifndef gpt_MTR_09_callback
void gpt_MTR_09_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_08;
#ifndef gpt_MTR_08_callback
void gpt_MTR_08_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_07;
#ifndef gpt_MTR_07_callback
void gpt_MTR_07_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_06;
#ifndef gpt_MTR_06_callback
void gpt_MTR_06_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_05;
#ifndef gpt_MTR_05_callback
void gpt_MTR_05_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_04;
#ifndef gpt_MTR_04_callback
void gpt_MTR_04_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_03;
#ifndef gpt_MTR_03_callback
void gpt_MTR_03_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_02;
#ifndef gpt_MTR_02_callback
void gpt_MTR_02_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_MTR_01;
#ifndef gpt_MTR_01_callback
void gpt_MTR_01_callback(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_Process_Manager;
#ifndef gpt_Process_Manager_callback
void gpt_Process_Manager_callback(timer_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS9;
#ifndef ext_irqLS9_callback
void ext_irqLS9_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS8;
#ifndef ext_irqLS8_callback
void ext_irqLS8_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS7;
#ifndef ext_irqLS7_callback
void ext_irqLS7_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS6;
#ifndef ext_irqLS6_callback
void ext_irqLS6_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS5;
#ifndef ext_irqLS5_callback
void ext_irqLS5_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS4;
#ifndef ext_irqLS4_callback
void ext_irqLS4_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS3;
#ifndef ext_irqLS3_callback
void ext_irqLS3_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS2;
#ifndef ext_irqLS2_callback
void ext_irqLS2_callback(external_irq_callback_args_t *p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irqLS1;
#ifndef ext_irqLS1_callback
void ext_irqLS1_callback(external_irq_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* HAL_DATA_H_ */
