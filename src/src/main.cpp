// Firmware Proto. WIP

//hi

/////////LIBRARY INCLUDES/////////

#include "config.h"

#include <Arduino.h>
#include <SPI.h>
// #include "SD.h"
#include "FS.h"
#include "USB.h"
#include "USBMSC.h"
#include "SD_MMC.h"
#include <vector>
#include <string>

// Graphics Libraries + fontsf
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

// encoder lib
#include <RotaryEncoder.h>

// db lib
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

#include "queries.h"
#include "database.h"

// sound
#include <Audio.h>
#include <driver/i2s.h>

#include <Power.h>

/////////CONSTRUCTORS/////////

RotaryEncoder *encoder = nullptr;

Audio audio;

Power powerBattery(batSensePin, chargeSensePin);

hw_timer_t *timer = NULL;
volatile bool timerFlag = false;

// hw_

// USBMSC msc;

// USBMSC msc;

/////////VARIABLES/////////

volatile int level = 1;
volatile bool redrawScreen = false;
volatile bool clearScreen = false;
volatile bool clearMenuFlag = false;
volatile bool clearSubMenuFlag = false;
volatile bool isPlayingScreen = false;
volatile bool playbackStatus = false;
volatile int returnToScreen;
volatile bool advanceScreen = false;

volatile int y = 1;
volatile int navY = 1;

volatile int x = 1;
volatile int w = 1;
volatile int z = 0;
volatile int l2limit;

volatile bool batteryTimerFlag;
volatile int batCount = 0; // innactivity timer

String globalPiecename;
String globalLength;

volatile int volume = 12;
int battery = powerBattery.getVoltage();
#include "gui.h"

volatile bool changeStatusFlag;

////function declarations////

std::vector<String> pieceArgv;
std::vector<String> composerArgv;
bool initLists();

void powerDown()
{
  esp_deep_sleep_start();
}

void audio_eof_mp3(const char *info)
{
  advanceTrack();
  /*
  static int i = 0;
  while(i < argv.length())
  {
    audio.connecttoFS("")
  }
  */
}
/////////ISRS/////////

void IRAM_ATTR checkPosition()
{
  batCount = 0;
  if (isPlayingScreen != true)
  {
    static int pos = 0;
    encoder->tick(); // just call tick() to check the state.
    int newPos = encoder->getPosition();

    if (pos != newPos)
    {
      redrawScreen = true;
      if (newPos > pos)
      {
        y++;
        navY++;
      }
      else if (newPos < pos)
      {
        y--;
        navY--;
      }
      pos = newPos;
    }

    switch (screen)
    {
    case 1:
      clearMenuFlag = true;
      if (y > 4)
      {
        y = 4;
      }
      if (y < 1)
      {
        y = 1;
      }
      break;
    case 2:
      clearSubMenuFlag = true;

      if (y > 10)
      {
        y = 1; // pageturn
        w++;
        advanceScreen = true;
      }
      if (y < 1)
      {
        if (w == 1)
          y = 1;
        navY = 1;
        if (w > 1)
        {
          y = 10;
          w--;
          advanceScreen = true;
        }
      }

      break;
    case 3:
      clearSubMenuFlag = true;
      if (y > argv.size())
      {
        y = argv.size();
      }
      if (y < 1)
      {
        y = 1;
      }
      break;
    case 4:
      clearSubMenuFlag = true;
      if (y > argv.size())
      {
        y = argv.size();
      }
      if (y < 1)
      {
        y = 1;
      }
      break;
    case 5:
      // settings menu stuff
      // brightness
      // sd card
      // battery voltage
      //
      break;
    case 6:
      if (y > argv.size())
      {
        y = argv.size();
      }
      if (y < 1)
      {
        y = 1;
      }
      clearSubMenuFlag = true;
      break;
    case 7:
      break;
    }
  }

  /*
    if (level == 1)
    {
      y = y + 1;
      clearMenuFlag = true;
    }
    else if (level == 2)
    {
      x = x + 1;
      clearSubMenuFlag = true;
    }
  }
  else if (newPos < pos)
  {
    if (level == 1)
    {
      y = y - 1;
      clearMenuFlag = true;
    }
    else if (level == 2)
    {
      x = x - 1;
      clearSubMenuFlag = true;
    }
  }
  */
}
volatile bool powerFlag = false;
unsigned long lastPressedTime;
volatile bool sdFlag;
void IRAM_ATTR centerButton()
{
  batCount = 0;
  // Debounce
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    switch (screen)
    {
    case 1:
      switch (y)
      {
      case 1:
        screen = 2;
        break;
      case 2:
        screen = 3;
        y = 1;
        break;
      case 3:
        screen = 4;
        y = 1;
        break;
      case 4:
        screen = 5;
        y = 1;
        break;
      }
      break;
    case 2:
      screen = 7;
      filteredBy = 2;
      break;
    case 3:
      screen = 6;
      // argv.clear();
      recalcDb = true;
      filteredBy = 3;
      break;
    case 4:
      screen = 6;
      // argv.clear();
      recalcDb = true;
      filteredBy = 4;

      break;
    case 5:

      switch (y)
      {
      case 1:
        ESP.restart();
        break;
      case 2:
        sdFlag = true;
        break;
      case 3:
        powerFlag = true;
        break;
      case 4:
        break;
      }

      break;
    case 6:
      screen = 7;
    case 7:
      break;
    }
    clearScreen = true;
    redrawScreen = true;
  }
  last_interrupt_time = interrupt_time;
}

