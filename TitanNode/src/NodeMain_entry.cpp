#include "NodeMain.h"
#include "NodeMainEntry.h"
#include "usb_io.h"
#include "SingleMotorLinearDrive.h"
#include "ProcessManagerTitan.h"
//extern external_irq_instance_t g_external_irqLS1;
//extern usbIO* usbDrive;
//usbIO* usbDrive = NULL;
extern ProcessManagerTitan* ptr_ProcessManager;

/*
SingleMotorLinearDrive *ptr_drive_handlers[MAX_DRIVES];
SingleMotorLinearDrive *ptr_motor_timers[MAX_MOTOR_TIMERS];
SingleMotorLinearDrive *ptr_limitswitches[MAX_LIMIT_SWITCHES];
*/
//int numberOfDrives = 0;

//char driveHandlerThread[MAX_DRIVES];

void nmi_pin_callback_Node(bsp_grp_irq_t irq)
{
    R_ICU->NMICLR_b.NMICLR = 1;
}

SingleMotorLinearDrive* getDriveHandler(int drive_index)
{
    if(drive_index<0) return NULL;
    if(drive_index>(MAX_DRIVES-1)) return NULL;
    return ptr_ProcessManager->ptr_drive_handlers[drive_index];
}

void NodeMain_entry(void)
{
    void *block_pool_start = NULL;
    ULONG block_size = sizeof(move)*MAX_MOVE_COUNT;
    ULONG block_allocation_size = block_size + 4;
    void (* p_callback_nmi)(bsp_grp_irq_t irq);
//    timer_instance_t *timer_instance;
    SingleMotorLinearDrive *tmp_drive_ptr;
    int i;

    char file_name[25];
    char section[25];
    char key[25];
    char value[50];
    while(ptr_ProcessManager==NULL){
       tx_thread_sleep(10);
    }
    while(ptr_ProcessManager->usbDrive==NULL){
        tx_thread_sleep(10);
    }
    while(ptr_ProcessManager->usbDrive->usb_init!=1){
        tx_thread_sleep(1000);
    }

    for(i=0;i<MAX_DRIVES;i++){
//        driveHandlerThread[i] = 1;
    }
    for(i=0;i<MAX_MOTOR_TIMERS;i++)
    {
//        ptr_ProcessManager->ptr_motor_timers[i] = NULL;

    }
    for(i=0;i<MAX_LIMIT_SWITCHES;i++){
//        ptr_ProcessManager->ptr_limitswitches[i] = NULL;
    }
    memset(file_name,0,25);
    memset(section,0,25);
    memset(key,0,25);
    memset(value,0,50);
    initialise_monitor_handles ();


    p_callback_nmi = nmi_pin_callback_Node;

    R_BSP_GroupIrqWrite(BSP_GRP_IRQ_NMI_PIN, p_callback_nmi);
    R_ICU->NMIER_b.NMIEN = 1;
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS1);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS2);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS3);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS4);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS5);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS6);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS7);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS8);
    genericOpenExtIRQ((external_irq_instance_t *)&g_external_irqLS9);
    sprintf(section,"main");
    sprintf(key,"drive_count");
    ptr_ProcessManager->drive_count = ptr_ProcessManager->usbDrive->getIniIValue(NULL, section, key);
    block_size = sizeof(move)*MAX_MOVE_COUNT;
    block_allocation_size = block_size + 4;
    block_pool_start = (VOID *) BASE_MEMORY_ADDRESS_MOVES;
    for(i=0;i<ptr_ProcessManager->drive_count;i++){
        tmp_drive_ptr = new SingleMotorLinearDrive();
        tmp_drive_ptr->SetUSBDrive(ptr_ProcessManager->usbDrive);
        tmp_drive_ptr->SetDriveUnitIndex(i);
        block_pool_start = (void *)(BASE_MEMORY_ADDRESS_MOVES + block_allocation_size*i);
        tmp_drive_ptr->SetupDriveUnit(block_size,block_pool_start,block_allocation_size);
        tmp_drive_ptr->gpt_timer = get_Gpt_Timer_Index(tmp_drive_ptr->drive_timer_index);
        tmp_drive_ptr->SetTimerFrequency(0);
        tmp_drive_ptr->TimerOpen();
        tmp_drive_ptr->TimerStop();
        ptr_ProcessManager->ptr_drive_handlers[i] = tmp_drive_ptr;
        if(tmp_drive_ptr->ls_index>-1 && tmp_drive_ptr->ls_index<(MAX_LIMIT_SWITCHES-1)){
            ptr_ProcessManager->ptr_limitswitches[tmp_drive_ptr->ls_index] = tmp_drive_ptr;
        }
        if( (tmp_drive_ptr->drive_timer_index>-1) && (tmp_drive_ptr->drive_timer_index<MAX_MOTOR_TIMERS)){
            ptr_ProcessManager->ptr_motor_timers[tmp_drive_ptr->drive_timer_index] = tmp_drive_ptr;
        }
//        driveHandlerThread[i] = 0;
    }
