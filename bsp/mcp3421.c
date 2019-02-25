#include "bsp/mcp3421.h"
#include "i2c.h"
#include "string.h"
#include "main.h"

static double lsb    = MCP3421_LSB_12BITS;
static char   gain   = MCP3421_GAIN_1_VALUE;
static MCP3421ConfigurationRegister configuration;

double get_lsb(void)
{
  switch(configuration.SampleRateSelectionBits)
  {
    case MCP3421_SAMPLE_RATE_3_75_SPS:
      return MCP3421_LSB_18BITS;
      break;
    case MCP3421_SAMPLE_RATE_15_SPS:
      return MCP3421_LSB_16BITS;
      break;
    case MCP3421_SAMPLE_RATE_60_SPS:
      return MCP3421_LSB_14BITS;
      break;
    case MCP3421_SAMPLE_RATE_240_SPS:
      return MCP3421_LSB_12BITS;
      break;
    default:
      return 0.0;
      break;
  }
}

char get_gain(void)
{
  switch(configuration.PGAGainSelectionBits)
  {
    case MCP3421_GAIN_1:
      return MCP3421_GAIN_1_VALUE;
      break;
    case MCP3421_GAIN_2:
      return MCP3421_GAIN_2_VALUE;
      break;
    case MCP3421_GAIN_4:
      return MCP3421_GAIN_4_VALUE;
      break;
    case MCP3421_GAIN_8:
      return MCP3421_GAIN_8_VALUE;
      break;
    default:
      return 0;
      break;
  }
}


return_state_t mcp3421_init (void)
{
  // init IIC device
  MX_I2C2_Init();
  HAL_StatusTypeDef status;

  status = HAL_I2C_IsDeviceReady(&hi2c2, MCP3421_DEVICE_ADDRESS, 15, 50);

  if (status == HAL_OK)
  {
    puts("MCP3421 is ready");
  }
  else
  {
    puts("MCP3421 is not ready");
    printf("Error code is %u\n", status);

    return RETURN_ERROR;
  }

  configuration.PGAGainSelectionBits    = MCP3421_GAIN_1;
  configuration.SampleRateSelectionBits = MCP3421_SAMPLE_RATE_240_SPS;
  configuration.ConvertionModeBit       = MCP3421_MODE_ONE_SHOT;
  configuration.ReadyBit                = MCP3421_CONVERTION_NO_EFFECT;

  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);

  lsb = get_lsb();
  gain = get_gain();

  return RETURN_OK;
}

void MCP3421InitiateConvertion (void)
{
  configuration.ReadyBit = MCP3421_INITIATE_CONVERTION;
  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);
}

void MCP3421SetConvertionModeContinuous (void)
{
  configuration.ConvertionModeBit = MCP3421_MODE_CONTINUOUS;
  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);
}

void MCP3421SetConvertionModeOneShot (void)
{
  configuration.ConvertionModeBit = MCP3421_MODE_ONE_SHOT;
  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);
}

void MCP3421SetConvertionRate (unsigned char value)
{
  configuration.SampleRateSelectionBits = value;
  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);

  lsb = get_lsb();
}

void MCP3421SetPGAGain (unsigned char value)
{
  configuration.PGAGainSelectionBits = value;
  HAL_I2C_Master_Transmit (&hi2c2, MCP3421_DEVICE_ADDRESS, &configuration.byte, 1, 0xff);

  gain = get_gain();
}

/**
 * @brief Get the value sign
 */
