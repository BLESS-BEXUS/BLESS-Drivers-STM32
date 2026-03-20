# BLESS Sensor Drivers for STM32 HAL

This repository contains C drivers for various sensors used in the **BLESS** (Bexus Low-power Embedded Sensor System) project. These drivers are built on top of the **STM32 Hardware Abstraction Layer (HAL)**.

> **⚠️ Project Status: Functional Subset**
> These drivers implement the specific features required for our high-altitude balloon mission. They do **not** cover 100% of the sensors' internal registers or functionalities. Users requiring advanced features should refer to the technical datasheets provided in the `Docs/` folder.

## Supported Hardware

### 1. INA219 - Current & Power Monitor
* [cite_start]**Bus Voltage Sensing**: Measures bus voltages from 0 to 26 V[cite: 12, 569].
* **Crucial Calibration**: The `INA219_INIT` function requires the **Maximum Expected Current**. This value is essential to calculate the internal Calibration Register and define the `Current_LSB`[cite: 697, 701, 703].
* [cite_start]**Data Handling**: Bus Voltage Register bits are shifted right by three positions and multiplied by a 4-mV LSB[cite: 716, 717, 1220].
* [cite_start]**Addressing**: Supports up to 16 programmable I2C addresses via A0 and A1 pins[cite: 12, 784].

### 2. TMP102 - Digital Temperature Sensor
* **Range**: Senses temperature from -40ºC to +125ºC.
* **Resolution**: 12-bit resolution (0.0625ºC per LSB).
* **Interface**: I2C compatible.

### 3. MAX31865 - RTD-to-Digital Converter
* **Sensor Type**: Optimized for PT100/PT1000 platinum RTDs.
* **Interface**: SPI.

## Repository Structure

* **`Drivers/`**: Contains the `.c` and `.h` source files for each individual sensor.
* **`Examples/`**: Contains `sensors.c`, a comprehensive reference implementation showing how to initialize all sensors and acquire data into a unified telemetry packet.
* **`Docs/`**: Technical datasheets and reference manuals for the integrated hardware.

## Installation & Integration

1. Add the required sensor files from the `Drivers/` directory to your STM32CubeIDE project (typically under `Core/Inc` and `Core/Src`).
2. Enable the corresponding I2C or SPI peripherals in your STM32CubeMX configuration (`.ioc` file).
3. [cite_start]**Important**: When calling `INA219_INIT`, you must provide the specific `Max_Expected_Current` for your application to ensure accurate power and current readings[cite: 703, 741].

## Usage
For a complete demonstration of how to initialize the drivers and handle sensor data acquisition (including error flagging and data scaling), please refer to the provided example:
👉 **`Examples/sensors.c`**

## License
This project is licensed under the **MIT License** - see the `LICENSE` file for details.
