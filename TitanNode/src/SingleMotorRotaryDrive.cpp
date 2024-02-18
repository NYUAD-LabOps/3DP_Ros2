/*
 * SingleMotorRotaryDrive.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: Windows
 */

#include <SingleMotorRotaryDrive.h>

SingleMotorRotaryDrive::SingleMotorRotaryDrive()
{

}

SingleMotorRotaryDrive::~SingleMotorRotaryDrive()
{
}


void SingleMotorRotaryDrive::DriveHomingBackoff(void)
{
    ioport_level_t level;
    R_BSP_SoftwareDelay (1, BSP_DELAY_UNITS_MILLISECONDS);
    g_ioport.p_api->pinRead (pinLimit0, &level);
    limit0State = level;
    SetDriveDir(dirFwd);
    //
    // sdasdasd
    //asdasdasd
    // sadasd
    //
    while(limit0State == LIMITACTIVESTATE){
        R_BSP_SoftwareDelay (1, BSP_DELAY_UNITS_MILLISECONDS);
        g_ioport.p_api->pinRead (pinLimit0, &level);
        limit0State = level;
        DriveStepHandler();
//        tx_thread_sleep(10);
    }
}
void SingleMotorRotaryDrive::DriveStartHoming()
{
    ioport_level_t level;
    DriveStop();
    R_BSP_SoftwareDelay (DEBOUNCE_TIME, BSP_DELAY_UNITS_MILLISECONDS);
    g_ioport.p_api->pinRead (pinLimit0, &level);
    limit0State = level;
    if(limit0State == LIMITACTIVESTATE) DriveHomingBackoff();
    SetDriveDir(dirHome);
    SetTimerFrequency(freqHome);
    homing = HOMING_GOTOHOME;
    homed = HOMING_NOT_HOMED;
    TimerStart();
}

void SingleMotorRotaryDrive::DriveMoveGeneric()
{

}

void SingleMotorRotaryDrive::DriveMoveGenericStart(int new_frequency,ioport_level_t new_direction)
{
    SetDriveDir(new_direction);
    SetTimerFrequency(new_frequency);
    move_generic = 1;
    TimerStart();
}
void SingleMotorRotaryDrive::DriveMoveGenericStop()
{
    DriveStop();
    move_generic = 0;
}


void SingleMotorRotaryDrive::DriveHoming()
{
    switch(homing){
        case HOMING_GOTOHOME:
            break;
        case HOMING_BACKINGOFF:
            if(limit0State==LIMITINACTIVESTATE && pos>=posBackOff){
                homing = HOMING_HOMED;
            }
            break;
        case HOMING_BACKOFF:
            DriveStop();
            SetDriveDir(dirFwd);
            SetTimerFrequency(freqHome);
            TimerStart();
            homing = HOMING_BACKINGOFF;
            pos = 0;
            break;
        case HOMING_HOMED:
            DriveStop();
            homing = HOMING_NOT_HOMING;
            homed = HOMING_HOMED;
            break;
    }
}

void SingleMotorRotaryDrive::DriveHandler()
{
    if (homed==HOMING_HOMED && hasLimits)
    {
        if (pos > posSoftLimitForward || pos < posSoftLimitReverse)
        {
            DriveStop();
        }
    }
    if(homing){
        DriveHoming();
        return;
    }
    if(move_generic){
//        DriveMoveGeneric();
        return;
    }
    if(homed==HOMING_NOT_HOMED) return;
    if(move_cycle!=CYCLE_RUN) return;
    while(move_count){
//        move_current = move_list.front();
//        move_list.pop_front();
//        move_count = move_list.size();
        posTarget = move_list[move_current].pos;
        if(pos>posTarget){
            dir = dirHome;
        }else{
            dir = dirFwd;
        }
        SetDriveDir(dir);
        SetTimerFrequency(move_list[move_current].frequency);
        DriveMoveIncrementCurrent();
        while(pos!=posTarget){
            tx_thread_relinquish();
        }
        if(move_count==0){
            DriveStop();
            move_cycle = CYCLE_NONE;
        }
    }


}

void SingleMotorRotaryDrive::SetTimerPointer(timer_instance_t *ptr_gpt_timer)
{
    gpt_timer = ptr_gpt_timer;
}



void SingleMotorRotaryDrive::SetDriveDir(ioport_level_t target_Dir)
{

    dirTarget = target_Dir;
    if(dirTarget==dirFwd){
        posDelta = 1;
    }else{
        posDelta = -1;
    }
    g_ioport.p_api->pinWrite (pinDir, dirTarget);
    dir = dirTarget;
}

void SingleMotorRotaryDrive::DriveStop()
{

    TimerStop ();
    frequency = 0;

}

