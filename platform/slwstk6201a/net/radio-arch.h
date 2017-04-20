#ifndef PLATFORM_SLWSTK6201A_NET_RADIO_ARCH_H_
#define PLATFORM_SLWSTK6201A_NET_RADIO_ARCH_H_

#include "radio-arch-config.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spidrv.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"
#include "rtcdriver.h"

// ToDo
// minimize dependencies
#include "ezradio_cmd.h"
#include "ezradio_api_lib.h"
#include "ezradio_comm.h"
#include "ezradio_hal.h"
#include "ezradio_plugin_manager.h"

#include "slwstk6201a-contiki-interface.h"
#include "net/packetbuf.h"
#include "net/mac/frame802154.h"
#include "net/rime/rimestats.h"


extern const struct radio_driver ezradio_driver;

#define EZRADIO_CHANNEL	0

/* EZRADIO_TX_CONFIG configures EZRADIODRV_PacketTxHandle_t as follows:
 * 	EZRADIODRV_Callback_t
 * 	EZRADIODRV_PacketLengthConfig_t
 * 		EZRADIODRV_TransmitLengthMode_t lenMode;  // Length mode.
 * 			ezradiodrvTransmitLenghtDefault               = 0,    // Transmit packet length is defined in the generated configuration
 * 			ezradiodrvTransmitLenghtCustomPacketLen       = 1,    // Transmit packet length is defined by the application for field1 only
 * 			ezradiodrvTransmitLenghtCustomFieldLen        = 2     // Transmit packet length is defined by the application for multiple fields
 * 		uint16_t pktLen;                          // Packet length.
 * 		EZRADIODRV_FieldLength_t fieldLen;        // Field lengths.
 * 		  uint8_t f1;       // Field 1 length
 * 		  uint8_t f2;       // Field 2 length
 * 		  uint8_t f3;       // Field 3 length
 * 		  uint8_t f4;       // Field 4 length
 * 		  uint8_t f5;       // Field 5 length
 * 	uint8_t channel
 * 	EZRADIODRV_TransmitPacketType_t
 * 		ezradiodrvPacketTypeNormal                    = 0,    // Normal packet type.
 * 		ezradiodrvPacketTypeAutoAck                   = 1,    // Auto acknowledge packet type.
 * 	uint16_t pktId
 */

#define EZRADIO_TX_CONFIG                                                      \
{                                           /* Packet TX                   */  \
  NULL,                                     /* CallBack                    */  \
  {                                         /* Packet length config        */  \
	ezradiodrvTransmitLenghtCustomPacketLen,/* Custom packet length         */ \
    64,                                     /* Packet length               */  \
    {64, 0, 0, 0, 0}                        /* Field lengths               */  \
  },                                                                           \
  EZRADIO_CHANNEL,                          /* Channel                     */  \
  ezradiodrvPacketTypeNormal,               /* Packet type                 */  \
  0,                                        /* Packet ID                   */  \
},


/* EZRADIO_TX_CONFIG configures EZRADIODRV_PacketTxHandle_t as follows:
 * EZRADIODRV_Callback_t userCallback;   // User callback.
 * 	typedef void (*EZRADIODRV_Callback_t)(EZRADIODRV_Handle_t handle, Ecode_t status);
 * uint8_t channel;                      // Reception channel.
 * uint8_t * pktBuf;                     // Pointer to the receive buffer.
*/
#define EZRADIO_RX_CONFIG                                                     \
{                                             /* Packet RX                */  \
  NULL,                                       /* CallBack                 */  \
  EZRADIO_CHANNEL,                            /* Channel                  */  \
  NULL,                                       /* Packet buffer            */  \
},

#define EZRADIO_CONFIG                                                        \
{                                                                             \
	EZRADIO_TX_CONFIG                             /* Tx config */             \
	EZRADIO_RX_CONFIG                             /* Rx plugin init */        \
}

#endif
