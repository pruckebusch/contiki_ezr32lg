#ifndef __GPIO_H__
#define __GPIO_H__

#include "em_gpio.h"

enum gpio_no {
  GPIO_PA0 = 0xA0,
  GPIO_PA1,
  GPIO_PA2,
  GPIO_PA3,
  GPIO_PA4,
  GPIO_PA5,
  GPIO_PA6,
  GPIO_PA7,
  GPIO_PA8,
  GPIO_PA9,
  GPIO_PA10,
  GPIO_PA11,
  GPIO_PA12,
  GPIO_PA13,
  GPIO_PA14,
  GPIO_PA15,

  GPIO_PB0 = 0xB0,
  GPIO_PB1,
  GPIO_PB2,
  GPIO_PB3,
  GPIO_PB4,
  GPIO_PB5,
  GPIO_PB6,
  GPIO_PB7,
  GPIO_PB8,
  GPIO_PB9,
  GPIO_PB10,
  GPIO_PB11,
  GPIO_PB12,
  GPIO_PB13,
  GPIO_PB14,
  GPIO_PB15,

  GPIO_PC0 = 0xC0,
  GPIO_PC1,
  GPIO_PC2,
  GPIO_PC3,
  GPIO_PC4,
  GPIO_PC5,
  GPIO_PC6,
  GPIO_PC7,
  GPIO_PC8,
  GPIO_PC9,
  GPIO_PC10,
  GPIO_PC11,
  GPIO_PC12,
  GPIO_PC13,
  GPIO_PC14,
  GPIO_PC15,

  GPIO_PD0 = 0xD0,
  GPIO_PD1,
  GPIO_PD2,
  GPIO_PD3,
  GPIO_PD4,
  GPIO_PD5,
  GPIO_PD6,
  GPIO_PD7,
  GPIO_PD8,
  GPIO_PD9,
  GPIO_PD10,
  GPIO_PD11,
  GPIO_PD12,
  GPIO_PD13,
  GPIO_PD14,
  GPIO_PD15,

  GPIO_PE0 = 0xE0,
  GPIO_PE1,
  GPIO_PE2,
  GPIO_PE3,
  GPIO_PE4,
  GPIO_PE5,
  GPIO_PE6,
  GPIO_PE7,
  GPIO_PE8,
  GPIO_PE9,
  GPIO_PE10,
  GPIO_PE11,
  GPIO_PE12,
  GPIO_PE13,
  GPIO_PE14,
  GPIO_PE15,

  GPIO_PF0 = 0xF0,
  GPIO_PF1,
  GPIO_PF2,
  GPIO_PF3,
  GPIO_PF4,
  GPIO_PF5,
  GPIO_PF6,
  GPIO_PF7,
  GPIO_PF8,
  GPIO_PF9,
  GPIO_PF10,
  GPIO_PF11,
  GPIO_PF12,
  GPIO_PF13,
  GPIO_PF14,
  GPIO_PF15,
};

#define GPIO_PORTNO(gpio) ((gpio>>4 & 0xF) - 0xA)
#define GPIO_PINNO(gpio)  (gpio & 0x0F)
#define GPIO_IRQNO(gpio)  GPIO_PINNO(gpio)

#define GPIO_MAX_IRQS 16

#define IRQ_NONE     (0)
#define IRQ_HANDLED  (1)

#define IRQ_TYPE_NONE         0x00  /* Default, unspecified type */
#define IRQ_TYPE_EDGE_RISING  0x01  /* Edge rising type */
#define IRQ_TYPE_EDGE_FALLING 0x02  /* Edge falling type */
#define IRQ_TYPE_EDGE_BOTH    (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#define IRQ_TYPE_LEVEL_HIGH   0x04  /* Level high type */
#define IRQ_TYPE_LEVEL_LOW    0x08  /* Level low type */

static int _initialized = 0;

typedef uint8_t irq_edge_type_t;

/*
 * irq_handler_t :
 * param 1: irqno
 * param 2: private data
 *
 */
typedef void (*irq_handler_t)(int, void *);
/*
int gpio_register_ext1irq(uint8_t intselno, uint8_t type, irq_handler_t handler, void *priv);
int gpio_register_ext1irq(uint8_t intselno, uint8_t type, irq_handler_t handler, void *priv);
*/
int gpio_register_irq(uint8_t gpio, irq_edge_type_t type, irq_handler_t handler, void *priv);
void gpio_enable_irq(uint8_t gpioirq_id);
void gpio_disable_irq(uint8_t gpioirq_id);

void gpio_init(void);

void gpio_set_input(uint8_t gpio);
void gpio_set_output(uint8_t gpio, uint8_t value);
void gpio_set_output_pushpull(uint8_t gpio, uint8_t value);
void gpio_set_mode(uint8_t gpio, GPIO_Mode_TypeDef mode, uint8_t value);

uint8_t gpio_get_value(uint8_t gpio);
void gpio_set_value(uint8_t gpio, uint8_t value);

int gpio_suspend(void);
int gpio_resume(void);
int gpio_set_wakeup(uint8_t gpio, char enable, char level);
int gpio_wait(uint8_t gpio);

int gpio_is_active();

#ifdef CONFIG_PM
int gpio_suspend(void);
int gpio_resume(void);
#endif

/** @} */
/** @} */
/** @} */

#endif /* __GPIO_H__ */
