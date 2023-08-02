//Arduino Example for the TMP61 sensor

#include "Arduino.h"
#include "TMP6x.h"                      // Include the header

#define PIN_ADC     1                   // Random ADC pin

TMP61 tmp61 = TMP61(TMP6x_Voltages::V33, 12);

void setup() 
{
   Serial.begin(115200);                // Init the serial device
   Serial.print("Ola! Feeling cool?");  // Welcome message 
}

void loop() 
{
    int a = analogRead(PIN_ADC);        // Read the analog value
    float t = tmp61.GetInterpolatedTemperature(a);  // Calculate the temperature
    
    Serial.print("Temperature is ");    // Begin printing output
    Serial.print(t);                    // Print the Temperature
    Serial.println("°C");               // Print the degrees plus a newline

    delay(5000);                        // Wait 5 seconds
}