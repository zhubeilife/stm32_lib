/**
  * @file       can_filter.h
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @brief      CAN Filter Set Example
  * @details    Get from <a href="https://blog.csdn.net/flydream0/article/details/52317532">blog</a>
  */

/**
 * @brief 32-bit identifier List mode
 */
static void CANFilterConfig_Scale32_IdList(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  // here we set two type id standard and extend
  uint32_t StdId =0x321;
  uint32_t ExtId =0x1800f001;

  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  // standard id
  sFilterConfig.FilterIdHigh = StdId<<5;
  sFilterConfig.FilterIdLow = 0|CAN_ID_STD;     // reset IDE bit
  // extend ID
  sFilterConfig.FilterMaskIdHigh = ((ExtId<<3)>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (ExtId<<3)&0xffff|CAN_ID_EXT;

  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief 16-bit identifier List mode
 */
static void CANFilterConfig_Scale16_IdList(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint32_t StdId1 =0x123;
  uint32_t StdId2 =0x124;
  uint32_t StdId3 =0x125;
  uint32_t StdId4 =0x126;


  sFilterConfig.FilterNumber = 1;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;

  sFilterConfig.FilterIdHigh = StdId1<<5;
  sFilterConfig.FilterIdLow = StdId2<<5;
  sFilterConfig.FilterMaskIdHigh = StdId3<<5;
  sFilterConfig.FilterMaskIdLow = StdId4<<5;

  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief 32-bit identifier Mask mode with standard
 */
static void CANFilterConfig_Scale32_IdMask_StandardIdOnly(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint16_t StdIdArray[10] ={0x7e0,0x7e1,0x7e2,0x7e3,0x7e4,
                            0x7e5,0x7e6,0x7e7,0x7e8,0x7e9};
  uint16_t      mask,num,tmp,i;

  sFilterConfig.FilterNumber = 2;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh =(StdIdArray[0]<<5);
  sFilterConfig.FilterIdLow =0;

  mask =0x7ff;
  num =sizeof(StdIdArray)/sizeof(StdIdArray[0]);
  for(i =0; i<num; i++)
  {
    tmp =StdIdArray[i] ^ (~StdIdArray[0]);
    mask &=tmp;
  }
  sFilterConfig.FilterMaskIdHigh =(mask<<5);
  sFilterConfig.FilterMaskIdLow =0|0x02; //Ö»œÓÊÕÊýŸÝÖ¡

  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief 32-bit identifier Mask mode with extend id
 */
static void CANFilterConfig_Scale32_IdMask_ExtendIdOnly(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint32_t ExtIdArray[10] ={0x1839f101,0x1835f102,0x1835f113,0x1835f124,0x1835f105,
                            0x1835f106,0x1835f107,0x1835f108,0x1835f109,0x1835f10A};
  uint32_t      mask,num,tmp,i;

  sFilterConfig.FilterNumber = 3;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh =((ExtIdArray[0]<<3) >>16) &0xffff;
  sFilterConfig.FilterIdLow =((ExtIdArray[0]<<3)&0xffff) | CAN_ID_EXT;

  mask =0x1fffffff;
  num =sizeof(ExtIdArray)/sizeof(ExtIdArray[0]);
  for(i =0; i<num; i++)
  {
    tmp =ExtIdArray[i] ^ (~ExtIdArray[0]);
    mask &=tmp;
  }
  mask <<=3;    //¶ÔÆëŒÄŽæÆ÷
  sFilterConfig.FilterMaskIdHigh = (mask>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (mask&0xffff)|0x02; //Ö»œÓÊÕÊýŸÝÖ¡
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
 * @brief 32-bit identifier Mask mode with extend and standard id
 */
static void CANFilterConfig_Scale32_IdMask_StandardId_ExtendId_Mix(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint32_t StdIdArray[10] ={0x711,0x712,0x713,0x714,0x715,
                          0x716,0x717,0x718,0x719,0x71a};
  uint32_t ExtIdArray[10] ={0x1900fAB1,0x1900fAB2,0x1900fAB3,0x1900fAB4,0x1900fAB5,
                            0x1900fAB6,0x1900fAB7,0x1900fAB8,0x1900fAB9,0x1900fABA};
  uint32_t      mask,num,tmp,i,standard_mask,extend_mask,mix_mask;

  sFilterConfig.FilterNumber = 4;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh =((ExtIdArray[0]<<3) >>16) &0xffff;
  sFilterConfig.FilterIdLow =((ExtIdArray[0]<<3)&0xffff);

  standard_mask =0x7ff;
  num =sizeof(StdIdArray)/sizeof(StdIdArray[0]);
  for(i =0; i<num; i++)
  {
    tmp =StdIdArray[i] ^ (~StdIdArray[0]);
    standard_mask &=tmp;
  }

  extend_mask =0x1fffffff;
  num =sizeof(ExtIdArray)/sizeof(ExtIdArray[0]);
  for(i =0; i<num; i++)
  {
    tmp =ExtIdArray[i] ^ (~ExtIdArray[0]);
    extend_mask &=tmp;
  }
  mix_mask =(StdIdArray[0]<<18)^ (~ExtIdArray[0]);
  mask =(standard_mask<<18)& extend_mask &mix_mask;
  mask <<=3;    //¶ÔÆëŒÄŽæÆ÷

  sFilterConfig.FilterMaskIdHigh = (mask>>16)&0xffff;
  sFilterConfig.FilterMaskIdLow = (mask&0xffff);
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief 16-bit identifier Mask mode
 */
static void CANFilterConfig_Scale16_IdMask(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint16_t StdIdArray1[10] ={0x7D1,0x7D2,0x7D3,0x7D4,0x7D5,
                          0x7D6,0x7D7,0x7D8,0x7D9,0x7DA};
  uint16_t StdIdArray2[10] ={0x751,0x752,0x753,0x754,0x755,
                          0x756,0x757,0x758,0x759,0x75A};
  uint16_t      mask,tmp,i,num;

  sFilterConfig.FilterNumber = 5;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;

  //config for filter1
  sFilterConfig.FilterIdLow =StdIdArray1[0]<<5;
  mask =0x7ff;
  num =sizeof(StdIdArray1)/sizeof(StdIdArray1[0]);
  for(i =0; i<num; i++)
  {
    tmp =StdIdArray1[i] ^ (~StdIdArray1[0]);
    mask &=tmp;
  }
  sFilterConfig.FilterMaskIdLow =(mask<<5)|0x10;    //only data frame can be receive

  //config for filter2
  sFilterConfig.FilterIdHigh = StdIdArray2[0]<<5;
  mask =0x7ff;
  num =sizeof(StdIdArray2)/sizeof(StdIdArray2[0]);
  for(i =0; i<num; i++)
  {
    tmp =StdIdArray2[i] ^ (~StdIdArray2[0]);
    mask &=tmp;
  }
  sFilterConfig.FilterMaskIdHigh = (mask<<5)|0x10;    //only data frame can be receive


  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
