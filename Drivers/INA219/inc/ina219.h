/*
 * ina219.h
 *
 *  Created on: 12 mar 2026
 *
 */

#ifndef INC_INA219_H_
#define INC_INA219_H_

#include "main.h"

/**** REGISTER ADDRESSES DEFINITION ****/

/* I2C ADDRESSES DEFINITION */
#define INA219_I2C_ADDRESS_GND_GND (0X40 << 1)
#define INA219_I2C_ADDRESS_GND_VS (0X41 << 1)
#define INA219_I2C_ADDRESS_GND_SDA (0x42 << 1)
#define INA219_I2C_ADDRESS_GND_SCL (0x43 << 1)
#define INA219_I2C_ADDRESS_VS_GND (0x44 << 1)
#define INA219_I2C_ADDRESS_VS_VS (0x45 << 1)
#define INA219_I2C_ADDRESS_VS_SDA (0x46 << 1)
#define INA219_I2C_ADDRESS_VS_SCL (0x47 << 1)
#define INA219_I2C_ADDRESS_SDA_GND (0x48 << 1)
#define INA219_I2C_ADDRESS_SDA_VS (0x49 << 1)
#define INA219_I2C_ADDRESS_SDA_SDA (0x4A << 1)
#define INA219_I2C_ADDRESS_SDA_SCL (0x4B << 1)
#define INA219_I2C_ADDRESS_SCL_GND (0x4C << 1)
#define INA219_I2C_ADDRESS_SCL_VS (0x4D << 1)
#define INA219_I2C_ADDRESS_SCL_SDA (0x4E << 1)
#define INA219_I2C_ADDRESS_SCL_SCL (0x4F << 1)

/* REGISTER ADDRESSES */
#define INA219_I2C_REG_CONF 0x00
#define INA219_I2C_REG_SHUNT 0x01
#define INA219_I2C_REG_BUS 0x02
#define INA219_I2C_REG_POWER 0x03
#define INA219_I2C_REG_CURRENT 0x04
#define INA219_I2C_REG_CALIBRATION 0x05

/* TIPICAL R_SHUNTS */
#define INA219_R100 0.1
#define INA219_R010 0.01

#define INA219_FIXED_SCALE_VALUE 0.04096


/* INA219 type definition */
typedef struct{
	uint16_t dev_address;
	float current_lsb;
	int16_t current;
	int16_t power;
	int16_t bus_vol;
} INA219_t;

/**** FUNCTION DEFINITIONS ****/

/**
 * @brief  Initialize INA219 sensor, calibrating depending of the resistance and max current expected.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  ina: Pointer to the INA structure.
 * @param  address: I2C address of the sensor.
 * @param  r_shunt: R value of the sensor resistance (ohms).
 * @param  max_current: Max current expected to measure.
 */
void INA219_INIT(I2C_HandleTypeDef *hi2c, INA219_t *ina, uint16_t address, float r_shunt, float max_current);

/**
 * @brief  Read the power value.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  ina: Pointer to the INA structure.
 * @retval Power in miliwatts (mW) or -1 in case of error.
 */
int32_t INA219_READ_POWER(I2C_HandleTypeDef *hi2c, INA219_t *ina);
/**
 * @brief  Read the power value.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  ina: Pointer to the INA structure.
 * @retval Current in miliamps (mA) or -2 in case of error via pointer to ina structure and code of error via return.
 */
uint8_t INA219_READ_CURRENT(I2C_HandleTypeDef *hi2c, INA219_t *ina);

/**
 * @brief  Read the bus voltage.
 * @param  hi2c: Pointer to the I2C config structure from HAL.
 * @param  @param  ina: Pointer to the INA structure.
 * @retval Bus voltage in milivolts (mV) via pointer to ina structure -2 and error code via return.
 */
uint8_t INA219_READ_BUS_VOLTAGE(I2C_HandleTypeDef *hi2c, INA219_t *ina);

#endif /* INC_INA219_H_ */
