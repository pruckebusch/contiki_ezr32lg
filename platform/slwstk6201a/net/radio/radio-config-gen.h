// Copyright 2017 Silicon Laboratories, Inc.
//
//

// Modem configuration parameters
// version: 1.3.0.119
// afc_en: 0
// ant_div: 0
// BER_mode: 0
// Ch_Fil_Bw_AFC: 0
// Chip_Version: 2
// crystal_tol: 20
// dsa_mode: 0
// dsource: 0
// ETSI: 0
// fc: 434000000
// Fdev: 20000
// Fdev_error: 0
// fhch: 10
// fhst: 250000
// freq_xo: 30000000
// hi_pfm_div_mode: 0
// High_perf_Ch_Fil: 1
// if_mode: 2
// inputBW: 0
// Manchester: 0
// Max_Rb_Error: 0
// modulation_type: 2
// OSRtune: 0
// pm_len: 16
// pm_pattern: 0
// raw_demod: 0
// Rsymb: 10000
// RXBW: 150000
// TC: 29

// Modem configuration calculated values
// if_freq: -468750.0
// nb_filter: 4
// nb_filter_bw: 82.6375
// wb_filter: 4
// wb_filter_bw: 82.6375

// This file contains the generated ObjectAPI byte arrays for the given configuration
// Enclosing macro to prevent multiple inclusion
#ifndef __SLAB_RADIO_CONFIG__
#define __SLAB_RADIO_CONFIG__


#define RADIO_CONFIG_POWER_UP { \
  0x02 /* CMD: Power up                                               */,\
  0x01 /* BOOT_OPTIONS,PATCH[7],FUNC[5:0]                             */,\
  0x00 /* XTAL_OPTIONS,TCXO[0]                                        */,\
  0x01 /* XO_FREQ,XO_FREQ[7:0],XO_FREQ[7:0],XO_FREQ[7:0],XO_FREQ[7:0] */,\
  0xC9 /*                                                             */,\
  0xC3 /*                                                             */,\
  0x80 /*                                                             */\
}

#define RADIO_CONFIG_POWER_UP_LEN (7)


#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_ENABLE { \
  0x11 /* CMD: Set property                                                               */,\
  0x01 /* GROUP: Int ctl                                                                  */,\
  0x01 /* NUM_PROPS                                                                       */,\
  0x00 /* START_PROP                                                                      */,\
  0x05 /* INT_CTL_ENABLE,CHIP_INT_STATUS_EN[2],MODEM_INT_STATUS_EN[1],PH_INT_STATUS_EN[0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_ENABLE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_PH_ENABLE { \
  0x11 /* CMD: Set property                                                                                                                                                                 */,\
  0x01 /* GROUP: Int ctl                                                                                                                                                                    */,\
  0x01 /* NUM_PROPS                                                                                                                                                                         */,\
  0x01 /* START_PROP                                                                                                                                                                        */,\
  0x38 /* INT_CTL_PH_ENABLE,FILTER_MATCH_EN[7],FILTER_MISS_EN[6],PACKET_SENT_EN[5],PACKET_RX_EN[4],CRC_ERROR_EN[3],ALT_CRC_ERROR_EN[2],TX_FIFO_ALMOST_EMPTY_EN[1],RX_FIFO_ALMOST_FULL_EN[0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_PH_ENABLE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_MODEM_ENABLE { \
  0x11 /* CMD: Set property                                                                                                                                                         */,\
  0x01 /* GROUP: Int ctl                                                                                                                                                            */,\
  0x01 /* NUM_PROPS                                                                                                                                                                 */,\
  0x02 /* START_PROP                                                                                                                                                                */,\
  0x00 /* INT_CTL_MODEM_ENABLE,RSSI_LATCH_EN[7],POSTAMBLE_DETECT_EN[6],INVALID_SYNC_EN[5],RSSI_JUMP_EN[4],RSSI_EN[3],INVALID_PREAMBLE_EN[2],PREAMBLE_DETECT_EN[1],SYNC_DETECT_EN[0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_MODEM_ENABLE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_CHIP_ENABLE { \
  0x11 /* CMD: Set property                                                                                                                              */,\
  0x01 /* GROUP: Int ctl                                                                                                                                 */,\
  0x01 /* NUM_PROPS                                                                                                                                      */,\
  0x03 /* START_PROP                                                                                                                                     */,\
  0x20 /* INT_CTL_CHIP_ENABLE,CAL_EN[6],FIFO_UNDERFLOW_OVERFLOW_ERROR_EN[5],STATE_CHANGE_EN[4],CMD_ERROR_EN[3],CHIP_READY_EN[2],LOW_BATT_EN[1],WUT_EN[0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_INT_CTL_CHIP_ENABLE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_A_MODE { \
  0x11 /* CMD: Set property              */,\
  0x02 /* GROUP: Frr ctl                 */,\
  0x01 /* NUM_PROPS                      */,\
  0x00 /* START_PROP                     */,\
  0x01 /* FRR_CTL_A_MODE,FRR_A_MODE[7:0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_A_MODE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_B_MODE { \
  0x11 /* CMD: Set property              */,\
  0x02 /* GROUP: Frr ctl                 */,\
  0x01 /* NUM_PROPS                      */,\
  0x01 /* START_PROP                     */,\
  0x02 /* FRR_CTL_B_MODE,FRR_B_MODE[7:0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_B_MODE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_C_MODE { \
  0x11 /* CMD: Set property              */,\
  0x02 /* GROUP: Frr ctl                 */,\
  0x01 /* NUM_PROPS                      */,\
  0x02 /* START_PROP                     */,\
  0x09 /* FRR_CTL_C_MODE,FRR_C_MODE[7:0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_C_MODE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_D_MODE { \
  0x11 /* CMD: Set property              */,\
  0x02 /* GROUP: Frr ctl                 */,\
  0x01 /* NUM_PROPS                      */,\
  0x03 /* START_PROP                     */,\
  0x00 /* FRR_CTL_D_MODE,FRR_D_MODE[7:0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_FRR_CTL_D_MODE_LEN (5)


#define RADIO_CONFIG_SET_PROPERTY_EZCONFIG_XO_TUNE { \
  0x11 /* CMD: Set property                */,\
  0x24 /* GROUP: Ezconfig                  */,\
  0x01 /* NUM_PROPS                        */,\
  0x03 /* START_PROP                       */,\
  0x45 /* EZCONFIG_XO_TUNE,TUNE_VALUE[6:0] */\
}

