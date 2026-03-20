/*
 * tmp102.h
 *
 *  Created on: 10 mar 2026
 *
 */

#ifndef INC_TMP102_H_
#define INC_TMP102_H_

#include "main.h"

/* DEFINITION OF THE I2C PARAMETERS */
// TMP102 I2C Addresses depending of the alt connection
#define TMP102_I2C_ADDRESS_GND (0x48 << 1)
#define TMP102_I2C_ADDRESS_V (0x49 << 1)
#define TMP102_I2C_ADDRESS_SDA (0x4A << 1)
#define TMP102_I2C_ADDRESS_SCL (0x4B << 1)

// TMP102 Registers
#define TMP102_I2C_REG_TEMP 0x00 // Temperature register (Read Only)
#define TMP102_I2C_REG_CONF 0x01 // Configuration register (R/W)
#define TMP102_I2C_REG_TLOW 0x02
#define TMP102_I2C_REG_THIGH 0x03

/* Temperature conversion tools */

// MAX Temperature (127.9375 ºC)
#define TMP102_MAX_TEMP 0x07FF // Higher than this value implies a negative temperature

// Temperature Resolution
#define TMP102_TEMP_RES 0.0625


/* TMP102 FUNCTIONS */

/**
 * @brief  Config the sensor.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  dev_address: I2C address of the sensor.
 * @param  config_value: 16-bit value which contains the config of the sensor (read datasheet).
 * @retval Temperature in celsius, or -999 if a communication error ocurs.
 */
void TMP102_Config(I2C_HandleTypeDef *hi2c, uint16_t dev_address, uint16_t config_value); // Config the TMP102 sensor

/**
 * @brief  Read a temperature measurement.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  dev_address: I2C address of the sensor.
 * @retval Temperature in celsius, or -999 if a communication error ocurrs.
 */
float TMP102_Read_Temp(I2C_HandleTypeDef *hi2c, uint16_t dev_address);


#endif /* INC_TMP102_H_ */
