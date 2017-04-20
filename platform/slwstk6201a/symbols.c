#include "loader/symbols.h"

extern int ACMP0_IRQHandler();
extern int ADC0_IRQHandler();
extern int ADC_Init();
extern int ADC_InitSingle();
extern int ADC_PrescaleCalc();
extern int AES_IRQHandler();
extern int BURTC_IRQHandler();
extern int BURTC_Init();
extern int BusFault_Handler();
extern int CMU_ClockDivSet();
extern int CMU_ClockEnable();
extern int CMU_ClockFreqGet();
extern int CMU_ClockSelectGet();
extern int CMU_ClockSelectSet();
extern int CMU_HFRCOBandSet();
extern int CMU_IRQHandler();
extern int CMU_OscillatorEnable();
extern int CORE_EnterAtomic();
extern int CORE_ExitAtomic();
extern int CORE_IrqIsBlocked();
extern int CORE_NvicIRQDisabled();
extern int DAC0_IRQHandler();
extern int DMADRV_AllocateChannel();
extern int DMADRV_Init();
extern int DMADRV_MemoryPeripheral();
extern int DMADRV_PeripheralMemory();
extern int DMA_ActivateBasic();
extern int DMA_ActivatePingPong();
extern int DMA_CfgChannel();
extern int DMA_CfgDescr();
extern int DMA_IRQHandler();
extern int DMA_Init();
extern int DMA_RefreshPingPong();
extern int DMA_Reset();
extern int DebugMon_Handler();
extern int Default_Handler();
extern int EMU_BUPDInit();
extern int EMU_EM4Init();
extern int EMU_IRQHandler();
extern int EMU_UpdateOscConfig();
extern int GPIOINT_CallbackRegister();
extern int GPIO_EVEN_IRQHandler();
extern int GPIO_ExtIntConfig();
extern int GPIO_ODD_IRQHandler();
extern int GPIO_PB1_IRQHandler();
extern int GPIO_PinModeSet();
extern int HardFault_Handler();
extern int I2C0_IRQHandler();
extern int I2C1_IRQHandler();
extern int INT_LockCnt();
extern int LESENSE_IRQHandler();
extern int LETIMER0_IRQHandler();
extern int LEUART0_IRQHandler();
extern int LEUART1_IRQHandler();
extern int MSC_ErasePage();
extern int MSC_IRQHandler();
extern int MSC_Init();
extern int MSC_LoadVerifyAddress();
extern int MSC_LoadWriteData();
extern int MSC_MassErase();
extern int MSC_WriteWord();
extern int MSC_WriteWordFast();
extern int MSC_WriteWordI();
extern int MemManage_Handler();
extern int NMI_Handler();
extern int PCNT0_IRQHandler();
extern int PCNT1_IRQHandler();
extern int PCNT2_IRQHandler();
extern int PRS_SourceAsyncSignalSet();
extern int PendSV_Handler();
extern int RMU_ResetCauseClear();
extern int RMU_ResetCauseGet();
extern int RMU_ResetControl();
extern int RTCDRV_AllocateTimer();
extern int RTCDRV_Init();
extern int RTCDRV_StopTimer();
extern int RTC_CompareGet();
extern int RTC_CompareSet();
extern int RTC_CounterReset();
extern int RTC_Enable();
extern int RTC_IRQHandler();
extern int RTC_Init();
extern int Reset_Handler();
extern int SPIDRV_Init();
extern int SPIDRV_MReceiveB();
extern int SPIDRV_MTransmitB();
extern int SVC_Handler();
extern int SYSTEM_ChipRevisionGet();
extern int SysTick_Handler();
extern int SystemCoreClock();
extern int SystemCoreClockGet();
extern int SystemHFClockGet();
extern int SystemHFXOClockGet();
extern int SystemInit();
extern int SystemLFRCOClockGet();
extern int SystemLFXOClockGet();
extern int SystemMaxCoreClockGet();
extern int SystemULFRCOClockGet();
extern int TIMER0_IRQHandler();
extern int TIMER1_IRQHandler();
extern int TIMER2_IRQHandler();
extern int TIMER3_IRQHandler();
extern int TIMER_Init();
extern int TIMER_InitCC();
extern int UART0_RX_IRQHandler();
extern int UART0_TX_IRQHandler();
extern int UART1_RX_IRQHandler();
extern int UART1_TX_IRQHandler();
extern int USART1_RX_IRQHandler();
extern int USART1_TX_IRQHandler();
extern int USART2_RX_IRQHandler();
extern int USART2_TX_IRQHandler();
extern int USARTRF0_RX_IRQHandler();
extern int USARTRF0_TX_IRQHandler();
extern int USART_BaudrateAsyncSet();
extern int USART_BaudrateSyncSet();
extern int USART_Enable();
extern int USART_InitAsync();
extern int USART_InitSync();
extern int USART_Reset();
extern int USART_Rx();
extern int USART_Tx();
extern int USB_IRQHandler();
extern int USTIMER_DeInit();
extern int USTIMER_Delay();
extern int USTIMER_Init();
extern int UsageFault_Handler();
extern int VCMP_IRQHandler();
extern int WDOGn_Enable();
extern int WDOGn_Feed();
extern int WDOGn_Init();
extern int abc_input();
extern int abc_open();
extern int abc_send();
extern int abc_sent();
extern int actionsensors_process();
extern int adc_get_battery();
extern int adc_init();
extern int announcement_heard();
extern int announcement_init();
extern int announcement_list();
extern int announcement_register_observer_callback();
extern int appRadioHandle();
extern int appRadioInitData();
extern int atexit();
extern int autostart_processes();
extern int autostart_start();
extern int battery_sensor();
extern int broadcast_announcement_init();
extern int broadcast_open();
extern int broadcast_send();
extern int burtc_crystal_init();
extern int button0_sensor();
extern int button1_sensor();
extern int cfs_close();
extern int cfs_coffee_format();
extern int cfs_open();
extern int cfs_read();
extern int cfs_seek();
extern int cfs_write();
extern int chameleon_bitopt();
extern int chameleon_create();
extern int chameleon_hdrsize();
extern int chameleon_init();
extern int chameleon_parse();
extern int channel_init();
extern int channel_lookup();
extern int channel_open();
extern int channel_set_attributes();
extern int clock_delay();
extern int clock_delay_msec();
extern int clock_init();
extern int clock_time();
extern int ctimer_init();
extern int ctimer_process();
extern int ctimer_set();
extern int dbg_putchar();
extern int dbg_send_bytes();
extern int dmaControlBlock();
extern int dma_init();
extern int elfloader_arch_allocate_ram();
extern int elfloader_arch_allocate_rom();
extern int elfloader_arch_relocate();
extern int elfloader_arch_write_rom();
extern int elfloader_autostart_processes();
extern int elfloader_init();
extern int elfloader_load();
extern int elfloader_unknown();
extern int energest_init();
extern int errno();
extern int etimer_expired();
extern int etimer_next_expiration_time();
extern int etimer_pending();
extern int etimer_process();
extern int etimer_request_poll();
extern int etimer_set();
extern int exit();
extern int ezradioReply();
extern int ezradio_comm_ClearCTS();
extern int ezradio_comm_CtsWentHigh();
extern int ezradio_comm_GetResp();
extern int ezradio_comm_PollCTS();
extern int ezradio_comm_ReadData();
extern int ezradio_comm_SendCmd();
extern int ezradio_comm_SendCmdGetResp();
extern int ezradio_comm_WriteData();
extern int ezradio_configuration_init();
extern int ezradio_driver();
extern int ezradio_fifo_info();
extern int ezradio_get_int_status();
extern int ezradio_hal_AssertShutdown();
extern int ezradio_hal_ClearNsel();
extern int ezradio_hal_DeassertShutdown();
extern int ezradio_hal_GpioInit();
extern int ezradio_hal_NirqLevel();
extern int ezradio_hal_SetNsel();
extern int ezradio_hal_SpiInit();
extern int ezradio_hal_SpiReadByte();
extern int ezradio_hal_SpiReadData();
extern int ezradio_hal_SpiWriteByte();
extern int ezradio_hal_SpiWriteData();
extern int ezradio_part_info();
extern int ezradio_process();
extern int ezradio_read_rx_fifo();
extern int ezradio_request_device_state();
extern int ezradio_reset();
extern int ezradio_start_rx();
extern int ezradio_start_tx();
extern int ezradio_write_ezconfig_array();
extern int ezradio_write_tx_fifo();
extern int fflush();
extern int flash_compread();
extern int flash_compwrite();
extern int flash_erase();
extern int flash_init();
extern int format_str_v();
extern int get_bits();
extern int get_bits_in_byte();
extern int gpio_init();
extern int gpio_is_active();
extern int gpio_set_input();
extern int gpio_set_mode();
extern int gpio_set_output_pushpull();
extern int gpio_set_value();
extern int led_test_process();
extern int leds_arch_init();
extern int leds_arch_set();
extern int leds_init();
extern int leds_invert();
extern int leds_off();
extern int leds_toggle();
extern int list_add();
extern int list_head();
extern int list_init();
extern int list_item_next();
extern int list_remove();
extern int list_tail();
extern int mac_call_sent_callback();
extern int main();
extern int memb_init();
extern int memb_inmemb();
extern int memcmp();
void *memcpy();
void *memset();
extern int mscRfAssertEFM();
extern int n_addr();
extern int netstack_init();
extern int node_id();
extern int node_id_restore();
extern int node_mac();
extern int nullmac_driver();
extern int nullrdc_noframer_driver();
extern int packetbuf_addr();
extern int packetbuf_addrs();
extern int packetbuf_attr();
extern int packetbuf_attr_clear();
extern int packetbuf_attr_copyfrom();
extern int packetbuf_attrs();
extern int packetbuf_clear();
extern int packetbuf_compact();
extern int packetbuf_copyfrom();
extern int packetbuf_datalen();
extern int packetbuf_dataptr();
extern int packetbuf_hdralloc();
extern int packetbuf_hdrlen();
extern int packetbuf_hdrptr();
extern int packetbuf_hdrreduce();
extern int packetbuf_is_reference();
extern int packetbuf_reference_ptr();
extern int packetbuf_set_addr();
extern int packetbuf_set_attr();
extern int packetbuf_set_datalen();
extern int packetbuf_totlen();
extern int power_init();
extern int power_init_backuppd();
int printf(const char *, ...);
extern int process_alloc_event();
extern int process_current();
extern int process_init();
extern int process_is_running();
extern int process_list();
extern int process_poll();
extern int process_post();
extern int process_post_synch();
extern int process_run();
extern int process_start();
extern int putchar();
extern int puts();
extern int queuebuf_init();
extern int queuebuf_to_packetbuf();
extern int radio_sensor();
extern int rand();
extern int random_init();
extern int random_rand();
extern int reg();
extern int rime_driver();
extern int rime_output();
extern int rimeaddr_copy();
extern int rimeaddr_node_addr();
extern int rimeaddr_null();
extern int rimeaddr_set_node_addr();
extern int ringbuf_get();
extern int ringbuf_init();
extern int ringbuf_put();
extern int rtimer_arch_init();
extern int rtimer_init();
extern int sensors();
extern int sensors_changed();
extern int sensors_event();
extern int sensors_flags();
extern int sensors_process();
extern int serial_line_event_message();
extern int serial_line_init();
extern int serial_line_input_byte();
extern int serial_line_process();
extern int set_bits();
extern int set_bits_in_byte();
extern int setupSWO();
extern int srand();
extern int strcmp();
extern int strlen();
extern int strncmp();
extern int symtab_lookup();
extern int system_update();
extern int timer_expired();
extern int timer_set();
extern int uart1_init();
extern int uart1_send_bytes();
extern int uart1_set_input();
extern int uart1_writeb();
extern int watchdog_init();
extern int watchdog_periodic();
extern int watchdog_start();


