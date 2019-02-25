/**
 * @brief   This for STM32 device retarget printf func to ITM/SWV, Semihost or UART
 *
 * @file    retarget.c
 * @author  bryan
 * @date    2018-07-12
 * @note
 *    There three type retarget according to macro define
 *  - RETARGET_ITM
 *
 *  - RETARGET_SEMIHOST
 *    + Add '-specs=rdimon.specs -lc -lrdimon' to link option
 *    + if want using %f with printf(), add '-u _scanf_float -u _printf_float'
 *      link option
 *
 *  - RETARGET_UART
 *    + Add UART handler
 *    + Remove '-specs=rdimon.specs -lc -lrdimon' link option
 *    + if want using %f with printf(), add '-u _scanf_float -u _printf_float'
 *      link option
 *    When using printf, remember to
 *    fflush(stdout); // This will flush any pending printf output
 *    or using retarget_disable_buffer()
 *    So you don't need to add "\n"
 */

#include "stm32f4xx_hal.h"
#include <stdio.h>

#define RETARGET_UART

#ifdef RETARGET_SEMIHOST
extern void initialise_monitor_handles(void);
#endif

#ifdef RETARGET_UART
extern UART_HandleTypeDef huart1;
#endif

#ifdef RETARGET_ITM

#endif

void retarget_init()
{
#ifdef RETARGET_SEMIHOST
  initialise_monitor_handles();
#endif
}

/**
 * @brief Write "len" of char from "ptr" to file id "fd", Return number of char written.
 *
 * @details
 *    1- When using semihost mode, don't implement this _write func
 * */
#ifndef RETARGET_SEMIHOST
int _write (int fd, char *ptr, int len)
{
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {

#ifdef RETARGET_UART
	HAL_UART_Transmit(&huart1, ptr++, 1, 0xFFFF);
#endif

#ifdef RETARGET_ITM
	// the implementation of ITM_SendChar  is provided in CMSIS package.
	ITM_SendChar(*ptr++);
#endif
  }

  return len;
}
#endif

//
//int _read (int fd, char *ptr, int len)
//{
//  /* Read "len" of char to "ptr" from file id "fd"
//   * Return number of char read.
//   * Need implementing with UART here. */
//  return len;
//}
//
//void _ttywrch(int ch) {
//  /* Write one char "ch" to the default console
//   * Need implementing with UART here. */
//}

/** @brief  disable I/O buffer for printf
 *  @parm   None
 *  @retval None
 *  @note   Disable I/O buffering for stdout stream
 *          so that chars are sent out as soon as
 *          they are printed
 */
void retarget_disable_buffer(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
}

