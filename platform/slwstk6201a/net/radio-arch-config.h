#ifndef PLATFORM_SLWSTK6201A_NET_RADIO_ARCH_CONFIG_H_
#define PLATFORM_SLWSTK6201A_NET_RADIO_ARCH_CONFIG_H_

#define PLATFORM_MAX_PAYLOAD_SIZE		64		// Max payload size in bytes

#if defined(USE_BAND_434)
  #define RF_FREQUENCY					434000000	// Hz
#elif defined(USE_BAND_868)
  #define RF_FREQUENCY					868000000	// Hz
#elif defined(USE_BAND_915)
  #define RF_FREQUENCY					915000000	// Hz
#else
  #error "Please define a frequency band in the compiler options."
#endif



#endif
