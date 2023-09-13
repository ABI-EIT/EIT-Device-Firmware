
void init_clocks()
{
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);

    SMC_SetPowerModeHsrun(SMC);

    CLOCK_SetSimSafeDivs();

    CLOCK_InitOsc0(&oscConfig);

    CLOCK_SetXtal0Freq(16000000U);
    CLOCK_SetXtal32Freq(32768U);

    CLOCK_SetMcgConfig(&mcgConfig);
    
    CLOCK_SetSimConfig(&simConfig);

    CLOCK_EnableUsbfs0Clock(kCLOCK_UsbSrcIrc48M, 48000000);

    SystemCoreClock     = CLOCK_GetCoreSysClkFreq();
    SystemPlatformClock = CLOCK_GetPlatClkFreq();
    SystemBusClock      = CLOCK_GetBusClkFreq();
    SystemUSBClock      = CLOCK_GetPllFllSelClkFreq();

    #ifdef SEMIHOSTING
        printf( "Core Clock Frequency : %ul\n"    , SystemCoreClock     );
        printf( "Platform Clock Frequency : %ul\n", SystemPlatformClock );
        printf( "Bus Clock Frequency : %ul\n"     , SystemBusClock      );
        printf( "USB clock Frequency : %ul\n"     , SystemUSBClock);
    #endif 
}


static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);
void init_edma()
{
    edma_config_t userConfig;
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DMA0, &userConfig);
    EDMA_CreateHandle(&g_hEDMA_Handle, DMA0, ADC_measure_DMA_channel);
    EDMA_SetCallback(&g_hEDMA_Handle, Edma_Callback, NULL);

    NVIC_SET_PRIORITY(IRQ_DMA_CH0 + ADC_measure_DMA_channel, 16);
    
    EDMA_EnableChannelInterrupts(DMA0, ADC_measure_DMA_channel, kEDMA_MajorInterruptEnable);
    EDMA_EnableAsyncRequest(DMA0, ADC_measure_DMA_channel, true);
}

void init_dmamux()
{
    DMAMUX_Init(DMAMUX);
    DMAMUX_SetSource(DMAMUX, ADC_measure_DMA_channel, ADC_measure_DMA_source); 
    DMAMUX_EnableChannel(DMAMUX, ADC_measure_DMA_channel);
}

void init_adc16()
{
    adc16_config_t adcUserConfig;

    adcUserConfig.referenceVoltageSource      = kADC16_ReferenceVoltageSourceVref;  /* VRref In */
    adcUserConfig.clockSource                 = kADC16_ClockSourceAlt1;              /* Bus Clock / 2 */
    adcUserConfig.enableAsynchronousClock     = false;                               /* ASync clock is not used */
    adcUserConfig.clockDivider                = kADC16_ClockDivider4;                /* Bus Clock (90) / 2 / 4 = 11.25MHz  (Must be between 2 and 12) */
    adcUserConfig.resolution                  = kADC16_Resolution16Bit;              /* 16 bit ADC readings */
    adcUserConfig.longSampleMode              = kADC16_LongSampleCycle24;           /*  */
    adcUserConfig.enableHighSpeed             = false;                                /* Regular mode */
    adcUserConfig.enableLowPower              = false;                               /* Regular Power */
    adcUserConfig.enableContinuousConversion  = true;                                /* Single conversions */
    adcUserConfig.hardwareAverageMode         = kADC16_HardwareAverageDisabled;      /* Disable averaging */

    //ADC16_GetDefaultConfig(&adcUserConfig);

    PORT_SetPinMux(PORTC, 2U, kPORT_PinDisabledOrAnalog); 
    
    ADC16_Init(ADC_measure_base, &adcUserConfig);
    //ADC16_SetHardwareAverage(ADC_measure_base, kADC16_HardwareAverageCount32);
    ADC16_DoAutoCalibration(ADC_measure_base);
    //ADC16_SetHardwareAverage(ADC_measure_base, adcUserConfig.hardwareAverageMode);
    ADC16_SetChannelMuxMode(ADC_measure_base, ADC_measure_mux);
    
    ADC16_EnableHardwareTrigger(ADC_measure_base, false);

    __NVIC_SetPriority(ADC0_IRQn, 16); // 0 is highest

    EnableIRQ(ADC0_IRQn);
}