#define RADIO_CONFIG_SET_PROPERTY_EZCONFIG_XO_TUNE_LEN (5)


#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_0 { \
  0x66 /* CMD: Ezconfig array write */,\
  0x74 /* DATA0                     */,\
  0x3C /* DATA1                     */,\
  0x08 /* DATA3                     */,\
  0x3D /* DATA4                     */,\
  0x34 /* DATA5                     */,\
  0x5E /* DATA6                     */,\
  0x76 /* DATA7                     */,\
  0x96 /* DATA8                     */,\
  0xBE /* DATA9                     */,\
  0xF4 /* DATA10                    */,\
  0x9F /* DATA11                    */,\
  0x67 /* DATA12                    */,\
  0xC6 /* DATA13                    */,\
  0x70 /* DATA14                    */,\
  0x66 /* DATA15                    */,\
  0xD0 /* DATA16                    */,\
  0x4A /* DATA17                    */,\
  0x55 /* DATA18                    */,\
  0x6B /* DATA19                    */,\
  0xBF /* DATA20                    */,\
  0xA3 /* DATA21                    */,\
  0x50 /* DATA22                    */,\
  0x01 /* DATA23                    */,\
  0x83 /* DATA24                    */,\
  0xC2 /* DATA25                    */,\
  0x02 /* DATA26                    */,\
  0xAA /* DATA27                    */,\
  0xE2 /* DATA28                    */,\
  0x4B /* DATA29                    */,\
  0x6B /* DATA30                    */,\
  0xEA /* DATA31                    */,\
  0x20 /* DATA32                    */,\
  0x4C /* DATA33                    */,\
  0x6C /* DATA34                    */,\
  0x1D /* DATA35                    */,\
  0x8A /* DATA36                    */,\
  0x23 /* DATA37                    */,\
  0xDB /* DATA38                    */,\
  0xF2 /* DATA39                    */,\
  0x9C /* DATA40                    */,\
  0x9B /* DATA41                    */,\
  0x68 /* DATA42                    */,\
  0x0C /* DATA43                    */,\
  0x9D /* DATA44                    */,\
  0x11 /* DATA45                    */,\
  0xE4 /* DATA46                    */,\
  0xA2 /* DATA47                    */,\
  0x3C /* DATA48                    */,\
  0x95 /* DATA49                    */,\
  0xF1 /* DATA50                    */,\
  0xF2 /* DATA51                    */,\
  0x86 /* DATA52                    */,\
  0x5D /* DATA53                    */,\
  0x1B /* DATA54                    */,\
  0xBF /* DATA55                    */,\
  0x22 /* DATA56                    */,\
  0x1B /* DATA57                    */,\
  0x84 /* DATA58                    */,\
  0x6F /* DATA59                    */,\
  0x34 /* DATA60                    */,\
  0x21 /* DATA61                    */,\
  0x3C /* DATA62                    */,\
  0x7B /* DATA63                    */,\
  0x6F /* DATA64                    */,\
  0xB7 /* DATA65                    */,\
  0xBD /* DATA66                    */,\
  0xF3 /* DATA67                    */,\
  0xFB /* DATA68                    */,\
  0x3B /* DATA69                    */,\
  0x89 /* DATA70                    */,\
  0xA6 /* DATA71                    */,\
  0x4D /* DATA72                    */,\
  0xDF /* DATA73                    */,\
  0x68 /* DATA74                    */,\
  0x1E /* DATA75                    */,\
  0xD7 /* DATA76                    */,\
  0xBB /* DATA77                    */,\
  0x35 /* DATA78                    */,\
  0x0E /* DATA79                    */,\
  0xC1 /* DATA80                    */,\
  0xA9 /* DATA81                    */,\
  0x7B /* DATA82                    */,\
  0xCB /* DATA83                    */,\
  0x09 /* DATA84                    */,\
  0x3E /* DATA85                    */,\
  0xEC /* DATA86                    */,\
  0xC9 /* DATA87                    */,\
  0x79 /* DATA88                    */,\
  0x4F /* DATA89                    */,\
  0x91 /* DATA90                    */,\
  0x4E /* DATA91                    */,\
  0x1A /* DATA92                    */,\
  0xE3 /* DATA93                    */,\
  0xB2 /* DATA94                    */,\
  0x20 /* DATA95                    */,\
  0xC0 /* DATA96                    */,\
  0xFE /* DATA97                    */,\
  0x20 /* DATA98                    */,\
  0x81 /* DATA99                    */,\
  0x03 /* DATA100                   */,\
  0x2F /* DATA101                   */,\
  0xCB /* DATA102                   */,\
  0x77 /* DATA103                   */,\
  0x11 /* DATA104                   */,\
  0xA7 /* DATA105                   */,\
  0x4F /* DATA106                   */\
}

