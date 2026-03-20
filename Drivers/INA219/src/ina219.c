/*
 * ina219.c
 *
 *  Created on: 12 mar 2026
 *
 */
#include "../Inc/ina219.h"

void INA219_INIT(I2C_HandleTypeDef *hi2c, INA219_t *ina, uint16_t address, float r_shunt, float max_current){
	ina->current_lsb = max_current / 32768.0;
	ina->dev_address = address;
	uint16_t cal = (INA219_FIXED_SCALE_VALUE / (ina->current_lsb * r_shunt));
	uint8_t data[2];

	data[0] = cal >> 8;
	data[1] = cal;

	HAL_I2C_Mem_Write(hi2c, ina->dev_address, INA219_I2C_REG_CALIBRATION, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
}

uint8_t INA219_READ_CURRENT(I2C_HandleTypeDef *hi2c, INA219_t *ina){
	uint8_t data[2];
	HAL_StatusTypeDef status;
	int16_t raw_current;

	status = HAL_I2C_Mem_Read(hi2c, ina->dev_address, INA219_I2C_REG_CURRENT, I2C_MEMADD_SIZE_8BIT, data, 2, 100);

	if(status != HAL_OK){
		return 0;
	}

	// Prepare power data
	raw_current = (data[0] << 8) | data[1];

	// Return the power in mW (current = raw_current * current_lsb * 1000)
	ina->current = raw_current * ina->current_lsb * 1000;
	return 1;
}

int32_t INA219_READ_POWER(I2C_HandleTypeDef *hi2c, INA219_t *ina){
	uint8_t data[2];
	HAL_StatusTypeDef status;
	uint16_t raw_power;

	status = HAL_I2C_Mem_Read(hi2c, ina->dev_address, INA219_I2C_REG_POWER, I2C_MEMADD_SIZE_8BIT, data, 2, 100);

	if(status != HAL_OK){
		return -1;
	}

	// Prepare power data
	raw_power = (data[0] << 8) | data[1];

	// Return the power in mW (power = raw_power * power_lsb * 1000) (power_lsb = current_lsb * 20)
	return raw_power * ina->current_lsb * 20 * 1000;
}

uint8_t INA219_READ_BUS_VOLTAGE(I2C_HandleTypeDef *hi2c, INA219_t *ina){
	uint8_t data[2];
	HAL_StatusTypeDef status;
	uint16_t raw_bus_voltage;

	status = HAL_I2C_Mem_Read(hi2c, ina->dev_address, INA219_I2C_REG_BUS, I2C_MEMADD_SIZE_8BIT, data, 2, 100);

	if(status != HAL_OK){
		return 0;
	}

	raw_bus_voltage = ((data[0] << 8) | data[1]) >> 3;

	ina->bus_vol = raw_bus_voltage * 4;
	return 1;
}
