char const logo[] = "\r\n\
#            █████╗ ██████╗ ██╗    ███████╗██╗████████╗\r\n\
#           ██╔══██╗██╔══██╗██║    ██╔════╝██║╚══██╔══╝\r\n\
#           ███████║██████╔╝██║    █████╗  ██║   ██║   \r\n\
#           ██╔══██║██╔══██╗██║    ██╔══╝  ██║   ██║   \r\n\
#           ██║  ██║██████╔╝██║    ███████╗██║   ██║   \r\n\
#           ╚═╝  ╚═╝╚═════╝ ╚═╝    ╚══════╝╚═╝   ╚═╝   \r\n\
#                                           \r\n\
#     ____________ ____ ________\r\n\
#      ___/  ____/__/ /_/_  ___/           __   ____ _ _ \r\n\
#      __/  __/  __/ / __/ /         __ __/  \\ |__ /| | | \r\n\
#      _/  /___  _/ /  _/ /          \\ V / () | |_ \\|_  _|\r\n\
#      /______/  /_/   /_/            \\_/ \\__(_)___(_)|_| \r\n\
";



// Font Generators :
//   Logo : https://patorjk.com/software/taag/#p=display&f=ANSI%20Shadow&t=ABI%20EIT
//   Version : https://patorjk.com/software/taag/#p=display&f=Small&t=v0.3.4
              

#include "Arduino.h"
#include <fsl_clock.h>
#include <fsl_gpio.h>
#include <fsl_port.h>
#include <fsl_smc.h>
#include <fsl_adc16.h>
#include <fsl_dmamux.h>
#include <fsl_edma.h>
#include <fsl_pdb.h>
#include <fsl_dac.h>

#ifdef SEMIHOSTING
#include <stdio.h>
extern "C" void initialise_monitor_handles(void);
#endif


#define DEVICE_NAME "ABI EIT" 
#define HARDWARE_VERSION "1.0" 
#define FIRMWARE_VERSION "0.3.4" 

#include "board.h"
#include "globals.h"
#include "setup.h"
#include "eit.h"
#include "tests.h"

void recalulatePeripherals();

#include "commands.h"

void setup();

extern "C" int main() 
{
    #ifdef SEMIHOSTING
  	    initialise_monitor_handles();
    #endif

    // Initialise Hardware
    setup();
    recalculateGlobals();
    recalulatePeripherals();

    // Wait to connect with the PC
    for(; !Serial ;) ; // TODO : Breathe LED here

    // NB any text printed to the serial should be escaped with a leading #
    // this is to not confuse any application that ..

    SL(); // Print empty comment line
    for(auto c : logo) {Serial.print(c);} // Print the logo character by character.. (wHY loop?)
    deviceInfo(); // Print device information (using the device information command)
    SDK_DelayAtLeastUs(g_iStartupDelay_ms * 1000, SystemCoreClock); // Give the user time (g_iStartupDelay_ms) to see the logo
    
    // Main Loop
    for (;;)
    {
        #ifdef ARDUINO
            yield(); // For Multitasking arduino libraries including usb serial
        #endif

        // Execute current task (depending on the configured mode)
        BOARD_LED_ON();
        if (g_bRun) { // Is there an active task
            g_ModeFunctions[g_eMode](); // Run the desired task
        }
        BOARD_LED_OFF();

        // Wait between task executions (g_iDelay_ms)
        SDK_DelayAtLeastUs(g_iDelay_ms * 1000, SystemCoreClock); // TODO: use the system tick counter to be hard real time
        
        // Check if we have recieved any commands via the serial port and act on them
        processCommands();
    }

    return 0;
}

void setup()
{
    Serial.begin(500000); // Does nothing over USB.
    Serial.setTimeout(1000); // sets the maximum number of milliseconds to wait for an input

    init_clocks();
    // init_systick();
    init_board();

    // Setup ADC with DMA
    init_edma();
    init_dmamux();
    init_adc16();

    // Setup PDB triggered DAC
    init_pdb();
    init_dac();
    
    // Initalise the Muxes
    driveSourceMux.init();
    driveGroundMux.init();
    senseAMux.init();
    senseBMux.init();

    // Initalise the digipots
    inputAmpGainResistor.init();
    inputAmpGainResistor.setResistance(AD5262::Channels::RDAC1, g_iInputGainResistor1_ohms);
    inputAmpGainResistor.setResistance(AD5262::Channels::RDAC2, g_iInputGainResistor2_ohms);

    howlandShuntResistor.init();
    howlandShuntResistor.setResistance(AD5262::Channels::RDAC1, g_iOutputGainResistor_ohms);

    // Initalise the Waveform Generator
    waveformGenerator.init();
    waveformGenerator.setReset();
    waveformGenerator.setFrequency(AD9833::FrequencyRegisters::FREQ0, g_fTarget_frequency);
    waveformGenerator.setPhase(AD9833::PhaseRegisters::PHASE0, 0);
    waveformGenerator.setControl();

    // Start DAC
    DAC_SetBufferReadPointer(DAC_base, 0U);
    PDB_DoSoftwareTrigger(PDB_base);
}