/**Handles behavior when limit switch is activated*/
void SingleMotorRotaryDrive::LimitHit()
{
    ioport_level_t level;
    R_BSP_SoftwareDelay (DEBOUNCE_TIME, BSP_DELAY_UNITS_MILLISECONDS);
    g_ioport.p_api->pinRead (pinLimit0, &level);
    limit0State = level;

    ///If the limit has been activated, and the motor is not in a homing routine,
    /// stop the motor.
    if (limit0State == LIMITACTIVESTATE && homing == HOMING_NOT_HOMING){
        DriveStop ();
        return;
    }else if(limit0State == LIMITACTIVESTATE && homing==HOMING_GOTOHOME){
        homing = HOMING_BACKOFF;
    }else if(limit0State == LIMITINACTIVESTATE && pos>=posBackOff){
        homing = HOMING_HOMED;
    }
}

///Handles counting steps, stopping the motor when target position is reached, and toggling the STEP pin.
void SingleMotorRotaryDrive::DriveStepHandler()
{
    if (stepState == IOPORT_LEVEL_HIGH)
    {
        stepState = IOPORT_LEVEL_LOW;
    }
    else
    {
        stepState = IOPORT_LEVEL_HIGH;
        pos += posDelta;
    }
    switch(motor_count)
    {
        case 0:
        case 1:
            g_ioport.p_api->pinWrite (pinStep, stepState);
            break;
        case 2:
            g_ioport.p_api->pinWrite (pinStep, stepState);
            g_ioport.p_api->pinWrite (pinStep2, stepState);
            break;
    }
}

void SingleMotorRotaryDrive::SetTimerFrequency(int new_targetFreq)
{
    frequency = new_targetFreq;
    if(frequency<0){
        frequency = 0;
        TimerStop();
    }
    gpt_timer->p_api->periodSet (gpt_timer->p_ctrl, frequency*2, TIMER_UNIT_FREQUENCY_HZ);
    TimerStart();
}

void SingleMotorRotaryDrive::TimerOpen()
{
    gpt_timer->p_api->open(gpt_timer->p_ctrl,gpt_timer->p_cfg);
}

void SingleMotorRotaryDrive::TimerStart()
{
    gpt_timer->p_api->start (gpt_timer->p_ctrl);
}


void SingleMotorRotaryDrive::TimerStop()
{
    gpt_timer->p_api->stop (gpt_timer->p_ctrl);
}


void SingleMotorRotaryDrive::OpenExtIRQ()
{
    ssp_err_t err;
    err = external_irq->p_api->open(external_irq->p_ctrl,external_irq->p_cfg);
    if(err){

    }else{

    }
}

void SingleMotorRotaryDrive::SetIrqInstance(external_irq_instance_t * ptr_external_irq)
{
    external_irq = ptr_external_irq;
}

void SingleMotorRotaryDrive::SetUSBDrive(usbIO* ptr_usb_drive)
{
    usb = ptr_usb_drive;
}

void SingleMotorRotaryDrive::SetDriveUnitIndex(INT drive_unit_index)
{
    drive_index = drive_unit_index;
}

