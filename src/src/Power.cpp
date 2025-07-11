#include "Power.h"
#include "Arduino.h"

Power::Power(int sp, int cp)
{
  sensePin = sp;
  chargePin = cp;
}

void Power::batteryCheck()
{
  /*
  adc resolution / system voltage = adc reading / voltage measured
  system voltage * ADC Reading / adc resolution

  vout = (vsource * R2) /(R1+R2)
  vout*(R1 +R2) / R2 = vsource
  */

  // voltage = (((double)(3.3 * analogRead(sensePin)) / 4095) * (2000)) / 1000;
  voltage = ((double)(analogReadMilliVolts(sensePin) * 2000) / 1000) / 1000;

  percentage = 100 * ((voltage - 3.35) / .8);
}

int Power::getPercentage()
{
  batteryCheck();
  return percentage;
}

double Power::getVoltage()
{
  batteryCheck();
  return voltage;
}

bool Power::isCharging()
{
  return false;
}
