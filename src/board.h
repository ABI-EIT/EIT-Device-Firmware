
#include <fsl_clock.h>
#include <fsl_gpio.h>
#include <fsl_port.h>

#include "ADG732.h"
#include "AD5262.h"
#include "AD9833.h"

#define PIN_INFO(_port, _pin) PORT ## _port , GPIO ## _port , _pin


/*******************************************************************************
 * Variables for clock configuration
 ******************************************************************************/
const mcg_config_t mcgConfig =
    {
        .mcgMode = kMCG_ModePEE,     /* PEE - PLL Engaged External */
        .irclkEnableMode = 0  ,      /* MCGIRCLK disabled */
        .ircs = kMCG_IrcSlow,        /* Slow internal reference clock selected */
        .fcrdiv = 0x0U,              /* Fast IRC divider: divided by  1*/
        .frdiv = 0x4U,               /* FLL reference clock divider: divided by 512 */
        .drs = kMCG_DrsLow,          /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default,  /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,    /* Selects System Oscillator (OSCCLK) */
        .pll0Config =
            {
                .enableMode = kMCG_PllEnableIndependent, /* MCGPLLCLK enabled */
                .prdiv = 1U,                             /* PLL Reference divider: divided by 2 */
                .vdiv = 29U,                             /* VCO divider: multiplied by 45 */
            },
        .pllcs = kMCG_PllClkSelPll0,  /* External PLL clock is selected */
    };
const sim_clock_config_t simConfig =
    {
        .pllFllSel = 0U,      /* PLLFLL select: MCGFLLCLK clock */
        .pllFllDiv = 0U,      /* PLLFLLSEL clock divider divisor: divided by 1 */
        .pllFllFrac = 0U,     /* PLLFLLSEL clock divider fraction: multiplied by 1 */
        .er32kSrc = 0U,       /* OSC32KSEL select: OSC32KCLK clock */
        .clkdiv1 =    SIM_CLKDIV1_OUTDIV1(0)  /* Core system div 1*/ 
                    | SIM_CLKDIV1_OUTDIV2(1)  /* Bus clock div 2 */
                    | SIM_CLKDIV1_OUTDIV3(0)  /* Flex bus div 1 */
                    | SIM_CLKDIV1_OUTDIV4(6), /* Flash clock div 7*/
    };
const osc_config_t oscConfig =
    {
        .freq = 16000000UL,                     /* Oscillator frequency: 16Hz */
        .capLoad = ( kOSC_Cap2P | kOSC_Cap8P ), /* Oscillator capacity load: 0pF */
        .workMode = kOSC_ModeOscLowPower,       /* Use external clock */
        .oscerConfig =
            {
                .enableMode = kOSC_ErClkEnable, /* Enable external reference clock */
                .erclkDiv = 0U,                 /* Divider for OSCERCLK: divided by 1*/
            }
    };


/*******************************************************************************
 * Mux configuration
 ******************************************************************************/

ADG732 senseAMux( // IN +
    PIN_INFO(E,26), // A0  = D24 (PTE26)
    PIN_INFO(A, 5), // A1  = D25 (PTA5 )
    PIN_INFO(A,14), // A2  = D26 (PTA14)
    PIN_INFO(A,15), // A3  = D27 (PTA15)
    PIN_INFO(A,16), // A4  = D28 (PTA16)
    PIN_INFO(C, 1), // !CS = D22 (PTC1 )
    PIN_INFO(C, 1), // !WR = D22 (PTC1 )
    PIN_INFO(B,16)  // !EN = D0  (PTB16)
);
ADG732 senseBMux( // IN -
    PIN_INFO(E,26), // A0  = D24 (PTE26)
    PIN_INFO(A, 5), // A1  = D25 (PTA5 )
    PIN_INFO(A,14), // A2  = D26 (PTA14)
    PIN_INFO(A,15), // A3  = D27 (PTA15)
    PIN_INFO(A,16), // A4  = D28 (PTA16)
    PIN_INFO(D, 5), // !CS = D20 (PTD5 )
    PIN_INFO(D, 5), // !WR = D20 (PTD5 )
    PIN_INFO(B,16)  // !EN = D0  (PTB16)
);
ADG732 driveSourceMux( // OUT +
    PIN_INFO(E,26), // A0  = D24 (PTE26)
    PIN_INFO(A, 5), // A1  = D25 (PTA5 )
    PIN_INFO(A,14), // A2  = D26 (PTA14)
    PIN_INFO(A,15), // A3  = D27 (PTA15)
    PIN_INFO(A,16), // A4  = D28 (PTA16)
    PIN_INFO(D, 2), // !CS = D7  (PTD2 )
    PIN_INFO(D, 2), // !WR = D7  (PTD2 )
    PIN_INFO(E,24)  // !EN = D33 (PTE24)
);
ADG732 driveGroundMux( // OUT -
    PIN_INFO(E,26), // A0  = D24 (PTE26)
    PIN_INFO(A, 5), // A1  = D25 (PTA5 )
    PIN_INFO(A,14), // A2  = D26 (PTA14)
    PIN_INFO(A,15), // A3  = D27 (PTA15)
    PIN_INFO(A,16), // A4  = D28 (PTA16)
    PIN_INFO(D, 3), // !CS = D8  (PTD3 )
    PIN_INFO(D, 3), // !WR = D8  (PTD3 )
    PIN_INFO(E,24)  // !EN = D33 (PTE24)
);


