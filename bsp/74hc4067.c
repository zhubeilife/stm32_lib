/**
  * @file       74hc4067.c
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @brief      This file is source file of 74hc4067.h
  *             16-Channel Analog Multiplexer/Demultiplexer.
  * @details    This is for Loaing Lshape Gripper Version 1.
  *             We are using two chips of 74hc4067 to connect with
  *             32 channels.
  */

#include "74hc4067.h"

void SO_set_bit (uint8_t bit)
{
  if (bit == 0)
  {
    S0_L;
  }
  else
  {
    S0_H;
  }
}

void S1_set_bit (uint8_t bit)
{
  if (bit == 0)
  {
    S1_L;
  }
  else
  {
    S1_H;
  }
}

void S2_set_bit (uint8_t bit)
{
  if (bit == 0)
  {
    S2_L;
  }
  else
  {
    S2_H;
  }
}

void S3_set_bit (uint8_t bit)
{
  if (bit == 0)
  {
    S3_L;
  }
  else
  {
    S3_H;
  }
}

void select_one_channel (uint8_t channel)
{
  /* Here we have two 74hc4067 chips, so we will select one channel
     between 0 ~ 32 pins */
  if (channel < 16)
  {
    CD74HC_ENABLE_2;
    CD74HC_DISABLE_1;

    SO_set_bit (channel & 0x01);
    S1_set_bit ((channel >> 1) & 0x01);
    S2_set_bit ((channel >> 2) & 0x01);
    S3_set_bit ((channel >> 3) & 0x01);
  }
  else
  {
    CD74HC_ENABLE_1;
    CD74HC_DISABLE_2;

    channel = channel - 16;

    SO_set_bit (channel & 0x01);
    S1_set_bit ((channel >> 1) & 0x01);
    S2_set_bit ((channel >> 2) & 0x01);
    S3_set_bit ((channel >> 3) & 0x01);
  }
}

void cd74hc4067_init (void)
{
  CD74HC_DISABLE_1;
  CD74HC_DISABLE_2;
}
