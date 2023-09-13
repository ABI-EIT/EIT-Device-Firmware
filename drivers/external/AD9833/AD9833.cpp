#include "AD9833.h"
#include <math.h>

template <typename T>
T bound(T value, T min, T max) 
{
    assert(( max >= value) && ( min <= value));
    if( max < value) return max;
    if( min > value) return min;
    return value;
}

template<typename Enum, typename Type = typename Enum::Type>
Type boundEnum(Type value) {
    return bound<Type>(value, Enum::_MIN, Enum::_MAX);
}

struct Registers {
    enum Type {  
        CONTROL = 0b0000000000000000,
        FREQ0   = 0b0100000000000000,
        FREQ1   = 0b1000000000000000,
        PHASE0  = 0b1100000000000000,
        PHASE1  = 0b1110000000000000,
    };
};
typedef Registers::Type Register;


struct WriteModeValues {
    enum Type {  //  BH____________
        FullWord = 0b10000000000000,
        HighOnly = 0b01000000000000,
        LowOnly  = 0b00000000000000,
    };
};
typedef WriteModeValues::Type WriteModeValue;

struct OutputModeValues {
    enum Type {  //  O_D_M_
        Sinusoid = 0b000000,
        Triangle = 0b000010,
        DAC_div2 = 0b100000,
        DAC      = 0b101000,
    };
};
typedef OutputModeValues::Type OutputModeValue;


struct SleepModeValues {
    enum Type {                     //  12______
        NoPowerDown                 = 0b00000000,
        DACPowerDown                = 0b01000000,
        InternalClockDisabled       = 0b10000000,
        DACAndInternalClockDisabled = 0b11000000,
    };
};
typedef SleepModeValues::Type SleepModeValue;


const Register FrequencyRegisterLUT[] = {
    Registers::FREQ0, // FrequencyRegisters::FREQ0
    Registers::FREQ1, // FrequencyRegisters::FREQ1
};

const Register PhaseRegisterLUT[] = {
    Registers::PHASE0, // PhaseRegisters::PHASE0
    Registers::PHASE1, // PhaseRegisters::PHASE1
};

const WriteModeValue WriteModeLUT[] = {
    WriteModeValues::LowOnly,   // WriteModes::LowOnly
    WriteModeValues::HighOnly,  // WriteModes::HighOnly
    WriteModeValues::FullWord , // WriteModes::FullWord
};

const OutputModeValue OutputModeLUT[] = {
    OutputModeValues::Sinusoid, // OutputModes::Sinusoid
    OutputModeValues::Triangle, // OutputModes::Triangle
    OutputModeValues::DAC_div2, // OutputModes::DAC_div2
    OutputModeValues::DAC     , // OutputModes::DAC     
};

const SleepModeValue SleepModeLUT[] = {
    SleepModeValues::NoPowerDown                , // SleepModes::NoPowerDown                
    SleepModeValues::DACPowerDown               , // SleepModes::DACPowerDown               
    SleepModeValues::InternalClockDisabled      , // SleepModes::InternalClockDisabled      
    SleepModeValues::DACAndInternalClockDisabled, // SleepModes::DACAndInternalClockDisabled
};

AD9833::AD9833(SPI_Type * spiBase,
               dspi_ctar_selection_t whichCTAR, dspi_which_pcs_t whichPCS,
               PORT_Type * port_MOSI, uint32_t pin_MOSI, port_mux_t mux_MOSI,
               PORT_Type * port_CLK , uint32_t pin_CLK , port_mux_t mux_CLK ,
               PORT_Type * port_CS  , uint32_t pin_CS  , port_mux_t mux_CS,
               uint32_t iMClockFrequency_hertz)
               :
    m_spiBase (spiBase),

    m_whichCTAR ( whichCTAR ),
    m_whichPCS  ( whichPCS ),

    m_pPort_MOSI( port_MOSI ),
    m_pPort_CLK ( port_CLK  ),
    m_pPort_CS  ( port_CS   ),

    m_iPin_MOSI ( pin_MOSI  ),
    m_iPin_CLK  ( pin_CLK   ),
    m_iPin_CS   ( pin_CS    ),

    m_mux_MOSI  ( mux_MOSI  ),
    m_mux_CLK   ( mux_CLK   ),
    m_mux_CS    ( mux_CS    ),

    m_iMClockFrequency_hertz ( iMClockFrequency_hertz ),

    m_sControl(WriteModeValues::FullWord | SleepModeValues::NoPowerDown  | OutputModeValues::Sinusoid )
{

}


void write(SPI_Type * spiBase, dspi_ctar_selection_t whichCTAR, dspi_which_pcs_t whichPCS, uint16_t data16)
{
    dspi_command_data_config_t commandConfig;
    commandConfig.isPcsContinuous    = false;
    commandConfig.whichCtar          = whichCTAR;
    commandConfig.whichPcs           = whichPCS;
    commandConfig.clearTransferCount = true;
    commandConfig.isEndOfQueue = true;

    DSPI_StopTransfer(spiBase);
    DSPI_FlushFifo(spiBase, true, true);
    DSPI_ClearStatusFlags(spiBase, (uint32_t)kDSPI_AllStatusFlag);
    DSPI_StartTransfer(spiBase);
    DSPI_MasterWriteDataBlocking(spiBase, &commandConfig, data16);
}

