/*
 * tmp102.c
 *
 *  Created on: 10 mar 2026
 *
 */

#include "../Inc/tmp102.h"


float TMP102_Read_Temp(I2C_HandleTypeDef *hi2c, uint16_t dev_address){
	uint8_t data[2];
	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(hi2c, dev_address, TMP102_I2C_REG_TEMP, I2C_MEMADD_SIZE_8BIT, data, 2, 100);


	if(status != HAL_OK){
		return -999.0;
	}

	//data[0] = 10011101
	//data[1] = 11110000
	//raw_temp = 11111001 11011111

	// Prepare the temperature
	uint16_t raw_temp = 0;
	raw_temp = ((data[0] << 8) | data[1]) >> 4;

	if(raw_temp > TMP102_MAX_TEMP){
		raw_temp |= 0xF000;
	}

	return raw_temp * TMP102_TEMP_RES;

}

void TMP102_Config(I2C_HandleTypeDef *hi2c, uint16_t dev_address, uint16_t config_value){
	uint8_t config[2];
	config[0] = config_value >> 8;
	config[1] = config_value & 0x00FF;
	HAL_I2C_Mem_Write(hi2c, dev_address, TMP102_I2C_REG_CONF, I2C_MEMADD_SIZE_8BIT, config, 2, 100);
}


