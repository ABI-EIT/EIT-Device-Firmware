#define lenof(array) ( sizeof(array) / sizeof(array[0]) )

// Non User Configurable Constants
const uint32_t g_iSensingDist = 1; // MUST sit between 1 and g_iElectrodes/2
const uint32_t g_iInitialDriveSenseDist = 1; // MUST sit between 1 and g_iElectrodes/2

// User Configurable Constants

bool g_bRun  = true;

struct Modes {
    enum Type {
        EIT = 0,
        TestFixedOutput = 1,
        TestInputs = 2,
        TestElectrodeInputRawValues = 3,
        TestOutputsToInputs = 4,
        TestEITRaw = 5,
        _COUNT,
        _MIN = 0,
        _MAX = _COUNT - 1,
    };
};
typedef Modes::Type Mode;
Mode g_eMode = Modes::EIT;

struct DACModes {
    enum Type {
        LowRes = 0,
        HighRes = 1,
        _COUNT,
        _MIN = 0,
        _MAX = _COUNT - 1,
    };
};
typedef DACModes::Type DACMode;

DACMode g_eDACMode = DACModes::HighRes;


uint32_t const g_iStartupDelay_ms  = 6000L;

uint32_t const g_iDelay_min_ms = 0;
uint32_t const g_iDelay_max_ms = 10000;
uint32_t g_iDelay_ms   = 1000L;


uint32_t const g_iElectrodes_min = 4;
uint32_t const g_iElectrodes_max = 32;
uint32_t g_iElectrodes = 16;

uint32_t g_iDrivingDist = 3; // Forced to sit between 1 and g_iElectrodes/2


uint32_t const g_iInputGainResistor_min_ohms  = 0;
uint32_t const g_iInputGainResistor_max_ohms  = 50000;
uint32_t g_iInputGainResistor1_ohms           = 1000;
uint32_t g_iInputGainResistor2_ohms           = 50000;

uint32_t const g_iOutputGainResistor_min_ohms = 0;     // TODO : Replace with SAFE value
uint32_t const g_iOutputGainResistor_max_ohms = 50000;
uint32_t g_iOutputGainResistor_ohms           = 6514; // 98.6uA RMS from calibration 2023-06-02

uint32_t const g_iSample_cycles_min     = 1;
uint32_t const g_iSample_cycles_max     = 20;
uint32_t g_iSample_cycles               = 10;

uint32_t const g_iSamples_per_cycle_min = 2;
uint32_t const g_iSamples_per_cycle_max = 20;
uint32_t g_iSamples_per_cycle           = 10;

uint32_t const g_iSample_rubbish_min    = 1;
uint32_t const g_iSample_rubbish_max    = 100;
uint32_t g_iSample_rubbish              = 10; // 10 Samples = 1 cycle at 10 samples per cycle. Should be plenty by inspection with Saleae. This trades off with max achievable frame rate.

bool g_bMapElectrodesToLines  = true;


uint16_t const g_dacValuesLowRes[] = { 2793, 2764, 2683, 2563, 2420, 2278, 2157, 2076, 2048, 2076, 2157, 2278, 2420, 2563, 2683, 2764 };
uint16_t const g_dacValuesHighRes[] = { 2793, 2784, 2760, 2721, 2669, 2606, 2535, 2459, 2381, 2305, 2234, 2171, 2119, 2080, 2056, 2048 };

// dependant variables
// NOTE : it is necessary to adjust these in recalculateGlobals as well.

uint32_t g_iPerip_frequency   = 90000000;
uint32_t g_iADC_frequency     = 249938; // A.C. Measured 2023-05-16
float    g_fADC_frequency     = 249937.5; // A.C. Measured 2023-05-16
uint32_t g_iTarget_frequency  = g_iADC_frequency / g_iSamples_per_cycle;
float    g_fTarget_frequency  = g_fADC_frequency / g_iSamples_per_cycle;
float    g_iTarget_period_us  = ( 1.0 / g_fTarget_frequency ) / 1000000.0;
uint32_t g_iSamples_useful    = g_iSamples_per_cycle * g_iSample_cycles;
uint32_t g_iSamples           = g_iSamples_useful + g_iSample_rubbish;

uint16_t g_iDAC_points           = g_eDACMode == DACModes::HighRes ? lenof(g_dacValuesHighRes)*2 - 2 : lenof(g_dacValuesLowRes);
uint16_t g_iPDB_cycleLength      = g_iPerip_frequency / g_iTarget_frequency;
uint16_t g_iDAC_trigger_interval = g_iPDB_cycleLength / g_iDAC_points ;
uint16_t g_iPDB_mod              = g_iDAC_trigger_interval * g_iDAC_points;



