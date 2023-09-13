//*****************************************************************************
// MK66F18 startup code for use with MCUXpresso IDE
//
// Version : 160420
//*****************************************************************************
//
// Copyright 2016-2020 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
// The BSD 3 Clause License
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//*****************************************************************************


#pragma GCC push_options
#pragma GCC optimize ("Og")



#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define AV __attribute__ ((section(".after_vectors")))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
// Flash Configuration block : 16-byte flash configuration field that stores
// default protection settings (loaded on reset) and security information that
// allows the MCU to restrict access to the Flash Memory module.
// Placed at address 0x400 by the linker script.
//*****************************************************************************
//__attribute__ ((used,section(".FlashConfig"))) const struct {
//    unsigned int word1;
//    unsigned int word2;
//    unsigned int word3;
//    unsigned int word4;
//} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE};

// Flash Security Setting. On Teensy 3.2, you can lock the MK20 chip to prevent
// anyone from reading your code.  You CAN still reprogram your Teensy while
// security is set, but the bootloader will be unable to respond to auto-reboot
// requests from Arduino. Pressing the program button will cause a full chip
// erase to gain access, because the bootloader chip is locked out.  Normally,
// erase occurs when uploading begins, so if you press the Program button
// accidentally, simply power cycling will run your program again.  When
// security is locked, any Program button press causes immediate full erase.
// Special care must be used with the Program button, because it must be made
// accessible to initiate reprogramming, but it must not be accidentally
// pressed when Teensy Loader is not being used to reprogram.  To set lock the
// security change this to 0xDC.  Teensy 3.0 and 3.1 do not support security lock.
#define FSEC 0xDE

// Flash Options
#define FOPT 0xF9

__attribute__ ((section(".flashconfig"), used))
const unsigned char flashconfigbytes[16] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, FSEC, FOPT, 0xFF, 0xFF
};

//*****************************************************************************
// Declaration of external SystemInit function
//*****************************************************************************
#if defined (__USE_CMSIS)
extern void SystemInit(void);
#endif // (__USE_CMSIS)

//*****************************************************************************
// Forward declaration of the core exception handlers.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions.
// If your application is a C++ one, then any interrupt handlers defined
// in C++ files within in your main application will need to have C linkage
// rather than C++ linkage. To do this, make sure that you are using extern "C"
// { .... } around the interrupt handler within your main application code.
//*****************************************************************************
     void ResetISR(void);
