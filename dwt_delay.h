/**
  * @file       dwt_delay.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @copyright  Dorabot Inc.
  * @brief      This file is general header file of dwt_delay.h.
  * @details
  */

#ifndef INC_DWT_DELAY_H_
#define INC_DWT_DELAY_H_

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @brief init DWT uint
 */
void DWT_Init(void);
/**
 * @brief  Delays for amount of micro seconds
 * @param  micros: Number of microseconds for delay
 * @retval None
 */
void DWT_Delay(uint32_t micros);

#ifdef __cplusplus
}
#endif

#endif /* INC_DWT_DELAY_DWT_DELAY_H_ */
