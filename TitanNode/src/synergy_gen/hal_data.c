/* generated HAL source file - do not edit */
#include "hal_data.h"
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_12) && !defined(SSP_SUPPRESS_ISR_GPT12)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 12);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_12_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_12_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_12_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 12, .autostart = true, .p_callback = gpt_MTR_12_callback, .p_context = &g_timer_MTR_12, .p_extend =
          &g_timer_MTR_12_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_12 =
{ .p_ctrl = &g_timer_MTR_12_ctrl, .p_cfg = &g_timer_MTR_12_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_11) && !defined(SSP_SUPPRESS_ISR_GPT11)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 11);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_11_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_11_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_11_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 11, .autostart = true, .p_callback = gpt_MTR_11_callback, .p_context = &g_timer_MTR_11, .p_extend =
          &g_timer_MTR_11_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_11 =
{ .p_ctrl = &g_timer_MTR_11_ctrl, .p_cfg = &g_timer_MTR_11_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_10) && !defined(SSP_SUPPRESS_ISR_GPT10)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 10);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_10_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_10_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_10_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 10, .autostart = true, .p_callback = gpt_MTR_10_callback, .p_context = &g_timer_MTR_10, .p_extend =
          &g_timer_MTR_10_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_10 =
{ .p_ctrl = &g_timer_MTR_10_ctrl, .p_cfg = &g_timer_MTR_10_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_09) && !defined(SSP_SUPPRESS_ISR_GPT9)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 9);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_09_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_09_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_09_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 9, .autostart = true, .p_callback = gpt_MTR_09_callback, .p_context = &g_timer_MTR_09, .p_extend =
          &g_timer_MTR_09_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_09 =
{ .p_ctrl = &g_timer_MTR_09_ctrl, .p_cfg = &g_timer_MTR_09_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_08) && !defined(SSP_SUPPRESS_ISR_GPT8)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 8);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_08_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_08_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_08_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 8, .autostart = true, .p_callback = gpt_MTR_08_callback, .p_context = &g_timer_MTR_08, .p_extend =
          &g_timer_MTR_08_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_08 =
{ .p_ctrl = &g_timer_MTR_08_ctrl, .p_cfg = &g_timer_MTR_08_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_07) && !defined(SSP_SUPPRESS_ISR_GPT7)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 7);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_07_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_07_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_07_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 7, .autostart = true, .p_callback = gpt_MTR_07_callback, .p_context = &g_timer_MTR_07, .p_extend =
          &g_timer_MTR_07_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_07 =
{ .p_ctrl = &g_timer_MTR_07_ctrl, .p_cfg = &g_timer_MTR_07_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_06) && !defined(SSP_SUPPRESS_ISR_GPT6)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 6);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_06_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_06_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_06_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 6, .autostart = true, .p_callback = gpt_MTR_06_callback, .p_context = &g_timer_MTR_06, .p_extend =
          &g_timer_MTR_06_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_06 =
{ .p_ctrl = &g_timer_MTR_06_ctrl, .p_cfg = &g_timer_MTR_06_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_05) && !defined(SSP_SUPPRESS_ISR_GPT5)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 5);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_05_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_05_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_05_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 5, .autostart = true, .p_callback = gpt_MTR_05_callback, .p_context = &g_timer_MTR_05, .p_extend =
          &g_timer_MTR_05_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_05 =
{ .p_ctrl = &g_timer_MTR_05_ctrl, .p_cfg = &g_timer_MTR_05_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_04) && !defined(SSP_SUPPRESS_ISR_GPT4)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 4);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_04_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_04_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_04_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 4, .autostart = true, .p_callback = gpt_MTR_04_callback, .p_context = &g_timer_MTR_04, .p_extend =
          &g_timer_MTR_04_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_04 =
{ .p_ctrl = &g_timer_MTR_04_ctrl, .p_cfg = &g_timer_MTR_04_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_03) && !defined(SSP_SUPPRESS_ISR_GPT3)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 3);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_03_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_03_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_03_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 3, .autostart = true, .p_callback = gpt_MTR_03_callback, .p_context = &g_timer_MTR_03, .p_extend =
          &g_timer_MTR_03_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_03 =
{ .p_ctrl = &g_timer_MTR_03_ctrl, .p_cfg = &g_timer_MTR_03_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_02) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_02_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_02_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_02_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 10, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 2, .autostart = true, .p_callback = gpt_MTR_02_callback, .p_context = &g_timer_MTR_02, .p_extend =
          &g_timer_MTR_02_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_02 =
{ .p_ctrl = &g_timer_MTR_02_ctrl, .p_cfg = &g_timer_MTR_02_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_MTR_01) && !defined(SSP_SUPPRESS_ISR_GPT1)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 1);
#endif
#endif
static gpt_instance_ctrl_t g_timer_MTR_01_ctrl;
static const timer_on_gpt_cfg_t g_timer_MTR_01_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_MTR_01_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 30000, .unit = TIMER_UNIT_FREQUENCY_HZ, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 1, .autostart = false, .p_callback = gpt_MTR_01_callback, .p_context = &g_timer_MTR_01, .p_extend =
          &g_timer_MTR_01_extend,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_MTR_01 =
{ .p_ctrl = &g_timer_MTR_01_ctrl, .p_cfg = &g_timer_MTR_01_cfg, .p_api = &g_timer_on_gpt };
#if (1) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer_Process_Manager) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t g_timer_Process_Manager_ctrl;
static const timer_on_gpt_cfg_t g_timer_Process_Manager_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer_Process_Manager_cfg =
{ .mode = TIMER_MODE_PERIODIC,
  .period = 1000,
  .unit = TIMER_UNIT_FREQUENCY_HZ,
  .duty_cycle = 50,
  .duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0,
  .autostart = false,
  .p_callback = gpt_Process_Manager_callback,
  .p_context = &g_timer_Process_Manager,
  .p_extend = &g_timer_Process_Manager_extend,
  .irq_ipl = (1), };
