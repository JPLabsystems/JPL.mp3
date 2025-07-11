#ifndef POWER_H
#define POWER_H

#include "Arduino.h"


class Power
{
    public:
        Power(int sp, int cp);
        int getPercentage();
        double getVoltage();
        bool isCharging();
    private:
        int sensePin;
        int chargePin;
        int percentage;
        double voltage;
        void batteryCheck();
        bool charging;
};

#endif