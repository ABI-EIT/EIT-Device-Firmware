#include "ADG732.h"

ADG732::ADG732(PORT_Type* port_a0, GPIO_Type * gpio_a0, uint32_t pin_a0,
               PORT_Type* port_a1, GPIO_Type * gpio_a1, uint32_t pin_a1,
               PORT_Type* port_a2, GPIO_Type * gpio_a2, uint32_t pin_a2,
               PORT_Type* port_a3, GPIO_Type * gpio_a3, uint32_t pin_a3,
               PORT_Type* port_a4, GPIO_Type * gpio_a4, uint32_t pin_a4,
               PORT_Type* port_cs, GPIO_Type * gpio_cs, uint32_t pin_cs,
               PORT_Type* port_wr, GPIO_Type * gpio_wr, uint32_t pin_wr,
               PORT_Type* port_en, GPIO_Type * gpio_en, uint32_t pin_en)
    :
    m_pPort_a0( port_a0 ),
    m_pPort_a1( port_a1 ),
    m_pPort_a2( port_a2 ),
    m_pPort_a3( port_a3 ),
    m_pPort_a4( port_a4 ),
    m_pPort_cs( port_cs ),
    m_pPort_wr( port_wr ),
    m_pPort_en( port_en ),

    m_pGpio_a0( gpio_a0 ),
    m_pGpio_a1( gpio_a1 ),
    m_pGpio_a2( gpio_a2 ),
    m_pGpio_a3( gpio_a3 ),
    m_pGpio_a4( gpio_a4 ),
    m_pGpio_cs( gpio_cs ),
    m_pGpio_wr( gpio_wr ),
    m_pGpio_en( gpio_en ),

    m_iPin_a0 ( pin_a0  ),
    m_iPin_a1 ( pin_a1  ),
    m_iPin_a2 ( pin_a2  ),
    m_iPin_a3 ( pin_a3  ),
    m_iPin_a4 ( pin_a4  ),
    m_iPin_cs ( pin_cs  ),
    m_iPin_wr ( pin_wr  ),
    m_iPin_en ( pin_en  )
{
    
}

void ADG732::init() 
{
    #if defined(FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    port_pin_config_t port_config =
    {
        #if defined(FSL_FEATURE_PORT_HAS_PULL_enNABLE) && FSL_FEATURE_PORT_HAS_PULL_enNABLE
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
    PORT_SetPinConfig(m_pPort_a0,  m_iPin_a0,  &port_config);
    PORT_SetPinConfig(m_pPort_a1,  m_iPin_a1,  &port_config);
    PORT_SetPinConfig(m_pPort_a2,  m_iPin_a2,  &port_config);
    PORT_SetPinConfig(m_pPort_a3,  m_iPin_a3,  &port_config);
    PORT_SetPinConfig(m_pPort_a4,  m_iPin_a4,  &port_config);
    PORT_SetPinConfig(m_pPort_cs,  m_iPin_cs,  &port_config);
    PORT_SetPinConfig(m_pPort_wr,  m_iPin_wr,  &port_config);
    PORT_SetPinConfig(m_pPort_en , m_iPin_en , &port_config);

    #endif /* FSL_FEATURE_PORT_PCR_MUX_WIDTH */

    gpio_pin_config_t const gpio_config = 
    {
        .pinDirection = kGPIO_DigitalOutput, 
        .outputLogic = 1,
    };

    GPIO_PinInit(m_pGpio_en,  m_iPin_en,  &gpio_config);
    enable(false);
    GPIO_PinInit(m_pGpio_cs,  m_iPin_cs,  &gpio_config);
    _chipSelect(false);
    GPIO_PinInit(m_pGpio_wr,  m_iPin_wr,  &gpio_config);
    _writeEnable(false);

    GPIO_PinInit(m_pGpio_a0,  m_iPin_a0,  &gpio_config);
    GPIO_PinInit(m_pGpio_a1,  m_iPin_a1,  &gpio_config);
    GPIO_PinInit(m_pGpio_a2,  m_iPin_a2,  &gpio_config);
    GPIO_PinInit(m_pGpio_a3,  m_iPin_a3,  &gpio_config);
    GPIO_PinInit(m_pGpio_a4,  m_iPin_a4,  &gpio_config);

    select(ADG732::Channels::_MIN);
}

void ADG732::select(ADG732::Channel channel)
{
    channel = (Channel) ( ( (unsigned int) channel )  & 0b11111 ) ;

    _chipSelect(true);
    _writeEnable(true);
    GPIO_PinWrite(m_pGpio_a0, m_iPin_a0, ( ( channel & (1 << 0) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_a1, m_iPin_a1, ( ( channel & (1 << 1) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_a2, m_iPin_a2, ( ( channel & (1 << 2) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_a3, m_iPin_a3, ( ( channel & (1 << 3) ) ? 1 : 0 ) );
    GPIO_PinWrite(m_pGpio_a4, m_iPin_a4, ( ( channel & (1 << 4) ) ? 1 : 0 ) );
    _writeEnable(false);
    _chipSelect(false);
}

void ADG732::enable(bool enable)
{
    GPIO_PinWrite(m_pGpio_en, m_iPin_en, enable ? 0 : 1);
}

void ADG732::_chipSelect(bool chipSelect)
{
    GPIO_PinWrite(m_pGpio_cs, m_iPin_cs, chipSelect ? 0 : 1);
}

void ADG732::_writeEnable(bool writeEnable)
{
    GPIO_PinWrite(m_pGpio_wr, m_iPin_wr, writeEnable ? 0 : 1);
}