#include <Dps422.h>
Dps422 Dps422PressureSensor = Dps422();

void setup()
{
  Serial.begin(9600);
  while (!Serial);


  // Call begin() to initialize the Dps422PressureSensor
  // The parameter is the bus address and the default address is 0x77 which does not need to be given.
  // Dps422PressureSensor.begin(Wire, 0x76);
  // Use the commented line below instead of the one above to use the default I2C address.

  Dps422PressureSensor.begin(Wire);
  Serial.println("Init complete!");
}



void loop()
{
  float temperature;
  float pressure;
  int16_t oversampling = 7;
  int16_t ret;
  Serial.println();

  // Lets the Dps422 perform a single temperature measurement with the last (or standard) configuration
  // The result will be written to the parameter temperature
  // ret = Dps422PressureSensor.measureTempOnce(temperature);
  // The commented line below does exactly the same as the one above, but you can also config the precision
  // Oversampling can be a value from 0 to 7
  // The Dps422 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  // Measurements with higher precision take more time, consult datasheet for more information

  ret = Dps422PressureSensor.measureTempOnce(temperature, oversampling);

  if (ret != 0)
  {
    // Something went wrong.
    // Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees of Celsius");
  }

  // Pressure measurement behaves like temperature measurement
  // ret = Dps422PressureSensor.measurePressureOnce(pressure);
  ret = Dps422PressureSensor.measurePressureOnce(pressure, oversampling);
  if (ret != 0)
  {
    // Something went wrong.
    // Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pascal");
  }

  // Wait some time
  delay(500);
}