/*******************************************************************************
 * Digipots
 ******************************************************************************/

AD5262 howlandShuntResistor(SPI0,
                            kDSPI_Ctar0, kDSPI_Pcs4,
                            PORTC, 6, kPORT_MuxAlt2,
                            PORTD, 1, kPORT_MuxAlt2,
                            PORTC, 0, kPORT_MuxAlt2,
                            50000);

AD5262 inputAmpGainResistor(SPI0,
                            kDSPI_Ctar0, kDSPI_Pcs3,
                            PORTC, 6, kPORT_MuxAlt2,
                            PORTD, 1, kPORT_MuxAlt2,
                            PORTD, 6, kPORT_MuxAlt2,
                            50000);


/*******************************************************************************
 * DDS Waveform Generator
 ******************************************************************************/
AD9833 waveformGenerator(SPI0,
                         kDSPI_Ctar1, kDSPI_Pcs0,
                         PORTC, 6, kPORT_MuxAlt2,
                         PORTD, 1, kPORT_MuxAlt2,
                         PORTC, 4, kPORT_MuxAlt2,
                         25000000);

/*******************************************************************************
 * LED configuration
 ******************************************************************************/

#ifndef BOARD_LED_GPIO
#define BOARD_LED_GPIO GPIOC
#endif
#define BOARD_LED_GPIO_PORT PORTC
#ifndef BOARD_LED_GPIO_PIN
#define BOARD_LED_GPIO_PIN 5U
#endif

gpio_pin_config_t const LED_Config = {kGPIO_DigitalOutput, 1};

#define LED_INIT(output)  \
    PORT_SetPinMux(BOARD_LED_GPIO_PORT, BOARD_LED_GPIO_PIN, kPORT_MuxAsGpio); \
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &LED_Config) /*!< Turn on target LED_RED */
#define BOARD_LED_ON() \
    GPIO_PinWrite(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, 1) /*!< Turn on target LED_RED */
#define BOARD_LED_OFF() \
    GPIO_PinWrite(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, 0) /*!< Turn off target LED_RED */
#define BOARD_LED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GPIO, 0x01 << BOARD_LED_GPIO_PIN) /*!< Toggle on target LED_RED */

#ifndef BOARD_TP_GPIO
#define BOARD_TP_GPIO GPIOB
#endif
#define BOARD_TP_GPIO_PORT PORTB
#ifndef BOARD_TP_GPIO_PIN
#define BOARD_TP_GPIO_PIN 16U
#endif

gpio_pin_config_t const TP_Config = {kGPIO_DigitalOutput, 1};
#define TP_INIT(output)  \
    PORT_SetPinMux(BOARD_TP_GPIO_PORT, BOARD_TP_GPIO_PIN, kPORT_MuxAsGpio); \
    GPIO_PinInit(BOARD_TP_GPIO, BOARD_TP_GPIO_PIN, &TP_Config) /*!< Turn on target TP */
#define BOARD_TP_ON() \
    GPIO_PinWrite(BOARD_TP_GPIO, BOARD_TP_GPIO_PIN, 1) /*!< Turn on target TP */
#define BOARD_TP_OFF() \
    GPIO_PinWrite(BOARD_TP_GPIO, BOARD_TP_GPIO_PIN, 0) /*!< Turn off target TP */
#define BOARD_TP_TOGGLE() \
    GPIO_PortToggle(BOARD_TP_GPIO, 0x01 << BOARD_TP_GPIO_PIN) /*!< Toggle on target TP */

/*******************************************************************************
 * ADC flag configuration
 ******************************************************************************/

#ifndef BOARD_ADCFLG_GPIO
#define BOARD_ADCFLG_GPIO GPIOB
#endif
#define BOARD_ADCFLG_GPIO_PORT PORTB
#ifndef BOARD_ADCFLG_GPIO_PIN
#define BOARD_ADCFLG_GPIO_PIN 17U
#endif

gpio_pin_config_t const ADCFLG_Config = {kGPIO_DigitalOutput, 1};
#define ADCFLG_INIT(output)  \
    PORT_SetPinMux(BOARD_ADCFLG_GPIO_PORT, BOARD_ADCFLG_GPIO_PIN, kPORT_MuxAsGpio); \
    GPIO_PinInit(BOARD_ADCFLG_GPIO, BOARD_ADCFLG_GPIO_PIN, &ADCFLG_Config) /*!< Turn on ADCFLG */
#define BOARD_ADCFLG_ON() \
    GPIO_PinWrite(BOARD_ADCFLG_GPIO, BOARD_ADCFLG_GPIO_PIN, 1) /*!< Turn on ADCFLG */
#define BOARD_ADCFLG_OFF() \
    GPIO_PinWrite(BOARD_ADCFLG_GPIO, BOARD_ADCFLG_GPIO_PIN, 0) /*!< Turn off ADCFLG */
#define BOARD_ADCFLG_TOGGLE() \
    GPIO_PortToggle(BOARD_ADCFLG_GPIO, 0x01 << BOARD_ADCFLG_GPIO_PIN) /*!< Toggle ADCFLG */


/*******************************************************************************
 * Initalise board
 ******************************************************************************/

void init_board()
{ 
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortE);
    LED_INIT(1);
    TP_INIT(1);
    ADCFLG_INIT(1);
}
