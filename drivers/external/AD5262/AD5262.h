#ifndef AD5262_H
#define AD5262_H

#include  "fsl_gpio.h"
#include  "fsl_port.h"
#include  "fsl_dspi.h"

class AD5262
{
    public:
        struct Channels {
            enum Type {
                RDAC1 = 0,
                RDAC2 = 1,
                _MIN = RDAC1,
                _MAX = RDAC2
            };
        };
        typedef Channels::Type Channel;

        AD5262(SPI_Type *spiBase,
               dspi_ctar_selection_t whichCTAR, dspi_which_pcs_t whichPCS,
               PORT_Type * port_MOSI, uint32_t pin_MOSI, port_mux_t mux_MOSI,
               PORT_Type * port_CLK , uint32_t pin_CLK , port_mux_t mux_CLK ,
               PORT_Type * port_CS  , uint32_t pin_CS  , port_mux_t mux_CS  ,
               uint32_t maxResistance_ohms);
        void init();
        void setResistance(Channel channel, uint32_t resistance_ohms);

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

        uint32_t m_iMaxResistance_ohms;

};

#endif // AD5262_H