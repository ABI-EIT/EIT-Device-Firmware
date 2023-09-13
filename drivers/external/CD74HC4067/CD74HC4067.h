#ifndef CD74HC4067_H
#define CD74HC4067_H

#include  "fsl_gpio.h"
#include  "fsl_port.h"

class CD74HC4067
{
    public:
        struct Channels 
        {
            enum Type 
            {
                C0   = 0  ,
                C1   = 1  ,
                C2   = 2  ,
                C3   = 3  ,
                C4   = 4  ,
                C5   = 5  ,
                C6   = 6  ,
                C7   = 7  ,
                C8   = 8  ,
                C9   = 9  ,
                C10  = 10 ,
                C11  = 11 ,
                C12  = 12 ,
                C13  = 13 ,
                C14  = 14 ,
                C15  = 15 ,
                _MIN = C0 ,
                _MAX = C15,
            };
        };
        typedef Channels::Type Channel;

        CD74HC4067(PORT_Type* port_s0, GPIO_Type * gpio_s0, uint32_t pin_s0,
                   PORT_Type* port_s1, GPIO_Type * gpio_s1, uint32_t pin_s1,
                   PORT_Type* port_s2, GPIO_Type * gpio_s2, uint32_t pin_s2,
                   PORT_Type* port_s3, GPIO_Type * gpio_s3, uint32_t pin_s3,
                   PORT_Type* port_e,  GPIO_Type * gpio_e,  uint32_t pin_e);
        void init() ;
        void select(Channel channel);
        void enable(bool enable = true);
    
    private :
        PORT_Type * m_pPort_s0;
        PORT_Type * m_pPort_s1;
        PORT_Type * m_pPort_s2;
        PORT_Type * m_pPort_s3;
        PORT_Type * m_pPort_e;

        GPIO_Type * m_pGpio_s0;
        GPIO_Type * m_pGpio_s1;
        GPIO_Type * m_pGpio_s2;
        GPIO_Type * m_pGpio_s3;
        GPIO_Type * m_pGpio_e;

        uint32_t m_iPin_s0;
        uint32_t m_iPin_s1;
        uint32_t m_iPin_s2;
        uint32_t m_iPin_s3;
        uint32_t m_iPin_e;

};

#endif // CD74HC4067_H