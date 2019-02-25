/**
  * @file       tle8108.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @copyright  Dorabot Inc.
  * @brief      This file is general header file of tle8108.h .
  * @details
  */

#ifndef __TLE8108EM_H_
#define __TLE8108EM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "main.h"
#include "spi.h"

#define SPI2_CS_SET   HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET)
#define SPI2_CS_RESET HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET)
#define SPI2_RST_SET   HAL_GPIO_WritePin(SPI2_RST_GPIO_Port, SPI2_RST_Pin, GPIO_PIN_SET)
#define SPI2_RST_RESET HAL_GPIO_WritePin(SPI2_RST_GPIO_Port, SPI2_RST_Pin, GPIO_PIN_RESET)

typedef union _spi_status
{
  uint16_t spi_switch_status;
  /**
   * Because STM32 is little endian
   * So spi_switch_buffer[0] is low 8 bits
   * */
  uint8_t spi_switch_buffer[2];
} _spi_status;

extern volatile _spi_status Tx_spi_status;
extern volatile _spi_status Rx_spi_status;

/**
 * @brief init tle8108 chip
 */
void tle8108em_init (void);
/**
 * @brief turn all tle 8108 pins on
 */
void tle8108em_turn_all_on (void);
/**
 * @brief turn all tle8108 pins off
 */
void tle8108em_turn_all_off (void);
/**
 * @brief change specified bit status
 *
 * @param bit which bits you want to change
 * @param status
 *              - OUT_ON
 *              - OUT_OFF
 */
void tle8108em_write_bit (uint8_t bit, uint8_t status);
/**
 * @brief change all bins state according to input new_state
 */
void tle8108em_write_all (uint16_t new_state);

#define OUT_ON    0x02  /**< bit set on */
#define OUT_OFF   0x03  /**< bit set off */

#define OUT1_ON     tle8108em_write_bit(5, OUT_ON)
#define OUT2_ON     tle8108em_write_bit(6, OUT_ON)
#define OUT3_ON     tle8108em_write_bit(7, OUT_ON)
#define OUT4_ON     tle8108em_write_bit(8, OUT_ON)
#define OUT5_ON     tle8108em_write_bit(1, OUT_ON)
#define OUT6_ON     tle8108em_write_bit(2, OUT_ON)
#define OUT7_ON     tle8108em_write_bit(3, OUT_ON)
#define OUT8_ON     tle8108em_write_bit(4, OUT_ON)

#define OUT1_OFF    tle8108em_write_bit(5, OUT_OFF)
#define OUT2_OFF    tle8108em_write_bit(6, OUT_OFF)
#define OUT3_OFF    tle8108em_write_bit(7, OUT_OFF)
#define OUT4_OFF    tle8108em_write_bit(8, OUT_OFF)
#define OUT5_OFF    tle8108em_write_bit(1, OUT_OFF)
#define OUT6_OFF    tle8108em_write_bit(2, OUT_OFF)
#define OUT7_OFF    tle8108em_write_bit(3, OUT_OFF)
#define OUT8_OFF    tle8108em_write_bit(4, OUT_OFF)

/**
 * @verbatim
 *
 *    (Device)                  (STATE)
 * Vacuum_Pump_FixedSide     OFF  |   ON   | BLOW
 * Vacuum_Pump_MovableSide   OFF  |   ON   | BLOW
 * Cylinder                  OFF  | EXTEND | RETRACT
 * Needle_Cylinder_Limit     LOCK | UNLOCK
 *
 * @endverbatim
 * */
#define Vacuum_Pump_ON          do { OUT3_OFF; OUT4_ON;  OUT5_OFF; OUT6_ON;  } while(0)
#define Vacuum_Pump_OFF         do { OUT3_OFF; OUT4_OFF; OUT5_OFF; OUT6_OFF; } while(0)
#define Vacuum_Pump_BLOW        do { OUT3_ON;  OUT4_OFF; OUT5_ON;  OUT6_OFF; } while(0)

#define Vacuum_Pump_Fixedside_ON    do { OUT3_OFF; OUT4_ON;  } while(0)
#define Vacuum_Pump_Fixedside_OFF   do { OUT3_OFF; OUT4_OFF; } while(0)
#define Vacuum_Pump_Fixedside_BLOW  do { OUT3_ON;  OUT4_OFF; } while(0)

#define Vacuum_Pump_Movableside_ON    do { OUT5_OFF; OUT6_ON;  } while(0)
#define Vacuum_Pump_Movableside_OFF   do { OUT5_OFF; OUT6_OFF; } while(0)
#define Vacuum_Pump_Movableside_BLOW  do { OUT5_ON;  OUT6_OFF; } while(0)

#define Cylinder_OFF                  do { OUT1_OFF; OUT2_OFF; } while(0)
#define Cylinder_EXTEND               do { OUT1_ON;  OUT2_OFF; } while(0)
#define Cylinder_RETRACT              do { OUT1_OFF; OUT2_ON; } while(0)

#define Needle_Cylinder_Limit_LOCK    do {  } while(0)
#define Needle_Cylinder_Limit_UNLOCK  do {  } while(0)

#ifdef __cplusplus
}
#endif

#endif // end of __TLE8108EM_H_
