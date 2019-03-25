#include <Dps422.h>
Dps422 Dps422PressureSensor = Dps422();

void onFifoFull();

const unsigned char pressureLength = 50;
uint8_t pressureCount = 0;
float pressure[pressureLength];
uint8_t temperatureCount = 0;
const unsigned char temperatureLength = 50;
float temperature[temperatureLength];



void setup()
{
  Serial.begin(9600);
  while (!Serial);

  // Call begin() to initialize the Dps422PressureSensor
  // The parameter is the bus address and the default address is 0x77 which does not need to be given.
  // Dps422PressureSensor.begin(Wire, 0x76);
  // Use the commented line below instead of the one above to use the default I2C address.

  Dps422PressureSensor.begin(Wire);

  // Clear interrupt flag by reading
  
  Dps422PressureSensor.getIntStatusFifoFull();

  // Initialization of Interrupt for Controller unit
  // SDO pin of Dps422 has to be connected with interrupt pin
  
  int16_t interruptPin = 3;
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onFifoFull, RISING);

  // Start of a continuous measurement just like before
  
  int16_t temp_mr = 3;
  int16_t temp_osr = 2;
  int16_t prs_mr = 1;
  int16_t prs_osr = 3;
  int16_t ret =Dps422PressureSensor.startMeasureBothCont(temp_mr, temp_osr, prs_mr, prs_osr);
  if (ret != 0)
  {
    Serial.print("Init FAILED! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.println("Init complete!");
  }
}


void loop()
{
  // Do other stuff
  Serial.println("loop running");
  delay(500);


  // If result arrays are full
  // This could also be in the interrupt handler, but it would take too much time for a proper ISR
  if (pressureCount == pressureLength && temperatureCount == temperatureLength)
  {
    // Print results
    Serial.println();
    Serial.println();
    Serial.print(temperatureCount);
    Serial.println(" temperature values found: ");
    for (int16_t i = 0; i < temperatureCount; i++)
    {
      Serial.print(temperature[i]);
      Serial.println(" degrees of Celsius");
    }
    Serial.println();
    Serial.print(pressureCount);
    Serial.println(" pressure values found: ");
    for (int16_t i = 0; i < pressureCount; i++)
    {
      Serial.print(pressure[i]);
      Serial.println(" Pascal");
    }
    Serial.println();
    Serial.println();
    // Reset result counters
    pressureCount = 0;
    temperatureCount = 0;
  }
}


// Interrupt handler
void onFifoFull()
{
  // Message for debugging

  Serial.println("Interrupt handler called");

  // Clear interrupt flag by reading

  Dps422PressureSensor.getIntStatusFifoFull();

  // Calculate the number of free indexes in the result arrays

  unsigned char prs_freespace = pressureLength - pressureCount;
  unsigned char temp_freespace = temperatureLength - temperatureCount;

  // Read the results from Dps422, new results will be added at the end of the arrays

  Dps422PressureSensor.getContResults(&temperature[temperatureCount], temp_freespace, &pressure[pressureCount], prs_freespace);

  // After reading the result counters are increased by the amount of new results

  pressureCount += prs_freespace;
  temperatureCount += temp_freespace;
}