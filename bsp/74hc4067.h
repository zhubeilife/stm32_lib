/**
  * @file       74hc4067.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @brief      This file is general header file of 74hc4067.h
  *             16-Channel Analog Multiplexer/Demultiplexer.
  * @details    This is for Loaing Lshape Gripper Version 1.
  *             We are using two chips of 74hc4067 to connect with
  *             32 channels.
  */

#ifndef _74HC4067_H_
#define _74HC4067_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "main.h"

/**
 * @defgroup 74hc4067EN  74hc4067 Enable pin
 * @brief    74hc4067 Enable pin with two chips
 * @{
 */

#define CD74HC_DISABLE_1     HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET)
#define CD74HC_ENABLE_1      HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET)
#define CD74HC_DISABLE_2     HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET)
#define CD74HC_ENABLE_2      HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET)

/** @} */  /* End of  74hc4067EN Group*/

/**
 * @defgroup AddressInputPin address input pins
 * @brief    74hc4067 address input pins
 * @{
 */

#define S0_H                 HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, GPIO_PIN_SET)
#define S0_L                 HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, GPIO_PIN_RESET)
#define S1_H                 HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, GPIO_PIN_SET)
#define S1_L                 HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, GPIO_PIN_RESET)
#define S2_H                 HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, GPIO_PIN_SET)
#define S2_L                 HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, GPIO_PIN_RESET)
#define S3_H                 HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, GPIO_PIN_SET)
#define S3_L                 HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, GPIO_PIN_RESET)

/** @} */  /* End of 74hc4067 address input pins groups */

/**
 * @brief  Init 74hc4067
 * @param  NONE
 * @return NONE
 */
void cd74hc4067_init (void);
/**
 * @brief select one channel
 * @param channel (0-31) the one needs to be selected
 */
void select_one_channel (uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif // end of _74HC4067_H_