int8_t get_sign (unsigned char data)
{
  if ((data & 0b10000000) == 0b10000000)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

uint32_t get_mask(void)
{
  switch(configuration.SampleRateSelectionBits)
  {
    case MCP3421_SAMPLE_RATE_3_75_SPS:
      return MCP3421_SAMPLE_RATE_3_75_SPS_MASK;
      break;
    case MCP3421_SAMPLE_RATE_15_SPS:
      return MCP3421_SAMPLE_RATE_15_SPS_MASK;
      break;
    case MCP3421_SAMPLE_RATE_60_SPS:
      return MCP3421_SAMPLE_RATE_60_SPS_MASK;
      break;
    case MCP3421_SAMPLE_RATE_240_SPS:
      return MCP3421_SAMPLE_RATE_240_SPS_MASK;
      break;
    default:
      return 0;
      break;
  }
}

int32_t get_raw_data (int8_t sign, MCP3421Data *data)
{
  int32_t  raw_data = 0;
  uint32_t temp     = 0;
  uint32_t mask     = get_mask();

  uint8_t * temp_pointer = &temp;
  *temp_pointer = data->lower;
  *(++temp_pointer) = data->middle;
  *(++temp_pointer) = data->upper;

  /* Get raw date according to setting */
  if (sign == 1)
  {
    raw_data = temp&mask;
  }
  else
  {
    temp = 0xff000000 | temp;
    temp = ~temp;
    temp += 1;
    raw_data = -temp;
  }

  return raw_data;
}

void MCP3421GetDateDelay(void)
{
  switch (configuration.SampleRateSelectionBits)
  {
    case MCP3421_SAMPLE_RATE_3_75_SPS:
      HAL_Delay(270);
      break;
    case MCP3421_SAMPLE_RATE_15_SPS:
      HAL_Delay(68);
      break;
    case MCP3421_SAMPLE_RATE_60_SPS:
      HAL_Delay(18);
      break;
    case MCP3421_SAMPLE_RATE_240_SPS:
      HAL_Delay(5);
      break;
    default:
      break;
  }
}

return_state_t MCP3421GetValue (float *return_data)
{
  float voltage    = 0.0;
  MCP3421Data data;
  data.config.ReadyBit = MCP3421_VALUE_IS_NOT_UPDATED;
  int8_t sign      = 1;
  int32_t raw_data = 0;
  uint8_t retry_times = 0;

  // the logic here is both I2C read return !HAL_OK or MCP3421_VALUE_IS_NOT_UPDATED
  // will let retry_times++;
  do
  {
    switch (configuration.SampleRateSelectionBits)
    {
      case MCP3421_SAMPLE_RATE_3_75_SPS:
        if (HAL_OK != HAL_I2C_Master_Receive (&hi2c2, MCP3421_DEVICE_ADDRESS, &data.upper, 4, 0xff))
        {
          retry_times++;
          data.config.ReadyBit = MCP3421_VALUE_IS_NOT_UPDATED;
          continue;
        }
        break;
      case MCP3421_SAMPLE_RATE_15_SPS:
      case MCP3421_SAMPLE_RATE_60_SPS:
      case MCP3421_SAMPLE_RATE_240_SPS:
        if (HAL_OK != HAL_I2C_Master_Receive (&hi2c2, MCP3421_DEVICE_ADDRESS, &data.middle, 3, 0xff))
        {
          retry_times++;
          data.config.ReadyBit = MCP3421_VALUE_IS_NOT_UPDATED;
          continue;
        }
        break;
      default:
        break;
    }

    retry_times++;
  }while ((data.config.ReadyBit == MCP3421_VALUE_IS_NOT_UPDATED) &&
          (retry_times <= MCP3421_MAX_RETRY_TIMES));

  if (retry_times > MCP3421_MAX_RETRY_TIMES)
  {
    return RETURN_ERROR;
  }


  switch (configuration.SampleRateSelectionBits)
  {
    case MCP3421_SAMPLE_RATE_3_75_SPS:
      sign = get_sign (data.upper);
      raw_data = get_raw_data (sign, &data);
      break;
    case MCP3421_SAMPLE_RATE_15_SPS:
    case MCP3421_SAMPLE_RATE_60_SPS:
    case MCP3421_SAMPLE_RATE_240_SPS:
      sign = get_sign (data.middle);
      if (sign == -1)
      {
        data.upper = 0xff;
      }
      else
      {
        data.upper = 0x00;
      }
      raw_data = get_raw_data (sign, &data);
      break;
    default:
      // puts("MCP3421GetValue is wrong!")
      break;
  }

  voltage = raw_data * (lsb / gain);

  *return_data = voltage;

  return RETURN_OK;
}
