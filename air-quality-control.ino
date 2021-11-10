//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 7          // what pin we're connected to
#define DHTTYPE DHT22     // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define MQ135 A1
#define RLOAD 1.0
#define r0Air 1
//#define r0CO 69.65
//#define r0CO2 553.232
//#define r0Ethanol 240.293
//#define r0NH4 164.8282
//#define r0Toluene 130.726
//#define r0Acetone 224.6261
#define scaleFactorCO 662.9382
#define exponentCO 4.0241
#define scaleFactorCO2 116.6020682
#define exponentCO2 2.769034857
#define scaleFactorEthanol 75.3103
#define exponentEthanol 3.1459
#define scaleFactorNH4 102.694
#define exponentNH4 2.48818
#define scaleFactorToluene 43.7748
#define exponentToluene 3.42936
#define scaleFactorAcetone 33.1197
#define exponentAcetone 3.36587
#define atmCO 1
#define atmCO2 350
#define atmEthanol 22.5
#define atmNH4 15
#define atmToluene 2.9
#define atmAcetone 16

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

float r0CO, r0CO2, r0Ethanol, r0NH4, r0Toluene, r0Acetone;

void setup() {
  Serial.begin(9600);
  dht.begin();

  delay(250);
  r0CO = getResistance() * pow((atmCO / scaleFactorCO), (1. / exponentCO));
  r0CO2 = getResistance() * pow((atmCO2 / scaleFactorCO2), (1. / exponentCO2));
  r0Ethanol = getResistance() * pow((atmEthanol / scaleFactorEthanol), (1. / exponentEthanol));
  r0NH4 = getResistance() * pow((atmNH4 / scaleFactorNH4), (1. / exponentNH4));
  r0Toluene = getResistance() * pow((atmToluene / scaleFactorToluene), (1. / exponentToluene));
  r0Acetone = getResistance() * pow((atmAcetone / scaleFactorAcetone), (1. / exponentAcetone));
  delay(100);

  Serial.println("Calibration for RZero value of respective Gases in ohm \n");
  Serial.print("CO RZero Value: \t"); Serial.print(r0CO); Serial.println( " ohm" );
  Serial.print("CO2 RZero Value: \t"); Serial.print(r0CO2); Serial.println( " ohm" );
  Serial.print("Ethanol RZero Value: \t"); Serial.print(r0Ethanol); Serial.println( " ohm" );
  Serial.print("NH4 RZero Value: \t"); Serial.print(r0NH4); Serial.println( " ohm" );
  Serial.print("Toluene RZero Value: \t"); Serial.print(r0Toluene); Serial.println( " ohm" );
  Serial.print("Acetone RZero Value: \t"); Serial.print(r0Acetone); Serial.println( " ohm" );
}

float getResistance() {
  int val = analogRead(MQ135);
  return ((1024. / (float)val) * 5. - 1.) * RLOAD;
}

void loop()
{
  Serial.println("\nStart of Results -----------------------------------------");
  // DHT 22
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  //Print temp and humidity values to serial monitor
  Serial.print("DHT 22\tHumidity: "); Serial.print(hum); Serial.print(" %, Temp: "); Serial.print(temp); Serial.println(" Celsius");

  // TMP36
  int sensorValueTMP36 = analogRead(A0);

  // print out the value A0 reads:
  Serial.print("TMP 36\tSensor Value: ");
  Serial.print(sensorValueTMP36);

  // convert the ADC reading to voltage
  float voltageTMP36 = (sensorValueTMP36 * 5.0) / 1024.0;
  Serial.print(", Volts: ");
  Serial.print(voltageTMP36);

  //convert the voltage to temperature in degrees
  Serial.print(", Temp: ");
  float temperature = (voltageTMP36 - .5) * 100;
  Serial.print(temperature);
  Serial.println(" Celsius");

  // MQ135
  int sensorValueMQ135 = analogRead(A1);

  // print out the value A1 reads:
  Serial.print("MQ 135 \tSensor Value: ");
  Serial.print(sensorValueMQ135);

  // convert the ADC reading to voltage
  float voltageMQ135 = (sensorValueMQ135 * 5.0) / 1024.0;
  Serial.print(", Volts: ");
  Serial.println(voltageMQ135);

  float ppmCO = scaleFactorCO * pow((getResistance() / r0CO), -exponentCO);
  float ppmCO2 = scaleFactorCO2 * pow((getResistance() / r0CO2), -exponentCO2);
  float ppmEthanol = scaleFactorEthanol * pow((getResistance() / r0Ethanol), -exponentEthanol);
  float ppmNH4 = scaleFactorNH4 * pow((getResistance() / r0NH4), -exponentNH4);
  float ppmToluene = scaleFactorToluene * pow((getResistance() / r0Toluene), -exponentToluene);
  float ppmAcetone = scaleFactorAcetone * pow((getResistance() / r0Acetone), -exponentAcetone);

  Serial.println("");
  Serial.println("Respective Gases with PPM");
  Serial.print("CO PPM: \t"); Serial.print(ppmCO); Serial.println( " ppm" );
  Serial.print("CO2 PPM: \t"); Serial.print(ppmCO2); Serial.println( " ppm" );
  Serial.print("Ethanol PPM: \t"); Serial.print(ppmEthanol); Serial.println( " ppm" );
  Serial.print("NH4 PPM: \t"); Serial.print(ppmNH4); Serial.println( " ppm" );
  Serial.print("Toluene PPM: \t"); Serial.print(ppmToluene); Serial.println( " ppm" );
  Serial.print("Acetone PPM: \t"); Serial.print(ppmAcetone); Serial.println( " ppm" );

  Serial.println("End of Results -------------------------------------------");
  delay(1000);
}
