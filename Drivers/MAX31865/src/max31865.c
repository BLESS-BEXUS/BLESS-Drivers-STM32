/*
 * max31865.c
 *
 *  Created on: 11 mar 2026
 *
 */
#include "../Inc/max31865.h"

void MAX31865_Config(SPI_HandleTypeDef *hspi, uint8_t config_value, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin){
	uint8_t data[2];
	data[0] = MAX31865_REG_CONFIG_WRITE;
	data[1] = config_value;
	// Wake up the sensor via CS
	HAL_GPIO_WritePin(cs_gpio_port, cs_gpio_pin, GPIO_PIN_RESET);
	// Once the sensor has waken up, send the config value
	HAL_SPI_Transmit(hspi, data, 2, 100);
	// Set CS to 1 again to close communication
	HAL_GPIO_WritePin(cs_gpio_port, cs_gpio_pin, GPIO_PIN_SET);
}

void MAX31865_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin){
	HAL_GPIO_WritePin(cs_gpio_port, cs_gpio_pin, GPIO_PIN_SET);
	// Once the sensor has waken up, send the config value
	MAX31865_Config(hspi, MAX31865_CONFIG_DEFAULT_VALUE, cs_gpio_port, cs_gpio_pin);
}

float MAX31865_Read_Temp(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio_port, uint16_t cs_gpio_pin){
	uint8_t tx_packet[3] = {MAX31865_REG_RTD_MSB, 0X00, 0X00};
	uint8_t rx_data[3];
	uint16_t adc_code = 0.0;
	HAL_StatusTypeDef status;
	// Wake up the sensor via CS
	HAL_GPIO_WritePin(cs_gpio_port, cs_gpio_pin, GPIO_PIN_RESET);

	// MAX31865 use auto-increment, so once the MSB register is sent,
	// while dummy packets are sent, the next register is read
	status = HAL_SPI_TransmitReceive(hspi, tx_packet, rx_data, 3, 100);

	// Set CS to 1 again to close communication
	HAL_GPIO_WritePin(cs_gpio_port, cs_gpio_pin, GPIO_PIN_SET);

	if(status != HAL_OK){
		return -318.65;
	}

	// Prepare the ADC_Code
	adc_code = ((rx_data[1] << 8) | rx_data[2]) >> 1;

	float resistance = (float)adc_code * R_REF / 32768.0;
	// Use the generalized formula to calculate the temperature in ºC (PT100, [-100 - 100 ºC])
	return (resistance - R_NOMINAL) / 0.3851;
}