#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_0_LEN (107)


#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_NOP_0 { \
  0x00 /* CMD: Nop */\
}

#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_NOP_0_LEN (1)


#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_1 { \
  0x66 /* CMD: Ezconfig array write */,\
  0x2A /* DATA0                     */,\
  0xFF /* DATA1                     */,\
  0x83 /* DATA3                     */,\
  0x87 /* DATA4                     */,\
  0xDC /* DATA5                     */,\
  0xD5 /* DATA6                     */,\
  0x2C /* DATA7                     */,\
  0x12 /* DATA8                     */,\
  0xE3 /* DATA9                     */,\
  0x2A /* DATA10                    */,\
  0x2A /* DATA11                    */,\
  0x61 /* DATA12                    */,\
  0x45 /* DATA13                    */,\
  0x53 /* DATA14                    */,\
  0x84 /* DATA15                    */,\
  0xC0 /* DATA16                    */,\
  0xBB /* DATA17                    */,\
  0x4C /* DATA18                    */,\
  0xBB /* DATA19                    */,\
  0x3D /* DATA20                    */,\
  0x0F /* DATA21                    */,\
  0x7C /* DATA22                    */,\
  0x4D /* DATA23                    */,\
  0xFE /* DATA24                    */,\
  0x84 /* DATA25                    */,\
  0x51 /* DATA26                    */,\
  0x00 /* DATA27                    */,\
  0x0D /* DATA28                    */,\
  0x04 /* DATA29                    */,\
  0x73 /* DATA30                    */,\
  0xEC /* DATA31                    */,\
  0x79 /* DATA32                    */,\
  0x3E /* DATA33                    */,\
  0x15 /* DATA34                    */,\
  0x24 /* DATA35                    */,\
  0xB9 /* DATA36                    */,\
  0x77 /* DATA37                    */,\
  0x2F /* DATA38                    */,\
  0x74 /* DATA39                    */,\
  0xC4 /* DATA40                    */,\
  0x98 /* DATA41                    */,\
  0x84 /* DATA42                    */,\
  0x81 /* DATA43                    */,\
  0xD1 /* DATA44                    */,\
  0xCA /* DATA45                    */,\
  0xED /* DATA46                    */,\
  0xC7 /* DATA47                    */,\
  0x01 /* DATA48                    */,\
  0xB7 /* DATA49                    */,\
  0x19 /* DATA50                    */,\
  0x16 /* DATA51                    */,\
  0x29 /* DATA52                    */,\
  0xA0 /* DATA53                    */,\
  0x90 /* DATA54                    */,\
  0x67 /* DATA55                    */,\
  0x09 /* DATA56                    */,\
  0xE0 /* DATA57                    */,\
  0x35 /* DATA58                    */,\
  0x0C /* DATA59                    */,\
  0x9B /* DATA60                    */,\
  0x56 /* DATA61                    */,\
  0x01 /* DATA62                    */,\
  0x0A /* DATA63                    */,\
  0x17 /* DATA64                    */,\
  0x6C /* DATA65                    */,\
  0x40 /* DATA66                    */,\
  0x13 /* DATA67                    */,\
  0xE2 /* DATA68                    */,\
  0x0B /* DATA69                    */,\
  0xD6 /* DATA70                    */,\
  0x36 /* DATA71                    */,\
  0x47 /* DATA72                    */,\
  0x0B /* DATA73                    */,\
  0x08 /* DATA74                    */,\
  0xF8 /* DATA75                    */,\
  0x2B /* DATA76                    */,\
  0xC4 /* DATA77                    */,\
  0xCB /* DATA78                    */,\
  0xD3 /* DATA79                    */,\
  0x52 /* DATA80                    */,\
  0x2D /* DATA81                    */,\
  0xA7 /* DATA82                    */,\
  0xCE /* DATA83                    */,\
  0x7D /* DATA84                    */,\
  0x8E /* DATA85                    */,\
  0x85 /* DATA86                    */,\
  0xC8 /* DATA87                    */,\
  0xAF /* DATA88                    */,\
  0x76 /* DATA89                    */,\
  0x75 /* DATA90                    */,\
  0xFB /* DATA91                    */,\
  0x26 /* DATA92                    */,\
  0xEF /* DATA93                    */,\
  0x15 /* DATA94                    */,\
  0xE7 /* DATA95                    */,\
  0x22 /* DATA96                    */,\
  0xBA /* DATA97                    */,\
  0xEB /* DATA98                    */,\
  0x30 /* DATA99                    */,\
  0x8D /* DATA100                   */,\
  0x6F /* DATA101                   */,\
  0xE1 /* DATA102                   */,\
  0xBC /* DATA103                   */,\
  0xC8 /* DATA104                   */,\
  0x5F /* DATA105                   */,\
  0xD2 /* DATA106                   */\
}

