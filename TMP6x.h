// (c) 2022 Sander Schinkelshoek
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef TMP6X_h
#define TMP6X_h

#define TMP6x_ERROR -99

class TMP6x
{
protected:
    float voltageIn = 0;
    float maxAdcVoltageGain = 0;
    int resistorBias = 0;
    int adcResolution = 12;
    int adcBits = 0;
    float voltageBiasBits = 0;
    float vBiasBits = 0;

    float temparture = 0;
    float resistance = 0;
    float tmp = 0;

    int x1 = 0; // the lower resistance value in the table
    int x2 = 0; // the higher resistance value in the table
    int y1 = 0; // the difference between the lower resistance value from the table from the actual resistance value
    int y2 = 0; // the difference between the higher resistance value from the table from the actual resistance value

    float calculateResistance(int adc);

public:
    TMP6x(float voltageIn, int resistorBias, int adcResolution, float maxAdcVoltageGain)
    {
        this->voltageIn = voltageIn;
        adcBits = (2 ^ adcResolution);
        if (maxAdcVoltageGain > 0)
            adcBits = (adcBits * voltageIn) / maxAdcVoltageGain;
        vBiasBits = voltageIn / (float)adcBits;
    }
    float LastCalculatedTemperature();
    float LastCalculatedResistance();
    float ToFahrentheit(float temperature);
};

class TMP61 : public TMP6x
{
private:
    int table_tmp61_5deg[34][2] = {
        {-40, 6543},
        {-35, 6761},
        {-30, 6987},
        {-25, 7220},
        {-20, 7460},
        {-15, 7707},
        {-10, 7962},
        {-5, 8225},
        {0, 8495},
        {5, 8772},
        {10, 9057},
        {15, 9350},
        {20, 9651},
        {25, 9959},
        {30, 10275},
        {35, 10599},
        {40, 10931},
        {45, 11270},
        {50, 11618},
        {55, 11975},
        {60, 12339},
        {65, 12712},
        {70, 13093},
        {75, 13483},
        {80, 13881},
        {85, 14288},
        {90, 14704},
        {95, 15129},
        {100, 15563},
        {105, 16006},
        {110, 16459},
        {115, 16921},
        {120, 17392},
        {125, 17874}};

    int table_tmp61_1deg[167][2] = {
        {-40, 6543},
        {-39, 6586},
        {-38, 6630},
        {-37, 6673},
        {-36, 6717},
        {-35, 6761},
        {-34, 6806},
        {-33, 6851},
        {-32, 6896},
        {-31, 6941},
        {-30, 6987},
        {-29, 7033},
        {-28, 7079},
        {-27, 7126},
        {-26, 7172},
        {-25, 7220},
        {-24, 7267},
        {-23, 7315},
        {-22, 7363},
        {-21, 7411},
        {-20, 7460},
        {-19, 7509},
        {-18, 7558},
        {-17, 7607},
        {-16, 7657},
        {-15, 7707},
        {-14, 7758},
        {-13, 7808},
        {-12, 7859},
        {-11, 7911},
        {-10, 7962},
        {-9, 8014},
        {-8, 8066},
        {-7, 8119},
        {-6, 8172},
        {-5, 8225},
        {-4, 8278},
        {-3, 8332},
        {-2, 8386},
        {-1, 8440},
        {0, 8495},
        {1, 8550},
        {2, 8605},
        {3, 8660},
        {4, 8716},
        {5, 8772},
        {6, 8829},
        {7, 8885},
        {8, 8942},
        {9, 9000},
        {10, 9057},
        {11, 9115},
        {12, 9174},
        {13, 9232},
        {14, 9291},
        {15, 9350},
        {16, 9410},
        {17, 9469},
        {18, 9529},
        {19, 9590},
        {20, 9651},
        {21, 9712},
        {22, 9773},
        {23, 9835},
        {24, 9897},
        {25, 9959},
        {26, 10021},
        {27, 10084},
        {28, 10147},
        {29, 10211},
        {30, 10275},
        {31, 10339},
        {32, 10403},
        {33, 10468},
        {34, 10533},
        {35, 10599},
        {36, 10664},
        {37, 10731},
        {38, 10797},
        {39, 10864},
        {40, 10931},
        {41, 10998},
        {42, 11066},
        {43, 11134},
        {44, 11202},
        {45, 11270},
        {46, 11339},
        {47, 11409},
        {48, 11478},
        {49, 11548},
        {50, 11618},
        {51, 11689},
        {52, 11760},
        {53, 11831},
        {54, 11903},
        {55, 11975},
        {56, 12047},
        {57, 12119},
        {58, 12192},
        {59, 12265},
        {60, 12339},
        {61, 12413},
        {62, 12487},
        {63, 12562},
        {64, 12637},
        {65, 12712},
        {66, 12787},
        {67, 12863},
        {68, 12940},
        {69, 13016},
        {70, 13093},
        {71, 13170},
        {72, 13248},
        {73, 13326},
        {74, 13404},
        {75, 13483},
        {76, 13562},
        {77, 13641},
        {78, 13721},
        {79, 13801},
        {80, 13881},
        {81, 13962},
        {82, 14043},
        {83, 14124},
        {84, 14206},
        {85, 14288},
        {86, 14371},
        {87, 14454},
        {88, 14537},
        {89, 14620},
        {90, 14704},
        {91, 14789},
        {92, 14873},
        {93, 14958},
        {94, 15043},
        {95, 15129},
        {96, 15215},
        {97, 15302},
        {98, 15389},
        {99, 15476},
        {100, 15563},
        {101, 15651},
        {102, 15739},
        {103, 15828},
        {104, 15917},
        {105, 16006},
        {106, 16096},
        {107, 16186},
        {108, 16277},
        {109, 16368},
        {110, 16459},
        {111, 16551},
        {112, 16643},
        {113, 16735},
        {114, 16828},
        {115, 16921},
        {116, 17014},
        {117, 17108},
        {118, 17203},
        {119, 17297},
        {120, 17392},
        {121, 17488},
        {122, 17584},
        {123, 17680},
        {124, 17777},
        {125, 17874}};

public:
    TMP61(float voltageBias, int adcResolution, float maxAdcVoltageGain) : TMP6x(voltageBias, 10000, adcResolution, maxAdcVoltageGain)
    {
    }
    float GetInterpolatedTemperature(int adc);
    int GetTemperature(int adc);
};

#endif