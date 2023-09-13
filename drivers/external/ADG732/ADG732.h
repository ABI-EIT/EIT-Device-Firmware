#ifndef ADG732_H
#define ADG732_H

#include  "fsl_gpio.h"
#include  "fsl_port.h"

class ADG732
{
    public:
        struct Channels 
        {
            enum Type 
            {
                C0   =   0,
                C1   =   1,
                C2   =   2,
                C3   =   3,
                C4   =   4,
                C5   =   5,
                C6   =   6,
                C7   =   7,
                C8   =   8,
                C9   =   9,
                C10  =  10,
                C11  =  11,
                C12  =  12,
                C13  =  13,
                C14  =  14,
                C15  =  15,
                C16  =  16,
                C17  =  17,
                C18  =  18,
                C19  =  19,
                C20  =  20,
                C21  =  21,
                C22  =  22,
                C23  =  23,
                C24  =  24,
                C25  =  25,
                C26  =  26,
                C27  =  27,
                C28  =  28,
                C29  =  29,
                C30  =  30,
                C31  =  31,
                _MIN =  C0,
                _MAX = C31,
            };
        };
        typedef Channels::Type Channel;

        ADG732(PORT_Type* port_a0, GPIO_Type * gpio_a0, uint32_t pin_a0,
               PORT_Type* port_a1, GPIO_Type * gpio_a1, uint32_t pin_a1,
               PORT_Type* port_a2, GPIO_Type * gpio_a2, uint32_t pin_a2,
               PORT_Type* port_a3, GPIO_Type * gpio_a3, uint32_t pin_a3,
               PORT_Type* port_a4, GPIO_Type * gpio_a4, uint32_t pin_a4,
               PORT_Type* port_cs, GPIO_Type * gpio_cs, uint32_t pin_cs,
               PORT_Type* port_wr, GPIO_Type * gpio_wr, uint32_t pin_wr,
               PORT_Type* port_en, GPIO_Type * gpio_en, uint32_t pin_en);
        void init();
        void select(Channel channel);
        void enable(bool enable = true);

    private :
        PORT_Type * m_pPort_a0;
        PORT_Type * m_pPort_a1;
        PORT_Type * m_pPort_a2;
        PORT_Type * m_pPort_a3;
        PORT_Type * m_pPort_a4;
        PORT_Type * m_pPort_cs;
        PORT_Type * m_pPort_wr;
        PORT_Type * m_pPort_en;

        GPIO_Type * m_pGpio_a0;
        GPIO_Type * m_pGpio_a1;
        GPIO_Type * m_pGpio_a2;
        GPIO_Type * m_pGpio_a3;
        GPIO_Type * m_pGpio_a4;
        GPIO_Type * m_pGpio_cs;
        GPIO_Type * m_pGpio_wr;
        GPIO_Type * m_pGpio_en;

        uint32_t m_iPin_a0;
        uint32_t m_iPin_a1;
        uint32_t m_iPin_a2;
        uint32_t m_iPin_a3;
        uint32_t m_iPin_a4;
        uint32_t m_iPin_cs;
        uint32_t m_iPin_wr;
        uint32_t m_iPin_en;

        void _chipSelect(bool chipSelect);
        void _writeEnable(bool chipSelect);
};

#endif // CD74HC4067_H