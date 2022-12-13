# Texas Instruments (TI) TMP6x Temperature sensors

Plain and easy to use Libary for the TI linear thermistors (TMP61, TMP63 and TMP64) using your own Analog Digital Converter (ADC). From -40°C to +125°C.

The following are supported: TMP61, TMP63 and TMP64

The TMP6x linear thermistors offer linearity and consistent sensitivity across temperature to enable simple and accurate methods for temperature conversion. The low power consumption and a small thermal mass of the device minimize the impact of self-heating.

This libary is heavily inspired by the calculations provided by the TI datasheets. References at the bottom.

# How to connect

More information on how to connect, please see the datasheet for recommendations.

# How to Use

1) Download and Add the source files to your project (Download the files, use the Arduino lib manager or Git Clone):
```git clone SndrSchnklshk/TMP6x```

2) Start using the Lib, include the following:
```#include "TMP6x.h"```

3) Construct an instance:
```TMP61 tmp61 = TMP61(3.3f, 16, 4.069);```

4) Read the (analog) Thermistor pin

5) Read Integer Temperature with 1° degree precision:
```tmp61.GetTemperature(yourAnalogValue);```

6) Read Decimal Temperature with linear interpolation:
```tmp61.GetInterpolatedTemperature(yourAnalogValue);```

7) Enjoy some temperature and support me ;)

## Full example
Example showing Arduino C code on how to use the libary.

```
//Arduino Example
#include "TMP6x.h"                      // Include the header

#define PIN_ADC     1                   // Random ADC pin

TMP61 tmp61 = TMP61(3.3f, 12);

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
```

# Future improvements

1) Add internal buffer with some sophisticated averaging
2) ...

# More information

TI Datasheet for more information (TMP61): [Download PDF](https://www.ti.com/lit/ds/symlink/tmp61.pdf)

TI Design Tool (Excel calculation): [Download ZIP](http://www.ti.com/lit/zip/sboc595)

The TMP6x Linear Thermistors are a products of Texas Instruments

Feel free to buy me beer ;)