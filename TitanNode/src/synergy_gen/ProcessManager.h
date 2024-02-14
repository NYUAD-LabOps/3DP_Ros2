/* generated thread header file - do not edit */
#ifndef PROCESSMANAGER_H_
#define PROCESSMANAGER_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void ProcessManager_entry(void);
                #else
extern void ProcessManager_entry(void);
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern TX_SEMAPHORE g_cdc_activate_semaphore;
extern TX_EVENT_FLAGS_GROUP g_usb_plug_events;
extern TX_EVENT_FLAGS_GROUP g_cdcacm_activate_event_flags0;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* PROCESSMANAGER_H_ */
