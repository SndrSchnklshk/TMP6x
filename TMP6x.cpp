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

float TMP6x::LastCalculatedTemperature()
{
    return temparture;
}

float TMP6x::LastCalculatedResistance()
{
    return resistance;
}

float TMP6x::ToFahrentheit(float temperatureC)
{
    return (temperatureC * 9.0f / 5.0f) + 32.0f;
}

//////////////////////////////////////////

float TMP61::GetInterpolatedTemperature(int adc)
{
    resistance = calculateResistance(adc);

    for (int i = 0; i < 34; ++i)
    {
        if (table_tmp61_5deg[i][1] >= resistance)
        {
            // Linear interpolation:
            //      y = y1 + ((x - x1) / (x2 - x1)) * (y2 - y1)

            x1 = table_tmp61_5deg[i - 1][1];
            x2 = table_tmp61_5deg[i][1];
            y1 = table_tmp61_5deg[i - 1][0];
            y2 = table_tmp61_5deg[i][0];

            temparture = y1 + ((resistance - x1) / (x2 - x1)) * (y2 - y1);

            return temparture;
        }
    }
    return TMP6x_ERROR;
}

int TMP61::GetTemperature(int adc)
{
    resistance = calculateResistance(adc);
    for (int i = 0; i < 167; ++i)
    {
        if (table_tmp61_1deg[i][1] >= resistance)
        {
            if (resistance - table_tmp61_1deg[i][1] <= resistance - table_tmp61_1deg[i - 1][1]) // if the high resistance is closer to the actual resistance
            {
                temparture = table_tmp61_1deg[i][0];
            }
            else
            {
                temparture = table_tmp61_1deg[i - 1][0];
            }
            return temparture;
        }
    }
    return TMP6x_ERROR;
}