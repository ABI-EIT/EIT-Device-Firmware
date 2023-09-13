#ifndef AD9833_H
#define AD9833_H

#include  "fsl_gpio.h"
#include  "fsl_port.h"
#include  "fsl_dspi.h"

class AD9833
{
    public:
        struct FrequencyRegisters {
            enum Type {
                FREQ0 = 0,
                FREQ1 = 1,
                _MIN = FREQ0,
                _MAX = FREQ1
            };
        };
        typedef FrequencyRegisters::Type FrequencyRegister;

        struct PhaseRegisters {
            enum Type {
                PHASE0 = 0,
                PHASE1 = 1,
                _MIN = PHASE0,
                _MAX = PHASE1
            };
        };
        typedef PhaseRegisters::Type PhaseRegister;

        struct WriteModes {
            enum Type {
                FullWord = 2,
                HighOnly = 1,
                LowOnly = 0,
                _MIN = LowOnly,
                _MAX = FullWord
            };
        };
        typedef WriteModes::Type WriteMode;

        struct SleepModes {
            enum Type {
                NoPowerDown = 0,
                DACPowerDown = 1,
                InternalClockDisabled = 2,
                DACAndInternalClockDisabled = 3,
                _MIN = NoPowerDown,
                _MAX = DACAndInternalClockDisabled
            };
        };
        typedef SleepModes::Type SleepMode;

        struct OutputModes {
            enum Type {       //  O D M
                Sinusoid = 0, //0b00000,
                Triangle = 1, //0b00001,
                DAC_div2 = 2, //0b10000,
                DAC      = 3, //0b10100,
                _MIN = Sinusoid,
                _MAX = DAC
            };
        };
        typedef OutputModes::Type OutputMode;

        AD9833(SPI_Type *spiBase,
               dspi_ctar_selection_t whichCTAR, dspi_which_pcs_t whichPCS,
               PORT_Type * port_MOSI, uint32_t pin_MOSI, port_mux_t mux_MOSI,
               PORT_Type * port_CLK , uint32_t pin_CLK , port_mux_t mux_CLK ,
               PORT_Type * port_CS  , uint32_t pin_CS  , port_mux_t mux_CS,
               uint32_t iMClockFrequency_hertz = 25000000);

        void init();
        void setFrequency(FrequencyRegister eFrequencyRegister, double dFrequency_hertz);
        void setPhase(PhaseRegister ePhaseRegister, float fPhase_radians);
        void setControl(FrequencyRegister eFrequencySelect = FrequencyRegisters::FREQ0, 
                        PhaseRegister ePhaseSelect = PhaseRegisters::PHASE0,
                        WriteMode eWriteMode = WriteModes::FullWord, 
                        SleepMode eWleepMode = SleepMode::NoPowerDown,
                        OutputMode eOutputMode = OutputModes::Sinusoid,
                        bool bReset = false);
        void setReset();

    private :
        SPI_Type * m_spiBase;
        dspi_ctar_selection_t m_whichCTAR;
        dspi_which_pcs_t m_whichPCS;

        PORT_Type * m_pPort_MOSI;
        PORT_Type * m_pPort_CLK;
        PORT_Type * m_pPort_CS;

        uint32_t m_iPin_MOSI;
        uint32_t m_iPin_CLK;
        uint32_t m_iPin_CS;

        port_mux_t m_mux_MOSI;
        port_mux_t m_mux_CLK;
        port_mux_t m_mux_CS;

        uint32_t m_iMClockFrequency_hertz;
        uint16_t m_sControl;

};

#endif // AD9833_H