void init_pdb()
{
    pdb_config_t pdbConfigStruct;
    // PDB Clock is Peripheral Clock.
    pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
    pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
    pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
    pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
    pdbConfigStruct.enableContinuousMode = true;
    
    PDB_Init(PDB_base, &pdbConfigStruct);
    //PDB_EnableInterrupts(PDB_base, kPDB_DelayInterruptEnable);
    PDB_SetModulusValue(PDB_base, g_iPDB_mod);
    PDB_SetCounterDelayValue(PDB_base, 0);

    /* Set DAC trigger. */
    pdb_dac_trigger_config_t pdbDacTriggerConfigStruct;
    pdbDacTriggerConfigStruct.enableExternalTriggerInput = false;
    pdbDacTriggerConfigStruct.enableIntervalTrigger      = true;
    PDB_SetDACTriggerConfig(PDB_base, kPDB_DACTriggerChannel0, &pdbDacTriggerConfigStruct);
    PDB_SetDACTriggerIntervalValue(PDB_base, kPDB_DACTriggerChannel0, g_iDAC_trigger_interval);

    /* Set ADC trigger */
    //pdb_adc_pretrigger_config_t pdbAdcPreTriggerConfigStruct;
    //pdbAdcPreTriggerConfigStruct.enablePreTriggerMask          = 1U << ADC_sense_channel;
    //pdbAdcPreTriggerConfigStruct.enableOutputMask              = 1U << ADC_sense_channel;
    //pdbAdcPreTriggerConfigStruct.enableBackToBackOperationMask = 0U;
    //PDB_SetADCPreTriggerConfig(PDB_base, kPDB_ADCTriggerChannel0, &pdbAdcPreTriggerConfigStruct);
    //PDB_SetADCPreTriggerDelayValue(PDB_base, kPDB_ADCTriggerChannel0, kPDB_ADCPreTrigger0, g_iDAC_trigger_interval * 1.5 );

    /* Load PDB values. */
    PDB_DoLoadValues(PDB_base);

    //EnableIRQ(PDB0_IRQn);
}

void init_dac()
{
    uint const length = DACModes::HighRes ? lenof(g_dacValuesHighRes) : lenof(g_dacValuesLowRes);
    uint16_t const * const dacValues = g_eDACMode == DACModes::HighRes ? g_dacValuesHighRes : g_dacValuesLowRes;

    /* Configure the DAC. */
    
    dac_config_t dacConfigStruct;
    DAC_GetDefaultConfig(&dacConfigStruct);
    dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
    dacConfigStruct.enableLowPowerMode     = false;

    dac_buffer_config_t dacBufferConfigStruct;
    DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
    dacBufferConfigStruct.triggerMode = kDAC_BufferTriggerByHardwareMode;
    dacBufferConfigStruct.workMode    = g_eDACMode == DACModes::HighRes ? kDAC_BufferWorkAsSwingMode : kDAC_BufferWorkAsNormalMode;
    // dacBufferConfigStruct.watermark   = g_eDACMode == kDAC_BufferWatermark1Word;
    dacBufferConfigStruct.upperLimit  = length -1;

    //Serial.print("\r\nDAC values : ");Serial.print(length);Serial.print("\r\n");
    
    DAC_Init(DAC_base, &dacConfigStruct);
    DAC_SetBufferConfig(DAC_base, &dacBufferConfigStruct);
    DAC_SetBufferReadPointer(DAC_base, 0U); /* Make sure the read pointer to the start. */
    for (uint i = 0U; i < length; ++i)
    {
        //Serial.print("\t");Serial.print(i);Serial.print(": ");Serial.print(dacValues[i]);Serial.print("\r\n");
        DAC_SetBufferValue(DAC_base, i, dacValues[i]);
    }
    DAC_EnableBuffer(DAC_base, true);
    //DAC_EnableBufferInterrupts(DAC_base, kDAC_BufferWatermarkInterruptEnable);
    
    DAC_Enable(DAC_base, true);             /* Enable output. */
    
    __NVIC_SetPriority(DAC0_IRQn, 16); // 0 is highest

    EnableIRQ(DAC0_IRQn);
}
