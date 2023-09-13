
#define WEAK __attribute__ ((weak))
#define WEAK_AV __attribute__ ((weak, section(".after_vectors")))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))


#pragma GCC push_options
#pragma GCC optimize ("Og")


void DMA0_DMA16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DMA17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_DMA18_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_DMA19_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_DMA20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA5_DMA21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA6_DMA22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA7_DMA23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA8_DMA24_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA9_DMA25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA10_DMA26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA11_DMA27_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA12_DMA28_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA13_DMA29_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA14_DMA30_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA15_DMA31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Read_Collision_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LVD_LVW_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG_EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_Tx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_Rx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Seconds_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBDCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved71_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SWI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART4_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART4_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved84_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved85_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SDHC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_1588_Timer_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_Transmit_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_Receive_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TSI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBHSDCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBHS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);


//*****************************************************************************
// Default core exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void NMI_Handler(void)
{ 
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void HardFault_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void MemManage_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void BusFault_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void UsageFault_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void SVC_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void DebugMon_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void PendSV_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void SysTick_Handler(void)
{
    for(;;);
    __builtin_unreachable();
}

//*****************************************************************************
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//*****************************************************************************
__attribute__ ((weak, section(".after_vectors"),noreturn)) 
void IntDefaultHandler(void)
{
    for(;;);
    __builtin_unreachable();
}

//*****************************************************************************
// Default application exception handlers. Override the ones here by defining
// your own handler routines in your application code. These routines call
// driver exception handlers or IntDefaultHandler() if no driver exception
// handler is included.
//*****************************************************************************
WEAK void DMA0_DMA16_IRQHandler(void)
{   DMA0_DMA16_DriverIRQHandler();
}

WEAK void DMA1_DMA17_IRQHandler(void)
{   DMA1_DMA17_DriverIRQHandler();
}

WEAK void DMA2_DMA18_IRQHandler(void)
{   DMA2_DMA18_DriverIRQHandler();
}

WEAK void DMA3_DMA19_IRQHandler(void)
{   DMA3_DMA19_DriverIRQHandler();
}

WEAK void DMA4_DMA20_IRQHandler(void)
{   DMA4_DMA20_DriverIRQHandler();
}

WEAK void DMA5_DMA21_IRQHandler(void)
{   DMA5_DMA21_DriverIRQHandler();
}

WEAK void DMA6_DMA22_IRQHandler(void)
{   DMA6_DMA22_DriverIRQHandler();
}

WEAK void DMA7_DMA23_IRQHandler(void)
{   DMA7_DMA23_DriverIRQHandler();
}

WEAK void DMA8_DMA24_IRQHandler(void)
{   DMA8_DMA24_DriverIRQHandler();
}

WEAK void DMA9_DMA25_IRQHandler(void)
{   DMA9_DMA25_DriverIRQHandler();
}

WEAK void DMA10_DMA26_IRQHandler(void)
{   DMA10_DMA26_DriverIRQHandler();
}

WEAK void DMA11_DMA27_IRQHandler(void)
{   DMA11_DMA27_DriverIRQHandler();
}

WEAK void DMA12_DMA28_IRQHandler(void)
{   DMA12_DMA28_DriverIRQHandler();
}

WEAK void DMA13_DMA29_IRQHandler(void)
{   DMA13_DMA29_DriverIRQHandler();
}

WEAK void DMA14_DMA30_IRQHandler(void)
{   DMA14_DMA30_DriverIRQHandler();
}

WEAK void DMA15_DMA31_IRQHandler(void)
{   DMA15_DMA31_DriverIRQHandler();
}

WEAK void DMA_Error_IRQHandler(void)
{   DMA_Error_DriverIRQHandler();
}

WEAK void MCM_IRQHandler(void)
{   MCM_DriverIRQHandler();
}

WEAK void FTFE_IRQHandler(void)
{   FTFE_DriverIRQHandler();
}

WEAK void Read_Collision_IRQHandler(void)
{   Read_Collision_DriverIRQHandler();
}

WEAK void LVD_LVW_IRQHandler(void)
{   LVD_LVW_DriverIRQHandler();
}

WEAK void LLWU_IRQHandler(void)
{   LLWU_DriverIRQHandler();
}

WEAK void WDOG_EWM_IRQHandler(void)
{   WDOG_EWM_DriverIRQHandler();
}

WEAK void RNG_IRQHandler(void)
{   RNG_DriverIRQHandler();
}

WEAK void I2C0_IRQHandler(void)
{   I2C0_DriverIRQHandler();
}

WEAK void I2C1_IRQHandler(void)
{   I2C1_DriverIRQHandler();
}

WEAK void SPI0_IRQHandler(void)
{   SPI0_DriverIRQHandler();
}

WEAK void SPI1_IRQHandler(void)
{   SPI1_DriverIRQHandler();
}

WEAK void I2S0_Tx_IRQHandler(void)
{   I2S0_Tx_DriverIRQHandler();
}

WEAK void I2S0_Rx_IRQHandler(void)
{   I2S0_Rx_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void UART0_RX_TX_IRQHandler(void)
{   UART0_RX_TX_DriverIRQHandler();
}

WEAK void UART0_ERR_IRQHandler(void)
{   UART0_ERR_DriverIRQHandler();
}

WEAK void UART1_RX_TX_IRQHandler(void)
{   UART1_RX_TX_DriverIRQHandler();
}

WEAK void UART1_ERR_IRQHandler(void)
{   UART1_ERR_DriverIRQHandler();
}

WEAK void UART2_RX_TX_IRQHandler(void)
{   UART2_RX_TX_DriverIRQHandler();
}

WEAK void UART2_ERR_IRQHandler(void)
{   UART2_ERR_DriverIRQHandler();
}

WEAK void UART3_RX_TX_IRQHandler(void)
{   UART3_RX_TX_DriverIRQHandler();
}

WEAK void UART3_ERR_IRQHandler(void)
{   UART3_ERR_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void CMP0_IRQHandler(void)
{   CMP0_DriverIRQHandler();
}

WEAK void CMP1_IRQHandler(void)
{   CMP1_DriverIRQHandler();
}

WEAK void FTM0_IRQHandler(void)
{   FTM0_DriverIRQHandler();
}

WEAK void FTM1_IRQHandler(void)
{   FTM1_DriverIRQHandler();
}

WEAK void FTM2_IRQHandler(void)
{   FTM2_DriverIRQHandler();
}

WEAK void CMT_IRQHandler(void)
{   CMT_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void RTC_Seconds_IRQHandler(void)
{   RTC_Seconds_DriverIRQHandler();
}

WEAK void PIT0_IRQHandler(void)
{   PIT0_DriverIRQHandler();
}

WEAK void PIT1_IRQHandler(void)
{   PIT1_DriverIRQHandler();
}

WEAK void PIT2_IRQHandler(void)
{   PIT2_DriverIRQHandler();
}

WEAK void PIT3_IRQHandler(void)
{   PIT3_DriverIRQHandler();
}

WEAK void PDB0_IRQHandler(void)
{   PDB0_DriverIRQHandler();
}

WEAK void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
}

WEAK void USBDCD_IRQHandler(void)
{   USBDCD_DriverIRQHandler();
}

WEAK void Reserved71_IRQHandler(void)
{   Reserved71_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK void MCG_IRQHandler(void)
{   MCG_DriverIRQHandler();
}

WEAK void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
}

WEAK void PORTA_IRQHandler(void)
{   PORTA_DriverIRQHandler();
}

WEAK void PORTB_IRQHandler(void)
{   PORTB_DriverIRQHandler();
}

WEAK void PORTC_IRQHandler(void)
{   PORTC_DriverIRQHandler();
}

WEAK void PORTD_IRQHandler(void)
{   PORTD_DriverIRQHandler();
}

WEAK void PORTE_IRQHandler(void)
{   PORTE_DriverIRQHandler();
}

WEAK void SWI_IRQHandler(void)
{   SWI_DriverIRQHandler();
}

WEAK void SPI2_IRQHandler(void)
{   SPI2_DriverIRQHandler();
}

WEAK void UART4_RX_TX_IRQHandler(void)
{   UART4_RX_TX_DriverIRQHandler();
}

WEAK void UART4_ERR_IRQHandler(void)
{   UART4_ERR_DriverIRQHandler();
}

WEAK void Reserved84_IRQHandler(void)
{   Reserved84_DriverIRQHandler();
}

WEAK void Reserved85_IRQHandler(void)
{   Reserved85_DriverIRQHandler();
}

WEAK void CMP2_IRQHandler(void)
{   CMP2_DriverIRQHandler();
}

WEAK void FTM3_IRQHandler(void)
{   FTM3_DriverIRQHandler();
}

WEAK void DAC1_IRQHandler(void)
{   DAC1_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)
{   ADC1_DriverIRQHandler();
}

WEAK void I2C2_IRQHandler(void)
{   I2C2_DriverIRQHandler();
}

WEAK void CAN0_ORed_Message_buffer_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Bus_Off_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Error_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Tx_Warning_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Rx_Warning_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Wake_Up_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void SDHC_IRQHandler(void)
{   SDHC_DriverIRQHandler();
}

WEAK void ENET_1588_Timer_IRQHandler(void)
{   ENET_1588_Timer_DriverIRQHandler();
}

WEAK void ENET_Transmit_IRQHandler(void)
{   ENET_Transmit_DriverIRQHandler();
}

WEAK void ENET_Receive_IRQHandler(void)
{   ENET_Receive_DriverIRQHandler();
}

WEAK void ENET_Error_IRQHandler(void)
{   ENET_Error_DriverIRQHandler();
}

WEAK void LPUART0_IRQHandler(void)
{   LPUART0_DriverIRQHandler();
}

WEAK void TSI0_IRQHandler(void)
{   TSI0_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK void TPM2_IRQHandler(void)
{   TPM2_DriverIRQHandler();
}

WEAK void USBHSDCD_IRQHandler(void)
{   USBHSDCD_DriverIRQHandler();
}

WEAK void I2C3_IRQHandler(void)
{   I2C3_DriverIRQHandler();
}

WEAK void CMP3_IRQHandler(void)
{   CMP3_DriverIRQHandler();
}

WEAK void USBHS_IRQHandler(void)
{   USBHS_DriverIRQHandler();
}

WEAK void CAN1_ORed_Message_buffer_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Bus_Off_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Error_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Tx_Warning_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Rx_Warning_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Wake_Up_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}



//*****************************************************************************


#pragma GCC pop_options
