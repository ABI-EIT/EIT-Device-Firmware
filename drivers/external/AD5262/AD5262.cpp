#include "AD5262.h"

AD5262::AD5262(SPI_Type *spiBase,
               dspi_ctar_selection_t whichCTAR, dspi_which_pcs_t whichPCS,
               PORT_Type * port_MOSI, uint32_t pin_MOSI, port_mux_t mux_MOSI,
               PORT_Type * port_CLK , uint32_t pin_CLK , port_mux_t mux_CLK ,
               PORT_Type * port_CS  , uint32_t pin_CS  , port_mux_t mux_CS  ,
               uint32_t maxResistance_ohms) 
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

    m_iMaxResistance_ohms ( maxResistance_ohms )
{

}

void AD5262::init()
{
    dspi_master_config_t masterConfig;

    const uint32_t transferBaudrate = 500000U ; // Max = 25 MHz

    masterConfig.whichCtar                                = m_whichCTAR;
    masterConfig.ctarConfig.baudRate                      = transferBaudrate;
    masterConfig.ctarConfig.bitsPerFrame                  = 9; // Address + Data
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
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
    PORT_SetPinMux(m_pPort_MOSI, m_iPin_MOSI, m_mux_MOSI);
    PORT_SetPinMux(m_pPort_CLK , m_iPin_CLK , m_mux_CLK );
    PORT_SetPinMux(m_pPort_CS  , m_iPin_CS  , m_mux_CS  );
    DSPI_MasterInit(m_spiBase, &masterConfig, srcFreq_hz);

}

void AD5262::setResistance(Channel channel, uint32_t resistance_ohms) 
{
    const uint32_t Rw = 60;
    uint16_t command = ((channel & 1) << 8);
    if ( resistance_ohms > (m_iMaxResistance_ohms + Rw ) )
    {
        resistance_ohms = (m_iMaxResistance_ohms + Rw );
    } 
    else if ( resistance_ohms < Rw) 
    {
        resistance_ohms = Rw;
    }
    
    command |= 0xFF & ( ((resistance_ohms - Rw) * 256) / m_iMaxResistance_ohms );
    //DSPI_MasterWriteCommandDataBlocking(m_spiBase, command);

    dspi_command_data_config_t commandConfig;
    commandConfig.isPcsContinuous    = false;
    commandConfig.whichCtar          = m_whichCTAR;
    commandConfig.whichPcs           = m_whichPCS;
    commandConfig.clearTransferCount = true;
    commandConfig.isEndOfQueue = true;

    DSPI_StopTransfer(m_spiBase);
    DSPI_FlushFifo(m_spiBase, true, true);
    DSPI_ClearStatusFlags(m_spiBase, (uint32_t)kDSPI_AllStatusFlag);
    DSPI_StartTransfer(m_spiBase);
    DSPI_MasterWriteDataBlocking(m_spiBase, &commandConfig, command);
}