// (c) 2022 Sander Schinkelshoek
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "TMP6x.h"

float TMP6x::calculateResistance(int adc)
{
    tmp = 0;
    resistance = 0;

    tmp = adcBits * adc;
    resistance = tmp / ((voltageIn - tmp) / resistorBias);
    return resistance;
}

float TMP61::GetInterpolatedTemperature(int adc) // 4th order polynomial regression
{
    resistance = calculateResistance(adc);

    for (int i = 0; i < 34; ++i)
    {
        if (table_tmp61_5deg[i][1] >= resistance)
        {
            // the linear interpolation process is y = y1 + ((x - x1) / (x2 - x1)) * (y2 - y1)
            x1 = table_tmp61_5deg[i - 1][1]; // find the lower resistance value in the table
            x2 = table_tmp61_5deg[i][1];     // find the higher resistance value in the table
            y1 = table_tmp61_5deg[i - 1][0]; // find the difference by subtracting the lower resistance value from the table from the actual resistance value
            y2 = table_tmp61_5deg[i][0];     // find the difference by subtracting the higher resistance value from the table from the actual resistance value

            temparture = y1 + ((resistance - x1) / (x2 - x1)) * (y2 - y1); // Use the low value resistance and temperature
            return resistance;
            break;
        }
    }
    return -99.99f;
}

int TMP61::GetTemperature(int adc)
{
    resistance = calculateResistance(adc);

    return 0;
}