/*
#include "Display.h"

Display::Display(int RST, int CS, int DC, int backlightPin, int brightness)
{
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

    digitalWrite(backlightPin, brightness);
    tft.init(240, 320);
    tft.fillScreen(ST77XX_BLACK);
    tft.setRotation(2);
}

void Display::drawScreen(int style, List *list;)
{
    switch (style)
    {
    case 1:
        // home screen
    case 2:
        // list
    case 3:
        // settings
    }
}

int Display::navigate(int direction)
{
    
}

void Display::drawStatusBar(double b, double v)
{
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);
    tft.setCursor(3, 15);
    tft.print("Volume: ");
    tft.print(v);
    tft.print("% | ");
    tft.print("Battery: ");
    tft.print(b);
    tft.print("%");
    tft.drawFastHLine(1, 20, 239, ST77XX_WHITE);
}
*/