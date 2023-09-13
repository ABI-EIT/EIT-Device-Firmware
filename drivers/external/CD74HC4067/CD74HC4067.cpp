#include "CD74HC4067.h"

CD74HC4067::CD74HC4067(PORT_Type* port_s0, GPIO_Type * gpio_s0, uint32_t pin_s0,
                       PORT_Type* port_s1, GPIO_Type * gpio_s1, uint32_t pin_s1,
                       PORT_Type* port_s2, GPIO_Type * gpio_s2, uint32_t pin_s2,
                       PORT_Type* port_s3, GPIO_Type * gpio_s3, uint32_t pin_s3,
                       PORT_Type* port_e,  GPIO_Type * gpio_e,  uint32_t pin_e)
    :
    m_pPort_s0( port_s0 ),
    m_pPort_s1( port_s1 ),
    m_pPort_s2( port_s2 ),
    m_pPort_s3( port_s3 ),
    m_pPort_e ( port_e ),

    m_pGpio_s0( gpio_s0 ),
    m_pGpio_s1( gpio_s1 ),
    m_pGpio_s2( gpio_s2 ),
    m_pGpio_s3( gpio_s3 ),
    m_pGpio_e ( gpio_e  ),

    m_iPin_s0 ( pin_s0  ),
    m_iPin_s1 ( pin_s1  ),
    m_iPin_s2 ( pin_s2  ),
    m_iPin_s3 ( pin_s3  ),
    m_iPin_e  ( pin_e   )
{
    
}

void CD74HC4067::init() 
{
    #if defined(FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    port_pin_config_t port_config =
    {
        #if defined(FSL_FEATURE_PORT_HAS_PULL_ENABLE) && FSL_FEATURE_PORT_HAS_PULL_ENABLE
            .pullSelect = kPORT_PullDisable,
        #endif
        #if defined(FSL_FEATURE_PORT_HAS_SLEW_RATE) && FSL_FEATURE_PORT_HAS_SLEW_RATE
            .slewRate = kPORT_FastSlewRate,
        #endif
        #if defined(FSL_FEATURE_PORT_HAS_PASSIVE_FILTER) && FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
            .passiveFilterEnable = kPORT_PassiveFilterDisable,
        #endif 
        #if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
            .openDrainEnable = kPORT_OpenDrainDisable,
        #endif 
        #if defined(FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH) && FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
            .driveStrength = kPORT_LowDriveStrength,
        #endif
        #if defined(FSL_FEATURE_PORT_PCR_MUX_WIDTH) && (FSL_FEATURE_PORT_PCR_MUX_WIDTH)
            .mux = kPORT_MuxAsGpio,
        #endif
        #if defined(FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK) && FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK
            .lockRegister = kPORT_UnlockRegister,
        #endif /* FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK */
    };
    PORT_SetPinConfig(m_pPort_s0,  m_iPin_s0,  &port_config);
    PORT_SetPinConfig(m_pPort_s1,  m_iPin_s1,  &port_config);
    PORT_SetPinConfig(m_pPort_s2,  m_iPin_s2,  &port_config);
    PORT_SetPinConfig(m_pPort_s3,  m_iPin_s3,  &port_config);
    PORT_SetPinConfig(m_pPort_e ,  m_iPin_e ,  &port_config);

    #endif /* FSL_FEATURE_PORT_PCR_MUX_WIDTH */

    gpio_pin_config_t const gpio_config = 
    {
        .pinDirection = kGPIO_DigitalOutput, 
        .outputLogic = 1,
    };

    GPIO_PinInit(m_pGpio_e,   m_iPin_e ,  &gpio_config);
    enable(false);

    GPIO_PinInit(m_pGpio_s0,  m_iPin_s0,  &gpio_config);
    GPIO_PinInit(m_pGpio_s1,  m_iPin_s1,  &gpio_config);
    GPIO_PinInit(m_pGpio_s2,  m_iPin_s2,  &gpio_config);
    GPIO_PinInit(m_pGpio_s3,  m_iPin_s3,  &gpio_config);

    select(CD74HC4067::Channels::_MIN);
}

void CD74HC4067::select(CD74HC4067::Channel channel)
{

    channel = (Channel) ( ( (unsigned int) channel )  & 0b1111 ) ;

    GPIO_PinWrite(m_pGpio_s0, m_iPin_s0, ( ( channel & (1 << 0) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_s1, m_iPin_s1, ( ( channel & (1 << 1) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_s2, m_iPin_s2, ( ( channel & (1 << 2) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_s3, m_iPin_s3, ( ( channel & (1 << 3) ) ? 1 : 0 ) );

    PORT_SetPinMux(m_pPort_s0, m_iPin_s0, ( ( channel & (1 << 0) ) ? kPORT_MuxAsGpio : kPORT_PinDisabledOrAnalog ) );
    PORT_SetPinMux(m_pPort_s1, m_iPin_s1, ( ( channel & (1 << 1) ) ? kPORT_MuxAsGpio : kPORT_PinDisabledOrAnalog ) );
    PORT_SetPinMux(m_pPort_s2, m_iPin_s2, ( ( channel & (1 << 2) ) ? kPORT_MuxAsGpio : kPORT_PinDisabledOrAnalog ) );
    PORT_SetPinMux(m_pPort_s3, m_iPin_s3, ( ( channel & (1 << 3) ) ? kPORT_MuxAsGpio : kPORT_PinDisabledOrAnalog ) );
}

void CD74HC4067::enable(bool enable)
{
    GPIO_PinWrite(m_pGpio_e, m_iPin_e, enable ? 0 : 1);
    PORT_SetPinMux(m_pPort_e,  m_iPin_e , enable ? kPORT_PinDisabledOrAnalog : kPORT_MuxAsGpio );
}  