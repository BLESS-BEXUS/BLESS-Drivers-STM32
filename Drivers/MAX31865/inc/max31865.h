/*
 * max31865.h
 *
 *  Created on: 11 mar 2026
 *
 */

#ifndef INC_MAX31865_H_
#define INC_MAX31865_H_

#include "main.h"

/**** REGISTER ADDRESSES ****/
#define MAX31865_REG_CONFIG_READ 0x00
#define MAX31865_REG_CONFIG_WRITE 0x80

#define MAX31865_REG_RTD_MSB 0x01
#define MAX31865_REG_RTD_LSB 0x02

#define MAX31865_REG_HIGH_FAULT_THRES_MSB_READ 0x03
#define MAX31865_REG_HIGH_FAULT_THRES_MSB_WRITE 0x83
#define MAX31865_REG_HIGH_FAULT_THRES_LSB_READ 0x04
#define MAX31865_REG_HIGH_FAULT_THRES_LSB_WRITE 0x84
#define MAX31865_REG_LOW_FAULT_THRES_MSB_READ 0x05
#define MAX31865_REG_LOW_FAULT_THRES_MSB_WRITE 0x85
#define MAX31865_REG_LOW_FAULT_THRES_LSB_READ 0x06
#define MAX31865_REG_LOW_FAULT_THRES_LSB_WRITE 0x86

#define MAX31865_REG_FAULT_STATUS 0x07

#define MAX31865_CONFIG_DEFAULT_VALUE 0xC3

// Resistance parameters (depends on the sensor)
#define R_REF 430.0 // 430 ohms resistance
#define R_NOMINAL 100.0 // PT100

/**** FUNCTION DEFINITIONS ****/
/**
 * @brief  Initialize MAX31865 sensor.
 * @param  hspi: Pointer to the SPI config structure from HAL.
 * @param  cs_gpio_port: Pointer to the GPIO port used as CS.
 * @param  cs_gpio_pin: GPIO pin used as CS.
 */
void MAX31865_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin);

/**
 * @brief  Config the sensor.
 * @param  hspi: Pointer to the SPI config structure from HAL.
 * @param  config_value: 8-bit value which contains the config of the sensor (read datasheet).
 * @param  cs_gpio_port: Pointer to the GPIO port used as CS.
 * @param  cs_gpio_pin: GPIO pin used as CS.
 */
void MAX31865_Config(SPI_HandleTypeDef *hspi, uint8_t config_value, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin);

/**
 * @brief  Take a temperature measurement. (This equation gives 0ºC error at 0ºC, -1.75ºC error at -100ºC, and -1.4ºC error at +100ºC because of the equation used)
 * @param  hspi: Pointer to the SPI config structure from HAL.
 * @param  cs_gpio_port: Pointer to the GPIO port used as CS.
 * @param  cs_gpio_pin: GPIO pin used as CS.
 * @retval Temperature in celsius, or -318.65 if a communication error ocurrs.
 */
float MAX31865_Read_Temp(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin);

#endif /* INC_MAX31865_H_ */
