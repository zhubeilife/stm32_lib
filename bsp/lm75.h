/**
  * @file       lm75.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @copyright  Dorabot Inc.
  * @brief      This file is general header file of lm75.h .
  * @details
  */

#ifndef __LM75_H_
#define __LM75_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"

/**
 * @verbatim
 * Register Functions
 *
 * RegisterName------ADDRESS------PORSTATE(hex)------PORSTATE(bin)------READ/WRITE
 * Temperature	       0x00        	0x000(X)	 	     0000 0000 0XXX XXX 	Read only
 * Configuration       0x01	   		  0x00          	 0000 0000		        R/W
 * Thyst	       	     0x02         0x4b0(X)      	 0100 1011 0XXX XXX 	R/W
 * Tos                 0x03         0x500(X)       	 0101 0000 0XXX XXX	  R/W
 *
 * NOTE:
 * 	X here means Don't care
 * @endverbatim
 */

#define LM75_REG_TEMP                 0x00 	/**< Register: Temperature */
#define LM75_REG_CONF                 0x01 	/**< Register: Configuration */
#define LM75_REG_THYS                 0x02 	/**< Register: Hysteresis */
#define LM75_REG_TOS                  0x03 	/**< Register: Overtemperature shutdown */


// Conversion_Mode_Selection
#define STLM75_CONTINUOUS_MODE                  ((uint8_t)0x00)  /**< Conversion continue mode */
#define STLM75_ONE_SHOT_MODE                    ((uint8_t)0x01)  /**< Conversion one shot mode */

// Operation_Mode
#define STLM75_COMPARATOR_MODE                  ((uint8_t)0x00)  /**< Operation compare mode */
#define STLM75_INTERRUPT_MODE                   ((uint8_t)0x02)  /**< Operation interrupt mode */

/* Maximum number of trials use for STLM75_IsReady function */
#define LM75_ISREADY_MAX_TRIALS      15  /**< max trials times for check whether lm75 is ready */
#define LM75_ISREADY_TIMEOUT         50  /**< timeout for checking whether lm75 is ready */
#define LM75_READ_MAX_TRIALS	       10  /**< max trials for every reading */

/**
 * @brief sensor state typedef
 */
typedef enum
{
  TSENSOR_OK 	  = 0,  /**< sensor is ok */
  TSENSOR_ERROR	= 1   /**< something is wrong with the sensor */
}TSENSOR_Status_TypDef;

/**
 * @brief init lm75
 *
 * @param DeviceAddr
 * @return TSENSOR_Status_TypDef indicates the sensor is Ok or not
 */
TSENSOR_Status_TypDef lm75_init(uint16_t DeviceAddr);
/**
 * @brief  Get sensor reading once
 * @param  [in]  DeviceAddr sensor address
 * @param  [out] raw_temp raw temp data
 * @retval value(0)  success to get sensor data
 * @retval value(-1) fail to get sensor data
 */
int8_t STLM75_ReadTemp(uint16_t DeviceAddr, uint16_t* raw_temp);

#ifdef __cplusplus
}
#endif

#endif // end of __LM75_H_