//    numberOfDrives = num_of_drives;
//    g_timer_MTR_01.p_cfg->p_callback = gpt_MTR_02_callback;
//    timer_instance = get_Gpt_Timer_Index(5);
//    genericTimerOpenandStart(timer_instance);

    while (1)
    {
        tx_thread_sleep (1);
    }
}

timer_instance_t *get_Gpt_Timer_Index(INT index)
{
    timer_instance_t *ret_val;
    ret_val = NULL;
    switch(index){
        case TIMER_INDEX_01:
            ret_val = (timer_instance_t *)&g_timer_MTR_01;
            break;
        case TIMER_INDEX_02:
            ret_val = (timer_instance_t *)&g_timer_MTR_02;
            break;
        case TIMER_INDEX_03:
            ret_val = (timer_instance_t *)&g_timer_MTR_03;
            break;
        case TIMER_INDEX_04:
            ret_val = (timer_instance_t *)&g_timer_MTR_04;
            break;
        case TIMER_INDEX_05:
            ret_val = (timer_instance_t *)&g_timer_MTR_05;
            break;
        case TIMER_INDEX_06:
            ret_val = (timer_instance_t *)&g_timer_MTR_06;
            break;
        case TIMER_INDEX_07:
            ret_val = (timer_instance_t *)&g_timer_MTR_07;
            break;
        case TIMER_INDEX_08:
            ret_val = (timer_instance_t *)&g_timer_MTR_08;
            break;
        case TIMER_INDEX_09:
            ret_val = (timer_instance_t *)&g_timer_MTR_09;
            break;
        case TIMER_INDEX_10:
            ret_val = (timer_instance_t *)&g_timer_MTR_10;
            break;
        case TIMER_INDEX_11:
            ret_val = (timer_instance_t *)&g_timer_MTR_11;
            break;
        case TIMER_INDEX_12:
            ret_val = (timer_instance_t *)&g_timer_MTR_12;
            break;
        default:
            ret_val = NULL;
    }
    return ret_val;
}

/*
void genericTimerOpenandStart(timer_instance_t *gpt_timer)
{
    gpt_timer->p_api->open(gpt_timer->p_ctrl,gpt_timer->p_cfg);
    genericTimerStart(gpt_timer);
}

void genericTimerStart(timer_instance_t *gpt_timer)
{
    gpt_timer->p_api->start (gpt_timer->p_ctrl);
}


void genericTimerStop(timer_instance_t *gpt_timer)
{
    gpt_timer->p_api->stop (gpt_timer->p_ctrl);
}
*/

void genericOpenExtIRQ(external_irq_instance_t * external_irq)
{
    ssp_err_t err;
    err = external_irq->p_api->open(external_irq->p_ctrl,external_irq->p_cfg);
    if(err){

    }else{

    }
}


void ext_irqLS1_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_01];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS2_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_02];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS3_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_03];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS4_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_04];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS5_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_05];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS6_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_06];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS7_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_07];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}

void ext_irqLS8_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_08];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}


void ext_irqLS9_callback(external_irq_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_limitswitches[LS_09];
    if(ptr_drive){
        ptr_drive->LimitHit();
    }
}



void gpt_Process_Manager_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_01];
    if(ptr_drive){
        ptr_drive->DriveStepHandler();
    }
}


void gpt_MTR_01_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_01];
    if(ptr_drive){
        ptr_drive->DriveStepHandler();
    }
}

void gpt_MTR_02_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_02];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_03_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_03];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_04_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_04];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_05_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_05];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_06_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_06];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_07_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_07];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_08_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_08];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_09_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_09];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_10_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_10];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_11_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_11];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}

void gpt_MTR_12_callback(timer_callback_args_t *p_args)
{
    SingleMotorLinearDrive *ptr_drive;
    ptr_drive = ptr_ProcessManager->ptr_motor_timers[TIMER_INDEX_12];
    if(ptr_drive){
        ptr_drive->DriveHandler();
    }
}