#ifdef ARDUINO
extern "C" void DMA0_DMA16_DriverIRQHandler(void);
extern "C" void  __attribute__((interrupt("IRQ"))) dma_ch0_isr(void)
{
    DMA0_DMA16_DriverIRQHandler();
}
#endif

static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    /* Clear Edma interrupt flag. */
    ADC16_EnableDMA(ADC_measure_base, false);
    EDMA_ClearChannelStatusFlags(DMA0, ADC_measure_DMA_channel, kEDMA_InterruptFlag);
    //ADC16_EnableHardwareTrigger(ADC_measure_base, false);
    //PDB_ClearADCPreTriggerStatusFlags(PDB_base,kPDB_ADCTriggerChannel0, kPDB_ADCPreTriggerChannel0ErrorFlag |kPDB_ADCPreTriggerChannel0Flag);
    g_bWaitForResults = false;
}

// Interrupt handlers. The driver library (MCUXpresso) registers these by their names.
#ifdef ARDUINO
void dac0_isr(void)		__attribute__ ((alias("DAC0_IRQHandler")));
#endif
extern "C" void __attribute__((interrupt("IRQ"))) DAC0_IRQHandler() 
{
    // Trigger the ADC
    ADC16_SetChannelConfig(ADC_measure_base, ADC_measure_group, &ADC_sense_config);
    DAC_ClearBufferStatusFlags(DAC_base, DAC_GetBufferStatusFlags(DAC_base));
    DAC_DisableBufferInterrupts(DAC_base, kDAC_BufferWatermarkInterruptEnable);
    SDK_ISR_EXIT_BARRIER;
}
#ifdef ARDUINO
void adc0_isr(void)		__attribute__ ((alias("ADC0_IRQHandler")));
#endif
extern "C" void __attribute__((interrupt("IRQ"))) ADC0_IRQHandler() 
{
    // This is used to measure the ADC sample time
    BOARD_ADCFLG_TOGGLE();    
}

void adc_collect_samples(uint32_t * sample_array, uint8_t samples)
{
    g_bWaitForResults = true;
        /* Setup transfer */
    EDMA_PrepareTransfer(&g_sTransferConfig, (void *) & (ADC_measure_base->R[0]), sizeof(ADC_measure_base->R[0]),
                         (void *)sample_array, sizeof(sample_array[0]), sizeof(ADC_measure_base->R[0]),
                         samples * sizeof(sample_array[0]), kEDMA_PeripheralToMemory);
    //EDMA_SubmitTransfer(&g_hEDMA_Handle, &g_sTransferConfig);
    
    EDMA_SetTransferConfig(DMA0, ADC_measure_DMA_channel, &g_sTransferConfig, NULL);
    /* Enable transfer. */
    
    EDMA_StartTransfer(&g_hEDMA_Handle);
    ADC16_EnableDMA(ADC_measure_base, true);
    //ADC16_SetChannelConfig(ADC_measure_base, ADC_measure_group, &ADC_sense_config);
    DAC_ClearBufferStatusFlags(DAC_base, DAC_GetBufferStatusFlags(DAC_base));
    DAC_EnableBufferInterrupts(DAC_base, kDAC_BufferWatermarkInterruptEnable);

    // The ADC read is started by the DAC watermark interrupt, this keeps the ADC read synchronized with the DAC
    // g_bWaitForResults is cleared when the DMA ADC read is complete
    for (;g_bWaitForResults;) __NOP(); 
}


void recalulatePeripherals()
{
    // set the digibots
    inputAmpGainResistor.init();
    inputAmpGainResistor.setResistance(AD5262::Channels::RDAC1, g_iInputGainResistor1_ohms);
    inputAmpGainResistor.setResistance(AD5262::Channels::RDAC2, g_iInputGainResistor2_ohms);

    howlandShuntResistor.init();
    howlandShuntResistor.setResistance(AD5262::Channels::RDAC1, g_iOutputGainResistor_ohms);

    // Initalise the Waveform Generator
    waveformGenerator.init();
    waveformGenerator.setFrequency(AD9833::FrequencyRegisters::FREQ0, g_fTarget_frequency);

    // Set the DAC frequency
    init_dac();
    init_pdb();
}