const int symbols_nelts = 354;
const struct symbols symbols[354] = {
{ "ACMP0_IRQHandler", (void *)&ACMP0_IRQHandler },
{ "ADC0_IRQHandler", (void *)&ADC0_IRQHandler },
{ "ADC_Init", (void *)&ADC_Init },
{ "ADC_InitSingle", (void *)&ADC_InitSingle },
{ "ADC_PrescaleCalc", (void *)&ADC_PrescaleCalc },
{ "AES_IRQHandler", (void *)&AES_IRQHandler },
{ "BURTC_IRQHandler", (void *)&BURTC_IRQHandler },
{ "BURTC_Init", (void *)&BURTC_Init },
{ "BusFault_Handler", (void *)&BusFault_Handler },
{ "CMU_ClockDivSet", (void *)&CMU_ClockDivSet },
{ "CMU_ClockEnable", (void *)&CMU_ClockEnable },
{ "CMU_ClockFreqGet", (void *)&CMU_ClockFreqGet },
{ "CMU_ClockSelectGet", (void *)&CMU_ClockSelectGet },
{ "CMU_ClockSelectSet", (void *)&CMU_ClockSelectSet },
{ "CMU_HFRCOBandSet", (void *)&CMU_HFRCOBandSet },
{ "CMU_IRQHandler", (void *)&CMU_IRQHandler },
{ "CMU_OscillatorEnable", (void *)&CMU_OscillatorEnable },
{ "CORE_EnterAtomic", (void *)&CORE_EnterAtomic },
{ "CORE_ExitAtomic", (void *)&CORE_ExitAtomic },
{ "CORE_IrqIsBlocked", (void *)&CORE_IrqIsBlocked },
{ "CORE_NvicIRQDisabled", (void *)&CORE_NvicIRQDisabled },
{ "DAC0_IRQHandler", (void *)&DAC0_IRQHandler },
{ "DMADRV_AllocateChannel", (void *)&DMADRV_AllocateChannel },
{ "DMADRV_Init", (void *)&DMADRV_Init },
{ "DMADRV_MemoryPeripheral", (void *)&DMADRV_MemoryPeripheral },
{ "DMADRV_PeripheralMemory", (void *)&DMADRV_PeripheralMemory },
{ "DMA_ActivateBasic", (void *)&DMA_ActivateBasic },
{ "DMA_ActivatePingPong", (void *)&DMA_ActivatePingPong },
{ "DMA_CfgChannel", (void *)&DMA_CfgChannel },
{ "DMA_CfgDescr", (void *)&DMA_CfgDescr },
{ "DMA_IRQHandler", (void *)&DMA_IRQHandler },
{ "DMA_Init", (void *)&DMA_Init },
{ "DMA_RefreshPingPong", (void *)&DMA_RefreshPingPong },
{ "DMA_Reset", (void *)&DMA_Reset },
{ "DebugMon_Handler", (void *)&DebugMon_Handler },
{ "Default_Handler", (void *)&Default_Handler },
{ "EMU_BUPDInit", (void *)&EMU_BUPDInit },
{ "EMU_EM4Init", (void *)&EMU_EM4Init },
{ "EMU_IRQHandler", (void *)&EMU_IRQHandler },
{ "EMU_UpdateOscConfig", (void *)&EMU_UpdateOscConfig },
{ "GPIOINT_CallbackRegister", (void *)&GPIOINT_CallbackRegister },
{ "GPIO_EVEN_IRQHandler", (void *)&GPIO_EVEN_IRQHandler },
{ "GPIO_ExtIntConfig", (void *)&GPIO_ExtIntConfig },
{ "GPIO_ODD_IRQHandler", (void *)&GPIO_ODD_IRQHandler },
{ "GPIO_PB1_IRQHandler", (void *)&GPIO_PB1_IRQHandler },
{ "GPIO_PinModeSet", (void *)&GPIO_PinModeSet },
{ "HardFault_Handler", (void *)&HardFault_Handler },
{ "I2C0_IRQHandler", (void *)&I2C0_IRQHandler },
{ "I2C1_IRQHandler", (void *)&I2C1_IRQHandler },
{ "INT_LockCnt", (void *)&INT_LockCnt },
{ "LESENSE_IRQHandler", (void *)&LESENSE_IRQHandler },
{ "LETIMER0_IRQHandler", (void *)&LETIMER0_IRQHandler },
{ "LEUART0_IRQHandler", (void *)&LEUART0_IRQHandler },
{ "LEUART1_IRQHandler", (void *)&LEUART1_IRQHandler },
{ "MSC_ErasePage", (void *)&MSC_ErasePage },
{ "MSC_IRQHandler", (void *)&MSC_IRQHandler },
{ "MSC_Init", (void *)&MSC_Init },
{ "MSC_LoadVerifyAddress", (void *)&MSC_LoadVerifyAddress },
{ "MSC_LoadWriteData", (void *)&MSC_LoadWriteData },
{ "MSC_MassErase", (void *)&MSC_MassErase },
{ "MSC_WriteWord", (void *)&MSC_WriteWord },
{ "MSC_WriteWordFast", (void *)&MSC_WriteWordFast },
{ "MSC_WriteWordI", (void *)&MSC_WriteWordI },
{ "MemManage_Handler", (void *)&MemManage_Handler },
{ "NMI_Handler", (void *)&NMI_Handler },
{ "PCNT0_IRQHandler", (void *)&PCNT0_IRQHandler },
{ "PCNT1_IRQHandler", (void *)&PCNT1_IRQHandler },
{ "PCNT2_IRQHandler", (void *)&PCNT2_IRQHandler },
{ "PRS_SourceAsyncSignalSet", (void *)&PRS_SourceAsyncSignalSet },
{ "PendSV_Handler", (void *)&PendSV_Handler },
{ "RMU_ResetCauseClear", (void *)&RMU_ResetCauseClear },
{ "RMU_ResetCauseGet", (void *)&RMU_ResetCauseGet },
{ "RMU_ResetControl", (void *)&RMU_ResetControl },
{ "RTCDRV_AllocateTimer", (void *)&RTCDRV_AllocateTimer },
{ "RTCDRV_Init", (void *)&RTCDRV_Init },
{ "RTCDRV_StopTimer", (void *)&RTCDRV_StopTimer },
{ "RTC_CompareGet", (void *)&RTC_CompareGet },
{ "RTC_CompareSet", (void *)&RTC_CompareSet },
{ "RTC_CounterReset", (void *)&RTC_CounterReset },
{ "RTC_Enable", (void *)&RTC_Enable },
{ "RTC_IRQHandler", (void *)&RTC_IRQHandler },
{ "RTC_Init", (void *)&RTC_Init },
{ "Reset_Handler", (void *)&Reset_Handler },
{ "SPIDRV_Init", (void *)&SPIDRV_Init },
{ "SPIDRV_MReceiveB", (void *)&SPIDRV_MReceiveB },
{ "SPIDRV_MTransmitB", (void *)&SPIDRV_MTransmitB },
{ "SVC_Handler", (void *)&SVC_Handler },
{ "SYSTEM_ChipRevisionGet", (void *)&SYSTEM_ChipRevisionGet },
{ "SysTick_Handler", (void *)&SysTick_Handler },
{ "SystemCoreClock", (void *)&SystemCoreClock },
{ "SystemCoreClockGet", (void *)&SystemCoreClockGet },
{ "SystemHFClockGet", (void *)&SystemHFClockGet },
{ "SystemHFXOClockGet", (void *)&SystemHFXOClockGet },
{ "SystemInit", (void *)&SystemInit },
{ "SystemLFRCOClockGet", (void *)&SystemLFRCOClockGet },
{ "SystemLFXOClockGet", (void *)&SystemLFXOClockGet },
{ "SystemMaxCoreClockGet", (void *)&SystemMaxCoreClockGet },
{ "SystemULFRCOClockGet", (void *)&SystemULFRCOClockGet },
{ "TIMER0_IRQHandler", (void *)&TIMER0_IRQHandler },
{ "TIMER1_IRQHandler", (void *)&TIMER1_IRQHandler },
{ "TIMER2_IRQHandler", (void *)&TIMER2_IRQHandler },
{ "TIMER3_IRQHandler", (void *)&TIMER3_IRQHandler },
{ "TIMER_Init", (void *)&TIMER_Init },
{ "TIMER_InitCC", (void *)&TIMER_InitCC },
{ "UART0_RX_IRQHandler", (void *)&UART0_RX_IRQHandler },
{ "UART0_TX_IRQHandler", (void *)&UART0_TX_IRQHandler },
{ "UART1_RX_IRQHandler", (void *)&UART1_RX_IRQHandler },
{ "UART1_TX_IRQHandler", (void *)&UART1_TX_IRQHandler },
{ "USART1_RX_IRQHandler", (void *)&USART1_RX_IRQHandler },
{ "USART1_TX_IRQHandler", (void *)&USART1_TX_IRQHandler },
{ "USART2_RX_IRQHandler", (void *)&USART2_RX_IRQHandler },
{ "USART2_TX_IRQHandler", (void *)&USART2_TX_IRQHandler },
{ "USARTRF0_RX_IRQHandler", (void *)&USARTRF0_RX_IRQHandler },
{ "USARTRF0_TX_IRQHandler", (void *)&USARTRF0_TX_IRQHandler },
{ "USART_BaudrateAsyncSet", (void *)&USART_BaudrateAsyncSet },
{ "USART_BaudrateSyncSet", (void *)&USART_BaudrateSyncSet },
{ "USART_Enable", (void *)&USART_Enable },
{ "USART_InitAsync", (void *)&USART_InitAsync },
{ "USART_InitSync", (void *)&USART_InitSync },
{ "USART_Reset", (void *)&USART_Reset },
{ "USART_Rx", (void *)&USART_Rx },
{ "USART_Tx", (void *)&USART_Tx },
{ "USB_IRQHandler", (void *)&USB_IRQHandler },
{ "USTIMER_DeInit", (void *)&USTIMER_DeInit },
{ "USTIMER_Delay", (void *)&USTIMER_Delay },
{ "USTIMER_Init", (void *)&USTIMER_Init },
{ "UsageFault_Handler", (void *)&UsageFault_Handler },
{ "VCMP_IRQHandler", (void *)&VCMP_IRQHandler },
{ "WDOGn_Enable", (void *)&WDOGn_Enable },
{ "WDOGn_Feed", (void *)&WDOGn_Feed },
{ "WDOGn_Init", (void *)&WDOGn_Init },
{ "abc_input", (void *)&abc_input },
{ "abc_open", (void *)&abc_open },
{ "abc_send", (void *)&abc_send },
{ "abc_sent", (void *)&abc_sent },
{ "actionsensors_process", (void *)&actionsensors_process },
{ "adc_get_battery", (void *)&adc_get_battery },
{ "adc_init", (void *)&adc_init },
{ "announcement_heard", (void *)&announcement_heard },
{ "announcement_init", (void *)&announcement_init },
{ "announcement_list", (void *)&announcement_list },
{ "announcement_register_observer_callback", (void *)&announcement_register_observer_callback },
{ "appRadioHandle", (void *)&appRadioHandle },
{ "appRadioInitData", (void *)&appRadioInitData },
{ "atexit", (void *)&atexit },
{ "autostart_processes", (void *)&autostart_processes },
{ "autostart_start", (void *)&autostart_start },
{ "battery_sensor", (void *)&battery_sensor },
{ "broadcast_announcement_init", (void *)&broadcast_announcement_init },
{ "broadcast_open", (void *)&broadcast_open },
{ "broadcast_send", (void *)&broadcast_send },
{ "burtc_crystal_init", (void *)&burtc_crystal_init },
{ "button0_sensor", (void *)&button0_sensor },
{ "button1_sensor", (void *)&button1_sensor },
{ "cfs_close", (void *)&cfs_close },
{ "cfs_coffee_format", (void *)&cfs_coffee_format },
{ "cfs_open", (void *)&cfs_open },
{ "cfs_read", (void *)&cfs_read },
{ "cfs_seek", (void *)&cfs_seek },
{ "cfs_write", (void *)&cfs_write },
{ "chameleon_bitopt", (void *)&chameleon_bitopt },
{ "chameleon_create", (void *)&chameleon_create },
{ "chameleon_hdrsize", (void *)&chameleon_hdrsize },
{ "chameleon_init", (void *)&chameleon_init },
{ "chameleon_parse", (void *)&chameleon_parse },
{ "channel_init", (void *)&channel_init },
{ "channel_lookup", (void *)&channel_lookup },
{ "channel_open", (void *)&channel_open },
{ "channel_set_attributes", (void *)&channel_set_attributes },
{ "clock_delay", (void *)&clock_delay },
{ "clock_delay_msec", (void *)&clock_delay_msec },
{ "clock_init", (void *)&clock_init },
{ "clock_time", (void *)&clock_time },
{ "ctimer_init", (void *)&ctimer_init },
{ "ctimer_process", (void *)&ctimer_process },
{ "ctimer_set", (void *)&ctimer_set },
{ "dbg_putchar", (void *)&dbg_putchar },
{ "dbg_send_bytes", (void *)&dbg_send_bytes },
{ "dmaControlBlock", (void *)&dmaControlBlock },
{ "dma_init", (void *)&dma_init },
{ "elfloader_arch_allocate_ram", (void *)&elfloader_arch_allocate_ram },
{ "elfloader_arch_allocate_rom", (void *)&elfloader_arch_allocate_rom },
{ "elfloader_arch_relocate", (void *)&elfloader_arch_relocate },
{ "elfloader_arch_write_rom", (void *)&elfloader_arch_write_rom },
{ "elfloader_autostart_processes", (void *)&elfloader_autostart_processes },
{ "elfloader_init", (void *)&elfloader_init },
{ "elfloader_load", (void *)&elfloader_load },
{ "elfloader_unknown", (void *)&elfloader_unknown },
{ "energest_init", (void *)&energest_init },
{ "errno", (void *)&errno },
{ "etimer_expired", (void *)&etimer_expired },
{ "etimer_next_expiration_time", (void *)&etimer_next_expiration_time },
{ "etimer_pending", (void *)&etimer_pending },
{ "etimer_process", (void *)&etimer_process },
{ "etimer_request_poll", (void *)&etimer_request_poll },
{ "etimer_set", (void *)&etimer_set },
{ "exit", (void *)&exit },
{ "ezradioReply", (void *)&ezradioReply },
{ "ezradio_comm_ClearCTS", (void *)&ezradio_comm_ClearCTS },
{ "ezradio_comm_CtsWentHigh", (void *)&ezradio_comm_CtsWentHigh },
{ "ezradio_comm_GetResp", (void *)&ezradio_comm_GetResp },
{ "ezradio_comm_PollCTS", (void *)&ezradio_comm_PollCTS },
{ "ezradio_comm_ReadData", (void *)&ezradio_comm_ReadData },
{ "ezradio_comm_SendCmd", (void *)&ezradio_comm_SendCmd },
{ "ezradio_comm_SendCmdGetResp", (void *)&ezradio_comm_SendCmdGetResp },
{ "ezradio_comm_WriteData", (void *)&ezradio_comm_WriteData },
{ "ezradio_configuration_init", (void *)&ezradio_configuration_init },
{ "ezradio_driver", (void *)&ezradio_driver },
{ "ezradio_fifo_info", (void *)&ezradio_fifo_info },
{ "ezradio_get_int_status", (void *)&ezradio_get_int_status },
{ "ezradio_hal_AssertShutdown", (void *)&ezradio_hal_AssertShutdown },
{ "ezradio_hal_ClearNsel", (void *)&ezradio_hal_ClearNsel },
{ "ezradio_hal_DeassertShutdown", (void *)&ezradio_hal_DeassertShutdown },
{ "ezradio_hal_GpioInit", (void *)&ezradio_hal_GpioInit },
{ "ezradio_hal_NirqLevel", (void *)&ezradio_hal_NirqLevel },
{ "ezradio_hal_SetNsel", (void *)&ezradio_hal_SetNsel },
{ "ezradio_hal_SpiInit", (void *)&ezradio_hal_SpiInit },
{ "ezradio_hal_SpiReadByte", (void *)&ezradio_hal_SpiReadByte },
{ "ezradio_hal_SpiReadData", (void *)&ezradio_hal_SpiReadData },
{ "ezradio_hal_SpiWriteByte", (void *)&ezradio_hal_SpiWriteByte },
{ "ezradio_hal_SpiWriteData", (void *)&ezradio_hal_SpiWriteData },
{ "ezradio_part_info", (void *)&ezradio_part_info },
{ "ezradio_process", (void *)&ezradio_process },
{ "ezradio_read_rx_fifo", (void *)&ezradio_read_rx_fifo },
{ "ezradio_request_device_state", (void *)&ezradio_request_device_state },
{ "ezradio_reset", (void *)&ezradio_reset },
{ "ezradio_start_rx", (void *)&ezradio_start_rx },
{ "ezradio_start_tx", (void *)&ezradio_start_tx },
{ "ezradio_write_ezconfig_array", (void *)&ezradio_write_ezconfig_array },
{ "ezradio_write_tx_fifo", (void *)&ezradio_write_tx_fifo },
{ "fflush", (void *)&fflush },
{ "flash_compread", (void *)&flash_compread },
{ "flash_compwrite", (void *)&flash_compwrite },
{ "flash_erase", (void *)&flash_erase },
{ "flash_init", (void *)&flash_init },
{ "format_str_v", (void *)&format_str_v },
{ "get_bits", (void *)&get_bits },
{ "get_bits_in_byte", (void *)&get_bits_in_byte },
{ "gpio_init", (void *)&gpio_init },
{ "gpio_is_active", (void *)&gpio_is_active },
{ "gpio_set_input", (void *)&gpio_set_input },
{ "gpio_set_mode", (void *)&gpio_set_mode },
{ "gpio_set_output_pushpull", (void *)&gpio_set_output_pushpull },
{ "gpio_set_value", (void *)&gpio_set_value },
{ "led_test_process", (void *)&led_test_process },
{ "leds_arch_init", (void *)&leds_arch_init },
{ "leds_arch_set", (void *)&leds_arch_set },
{ "leds_init", (void *)&leds_init },
{ "leds_invert", (void *)&leds_invert },
{ "leds_off", (void *)&leds_off },
{ "leds_toggle", (void *)&leds_toggle },
{ "list_add", (void *)&list_add },
{ "list_head", (void *)&list_head },
{ "list_init", (void *)&list_init },
{ "list_item_next", (void *)&list_item_next },
{ "list_remove", (void *)&list_remove },
{ "list_tail", (void *)&list_tail },
{ "mac_call_sent_callback", (void *)&mac_call_sent_callback },
{ "main", (void *)&main },
{ "memb_init", (void *)&memb_init },
{ "memb_inmemb", (void *)&memb_inmemb },
{ "memcmp", (void *)&memcmp },
{ "memcpy", (void *)&memcpy },
{ "memset", (void *)&memset },
{ "mscRfAssertEFM", (void *)&mscRfAssertEFM },
{ "n_addr", (void *)&n_addr },
{ "netstack_init", (void *)&netstack_init },
{ "node_id", (void *)&node_id },
{ "node_id_restore", (void *)&node_id_restore },
{ "node_mac", (void *)&node_mac },
{ "nullmac_driver", (void *)&nullmac_driver },
{ "nullrdc_noframer_driver", (void *)&nullrdc_noframer_driver },
{ "packetbuf_addr", (void *)&packetbuf_addr },
{ "packetbuf_addrs", (void *)&packetbuf_addrs },
{ "packetbuf_attr", (void *)&packetbuf_attr },
{ "packetbuf_attr_clear", (void *)&packetbuf_attr_clear },
{ "packetbuf_attr_copyfrom", (void *)&packetbuf_attr_copyfrom },
{ "packetbuf_attrs", (void *)&packetbuf_attrs },
{ "packetbuf_clear", (void *)&packetbuf_clear },
{ "packetbuf_compact", (void *)&packetbuf_compact },
{ "packetbuf_copyfrom", (void *)&packetbuf_copyfrom },
{ "packetbuf_datalen", (void *)&packetbuf_datalen },
{ "packetbuf_dataptr", (void *)&packetbuf_dataptr },
{ "packetbuf_hdralloc", (void *)&packetbuf_hdralloc },
{ "packetbuf_hdrlen", (void *)&packetbuf_hdrlen },
{ "packetbuf_hdrptr", (void *)&packetbuf_hdrptr },
{ "packetbuf_hdrreduce", (void *)&packetbuf_hdrreduce },
{ "packetbuf_is_reference", (void *)&packetbuf_is_reference },
{ "packetbuf_reference_ptr", (void *)&packetbuf_reference_ptr },
{ "packetbuf_set_addr", (void *)&packetbuf_set_addr },
{ "packetbuf_set_attr", (void *)&packetbuf_set_attr },
{ "packetbuf_set_datalen", (void *)&packetbuf_set_datalen },
{ "packetbuf_totlen", (void *)&packetbuf_totlen },
{ "power_init", (void *)&power_init },
{ "power_init_backuppd", (void *)&power_init_backuppd },
{ "printf", (void *)&printf },
{ "process_alloc_event", (void *)&process_alloc_event },
{ "process_current", (void *)&process_current },
{ "process_init", (void *)&process_init },
{ "process_is_running", (void *)&process_is_running },
{ "process_list", (void *)&process_list },
{ "process_poll", (void *)&process_poll },
{ "process_post", (void *)&process_post },
{ "process_post_synch", (void *)&process_post_synch },
{ "process_run", (void *)&process_run },
{ "process_start", (void *)&process_start },
{ "putchar", (void *)&putchar },
{ "puts", (void *)&puts },
{ "queuebuf_init", (void *)&queuebuf_init },
{ "queuebuf_to_packetbuf", (void *)&queuebuf_to_packetbuf },
{ "radio_sensor", (void *)&radio_sensor },
{ "rand", (void *)&rand },
{ "random_init", (void *)&random_init },
{ "random_rand", (void *)&random_rand },
{ "reg", (void *)&reg },
{ "rime_driver", (void *)&rime_driver },
{ "rime_output", (void *)&rime_output },
{ "rimeaddr_copy", (void *)&rimeaddr_copy },
{ "rimeaddr_node_addr", (void *)&rimeaddr_node_addr },
{ "rimeaddr_null", (void *)&rimeaddr_null },
{ "rimeaddr_set_node_addr", (void *)&rimeaddr_set_node_addr },
{ "ringbuf_get", (void *)&ringbuf_get },
{ "ringbuf_init", (void *)&ringbuf_init },
{ "ringbuf_put", (void *)&ringbuf_put },
{ "rtimer_arch_init", (void *)&rtimer_arch_init },
{ "rtimer_init", (void *)&rtimer_init },
{ "sensors", (void *)&sensors },
{ "sensors_changed", (void *)&sensors_changed },
{ "sensors_event", (void *)&sensors_event },
{ "sensors_flags", (void *)&sensors_flags },
{ "sensors_process", (void *)&sensors_process },
{ "serial_line_event_message", (void *)&serial_line_event_message },
{ "serial_line_init", (void *)&serial_line_init },
{ "serial_line_input_byte", (void *)&serial_line_input_byte },
{ "serial_line_process", (void *)&serial_line_process },
{ "set_bits", (void *)&set_bits },
{ "set_bits_in_byte", (void *)&set_bits_in_byte },
{ "setupSWO", (void *)&setupSWO },
{ "srand", (void *)&srand },
{ "strcmp", (void *)&strcmp },
{ "strlen", (void *)&strlen },
{ "strncmp", (void *)&strncmp },
{ "symtab_lookup", (void *)&symtab_lookup },
{ "system_update", (void *)&system_update },
{ "timer_expired", (void *)&timer_expired },
{ "timer_set", (void *)&timer_set },
{ "uart1_init", (void *)&uart1_init },
{ "uart1_send_bytes", (void *)&uart1_send_bytes },
{ "uart1_set_input", (void *)&uart1_set_input },
{ "uart1_writeb", (void *)&uart1_writeb },
{ "watchdog_init", (void *)&watchdog_init },
{ "watchdog_periodic", (void *)&watchdog_periodic },
{ "watchdog_start", (void *)&watchdog_start },
{ (const char *)0, (void *)0} };
