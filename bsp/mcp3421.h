/**
  * @file       mcp3421.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @copyright  Dorabot Inc.
  * @brief      This file is general header file of mcp3421.h .
  * @details
  */

#ifndef __MCP3421_H_
#define __MCP3421_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

/**
 * @brief read sensor return state
 */
typedef enum return_state
{
  RETURN_OK     = 0,  /**< sucess get sensor reading */
  RETURN_ERROR        /**< fails to get sensor reading */
}return_state_t;

/**< Read date MAX Retry time */
#define MCP3421_MAX_RETRY_TIMES         0x0A

/**< MCP3421 device address */
#define MCP3421_DEVICE_ADDRESS      0b11010000

/**< Position of the Ready Bit */
#define MCP3421_READY_BIT               (1 << 7)
/**< Position of the Convertion Mode Bit */
#define MCP3421_CONVERTION_MODE         (1 << 4)
/**< Position of the Sample Rate Bits */
#define MCP3421_SAMPLE_RATE             (3 << 2)
/**< Position of the Gain Selection Bits */
#define MCP3421_GAIN_SELECTION          (3 << 0)

/**< Sets the ADC to 240 samples per second (12 bits of resolution) */
#define MCP3421_SAMPLE_RATE_240_SPS           0b00
/**< Sets the ADC to 60 samples per second (14 bits of resolution) */
#define MCP3421_SAMPLE_RATE_60_SPS            0b01
/**< Sets the ADC to 15 samples per second (16 bits of resolution) */
#define MCP3421_SAMPLE_RATE_15_SPS            0b10
/**< Sets the ADC to 3.75 samples per second (18 bits of resolution) */
#define MCP3421_SAMPLE_RATE_3_75_SPS          0b11

/**<  Mask Sets the ADC to 240 samples per second (12 bits of resolution) */
#define MCP3421_SAMPLE_RATE_240_SPS_MASK     0x7ff
/**<  Mask Sets the ADC to 60 samples per second (14 bits of resolution) */
#define MCP3421_SAMPLE_RATE_60_SPS_MASK      0x1fff
/**<  Mask Sets the ADC to 15 samples per second (16 bits of resolution) */
#define MCP3421_SAMPLE_RATE_15_SPS_MASK      0x7fff
/**<  Mask Sets the ADC to 3.75 samples per second (18 bits of resolution) */
#define MCP3421_SAMPLE_RATE_3_75_SPS_MASK    0x1ffff

/**< Sets the gain of the PGA to 1 */
#define MCP3421_GAIN_1                  0b00
/**< Sets the gain of the PGA to 2 */
#define MCP3421_GAIN_2                  0b01
/**< Sets the gain of the PGA to 4 */
#define MCP3421_GAIN_4                  0b10
/**< Sets the gain of the PGA to 8 */
#define MCP3421_GAIN_8                  0b11

/**< Indentifies if the convertion is completed. */
#define MCP3421_CONVERTION_READY        0
/**< Indentifies if the convertion is in action. */
#define MCP3421_CONVERTION_NOT_READY    1
/**<  Value will make no effect with One-Shot Conversion Mode */
#define MCP3421_CONVERTION_NO_EFFECT    0
/**< Value to initiate a new convertion on the ReadyBit if One-Shot mode is selected. */
#define MCP3421_INITIATE_CONVERTION     1
/**< Sets the ADC to continuous convertion mode.*/
#define MCP3421_MODE_CONTINUOUS         1
/**< Sets the ADC to One-Shot mode, convertion are asked by the user. */
#define MCP3421_MODE_ONE_SHOT           0
/**< Identifies that output register is updated with the lastest convertion. */
#define MCP3421_VALUE_IS_UPDATED        0
/**< Identifies that output register is not updated with the lastest convertion. */
#define MCP3421_VALUE_IS_NOT_UPDATED    1

/**< Value of the LSB for 12 bits of resolution. */
#define MCP3421_LSB_12BITS              (1E-3)
/**< Value of the LSB for 14 bits of resolution. */
#define MCP3421_LSB_14BITS              (250E-6)
/**< Value of the LSB for 16 bits of resolution. */
#define MCP3421_LSB_16BITS              (62.5E-6)
/**< Value of the LSB for 18 bits of resolution. */
#define MCP3421_LSB_18BITS              (15.625E-6)

/**< Decimal absolute value of the gain selected for formula use, this case 1 */
#define MCP3421_GAIN_1_VALUE            1
/**< Decimal absolute value of the gain selected for formula use, this case 2 */
#define MCP3421_GAIN_2_VALUE            2
/**< Decimal absolute value of the gain selected for formula use, this case 4 */
#define MCP3421_GAIN_4_VALUE            4
/**< Decimal absolute value of the gain selected for formula use, this case 8 */
#define MCP3421_GAIN_8_VALUE            8