AV void NMI_Handler(void);
AV void HardFault_Handler(void);
AV void MemManage_Handler(void);
AV void BusFault_Handler(void);
AV void UsageFault_Handler(void);
AV void SVC_Handler(void);
AV void DebugMon_Handler(void);
AV void PendSV_Handler(void);
AV void SysTick_Handler(void);
AV void IntDefaultHandler(void);
//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
extern void DMA0_DMA16_IRQHandler(void);
extern void DMA1_DMA17_IRQHandler(void);
extern void DMA2_DMA18_IRQHandler(void);
extern void DMA3_DMA19_IRQHandler(void);
extern void DMA4_DMA20_IRQHandler(void);
extern void DMA5_DMA21_IRQHandler(void);
extern void DMA6_DMA22_IRQHandler(void);
extern void DMA7_DMA23_IRQHandler(void);
extern void DMA8_DMA24_IRQHandler(void);
extern void DMA9_DMA25_IRQHandler(void);
extern void DMA10_DMA26_IRQHandler(void);
extern void DMA11_DMA27_IRQHandler(void);
extern void DMA12_DMA28_IRQHandler(void);
extern void DMA13_DMA29_IRQHandler(void);
extern void DMA14_DMA30_IRQHandler(void);
extern void DMA15_DMA31_IRQHandler(void);
extern void DMA_Error_IRQHandler(void);
extern void MCM_IRQHandler(void);
extern void FTFE_IRQHandler(void);
extern void Read_Collision_IRQHandler(void);
extern void LVD_LVW_IRQHandler(void);
extern void LLWU_IRQHandler(void);
extern void WDOG_EWM_IRQHandler(void);
extern void RNG_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void SPI0_IRQHandler(void);
extern void SPI1_IRQHandler(void);
extern void I2S0_Tx_IRQHandler(void);
extern void I2S0_Rx_IRQHandler(void);
extern void Reserved46_IRQHandler(void);
extern void UART0_RX_TX_IRQHandler(void);
extern void UART0_ERR_IRQHandler(void);
extern void UART1_RX_TX_IRQHandler(void);
extern void UART1_ERR_IRQHandler(void);
extern void UART2_RX_TX_IRQHandler(void);
extern void UART2_ERR_IRQHandler(void);
extern void UART3_RX_TX_IRQHandler(void);
extern void UART3_ERR_IRQHandler(void);
extern void ADC0_IRQHandler(void);
extern void CMP0_IRQHandler(void);
extern void CMP1_IRQHandler(void);
extern void FTM0_IRQHandler(void);
extern void FTM1_IRQHandler(void);
extern void FTM2_IRQHandler(void);
extern void CMT_IRQHandler(void);
extern void RTC_IRQHandler(void);
extern void RTC_Seconds_IRQHandler(void);
extern void PIT0_IRQHandler(void);
extern void PIT1_IRQHandler(void);
extern void PIT2_IRQHandler(void);
extern void PIT3_IRQHandler(void);
extern void PDB0_IRQHandler(void);
extern void USB0_IRQHandler(void);
extern void USBDCD_IRQHandler(void);
extern void Reserved71_IRQHandler(void);
extern void DAC0_IRQHandler(void);
extern void MCG_IRQHandler(void);
extern void LPTMR0_IRQHandler(void);
extern void PORTA_IRQHandler(void);
extern void PORTB_IRQHandler(void);
extern void PORTC_IRQHandler(void);
extern void PORTD_IRQHandler(void);
extern void PORTE_IRQHandler(void);
extern void SWI_IRQHandler(void);
extern void SPI2_IRQHandler(void);
extern void UART4_RX_TX_IRQHandler(void);
extern void UART4_ERR_IRQHandler(void);
extern void Reserved84_IRQHandler(void);
extern void Reserved85_IRQHandler(void);
extern void CMP2_IRQHandler(void);
extern void FTM3_IRQHandler(void);
extern void DAC1_IRQHandler(void);
extern void ADC1_IRQHandler(void);
extern void I2C2_IRQHandler(void);
extern void CAN0_ORed_Message_buffer_IRQHandler(void);
extern void CAN0_Bus_Off_IRQHandler(void);
extern void CAN0_Error_IRQHandler(void);
extern void CAN0_Tx_Warning_IRQHandler(void);
extern void CAN0_Rx_Warning_IRQHandler(void);
extern void CAN0_Wake_Up_IRQHandler(void);
extern void SDHC_IRQHandler(void);
extern void ENET_1588_Timer_IRQHandler(void);
extern void ENET_Transmit_IRQHandler(void);
extern void ENET_Receive_IRQHandler(void);
extern void ENET_Error_IRQHandler(void);
extern void LPUART0_IRQHandler(void);
extern void TSI0_IRQHandler(void);
extern void TPM1_IRQHandler(void);
extern void TPM2_IRQHandler(void);
extern void USBHSDCD_IRQHandler(void);
extern void I2C3_IRQHandler(void);
extern void CMP3_IRQHandler(void);
extern void USBHS_IRQHandler(void);
extern void CAN1_ORed_Message_buffer_IRQHandler(void);
extern void CAN1_Bus_Off_IRQHandler(void);
extern void CAN1_Error_IRQHandler(void);
extern void CAN1_Tx_Warning_IRQHandler(void);
extern void CAN1_Rx_Warning_IRQHandler(void);
extern void CAN1_Wake_Up_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
extern void DMA0_DMA16_DriverIRQHandler(void);
extern void DMA1_DMA17_DriverIRQHandler(void);
extern void DMA2_DMA18_DriverIRQHandler(void);
extern void DMA3_DMA19_DriverIRQHandler(void);
extern void DMA4_DMA20_DriverIRQHandler(void);
extern void DMA5_DMA21_DriverIRQHandler(void);
extern void DMA6_DMA22_DriverIRQHandler(void);
extern void DMA7_DMA23_DriverIRQHandler(void);
extern void DMA8_DMA24_DriverIRQHandler(void);
extern void DMA9_DMA25_DriverIRQHandler(void);
extern void DMA10_DMA26_DriverIRQHandler(void);
extern void DMA11_DMA27_DriverIRQHandler(void);
extern void DMA12_DMA28_DriverIRQHandler(void);
extern void DMA13_DMA29_DriverIRQHandler(void);
extern void DMA14_DMA30_DriverIRQHandler(void);
extern void DMA15_DMA31_DriverIRQHandler(void);
extern void DMA_Error_DriverIRQHandler(void);
extern void MCM_DriverIRQHandler(void);
extern void FTFE_DriverIRQHandler(void);
extern void Read_Collision_DriverIRQHandler(void);
extern void LVD_LVW_DriverIRQHandler(void);
extern void LLWU_DriverIRQHandler(void);
extern void WDOG_EWM_DriverIRQHandler(void);
extern void RNG_DriverIRQHandler(void);
extern void I2C0_DriverIRQHandler(void);
extern void I2C1_DriverIRQHandler(void);
extern void SPI0_DriverIRQHandler(void);
extern void SPI1_DriverIRQHandler(void);
extern void I2S0_Tx_DriverIRQHandler(void);
extern void I2S0_Rx_DriverIRQHandler(void);
extern void Reserved46_DriverIRQHandler(void);
extern void UART0_RX_TX_DriverIRQHandler(void);
extern void UART0_ERR_DriverIRQHandler(void);
extern void UART1_RX_TX_DriverIRQHandler(void);
extern void UART1_ERR_DriverIRQHandler(void);
extern void UART2_RX_TX_DriverIRQHandler(void);
extern void UART2_ERR_DriverIRQHandler(void);
extern void UART3_RX_TX_DriverIRQHandler(void);
extern void UART3_ERR_DriverIRQHandler(void);
extern void ADC0_DriverIRQHandler(void);
extern void CMP0_DriverIRQHandler(void);
extern void CMP1_DriverIRQHandler(void);
extern void FTM0_DriverIRQHandler(void);
extern void FTM1_DriverIRQHandler(void);
extern void FTM2_DriverIRQHandler(void);
extern void CMT_DriverIRQHandler(void);
extern void RTC_DriverIRQHandler(void);
extern void RTC_Seconds_DriverIRQHandler(void);
extern void PIT0_DriverIRQHandler(void);
extern void PIT1_DriverIRQHandler(void);
extern void PIT2_DriverIRQHandler(void);
extern void PIT3_DriverIRQHandler(void);
extern void PDB0_DriverIRQHandler(void);
extern void USB0_DriverIRQHandler(void);
extern void USBDCD_DriverIRQHandler(void);
extern void Reserved71_DriverIRQHandler(void);
extern void DAC0_DriverIRQHandler(void);
extern void MCG_DriverIRQHandler(void);
extern void LPTMR0_DriverIRQHandler(void);
extern void PORTA_DriverIRQHandler(void);
extern void PORTB_DriverIRQHandler(void);
extern void PORTC_DriverIRQHandler(void);
extern void PORTD_DriverIRQHandler(void);
extern void PORTE_DriverIRQHandler(void);
extern void SWI_DriverIRQHandler(void);
extern void SPI2_DriverIRQHandler(void);
extern void UART4_RX_TX_DriverIRQHandler(void);
extern void UART4_ERR_DriverIRQHandler(void);
extern void Reserved84_DriverIRQHandler(void);
extern void Reserved85_DriverIRQHandler(void);
extern void CMP2_DriverIRQHandler(void);
extern void FTM3_DriverIRQHandler(void);
extern void DAC1_DriverIRQHandler(void);
extern void ADC1_DriverIRQHandler(void);
extern void I2C2_DriverIRQHandler(void);
extern void CAN0_DriverIRQHandler(void);
extern void SDHC_DriverIRQHandler(void);
extern void ENET_1588_Timer_DriverIRQHandler(void);
extern void ENET_Transmit_DriverIRQHandler(void);
extern void ENET_Receive_DriverIRQHandler(void);
extern void ENET_Error_DriverIRQHandler(void);
extern void LPUART0_DriverIRQHandler(void);
extern void TSI0_DriverIRQHandler(void);
extern void TPM1_DriverIRQHandler(void);
extern void TPM2_DriverIRQHandler(void);
extern void USBHSDCD_DriverIRQHandler(void);
extern void I2C3_DriverIRQHandler(void);
extern void CMP3_DriverIRQHandler(void);
extern void USBHS_DriverIRQHandler(void);
extern void CAN1_DriverIRQHandler(void);