/* Instance structure to use this module. */
const timer_instance_t g_timer_Process_Manager =
{ .p_ctrl = &g_timer_Process_Manager_ctrl, .p_cfg = &g_timer_Process_Manager_cfg, .p_api = &g_timer_on_gpt };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS9) && !defined(SSP_SUPPRESS_ISR_ICU4)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ4);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS9_ctrl;
static const external_irq_cfg_t g_external_irqLS9_cfg =
{ .channel = 4,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS9_callback,
  .p_context = &g_external_irqLS9,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS9 =
{ .p_ctrl = &g_external_irqLS9_ctrl, .p_cfg = &g_external_irqLS9_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS8) && !defined(SSP_SUPPRESS_ISR_ICU6)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ6);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS8_ctrl;
static const external_irq_cfg_t g_external_irqLS8_cfg =
{ .channel = 6,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = false,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS8_callback,
  .p_context = &g_external_irqLS8,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS8 =
{ .p_ctrl = &g_external_irqLS8_ctrl, .p_cfg = &g_external_irqLS8_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS7) && !defined(SSP_SUPPRESS_ISR_ICU5)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ5);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS7_ctrl;
static const external_irq_cfg_t g_external_irqLS7_cfg =
{ .channel = 5,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS7_callback,
  .p_context = &g_external_irqLS7,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS7 =
{ .p_ctrl = &g_external_irqLS7_ctrl, .p_cfg = &g_external_irqLS7_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS6) && !defined(SSP_SUPPRESS_ISR_ICU9)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ9);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS6_ctrl;
static const external_irq_cfg_t g_external_irqLS6_cfg =
{ .channel = 9,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS6_callback,
  .p_context = &g_external_irqLS6,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS6 =
{ .p_ctrl = &g_external_irqLS6_ctrl, .p_cfg = &g_external_irqLS6_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS5) && !defined(SSP_SUPPRESS_ISR_ICU8)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ8);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS5_ctrl;
static const external_irq_cfg_t g_external_irqLS5_cfg =
{ .channel = 8,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = false,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS5_callback,
  .p_context = &g_external_irqLS5,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS5 =
{ .p_ctrl = &g_external_irqLS5_ctrl, .p_cfg = &g_external_irqLS5_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS4) && !defined(SSP_SUPPRESS_ISR_ICU3)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ3);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS4_ctrl;
static const external_irq_cfg_t g_external_irqLS4_cfg =
{ .channel = 3,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = false,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS4_callback,
  .p_context = &g_external_irqLS4,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS4 =
{ .p_ctrl = &g_external_irqLS4_ctrl, .p_cfg = &g_external_irqLS4_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS3) && !defined(SSP_SUPPRESS_ISR_ICU2)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ2);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS3_ctrl;
static const external_irq_cfg_t g_external_irqLS3_cfg =
{ .channel = 2,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS3_callback,
  .p_context = &g_external_irqLS3,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS3 =
{ .p_ctrl = &g_external_irqLS3_ctrl, .p_cfg = &g_external_irqLS3_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS2) && !defined(SSP_SUPPRESS_ISR_ICU1)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ1);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS2_ctrl;
static const external_irq_cfg_t g_external_irqLS2_cfg =
{ .channel = 1,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS2_callback,
  .p_context = &g_external_irqLS2,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS2 =
{ .p_ctrl = &g_external_irqLS2_ctrl, .p_cfg = &g_external_irqLS2_cfg, .p_api = &g_external_irq_on_icu };
#if (0) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irqLS1) && !defined(SSP_SUPPRESS_ISR_ICU0)
SSP_VECTOR_DEFINE(icu_irq_isr, ICU, IRQ0);
#endif
#endif
static icu_instance_ctrl_t g_external_irqLS1_ctrl;
static const external_irq_cfg_t g_external_irqLS1_cfg =
{ .channel = 0,
  .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = ext_irqLS1_callback,
  .p_context = &g_external_irqLS1,
  .p_extend = NULL,
  .irq_ipl = (0), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irqLS1 =
{ .p_ctrl = &g_external_irqLS1_ctrl, .p_cfg = &g_external_irqLS1_cfg, .p_api = &g_external_irq_on_icu };
void g_hal_init(void)
{
    g_common_init ();
}