void IRAM_ATTR centerRelase()
{
  /*
  unsigned long pressedTime = millis();
  if((pressedTime- lastPressedTime) > 30000)
  {
    ESP.restart();
  }
  */
}

void IRAM_ATTR topButton()
{
  batCount = 0;

  // Debounce
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    isPlayingScreen = false;

    switch (screen)
    {
    case 1:
      if (playbackStatus == true)
      {
        returnToScreen = 7;
      }
      break;
    case 2:
      screen = 1;
      y = 1;
      navY = 1;
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    case 3:
      screen = 1;
      y = 2;
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    case 4:
      screen = 1;
      y = 3;
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    case 5:
      screen = 1;
      y = 4;
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    case 6:
      switch (filteredBy)
      {
      case 3:
        screen = 3;
        break;
      case 4:
        screen = 4;
        break;
      }
      y = 1;
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    case 7:
      z = 0;
      argv.clear();
      switch (filteredBy)
      {
      case 2:
        screen = 2;
        navY = 1;
        y = 1;
        break;
      case 3:
        screen = 3;
        y = 1;

        break;
      case 4:
        screen = 4;
        y = 1;

        break;
      }
      clearScreen = true;
      redrawScreen = true;
      argv.clear();
      recalcDb = true;
      break;
    default:
      break;
    }
  }
  last_interrupt_time = interrupt_time;
}

volatile bool pauseResumeFlag = false;
void IRAM_ATTR bottomButton()
{
  batCount = 0;

  // Debounce
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    pauseResumeFlag = true;
  }
  last_interrupt_time = interrupt_time;
}

volatile bool changeVolumeFlag = false;

void IRAM_ATTR volumeUp()
{
  batCount = 0;

  changeStatusFlag = true;

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200)
  {
    last_interrupt_time = interrupt_time;
    volume = volume + 1;
    if (volume >= 21)
    {
      volume = 21;
    }
    changeVolumeFlag = true;
  }
  // last_interrupt_time = interrupt_time;
}

void IRAM_ATTR volumeDown()
{
  batCount = 0;

  changeStatusFlag = true;

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    last_interrupt_time = interrupt_time;
    volume = volume - 1;
    if (volume <= 0)
    {
      volume = 0;
    }
    changeVolumeFlag = true;
  }
  // last_interrupt_time = interrupt_time;
}

volatile bool rightButtonFlag;
void IRAM_ATTR rightButton()
{
  batCount = 0;

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    last_interrupt_time = interrupt_time;
    rightButtonFlag = true;
  }
  last_interrupt_time = interrupt_time;
}

volatile bool holdState = false;
volatile bool holdFlag = false;
const unsigned long debounceDelay = 200; // Renamed for clarity

void IRAM_ATTR holdFunc()
{
  batCount = 0;

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceDelay)
  {
    last_interrupt_time = interrupt_time;
    holdState = !holdState;
    holdFlag = true;
  }
  // last_interrupt_time should NOT be updated unconditionally
}

void IRAM_ATTR powerFunc()
{
  powerFlag = true;
}

void IRAM_ATTR batteryTimer()
{
  batteryTimerFlag = true;
  changeStatusFlag = true;

  batCount++;
}

volatile bool leftButtonFlag;
void IRAM_ATTR leftFunc()
{
  batCount = 0;

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    last_interrupt_time = interrupt_time;
    leftButtonFlag = true;
  }
  last_interrupt_time = interrupt_time;
}
/////////SETUP/////////

