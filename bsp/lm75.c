#include "bsp/lm75.h"
#include "i2c.h"

/**
  * @brief  Reads one byte from the TSENSOR.
  * @param  DevAddress: Target device address
  * @param  pBuffer : pointer to the buffer that receives the data read from the TSENSOR.
  * @param  ReadAddr : TSENSOR's internal address to read from.
  * @param  Length: Number of data to read
  */
int8_t TSENSOR_IO_Read(uint16_t DevAddress, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t Length)
{
  //I2Cx_ReadBuffer(DevAddress, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Length);

  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&hi2c1, DevAddress, (uint16_t)ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, 50);

  /* Check the communication status */
  if(status != HAL_OK)
  {
	  return -1;
  }

  return 0;
}

/**
  * @brief  Writes one byte to the TSENSOR.
  * @param  DevAddress: Target device address
  * @param  pBuffer: Pointer to data buffer
  * @param  WriteAddr: TSENSOR's internal address to write to.
  * @param  Length: Number of data to write
  */
//void TSENSOR_IO_Write(uint16_t DevAddress, uint8_t* pBuffer, uint8_t WriteAddr, uint16_t Length)
//{
//  I2Cx_WriteBuffer(DevAddress, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Length);
//}

TSENSOR_Status_TypDef lm75_init(uint16_t DeviceAddr)
{
  if (HAL_I2C_IsDeviceReady(&hi2c1, DeviceAddr, LM75_ISREADY_MAX_TRIALS, LM75_ISREADY_TIMEOUT) == HAL_OK)
  {
    printf("Get %d OK\r\n", DeviceAddr);
    return TSENSOR_OK;
  }
  else
  {
    printf("Get %d FAIL\r\n", DeviceAddr);
    return TSENSOR_ERROR;
  }
}

/**
  * @brief  Read The Temperature Sensor Status
  * @param  DeviceAddr : Device ID address.
  * @retval Status
  */
uint8_t STLM75_ReadStatus(uint16_t DeviceAddr)
{
  uint8_t tmp = 0;

  /* Read Status register */
  TSENSOR_IO_Read(DeviceAddr, &tmp, LM75_REG_CONF, 1);

  /* Return Temperature Sensor Status */
  return (uint8_t)(tmp);
}

/**
  * @brief  Read ID address of STLM75
  * @param  DeviceAddr : Device ID address.
  * @retval ID name
  */
int8_t STLM75_ReadTemp(uint16_t DeviceAddr, uint16_t* raw_temp)
{
  uint16_t tempreg = 0;
  uint16_t tmp = 0;
  uint8_t i = 0;
  int8_t read_state = 0;

  while (i < LM75_READ_MAX_TRIALS)
  {
	 /* Read Temperature registers */
	 read_state = TSENSOR_IO_Read(DeviceAddr, (uint8_t*)(&tempreg), LM75_REG_TEMP, 2);

	 if (read_state == 0)
	 {
	   break;
	 }

	 i++;

	 if (i >= LM75_READ_MAX_TRIALS)
	 {
	   return -1;
	 }
  }

  tmp = ((tempreg & 0x00FF) << 8) | ((tempreg & 0xFF00) >> 8);
  tempreg = (((tmp & 0x7F80) >> 7) | (tmp & 0x8000));

  /* Return Temperature value */
  *raw_temp = tempreg;

  return 0;
}