/**
 * @brief Structure of the internal configuration register
 *
 */
typedef union
{
  unsigned char byte;  /**< Byte of the present configuration*/

  struct
  {
    /**< PGA Gain Selection Bits*/
    unsigned char PGAGainSelectionBits : 2;
    /**< Sample Rate Selection Bit*/
    unsigned char SampleRateSelectionBits : 2;
    /**< Conversion Mode Bit*/
    unsigned char ConvertionModeBit : 1;
    unsigned char : 2;
    /**< Ready Bit*/
    unsigned char ReadyBit : 1;
  };
  /**< MCP3421 Configuration Register Format*/
} MCP3421ConfigurationRegister;

/**
 * @verbatim
 * Data Format
 *
 * Conversion Option  Digital Output Codes
 *
 * 18-bits  MMMMMMD17D16 (1st data byte) - D15 ~ D8 (2nd data byte) - D7 ~ D0 (3rd data byte) - Configuration byte. (Note 1)
 * 16-bits  D15 ~ D8 (1st data byte) - D7 ~ D0 (2nd data byte) - Configuration byte. (Note 2)
 * 14-bits  MMD13D ~ D8 (1st data byte) - D7 ~ D0 (2nd data byte) - Configuration byte. (Note 3)
 * 12-bits  MMMMD11 ~ D8 (1st data byte) - D7 ~ D0 (2nd data byte) - Configuration byte. (Note 4)
 *
 * Note
 *      1: D17 is MSB (= sign bit), M is repeated MSB of the data byte.
 *      2: D15 is MSB (= sign bit).
 *      3: D13 is MSB (= sign bit), M is repeated MSB of the data byte.
 *      4: D11 is MSB (= sign bit), M is repeated MSB of the data byte.
 * @endverbatim
 */

/**
 * @brief Union to simplify the convertion of the values. From the bytes retrieved by
 *        the MCP3421 is
 * @note
 *        - for 18bits   Upper Middle Lower Configuration
 *        - for others   Middle Lower Configuration
 */
typedef union
{
  /**< Value retrieved from the ADC signed.*/
  int32_t value;

  struct
  {
    /**< Lower data byte from the ADC*/
    unsigned char upper;
    /**< Middle data byte from the ADC*/
    unsigned char middle;
    /**< Upper data byte  from the ADC*/
    unsigned char lower;

    /**<  Configurate byte*/
    MCP3421ConfigurationRegister config;
  };
  /**< MCP3421 Data Format*/
} MCP3421Data;

/**
 * @brief init mcp3421
 * @return return_state_t
 */
return_state_t mcp3421_init (void);
/**
 * @brief   Sends a command to the MCP3421 to initiate a new convertion.
 * @details  One-Shot convertion must be configured.
 *           In continuous mode this funtion as no effect on the ADC.
 */
void MCP3421InitiateConvertion (void);
/**
 * @brief Sets the MCP3421 convertion mode to Continuous convertion mode.
 */
void MCP3421SetConvertionModeContinuous (void);
/**
 * @brief Sets the MCP3421 convertion mode to One-Shot mode.
 */
void MCP3421SetConvertionModeOneShot (void);
/**
 * @brief Sets the convertion rate on the MCP3421.
 * @param value Value to select the convertion rate.
 * @note  Must select one of the following values:
 *          #MCP3421_SAMPLE_RATE_240_SPS ,
 *          #MCP3421_SAMPLE_RATE_60_SPS ,
 *          #MCP3421_SAMPLE_RATE_15_SPS and
 *          #MCP3421_SAMPLE_RATE_3_75_SPS.
 */
void MCP3421SetConvertionRate (unsigned char value);
/**
 * @brief Sets the gain of the internal PGA.
 * @param value Value to select the gain internally.
 * @note  Must select one of the following values:
 *          #MCP3421_GAIN_1,
 *          #MCP3421_GAIN_2,
 *          #MCP3421_GAIN_4 and
 *          #MCP3421_GAIN_8.
 */
void MCP3421SetPGAGain (unsigned char value);
/**
 * @brief  This funtion gets the value from the ADC. The funtion as blocking properties,
 *         if the convertion is not completed the device is continuous asked if the
 *         convertion is completed. When is completed the value in volts is returned.
 * @parm   [out] return_date return data pointer
 * @return return_state_t
 */
return_state_t MCP3421GetValue (float *return_data);
/**
 * @brief delay some time to read the data according to the sample rate
 */
void MCP3421GetDateDelay(void);

#ifdef __cplusplus
}
#endif

#endif // end of __MCP3421_H_