void SingleMotorRotaryDrive::SetupDriveUnit(ULONG block_size,void *block_pool_start,ULONG block_allocation_size)
{
//    void *block_pool_start = NULL;
//    ULONG block_size = sizeof(move)*MAX_MOVE_COUNT;
//    ULONG block_allocation_size = block_size + 4;
    CHAR *memory_ptr = NULL;
    CHAR section[25],key[25];
    UINT mb_status = 0;
    int i;
    sprintf(section,"drive%u_bp",drive_index);

//    block_pool_start = (VOID *) BASE_MEMORY_ADDRESS_MOVES;
    mb_status = tx_block_pool_create(&move_block_pool, section, block_size,block_pool_start , block_allocation_size);
    switch(mb_status){
    case TX_SUCCESS: // (0x00) Successful memory block pool creation.
        printf("MB - success\n");
        break;
    case TX_POOL_ERROR: //  (0x02) Invalid memory block pool pointer. Either the pointer is NULL or the pool is already created.
        printf("MB - Pool Error\n");
        break;
    case TX_PTR_ERROR: // (0x03) Invalid starting address of the pool.
        printf("MB - PTR error\n");
        break;
    case TX_SIZE_ERROR: // (0x05) Size of pool is invalid.
        printf("MB - size error\n");
        break;
    case TX_CALLER_ERROR:  // (0x13) Invalid caller of this service.
        printf("MB - caller error\n");
        break;
    default:
        break;
    }
    mb_status = tx_block_allocate(&move_block_pool, (void **)&memory_ptr, TX_NO_WAIT);
    switch(mb_status){
        case TX_SUCCESS: //  (0x00) Successful memory block allocation.
            move_list = (move *)memory_ptr;
            printf("MB A - success\n");
            break;
        case TX_DELETED: //  (0x01) Memory block pool was deleted while thread was suspended.
            printf("MB A - deleted\n");
            break;
        case TX_NO_MEMORY: //  (0x10) Service was unable to allocate a block of memory within the specified time to wait.
            printf("MB A - no memory\n");
            break;
        case TX_WAIT_ABORTED: //  (0x1A) Suspension was aborted by another thread, timer or ISR.
            printf("MB A - wait aborted\n");
            break;
        case TX_POOL_ERROR: //  (0x02) Invalid memory block pool pointer.
            printf("MB A - pool error\n");
            break;
        case TX_PTR_ERROR: //  (0x03) Invalid pointer to destination pointer.
            printf("MB A - ptr error\n");
            break;
        case TX_WAIT_ERROR: //  (0x04) A wait option other than TX_NO_WAIT was specified on a call from a nonthread.    case TX_SUCCESS: // (0x00) Successful memory block pool creation.
            printf("MB A - Wait error\n");
            break;
        default:
            break;
    }
    for (i = 0; i < MAX_MOVE_COUNT; i++)
    {
        move_list[i].pos = 0;
        move_list[i].frequency = 0;
    }
    homed = HOMING_NOT_HOMED;
    homing = HOMING_NOT_HOMING;
    move_cycle = CYCLE_NONE;
    move_count = 0;
    move_current = 0;
    move_index = 0;
    motor_count = 0;

    sprintf(key,"motorcount");
    motor_count = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;


    sprintf(section,"drive%u",drive_index);
    usb->SetDefaultIniSection(section);
    sprintf(key,"pinStep");
    pinStep = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"pinStep2");
    pinStep2 = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"ls0");
    pinLimit0 = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"ls02");
    pinLimit02 = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"ls1");
    pinLimit1 = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"ls12");
    pinLimit12 = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"hasLimits");
    hasLimits = (ioport_level_t)usb->getIniIValue(NULL,NULL,key);
    referenced = 0;
    sprintf(key,"pinDir");
    pinDir = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    sprintf(key,"pinEnable");
    pinEnable = (ioport_port_pin_t)usb->getIniHextoLongValue(NULL,NULL,key);
    stepState = IOPORT_LEVEL_LOW;
    sprintf(key,"dirFwd");
    dirFwd =  (ioport_level_t)usb->getIniIValue(NULL,NULL,key);  // forward direction logical level
    dir = dirFwd;
    dirTarget = dirFwd;
    sprintf(key,"dirHome");
    dirHome =  (ioport_level_t)usb->getIniIValue(NULL,NULL,key);  // forward direction logical level
    homing = 0;
    sprintf(key,"limitSwitchIndex");
    ls_index = usb->getIniIValue(NULL,NULL,key);
    sprintf(key,"driveTimerIndex");
    drive_timer_index = usb->getIniIValue(NULL,NULL,key);
    g_ioport.p_api->pinWrite (pinDir, dirFwd);
    sprintf(key,"freqBase");
    freqBase = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    sprintf(key,"freqHome");
    freqHome = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    sprintf(key,"homeBackOff");
    posBackOff = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;


    limit0State = LIMITINACTIVESTATE;
    frequency = 0;
    sprintf(key,"mtrEnable");
    mtrEnableState = (ioport_level_t)usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    sprintf(key,"mtrDisable");
    mtrDisableState = (ioport_level_t)usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    init = 1;
    sprintf(key,"posMax");
    posMax = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    sprintf(key,"posSLF");
    posSoftLimitForward = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    sprintf(key,"posSLR");
    posSoftLimitReverse = usb->getIniIValue(NULL,NULL,key);  //HOMEVX;
    SetDriveEnable();
}

void SingleMotorRotaryDrive::SetDriveEnable()
{
    switch(motor_count){
        case 0:
        case 1:
            mtrEnabledStatus = mtrEnableState;
            g_ioport.p_api->pinWrite (pinEnable, mtrEnabledStatus);
            break;
        case 2:
            mtrEnabledStatus = mtrEnableState;
            g_ioport.p_api->pinWrite (pinEnable, mtrEnabledStatus);
            g_ioport.p_api->pinWrite (pinEnable2, mtrEnabledStatus);
            break;
    }
}

void SingleMotorRotaryDrive::DriveStep()
{
    switch(motor_count){
        case 0:
        case 1:
            g_ioport.p_api->pinWrite (pinStep, stepState);
            break;
        case 2:
            g_ioport.p_api->pinWrite (pinStep2, stepState);
            break;
    }
}

void SingleMotorRotaryDrive::DriveMoveAdd(move new_move)
{
    if(move_index==MAX_MOVE_COUNT){
        move_index = 0;
    }
    move_list[move_index] = new_move;
    move_index++;
    move_count++;
}

move SingleMotorRotaryDrive::DriveMoveGetCurrent(void)
{
    return move_list[move_current];
}

void SingleMotorRotaryDrive::DriveMoveIncrementCurrent(void)
{
    move_current++;
    if(move_current==MAX_MOVE_COUNT) move_current = 0;
    move_count--;
    if(move_count==0){
        move_current = 0;
        move_index = 0;
    }
}


void SingleMotorRotaryDrive::DriveCycleFeedHold()
{
    move_cycle = CYCLE_FEED_HOLD;
}
void SingleMotorRotaryDrive::DriveCycleNone()
{
    move_cycle = CYCLE_NONE;
}
void SingleMotorRotaryDrive::DriveCycleStart()
{
    move_cycle = CYCLE_RUN;
}