#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_1_LEN (107)


#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_NOP_1 { \
  0x00 /* CMD: Nop */\
}

#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_NOP_1_LEN (1)


#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_2 { \
  0x66 /* CMD: Ezconfig array write */,\
  0xD7 /* DATA0                     */,\
  0x1B /* DATA1                     */,\
  0x67 /* DATA3                     */,\
  0xBA /* DATA4                     */,\
  0x34 /* DATA5                     */,\
  0x2F /* DATA6                     */,\
  0x72 /* DATA7                     */,\
  0x28 /* DATA8                     */,\
  0x20 /* DATA9                     */,\
  0xC6 /* DATA10                    */,\
  0x48 /* DATA11                    */,\
  0x9F /* DATA12                    */\
}

#define RADIO_CONFIG_EZCONFIG_ARRAY_WRITE_2_LEN (13)


#define RADIO_CONFIG_EZCONFIG_CHECK { \
  0x19 /* CMD: Ezconfig check                  */,\
  0x17 /* CHECKSUM,CHECKSUM[7:0],CHECKSUM[7:0] */,\
  0x76 /*                                      */\
}

#define RADIO_CONFIG_EZCONFIG_CHECK_LEN (3)


#define RADIO_CONFIG_GPIO_PIN_CFG { \
  0x13 /* CMD: Gpio pin cfg                */,\
  0x1D /* GPIO0,PULL_CTL[6],GPIO_MODE[5:0] */,\
  0x1D /* GPIO1,PULL_CTL[6],GPIO_MODE[5:0] */,\
  0x20 /* GPIO2,PULL_CTL[6],GPIO_MODE[5:0] */,\
  0x21 /* GPIO3,PULL_CTL[6],GPIO_MODE[5:0] */,\
  0x00 /* NIRQ,PULL_CTL[6],NIRQ_MODE[5:0]  */,\
  0x00 /* SDO,PULL_CTL[6],SDO_MODE[5:0]    */,\
  0x00 /* GEN_CONFIG,DRV_STRENGTH[6:5]     */\
}

#define RADIO_CONFIG_GPIO_PIN_CFG_LEN (8)


#define RADIO_CONFIG_COUNT (17)


#endif // __SLAB_RADIO_CONFIG__


//        _  _                          
//       | )/ )         Wireless        
//    \\ |//,' __       Application     
//    (")(_)-"()))=-    Software        
//       (\\            Platform        
