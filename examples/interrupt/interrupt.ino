
#ifndef EXT_INTR_0  
#define EXT_INTR_0 9 // for xmc2g0
#endif

// uncomment to use SPI
// #define DPS_SPI

// uncomment to use DPS422
// #define DPS422

#ifdef DPS422
#define DPS_FIFO_FULL_INTR DPS422_FIFO_FULL_INTR
#include <Dps422.h>
Dps422 DigitalPressureSensor = Dps422();
#else
#define DPS_FIFO_FULL_INTR DPS310_FIFO_FULL_INTR
#include <Dps310.h>
Dps310 DigitalPressureSensor = Dps310();
#endif


void onFifoFull();

const unsigned char pressureLength = 50;
unsigned char pressureCount = 0;
float pressure[pressureLength];
unsigned char temperatureCount = 0;
const unsigned char temperatureLength = 50;
float temperature[temperatureLength];

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  
#ifdef DPS_SPI
  DigitalPressureSensor.begin(SPI, PIN_SPI_SS);
#else 
  //Call begin to initialize DigitalPressureSensor
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  //DigitalPressureSensor.begin(Wire, 0x76);
  //Use the commented line below instead of the one above to use the default I2C address.
  //if you are using the Pressure 3 click Board, you need 0x76
  DigitalPressureSensor.begin(Wire);
#endif

  int16_t ret = DigitalPressureSensor.setInterruptSources(DPS_FIFO_FULL_INTR);
  //clear interrupt flag by reading
  DigitalPressureSensor.getIntStatusFifoFull();

  //initialization of Interrupt for Controller unit
  //SDO pin of Dps310 has to be connected with interrupt pin

  pinMode(EXT_INTR_0, INPUT);
  attachInterrupt(digitalPinToInterrupt(EXT_INTR_0), onFifoFull, RISING);

  //start of a continuous measurement just like before
  ret = DigitalPressureSensor.startMeasureBothCont(DPS__MEASUREMENT_RATE_8, DPS__MEASUREMENT_RATE_4, DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_8);
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
  //do other stuff
  Serial.println("loop running");
  delay(500);


  //if result arrays are full
  //This could also be in the interrupt handler, but it would take too much time for a proper ISR
  if (pressureCount == pressureLength && temperatureCount == temperatureLength)
  {
    //print results
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
    //reset result counters
    pressureCount = 0;
    temperatureCount = 0;
  }
}


//interrupt handler
void onFifoFull()
{
  //message for debugging
  // Serial.println("Interrupt handler called");

  //clear interrupt flag by reading
  DigitalPressureSensor.getIntStatusFifoFull();

  //calculate the number of free indexes in the result arrays
  unsigned char prs_freespace = pressureLength - pressureCount;
  unsigned char temp_freespace = temperatureLength - temperatureCount;
  //read the results from Dps310, new results will be added at the end of the arrays
  DigitalPressureSensor.getContResults(&temperature[temperatureCount], temp_freespace, &pressure[pressureCount], prs_freespace);
  //after reading the result counters are increased by the amount of new results
  pressureCount += prs_freespace;
  temperatureCount += temp_freespace;
}
