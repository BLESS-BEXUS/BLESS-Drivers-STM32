/*
 * sensors.h
 *
 *  Created on: 17 mar 2026
 *      Author: Mariio
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "max31865.h"
#include "tmp102.h"
#include "ina219.h"

#include "telemetry.h"

void Sensors_Init();
uint8_t readSensors(TelemetryPacket *packet);


#endif /* INC_SENSORS_H_ */