//*****************************************************************************
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#else
extern int main(void);
#endif

//*****************************************************************************
// External declaration for the pointer to the stack top from the Linker Script
//*****************************************************************************
//extern void _vStackTop(void);
extern unsigned long _estack;
//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
// The vector table.
// This relies on the linker script to place at correct location in memory.
//*****************************************************************************

__attribute__ ((section(".dmabuffers"), used, aligned(512)))

void (* const g_pfnVectors[])(void);
//extern void * __Vectors __attribute__ ((alias ("g_pfnVectors")));
extern void * _VectorsFlash __attribute__ ((alias ("g_pfnVectors")));

void (* _VectorsRam[sizeof(_VectorsFlash)])(void);

__attribute__ ((used, section(".vectors")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM4
    (void (*)(void))((unsigned long)&_estack),// The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - MK66F18
    DMA0_DMA16_IRQHandler,                // 16 : DMA Channel 0, 16 Transfer Complete
    DMA1_DMA17_IRQHandler,                // 17 : DMA Channel 1, 17 Transfer Complete
    DMA2_DMA18_IRQHandler,                // 18 : DMA Channel 2, 18 Transfer Complete
    DMA3_DMA19_IRQHandler,                // 19 : DMA Channel 3, 19 Transfer Complete
    DMA4_DMA20_IRQHandler,                // 20 : DMA Channel 4, 20 Transfer Complete
    DMA5_DMA21_IRQHandler,                // 21 : DMA Channel 5, 21 Transfer Complete
    DMA6_DMA22_IRQHandler,                // 22 : DMA Channel 6, 22 Transfer Complete
    DMA7_DMA23_IRQHandler,                // 23 : DMA Channel 7, 23 Transfer Complete
    DMA8_DMA24_IRQHandler,                // 24 : DMA Channel 8, 24 Transfer Complete
    DMA9_DMA25_IRQHandler,                // 25 : DMA Channel 9, 25 Transfer Complete
    DMA10_DMA26_IRQHandler,               // 26 : DMA Channel 10, 26 Transfer Complete
    DMA11_DMA27_IRQHandler,               // 27 : DMA Channel 11, 27 Transfer Complete
    DMA12_DMA28_IRQHandler,               // 28 : DMA Channel 12, 28 Transfer Complete
    DMA13_DMA29_IRQHandler,               // 29 : DMA Channel 13, 29 Transfer Complete
    DMA14_DMA30_IRQHandler,               // 30 : DMA Channel 14, 30 Transfer Complete
    DMA15_DMA31_IRQHandler,               // 31 : DMA Channel 15, 31 Transfer Complete
    DMA_Error_IRQHandler,                 // 32 : DMA Error Interrupt
    MCM_IRQHandler,                       // 33 : Normal Interrupt
    FTFE_IRQHandler,                      // 34 : FTFE Command complete interrupt
    Read_Collision_IRQHandler,            // 35 : Read Collision Interrupt
    LVD_LVW_IRQHandler,                   // 36 : Low Voltage Detect, Low Voltage Warning
    LLWU_IRQHandler,                      // 37 : Low Leakage Wakeup Unit
    WDOG_EWM_IRQHandler,                  // 38 : WDOG Interrupt
    RNG_IRQHandler,                       // 39 : RNG Interrupt
    I2C0_IRQHandler,                      // 40 : I2C0 interrupt
    I2C1_IRQHandler,                      // 41 : I2C1 interrupt
    SPI0_IRQHandler,                      // 42 : SPI0 Interrupt
    SPI1_IRQHandler,                      // 43 : SPI1 Interrupt
    I2S0_Tx_IRQHandler,                   // 44 : I2S0 transmit interrupt
    I2S0_Rx_IRQHandler,                   // 45 : I2S0 receive interrupt
    Reserved46_IRQHandler,                // 46 : Reserved interrupt
    UART0_RX_TX_IRQHandler,               // 47 : UART0 Receive/Transmit interrupt
    UART0_ERR_IRQHandler,                 // 48 : UART0 Error interrupt
    UART1_RX_TX_IRQHandler,               // 49 : UART1 Receive/Transmit interrupt
    UART1_ERR_IRQHandler,                 // 50 : UART1 Error interrupt
    UART2_RX_TX_IRQHandler,               // 51 : UART2 Receive/Transmit interrupt
    UART2_ERR_IRQHandler,                 // 52 : UART2 Error interrupt
    UART3_RX_TX_IRQHandler,               // 53 : UART3 Receive/Transmit interrupt
    UART3_ERR_IRQHandler,                 // 54 : UART3 Error interrupt
    ADC0_IRQHandler,                      // 55 : ADC0 interrupt
    CMP0_IRQHandler,                      // 56 : CMP0 interrupt
    CMP1_IRQHandler,                      // 57 : CMP1 interrupt
    FTM0_IRQHandler,                      // 58 : FTM0 fault, overflow and channels interrupt
    FTM1_IRQHandler,                      // 59 : FTM1 fault, overflow and channels interrupt
    FTM2_IRQHandler,                      // 60 : FTM2 fault, overflow and channels interrupt
    CMT_IRQHandler,                       // 61 : CMT interrupt
    RTC_IRQHandler,                       // 62 : RTC interrupt
    RTC_Seconds_IRQHandler,               // 63 : RTC seconds interrupt
    PIT0_IRQHandler,                      // 64 : PIT timer channel 0 interrupt
    PIT1_IRQHandler,                      // 65 : PIT timer channel 1 interrupt
    PIT2_IRQHandler,                      // 66 : PIT timer channel 2 interrupt
    PIT3_IRQHandler,                      // 67 : PIT timer channel 3 interrupt
    PDB0_IRQHandler,                      // 68 : PDB0 Interrupt
    USB0_IRQHandler,                      // 69 : USB0 interrupt
    USBDCD_IRQHandler,                    // 70 : USBDCD Interrupt
    Reserved71_IRQHandler,                // 71 : Reserved interrupt
    DAC0_IRQHandler,                      // 72 : DAC0 interrupt
    MCG_IRQHandler,                       // 73 : MCG Interrupt
    LPTMR0_IRQHandler,                    // 74 : LPTimer interrupt
    PORTA_IRQHandler,                     // 75 : Port A interrupt
    PORTB_IRQHandler,                     // 76 : Port B interrupt
    PORTC_IRQHandler,                     // 77 : Port C interrupt
    PORTD_IRQHandler,                     // 78 : Port D interrupt
    PORTE_IRQHandler,                     // 79 : Port E interrupt
    SWI_IRQHandler,                       // 80 : Software interrupt
    SPI2_IRQHandler,                      // 81 : SPI2 Interrupt
    UART4_RX_TX_IRQHandler,               // 82 : UART4 Receive/Transmit interrupt
    UART4_ERR_IRQHandler,                 // 83 : UART4 Error interrupt
    Reserved84_IRQHandler,                // 84 : Reserved interrupt
    Reserved85_IRQHandler,                // 85 : Reserved interrupt
    CMP2_IRQHandler,                      // 86 : CMP2 interrupt
    FTM3_IRQHandler,                      // 87 : FTM3 fault, overflow and channels interrupt
    DAC1_IRQHandler,                      // 88 : DAC1 interrupt
    ADC1_IRQHandler,                      // 89 : ADC1 interrupt
    I2C2_IRQHandler,                      // 90 : I2C2 interrupt
    CAN0_ORed_Message_buffer_IRQHandler,  // 91 : CAN0 OR'd message buffers interrupt
    CAN0_Bus_Off_IRQHandler,              // 92 : CAN0 bus off interrupt
    CAN0_Error_IRQHandler,                // 93 : CAN0 error interrupt
    CAN0_Tx_Warning_IRQHandler,           // 94 : CAN0 Tx warning interrupt
    CAN0_Rx_Warning_IRQHandler,           // 95 : CAN0 Rx warning interrupt
    CAN0_Wake_Up_IRQHandler,              // 96 : CAN0 wake up interrupt
    SDHC_IRQHandler,                      // 97 : SDHC interrupt
    ENET_1588_Timer_IRQHandler,           // 98 : Ethernet MAC IEEE 1588 Timer Interrupt
    ENET_Transmit_IRQHandler,             // 99 : Ethernet MAC Transmit Interrupt
    ENET_Receive_IRQHandler,              // 100: Ethernet MAC Receive Interrupt
    ENET_Error_IRQHandler,                // 101: Ethernet MAC Error and miscelaneous Interrupt
    LPUART0_IRQHandler,                   // 102: LPUART0 status/error interrupt
    TSI0_IRQHandler,                      // 103: TSI0 interrupt
    TPM1_IRQHandler,                      // 104: TPM1 fault, overflow and channels interrupt
    TPM2_IRQHandler,                      // 105: TPM2 fault, overflow and channels interrupt
    USBHSDCD_IRQHandler,                  // 106: USBHSDCD, USBHS Phy Interrupt
    I2C3_IRQHandler,                      // 107: I2C3 interrupt
    CMP3_IRQHandler,                      // 108: CMP3 interrupt
    USBHS_IRQHandler,                     // 109: USB high speed OTG interrupt
    CAN1_ORed_Message_buffer_IRQHandler,  // 110: CAN1 OR'd message buffers interrupt
    CAN1_Bus_Off_IRQHandler,              // 111: CAN1 bus off interrupt
    CAN1_Error_IRQHandler,                // 112: CAN1 error interrupt
    CAN1_Tx_Warning_IRQHandler,           // 113: CAN1 Tx warning interrupt
    CAN1_Rx_Warning_IRQHandler,           // 114: CAN1 Rx warning interrupt
    CAN1_Wake_Up_IRQHandler,              // 115: CAN1 wake up interrupt


}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors.init_data")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = ( unsigned int * )( start );
    unsigned int *pulSrc = ( unsigned int * )( romstart );
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors.init_bss")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = ( unsigned int * )( start );
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;


extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".startup"),optimize("-Os")))
void ResetISR(void) {

    // Disable interrupts
    __asm volatile ("cpsid i");


#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();

#else
    // Disable Watchdog
    //  Write 0xC520 to watchdog unlock register
    *(( volatile unsigned short * )( 0x4005200E )) = 0xC520;
    //  Followed by 0xD928 to complete the unlock
    *(( volatile unsigned short * )( 0x4005200E )) = 0xD928;
    __asm volatile ("nop");
    __asm volatile ("nop");
    // Now disable watchdog via STCTRLH register
    *(( volatile unsigned short * )( 0x40052000 )) = 0x01D2u;
#endif // (__USE_CMSIS)

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

	unsigned int  *src = &_etext;
	unsigned int  *dest = &_sdata;
    while (dest < &_edata) *dest++ = *src++;
	dest = &_sbss;
	while (dest < &_ebss) *dest++ = 0;

//    // Load base address of Global Section Table
//    SectionTableAddr = &__data_section_table;
//
//    // Copy the data sections from flash to SRAM.
//    while (SectionTableAddr < &__data_section_table_end) {
//        LoadAddr = *SectionTableAddr++;
//        ExeAddr = *SectionTableAddr++;
//        SectionLen = *SectionTableAddr++;
//        data_init(LoadAddr, ExeAddr, SectionLen);
//    }
//
//    // At this point, SectionTableAddr = &__bss_section_table;
//    // Zero fill the bss segment
//    while (SectionTableAddr < &__bss_section_table_end) {
//        ExeAddr = *SectionTableAddr++;
//        SectionLen = *SectionTableAddr++;
//        bss_init(ExeAddr, SectionLen);
//    }

#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will enable the FPU
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
    //
    // Code to enable the Cortex-M4 FPU only included
    // if appropriate build options have been selected.
    // Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
    //
    // Read CPACR (located at address 0xE000ED88)
    // Set bits 20-23 to enable CP10 and CP11 coprocessors
    // Write back the modified value to the CPACR
    __asm volatile ("LDR.W R0, =0xE000ED88\n\t"
                  "LDR R1, [R0]\n\t"
                  "ORR R1, R1, #(0xF << 20)\n\t"
                  "STR R1, [R0]");
#endif // (__VFP_FP__) && !(__SOFTFP__)
#endif // (__USE_CMSIS)


#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will setup the VTOR register

    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.
    unsigned int * pSCB_VTOR = ( unsigned int  * )( 0xE000ED08 );
	for (int i=0; i < (sizeof(_VectorsRam)/sizeof(_VectorsRam[0]) ); i++) _VectorsRam[i] = g_pfnVectors[i];
    pSCB_VTOR = (unsigned int)_VectorsRam;
    //if ( ( unsigned int const * )( g_pfnVectors ) != ( unsigned int const * )( 0x00000000 ) ) {
    //    *pSCB_VTOR = ( unsigned int )( g_pfnVectors );
    //}
#endif // (__USE_CMSIS)
#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

    // Reenable interrupts
    //__asm volatile ("cpsie i");

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main();
#else
    main();
#endif

    //
    // main shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}




#pragma GCC pop_options

