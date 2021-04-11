/**
  * @file       tle8108.c
  * @author     bryan (zhubeilife@gmail.com)
  * @date       2018
  * @version    v0.001
  * @brief      This file is general source file of tle8108.c .
  * @details
  */

#include "bsp/tle8108em.h"

volatile _spi_status Tx_spi_status;
volatile _spi_status Rx_spi_status;

void tle8108em_init (void)
{
  //Hal Init SPI2
  MX_SPI2_Init();

  //Reset the chip
  SPI2_RST_RESET;
  HAL_Delay (10); //delay for 10ms
  SPI2_RST_SET;

  //Set CS Pin to High
  SPI2_CS_SET;

  //Init Tx_spi_status and set all pin to off state
  Tx_spi_status.spi_switch_status = 0xFFFF;
  tle8108em_turn_all_off();
}

void tle8108em_turn_all_on (void)
{
  Tx_spi_status.spi_switch_status = 0xAAAA;

  SPI2_CS_RESET;
  HAL_SPI_Transmit (&hspi2, Tx_spi_status.spi_switch_buffer, 2, 10);
  SPI2_CS_SET;
}

void tle8108em_turn_all_off (void)
{
  Tx_spi_status.spi_switch_status = 0xFFFF;

  SPI2_CS_RESET;
  HAL_SPI_Transmit (&hspi2, Tx_spi_status.spi_switch_buffer, 2, 10);
  SPI2_CS_SET;
}

void tle8108em_write_bit (uint8_t bit, uint8_t status)
{
  Tx_spi_status.spi_switch_status &= ~ (0x03 << ((bit - 1) * 2));
  Tx_spi_status.spi_switch_status |= (status << ((bit - 1) * 2));

  SPI2_CS_RESET;
  HAL_SPI_Transmit (&hspi2, Tx_spi_status.spi_switch_buffer, 2, 10);
  SPI2_CS_SET;
}

void tle8108em_write_all (uint16_t new_state)
{
  Tx_spi_status.spi_switch_status = new_state;

  SPI2_CS_RESET;
  HAL_SPI_Transmit (&hspi2, Tx_spi_status.spi_switch_buffer, 2, 10);
  SPI2_CS_SET;
}
