# Digital-Pressure-Sensor

[![Build Status](https://travis-ci.org/Infineon/DPS310-Pressure-Sensor.svg?branch=master)](https://travis-ci.org/Infineon/DPS310-Pressure-Sensor)

<img src="https://github.com/Infineon/Assets/blob/master/Pictures/DPS310_PP.jpg">

Library of Infineon's highly sensitive [DPS310 sensor](https://www.infineon.com/cms/de/product/sensor/capacitive-pressure-sensor-for-consumer-applications/DPS310/productType.html?productType=5546d462525dbac4015312b96a743801) and [DPS422 sensor](https://www.infineon.com/cms/en/product/sensor/barometric-pressure-sensor-for-consumer-applications/dps422/) for Arduino.

## Summary
The [DPS310](https://www.infineon.com/dgdl/Infineon-DPS310-DS-v01_00-EN.pdf?fileId=5546d462576f34750157750826c42242) is a miniaturized digital barometric air pressure sensor with a high accuracy and a low current consumption, capable of measuring both pressure and temperature. The internal signal processor converts the output from the pressure and temperature sensor elements to 24 bit results. Each unit is individually calibrated, the calibration coefficients calculated during this process are stored in the calibration registers. The coefficients are used in the application to convert the measurement results to high
accuracy pressure and temperature values.

Sensor measurements and calibration coefficients are available through the serial I2C or SPI interface.

## Usage
Please follow the example sketches in the /examples directory in this library to learn more about the usage of the library. Especially, take care of the SPI and I²C configuration of the sensor. For more information, please consult the datasheet [here](https://www.infineon.com/dgdl/Infineon-DPS310-DS-v01_00-EN.pdf?fileId=5546d462576f34750157750826c42242).

For different sensor types, the initialization should be adapted, as in example **background**:

```
// #define DPS422
#ifdef DPS422
#include <Dps422.h>
Dps422 DigitalPressureSensor = Dps422();
#else
#include <Dps310.h>
Dps310 DigitalPressureSensor = Dps310();
#endif
```

Also you can switch between SPI and I2C with this define (by default I2C is used):
```
// uncomment to use SPI
// #define DPS_SPI
```
Each sensor can only work either SPI or I2C. To convert from SPI to I2C, for example, you have to re-solder the resistors on the shield.

## Known Issues
### Temperature Measurement Issue
There could be a problem with the fuse bits in the DPS310 with which you are using this library. If your DPS310 indicates a temperature around 60 °C although you expect around room temperature, e.g. 20 °C, please call the function correctTemp() as indicated in the examples to fix this issue.
Many excuses for any problems arising from this problem.
In case you need additional help, please do not hesitate to open an issue in this repository.

### SPI with XMC2Go
If your sensor's MISO and MOSI are in different order as the XMC2Go shield, add the following line to the top of the sketch:
```
#define XMC2GO_SWAP_MOSI_MISO
``` 

### Interrupt mode
Interrupt mode not working reliably on XMC2Go for both DPS310 and DPS422.

## Key Features and Benefits
* Operation range: Pressure: 300 –1200 hPa. Temperature: -40 – 85 °C.
* Pressure sensor precision: ± 0.005 hPa (or ±0.05 m) (high precision mode).
* Relative accuracy: ± 0.06 hPa (or ±0.5 m)
* Absolute accuracy: ± 1 hPa (or ±8 m)
* Temperature accuracy: ± 0.5°C.
* Pressure temperature sensitivity: 0.5Pa/K
* Measurement time: Typical: 27.6 ms for standard mode (16x). Minimum: 3.6 ms for low precision mode.
* Average current consumption: 1.7 µA for Pressure Measurement, 1.5uA for Temperature measurement @1Hz sampling rate, Standby: 0.5 µA.
* Interface: I2C and SPI (both with optional interrupt)

## Hardware
Please find the datasheet of the DPS310 [here](https://www.infineon.com/dgdl/Infineon-DPS310-DS-v01_00-EN.pdf?fileId=5546d462576f34750157750826c42242). It depends on the evaluation board which you are using or the respective configuration of the sensor on your PCB (maybe designed by yourself) which communication protocol as well as addresses you need to use for communicating with the sensor.
Please note that currently no specific evaluation board for Arduino is available by Infineon, but the existing ones can be used together with this library as well as respective wiring.

## Installation

### Integration of Library
Please download this repository from GitHub by clicking on the following field in the latest [release](https://github.com/Infineon/DPS310-Pressure-Sensor/releases) of this repository or directly [here](https://github.com/Infineon/DPS310-Pressure-Sensor/releases/download/V1.0.5/DPS310-Pressure-Sensor.zip):

![Download Library](https://raw.githubusercontent.com/Infineon/assets/master/Pictures/DL_DPS310_Rel.jpg)

To install the DPS310 pressure sensor library in the Arduino IDE, please go now to **Sketch** > **Include Library** > **Add .ZIP Library...** in the Arduino IDE and navigate to the downloaded .ZIP file of this repository. The library will be installed in your Arduino sketch folder in libraries and you can select as well as include this one to your project under **Sketch** > **Include Library** > **IFX_DPS310**.

![Install Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Library_Install_ZIP.png)

