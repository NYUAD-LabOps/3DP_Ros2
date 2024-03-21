/* generated thread source file - do not edit */
#include "ProcessManager.h"

TX_THREAD ProcessManager;
void ProcessManager_create(void);
static void ProcessManager_func(ULONG thread_input);
static uint8_t ProcessManager_stack[2048] BSP_PLACE_IN_SECTION_V2(".stack.ProcessManager") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_SEMAPHORE g_cdc_activate_semaphore;
TX_EVENT_FLAGS_GROUP g_usb_plug_events;
TX_EVENT_FLAGS_GROUP g_cdcacm_activate_event_flags0;
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void ProcessManager_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_cdc_activate_semaphore;
    err_g_cdc_activate_semaphore = tx_semaphore_create (&g_cdc_activate_semaphore, (CHAR*) "New Semaphore", 0);
    if (TX_SUCCESS != err_g_cdc_activate_semaphore)
    {
        tx_startup_err_callback (&g_cdc_activate_semaphore, 0);
    }
    UINT err_g_usb_plug_events;
    err_g_usb_plug_events = tx_event_flags_create (&g_usb_plug_events, (CHAR*) "USB Plug Event Flags");
    if (TX_SUCCESS != err_g_usb_plug_events)
    {
        tx_startup_err_callback (&g_usb_plug_events, 0);
    }
    UINT err_g_cdcacm_activate_event_flags0;
    err_g_cdcacm_activate_event_flags0 = tx_event_flags_create (&g_cdcacm_activate_event_flags0,
                                                                (CHAR*) "CDC-ACM Events");
    if (TX_SUCCESS != err_g_cdcacm_activate_event_flags0)
    {
        tx_startup_err_callback (&g_cdcacm_activate_event_flags0, 0);
    }

    UINT err;
    err = tx_thread_create (&ProcessManager, (CHAR*) "ProcessManager", ProcessManager_func, (ULONG) NULL,
                            &ProcessManager_stack, 2048, 12, 12, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&ProcessManager, 0);
    }
}

static void ProcessManager_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    ProcessManager_entry ();
}
