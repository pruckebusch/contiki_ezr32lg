# 1 "../../../cpu/arm//ezr32/ezr32lg/Source/startup_ezr32lg.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "../../../cpu/arm//ezr32/ezr32lg/Source/startup_ezr32lg.S"
# 35 "../../../cpu/arm//ezr32/ezr32lg/Source/startup_ezr32lg.S"
    .syntax unified
    .arch armv7-m
    .section .stack
    .align 3



    .equ Stack_Size, 0x00000400

    .globl __StackTop
    .globl __StackLimit
__StackLimit:
    .space Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3



    .equ Heap_Size, 0x00000C00

    .globl __HeapBase
    .globl __HeapLimit
__HeapBase:
    .if Heap_Size
    .space Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .vectors
    .align 2
    .globl __Vectors
__Vectors:
    .long __StackTop
    .long Reset_Handler
    .long NMI_Handler
    .long HardFault_Handler
    .long MemManage_Handler
    .long BusFault_Handler
    .long UsageFault_Handler
    .long Default_Handler
    .long Default_Handler
    .long Default_Handler
    .long Default_Handler
    .long SVC_Handler
    .long DebugMon_Handler
    .long Default_Handler
    .long PendSV_Handler
    .long SysTick_Handler



    .long DMA_IRQHandler
    .long GPIO_EVEN_IRQHandler
    .long TIMER0_IRQHandler
    .long USARTRF0_RX_IRQHandler
    .long USARTRF0_TX_IRQHandler
    .long USB_IRQHandler
    .long ACMP0_IRQHandler
    .long ADC0_IRQHandler
    .long DAC0_IRQHandler
    .long I2C0_IRQHandler
    .long I2C1_IRQHandler
    .long GPIO_ODD_IRQHandler
    .long TIMER1_IRQHandler
    .long TIMER2_IRQHandler
    .long TIMER3_IRQHandler
    .long USART1_RX_IRQHandler
    .long USART1_TX_IRQHandler
    .long LESENSE_IRQHandler
    .long USART2_RX_IRQHandler
    .long USART2_TX_IRQHandler
    .long UART0_RX_IRQHandler
    .long UART0_TX_IRQHandler
    .long UART1_RX_IRQHandler
    .long UART1_TX_IRQHandler
    .long LEUART0_IRQHandler
    .long LEUART1_IRQHandler
    .long LETIMER0_IRQHandler
    .long PCNT0_IRQHandler
    .long PCNT1_IRQHandler
    .long PCNT2_IRQHandler
    .long RTC_IRQHandler
    .long BURTC_IRQHandler
    .long CMU_IRQHandler
    .long VCMP_IRQHandler
    .long Default_Handler
    .long MSC_IRQHandler
    .long AES_IRQHandler
    .long Default_Handler
    .long EMU_IRQHandler
    .long Default_Handler


    .size __Vectors, . - __Vectors

    .text
    .thumb
    .thumb_func
    .align 2
    .globl Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:

    ldr r0, =SystemInit
    blx r0
# 196 "../../../cpu/arm//ezr32/ezr32lg/Source/startup_ezr32lg.S"
    ldr r1, =__etext
    ldr r2, =__data_start__
    ldr r3, =__data_end__

.L_loop1:
    cmp r2, r3
    ittt lt
    ldrlt r0, [r1], #4
    strlt r0, [r2], #4
    blt .L_loop1
# 267 "../../../cpu/arm//ezr32/ezr32lg/Source/startup_ezr32lg.S"
    bl _start

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align 1
    .thumb_func
    .weak Default_Handler
    .type Default_Handler, %function
Default_Handler:
    b .
    .size Default_Handler, . - Default_Handler




    .macro def_irq_handler handler_name
    .weak \handler_name
    .set \handler_name, Default_Handler
    .endm

    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler MemManage_Handler
    def_irq_handler BusFault_Handler
    def_irq_handler UsageFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler DebugMon_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler

    def_irq_handler DMA_IRQHandler
    def_irq_handler GPIO_EVEN_IRQHandler
    def_irq_handler TIMER0_IRQHandler
    def_irq_handler USARTRF0_RX_IRQHandler
    def_irq_handler USARTRF0_TX_IRQHandler
    def_irq_handler USB_IRQHandler
    def_irq_handler ACMP0_IRQHandler
    def_irq_handler ADC0_IRQHandler
    def_irq_handler DAC0_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler GPIO_ODD_IRQHandler
    def_irq_handler TIMER1_IRQHandler
    def_irq_handler TIMER2_IRQHandler
    def_irq_handler TIMER3_IRQHandler
    def_irq_handler USART1_RX_IRQHandler
    def_irq_handler USART1_TX_IRQHandler
    def_irq_handler LESENSE_IRQHandler
    def_irq_handler USART2_RX_IRQHandler
    def_irq_handler USART2_TX_IRQHandler
    def_irq_handler UART0_RX_IRQHandler
    def_irq_handler UART0_TX_IRQHandler
    def_irq_handler UART1_RX_IRQHandler
    def_irq_handler UART1_TX_IRQHandler
    def_irq_handler LEUART0_IRQHandler
    def_irq_handler LEUART1_IRQHandler
    def_irq_handler LETIMER0_IRQHandler
    def_irq_handler PCNT0_IRQHandler
    def_irq_handler PCNT1_IRQHandler
    def_irq_handler PCNT2_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler BURTC_IRQHandler
    def_irq_handler CMU_IRQHandler
    def_irq_handler VCMP_IRQHandler
    def_irq_handler MSC_IRQHandler
    def_irq_handler AES_IRQHandler
    def_irq_handler EMU_IRQHandler


    .end
