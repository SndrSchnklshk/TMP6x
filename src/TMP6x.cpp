// (c) 2022 Sander Schinkelshoek
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "TMP6x.h"

float TMP6x::calculateResistance(int adc)
{
    tmp = 0;
    resistance = 0;

    tmp = vBiasBits * adc;
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

/// @brief Converts the given temperature to Fahrenheit
/// @param temperatureC Temperature in degrees Celcius
/// @return Returns the temperature in Fahrenheit
float TMP6x::ToFahrentheit(float temperatureC)
{
    return (temperatureC * 9.0f / 5.0f) + 32.0f;
}

//////////////////////////////////////////

int TMP61::getRecord(int row, short col)
{
    switch (voltage)
    {

    case TMP6x_Voltages::V18:
        return table_v18_tmp61_1deg[row][col];
    default:
    case TMP6x_Voltages::V33:
        return table_v33_tmp61_1deg[row][col];
    case TMP6x_Voltages::V50:
        return table_v50_tmp61_1deg[row][col];
    }
}

float TMP61::GetInterpolatedTemperature(int adc)
{
    resistance = calculateResistance(adc);

    for (int i = 0; i < 167; ++i)
    {
        if (getRecord(i, 1) >= resistance)
        {
            // Linear interpolation:
            //      y = y1 + ((x - x1) / (x2 - x1)) * (y2 - y1)

            x1 = getRecord(i - 1, 1);
            x2 = getRecord(i, 1);
            y1 = getRecord(i - 1, 0);
            y2 = getRecord(i, 0);

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
        if (getRecord(i, 1) >= resistance)
        {
            if (resistance - getRecord(i, 1) <= resistance - getRecord(i - 1, 1)) // if the high resistance is closer to the actual resistance
            {
                temparture = getRecord(i, 0);
            }
            else
            {
                temparture = getRecord(i - 1, 0);
            }
            return temparture;
        }
    }
    return TMP6x_ERROR;
}