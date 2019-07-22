# DPS422 Barometric Pressure Sensor

[![Build Status](https://travis-ci.org/Infineon/DPS422-Library-Arduino.svg?branch=master)](https://travis-ci.org/Infineon/DPS422-Library-Arduino)

<img src="https://www.infineon.com/export/sites/default/media/products/Small_Signal_Discretes/WLGA-8-1.png_1924866192.png" width=150><img src="https://github.com/Infineon/Assets/blob/master/Pictures/DPS422-Pressure-Shield2Go_Top.png" width=300>

Library of Infineon's highly sensitive [DPS422 sensor](https://www.infineon.com/cms/en/product/sensor/barometric-pressure-sensor-for-consumer-applications/dps422/) for Arduino.

## Summary

The [DPS422](https://www.infineon.com/cms/en/product/sensor/barometric-pressure-sensor-for-consumer-applications/dps422/) is a miniaturized digital barometric air pressure and temperature sensor with high accuracy and low current consumption. Pressure sensing is carried out using a capacitive sensor element, guaranteeing high accuracy over temperature. The small 2.0 x 2.5 x 0.73 mm package makes the DPS422 ideal for mobile applications and wearable devices.

The pressure and temperature sensor elements are measured by a 24-bit ΣΔ ADC. Measurement results can be accessed over I2C or SPI, with an optional configurable interrupt and a result FIFO capable of holding 32 pressure and/or temperature measurements.

Individual calibration coefficients are generated for each unit during testing, and stored in the fuse registers.
These coefficients are used in the application to convert the measurement results to high accuracy pressure and temperature values.

Sensor measurements and calibration coefficients are available through the serial I2C or SPI interface.

## Summary of Features

* Package dimensions: 8-pin LGA, 2.0 x 2.5 x 0.73 mm (typ)
* Operation range: Pressure: 300 –1200 hPa. Temperature: -40°C – +85 °C
* Pressure sensor precision: ± 0.005 hPa (or ±5 cm)
* Relative accuracy: ± 0.06 hPa (or ±50 cm)
* Absolute accuracy: ± 1 hPa (or ±8 m)
* Temperature accuracy: ± 0.4°C
* Pressure temperature sensitivity: < 0.5Pa/K
* Measurement time: Typical: 27.6 ms for standard mode (16x). Minimum: 3.6 ms for low precision mode
* Average current consumption: 1.7 μA for pressure measurement, 2μA for temperature measurement @1Hz sampling rate, Standby: <1 μA
* Supply voltage: VDDIO: 1.2 – 3.6 V, VDD: 1.7 – 3.6 V
* Operating modes: Command (manual), background (automatic), and standby
* Calibration: Individually calibrated with coefficients for measurement correction
* FIFO: Stores up to 32 pressure or temperature measurements
* Interface: I2C with optional interrupt, 4-wire SPI, 3-wire SPI with optional interrupt

## Benefits

* Highest precision and fast read-out speed enable accurate gesture and motion tracking
* Small footprint and thin package facilitate system integration
* Low power consumption required for mobile applications and wearables
* Absolute temperature sensor can be used in applications like weather stations or thermostats
* Intelligent FIFO improves system power consumption & enables MCU multitasking
 

## Target Applications

* Local weather station and thermostat (micro weather forecasting; wind speed measurement; room temperature control)
* Air flow control (smart filter replacement, e.g. in whitegoods; Servers CPU ventilation control)
* Health and sports (fall detection; accurate elevation gain, e.g. for smart watches)
* Outdoor navigation (GPS start-up time and accuracy improvement; dead-reckoning e.g. in tunnels)
* Indoor navigation (floor detection e.g. in shopping malls and parking garages)
* Smart Home (intruder detection and environmental monitoring of premises)

## Installation

### Integration of Library

The master branch is always release ready; therefore, you can just download this library by downloading it from GitHub directly:

Please download this repository from GitHub by clicking on the above button `Clone or download` of this repository:

![Download Library](https://github.com/Infineon/Assets/blob/master/Pictures/Download_Repo.png)

To install the DPS422 pressure sensor library in the Arduino IDE, please go now to **Sketch** > **Include Library** > **Add .ZIP Library...** in the Arduino IDE and navigate to the downloaded .ZIP file of this repository. The library will be installed in your Arduino sketch folder in libraries and you can select as well as include this one to your project under **Sketch** > **Include Library** > **DPS422 Barometric Pressure Sensor**.

![Install Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Library_Install_ZIP.png)

## Usage
Please see the example sketches in the `/examples` directory in this library to learn more about the usage of the library. Especially, take care of the respective SPI and I²C configuration of the sensor. 
For more information, please consult the datasheet [here](https://www.infineon.com/dgdl/Infineon-DPS422-DS-v01_03-EN.pdf?fileId=5546d46264fee02f01650249502c1ddf).

Currently, there exists the DPS422 Pressure Shield2Go evaluation board as a break out board:

* [DPS422 Pressure Shield2Go](https://www.infineon.com/cms/en/product/evaluation-boards/s2go-pressure-dps422/)

### DPS422 Pressure Shield2Go
The DPS422 Pressure Shield2Go is a standalone break out board with Infineon's Shield2Go formfactor and pin out. You can connect it easily to any microcontroller of your choice which is Arduino compatible and has 3.3 V logic level (please note that the Arduino UNO has 5 V logic level and cannot be used without level shifting).
Please consult the [wiki](https://github.com/Infineon/DPS422-Library-Arduino/wiki) for additional details about the board.

Each sensor can only work either SPI or I2C. To convert from SPI to I2C, for example, you have to re-solder the resistors on the Shield2Go. Please take care that every Shield2Go for the DPS422 is shipped as I2C configuration right now.

* [Link](https://github.com/Infineon/DPS422-Library-Arduino/wiki) to the wiki with more information

However, every Shield2Go is directly compatible with Infineon's XMC2Go and the recommended quick start is to use an XMC2Go for evaluation. Therefore, please install (if not already done) also the [XMC-for-Arduino](https://github.com/Infineon/XMC-for-Arduino) implementation and choose afterwards **XMC1100 XMC2Go** from the **Tools**>**Board** menu in the Arduino IDE if working with this evaluation board. To use it, please plug the DPS422 Pressure Shield2Go onto the XMC2Go as shown below.

<img src="https://github.com/Infineon/Assets/blob/master/Pictures/DPS422_S2Go_w_XMC2Go.png" width=250>

Please be aware that the DPS422 is sensitive to light and should be shielded, e.g. by the XMC 2Go as shown above, against direct light exposure.

## Known Issues

In case you need additional help, please do not hesitate to open an issue in this repository.

### Additional Information
Please find the datasheet of the DPS422 [here](https://www.infineon.com/dgdl/Infineon-DPS422-DS-v01_03-EN.pdf?fileId=5546d46264fee02f01650249502c1ddf). It depends on the evaluation board which you are using or the respective configuration of the sensor on your PCB which communication protocol as well as addresses you need to use for communicating with the sensor.