void setup()
{
  noInterrupts();

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &batteryTimer, true);
  timerAlarmWrite(timer, 5000000, true);
  timerAlarmEnable(timer);

  interrupts();

  battery = powerBattery.getPercentage();

  Serial.begin(9600);
  SPI.begin();

  pinMode(14, INPUT_PULLUP);

  pinMode(center, INPUT_PULLUP);
  attachInterrupt(center, centerButton, FALLING);
  // attachInterrupt(center, centerRelase, RISING);

  pinMode(up, INPUT_PULLUP);
  attachInterrupt(up, topButton, FALLING);

  pinMode(down, INPUT_PULLUP);
  attachInterrupt(down, bottomButton, FALLING);

  pinMode(right, INPUT_PULLUP);
  attachInterrupt(right, rightButton, FALLING);

  pinMode(vUp, INPUT_PULLUP);
  attachInterrupt(vUp, volumeDown, FALLING);

  pinMode(vDown, INPUT_PULLUP);
  attachInterrupt(vDown, volumeUp, FALLING);

  pinMode(hold, INPUT_PULLUP);
  attachInterrupt(hold, holdFunc, CHANGE);

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(0, powerFunc, FALLING);

  pinMode(left, INPUT_PULLUP);
  attachInterrupt(left, leftFunc, FALLING);

  encoder = new RotaryEncoder(encA, encB, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(encA, checkPosition, CHANGE);
  attachInterrupt(encB, checkPosition, CHANGE);

  SD_MMC.setPins(36, 35, 37);
  if (!SD_MMC.begin("/sdcard", true))
  {
    Serial.println("SD init failure");
  }
  else
  {
    Serial.println("SD initialized successfully!");
  }

  sqlite3_initialize();
  int rc = sqlite3_open("/sdcard/player/playerdb.db3", &db);
  if (rc != SQLITE_OK)
  {
    Serial.println("SQLite error");
  }
  else
  {
    Serial.println("DB loaded!");
  }

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(21); // 0...21

  tft.init(240, 320);
  pinMode(9, OUTPUT);
  analogWrite(9, 100); // brigthness??
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);

  tft.setCursor(0, 160);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  tft.print("    JPL.mp3\n    v0.1.3.a\n    fw v1.00.10.5.25");
  delay(3000);
  tft.setTextSize(1);

  cleanScreen();

  screen1(1);
  drawStatusBar(battery, volume);

  esp_sleep_enable_ext0_wakeup(static_cast<gpio_num_t>(digitalPinToInterrupt(38)), LOW); // Wake up on low level
  screen = 1;

  ////////
}

/////////LOOP/////////

void loop()
{
  // Serial.println(audio.getAudioFileDuration());
  audio.loop();

  if (screen == 7 && playbackStatus == true) // update progress bar
  {
    updateProgress();
  }
  if (leftButtonFlag)
  {
    leftButtonFlag = false;
    audio.stopSong();
    advanceTrack();
    z--;
  }
  if (rightButtonFlag)
  {
    rightButtonFlag = false;
    audio.stopSong();
    advanceTrack();
    z++;
  }
  if (changeStatusFlag)
  {
    changeStatusFlag = false;
    drawStatusBar(battery, volume);
  }
  if (sdFlag)
  {
    sdFlag = false;

    SD_MMC.setPins(36, 35, 37);
    SD_MMC.begin("/sdcard", true);
    sqlite3_initialize();
    sqlite3_open("/sdcard/player/playerdb.db3", &db);
  }

  if (batteryTimerFlag)
  {
    noInterrupts();
    batteryTimerFlag = false;
    interrupts();

    // Serial.println("TIMER FUNCTION WOOHOO");

    int p = powerBattery.getPercentage();
    battery = p;
    if (p == 0)
    {
      powerDown();
    }

    if (batCount > 5 && playbackStatus == false)
    {
      Serial.println(gpio_reset_pin(GPIO_NUM_16)); // Resets all configurations of pin 5
      Serial.println(esp_sleep_enable_ext0_wakeup(GPIO_NUM_16, LOW));

      esp_deep_sleep_start();
    }
    // more stuff
  }
  if (advanceScreen)
  {
    l2limit = advanceScreen2();
    advanceScreen = false;
  }
  if (powerFlag)
  {
    powerFlag = false;
    Serial.println(gpio_reset_pin(GPIO_NUM_16)); // Resets all configurations of pin 5
    Serial.println(esp_sleep_enable_ext0_wakeup(GPIO_NUM_16, LOW));

    esp_deep_sleep_start();
  }
  if (changeVolumeFlag)
  {
    audio.setVolume(volume);
    changeVolumeFlag = false;
    drawStatusBar(battery, volume);
  }
  if (pauseResumeFlag)
  {
    audio.pauseResume();
    pauseResumeFlag = false;
  }
  if (holdFlag)
  {
    Serial.println(holdState);
    holdFlag = false;
  }

  if (clearScreen == true)
  {
    cleanScreen();
    clearScreen = false;
  }
  if (clearMenuFlag == true)
  {
    clearMenu();
    clearMenuFlag = false;
  }
  if (clearSubMenuFlag == true)
  {
    cleanSubmenuCursor();
    clearSubMenuFlag = false;
  }

  if (redrawScreen == true)
  {
    if (screen != 1)
    {
      drawStatusBar(battery, volume);
    }
    /*
    if (level == 1)
    {
      drawMenu(y);
    }

    if (level == 2)
    {
      drawSubmenu(y);
    }

    if (level == 3)
    {
      drawFilterMenu(argv[x - 1]);
    }

    if (level == 4)
    {
      beginPlayback(argv[x - 1]);
    }
    */

    switch (screen)
    {
    case 1:
      screen1(y);
      break;
    case 2:
      screen2();
      break;
    case 3:
      screen3();
      break;
    case 4:
      screen4();
      break;
    case 5:
      screen5();
      break;
    case 6:
      const char *sql;
      if (filteredBy == 3)
      {
        sql = queries[3];
      }
      else if (filteredBy == 4)
      {
        sql = queries[4];
      }
      screen6(argv[y - 1], sql);
      break;
    case 7:
      screen7(argv[navY - 1]);
      break;
    }
    if (returnToScreen == 7)
    {
      returnToScreen7();
    }
    redrawScreen = false;
  }
}