void recalculateGlobals() 
{
    g_iTarget_frequency  = g_iADC_frequency / g_iSamples_per_cycle;
    g_fTarget_frequency  = g_fADC_frequency / g_iSamples_per_cycle;
    g_iTarget_period_us  = ( 1.0 / g_fTarget_frequency ) / 1000000.0;
    g_iSamples_useful    = g_iSamples_per_cycle * g_iSample_cycles;
    g_iSamples           = g_iSamples_useful + g_iSample_rubbish;

    g_iDAC_points = g_eDACMode == DACModes::HighRes ? lenof(g_dacValuesHighRes)*2 - 2 : lenof(g_dacValuesLowRes);

    g_iPDB_cycleLength      = g_iPerip_frequency / g_iTarget_frequency;
    g_iDAC_trigger_interval = g_iPDB_cycleLength / g_iDAC_points ;
    g_iPDB_mod              = g_iDAC_trigger_interval * g_iDAC_points;

    if( g_iDrivingDist > g_iElectrodes/2) g_iDrivingDist = g_iElectrodes/2;
}

// ADC Array

uint32_t const g_iSamples_useful_max = g_iSamples_per_cycle_max * g_iSample_cycles_max;
uint32_t const g_iSamples_max        = g_iSamples_useful_max + g_iSample_rubbish_max;
volatile uint32_t g_aiSamples[g_iSamples_max];


// System 

uint32_t SystemCoreClock = 20971520u;
uint32_t SystemPlatformClock = 0;
uint32_t SystemBusClock = 0;
uint32_t SystemUSBClock = 0;

uint32_t const g_iAdc16_16bitFullRange = 65536U;



adc16_channel_config_t const ADC_sense_config =
{
    .channelNumber                        = 4,      // PTC2, Teensy_A9 or Teensy_23, ADC0_SE4b 
    .enableInterruptOnConversionCompleted = true,
    .enableDifferentialConversion         = false,
};


adc16_channel_config_t const ADC_drive_config =
{
    .channelNumber                        = 12,      // PTB2, Teensy_A5 or Teensy_19, ADC0_SE12 PTB2
    .enableInterruptOnConversionCompleted = false,
    .enableDifferentialConversion         = false,
};

ADC_Type * const               ADC_measure_base         = ADC0;
uint const                     ADC_sense_channel        = ADC_sense_config.channelNumber;
uint const                     ADC_measure_group        = 0;
adc16_channel_mux_mode_t const ADC_measure_mux          = kADC16_ChannelMuxB;
uint const                     ADC_measure_DMA_channel  = 0;
uint const                     ADC_measure_DMA_source   = 40; /*ADC0*/


DAC_Type * const               DAC_base                = DAC0;
PDB_Type * const               PDB_base                = PDB0;


volatile bool g_bWaitForResults = true;
edma_handle_t g_hEDMA_Handle; /* Edma handler. */
edma_transfer_config_t g_sTransferConfig;



char const * getModeLabels(Mode mode)
{
    switch(mode)
    {
        default :
            return "ERROR";
        case Modes::EIT:
            return "EIT";
        case Modes::TestFixedOutput:
            return "Test output with fixed pins";
        case Modes::TestInputs:
            return "Test inputs (EIT)";
        case Modes::TestElectrodeInputRawValues:
            return "Test electrode inputs (raw)";
        case Modes::TestOutputsToInputs:
            return "Test output to input matrix (EIT)";
        case Modes::TestEITRaw:
            return "EIT (raw)";
    }
}

void collect_eit_frame();
void TestFixedOutput();
void TestElectrodeInputRawValues();
void TestInputs();
void TestOutputsToInputs();
void TestEITRaw();


// Mode Functions Look Up Table
//  NB: Order must match Mode enum
void (* g_ModeFunctions [])() = {
    collect_eit_frame,              // Modes::EIT
    TestFixedOutput,                // Modes::TestFixedOutput
    TestElectrodeInputRawValues,    // Modes::TestInputs
    TestInputs,                     // Modes::TestElectrodeInputRawValues
    TestOutputsToInputs,            // Modes::TestOutputsToInputs
    TestEITRaw,                     // Modes::TestEITRaw
};


char const * getDACModeLabel(DACMode mode)
{
    switch(mode)
    {
        default :
            return "ERROR";
        case DACModes::LowRes:
            return "Low resolution (16 Point)";
        case DACModes::HighRes:
            return "High resolution (30 Point)";
    }
}