void AD9833::init()
{
    dspi_master_config_t masterConfig;

    const uint32_t transferBaudrate = 500000U ; // Max = 25 MHz

    masterConfig.whichCtar                                = m_whichCTAR;
    masterConfig.ctarConfig.baudRate                      = transferBaudrate;
    masterConfig.ctarConfig.bitsPerFrame                  = 16;
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveLow;
    masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 50;  // datasheet: 5ns ,
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 50;  // datasheet: 0ns ,
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 50;  // datasheet: 20ns

    masterConfig.whichPcs                   = m_whichPCS;
    masterConfig.pcsActiveHighOrLow         = kDSPI_PcsActiveLow;

    masterConfig.enableContinuousSCK        = false;
    masterConfig.enableRxFifoOverWrite      = true;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint                = kDSPI_SckToSin0Clock;
    
    uint32_t srcFreq_hz = CLOCK_GetFreq(BUS_CLK);

    DSPI_MasterInit(m_spiBase, &masterConfig, srcFreq_hz);

    PORT_SetPinMux(m_pPort_MOSI, m_iPin_MOSI, m_mux_MOSI);
    PORT_SetPinMux(m_pPort_CLK , m_iPin_CLK , m_mux_CLK );
    PORT_SetPinMux(m_pPort_CS  , m_iPin_CS  , m_mux_CS  );
}

void AD9833::setFrequency(FrequencyRegister eFrequencyRegister, double dFrequency_hertz)
{
    eFrequencyRegister = boundEnum<FrequencyRegisters>(eFrequencyRegister);
    dFrequency_hertz = bound<double>(dFrequency_hertz, 0, m_iMClockFrequency_hertz/2);

    const Register reg = FrequencyRegisterLUT[(unsigned int) eFrequencyRegister];

    // FREQREG = (fOut * (2^28)) / fMClk
    uint32_t FREQREG = ( ( dFrequency_hertz * 0x10000000 ) / m_iMClockFrequency_hertz );
    FREQREG &= 0xFFFFFFF; // 28 Bits
    
    uint16_t low  = (FREQREG & 0x3FFF); // 14 LSbits
    uint16_t high = ((FREQREG >> 14) & 0x3FFF); // 14 MSbits
    if ((m_sControl & WriteModeValues::LowOnly  ) || (m_sControl & WriteModeValues::FullWord ) ) write(m_spiBase, m_whichCTAR, m_whichPCS, reg | low  );
    if ((m_sControl & WriteModeValues::HighOnly ) || (m_sControl & WriteModeValues::FullWord ) ) write(m_spiBase, m_whichCTAR, m_whichPCS, reg | high );
}

void AD9833::setPhase(PhaseRegister ePhaseRegister, float fPhase_radians)
{
    ePhaseRegister = boundEnum<PhaseRegisters>(ePhaseRegister);
    fPhase_radians = bound<float>(fPhase_radians, 0, 2*M_PI);

    const Register reg = PhaseRegisterLUT[(unsigned int) ePhaseRegister];

    // PHASEREG = (Phase * (2^12) )/ ( 2 * PI )
    uint32_t PHASEREG = ( ( fPhase_radians * (4096) ) / ( 2 * M_PI ) ) ;
    PHASEREG &= 0xFFFFFF; // 24 Bits
    
    uint16_t low  = (PHASEREG & 0xFFF); // 12 LSbits
    uint16_t high = ((PHASEREG >> 12) & 0xFFF); // 12 MSbits
    if ((m_sControl & WriteModeValues::LowOnly  ) || (m_sControl & WriteModeValues::FullWord ) ) write(m_spiBase, m_whichCTAR, m_whichPCS, reg | low  );
    if ((m_sControl & WriteModeValues::HighOnly ) || (m_sControl & WriteModeValues::FullWord ) ) write(m_spiBase, m_whichCTAR, m_whichPCS, reg | high );
}

void AD9833::setControl(FrequencyRegister eFrequencySelect, 
                        PhaseRegister ePhaseSelect,
                        WriteMode eWriteMode, 
                        SleepMode eSleepMode,
                        OutputMode eOutputMode,
                        bool bReset)
{
    eFrequencySelect = boundEnum<FrequencyRegisters>(eFrequencySelect);
    ePhaseSelect = boundEnum<PhaseRegisters>(ePhaseSelect);
    eWriteMode = boundEnum<WriteModes>(eWriteMode);
    eSleepMode = boundEnum<SleepModes>(eSleepMode);
    eOutputMode = boundEnum<OutputModes>(eOutputMode);


    uint16_t control = 0
        | WriteModeLUT[(unsigned int)eWriteMode]
        | ( ( (eFrequencySelect == FrequencyRegisters::FREQ0 ) ? 0 : 1 ) << 11 )
        | ( ( (ePhaseSelect     == PhaseRegisters::PHASE0    ) ? 0 : 1 ) << 10 )
        | ( ( bReset ? 1 : 0) << 8 )
        | SleepModeLUT[(unsigned int)eSleepMode]
        | OutputModeLUT[(unsigned int)eOutputMode];
    
    write(m_spiBase, m_whichCTAR, m_whichPCS, control );
    
    m_sControl = control;
}

void AD9833::setReset()
{
    uint16_t control = ( 1 << 8 ) | ( m_sControl & (~(1 << 8)) );
    write(m_spiBase, m_whichCTAR, m_whichPCS, control );
    m_sControl = control;
}