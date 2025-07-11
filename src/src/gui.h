#ifndef gui_h
#define gui_h

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Arduino.h>

#include "queries.h"
#include "config.h"
#include "database.h"

#define backgroundColor ST77XX_BLACK
#define primaryColor ST77XX_WHITE
#define accentColor ST77XX_ORANGE

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

std::vector<String> argv;

// volatile int y = 1;
// volatile int x = 1;
volatile bool recalcDb = true;

volatile int screen = 1;

volatile bool piecemenuFlag = false;

volatile int filteredBy;

String secondsToMin(int secs);

typedef struct pieceInfo
{
  String title;
  String composer;
  String era;
  String performer;
  double lengthSecs;
};

pieceInfo getInfo(String pN)
{
  // to be implemented with overloads
}

/*
1 = home screen

2 = all pieces
3 = composers
4 = eras
5 = settings

6 = pieces, filtered

7 = playing

1 - 2 - 7
1 - 3, 4 - 6 - 7
*/

void drawStatusBar(int per, int v)
{
  tft.fillRect(0, 0, 240, 20, ST77XX_BLACK);
  tft.setFont(NULL);
  // tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.setCursor(3, 3);
  tft.print("V/");
  tft.print(v);
  tft.print(" | ");
  tft.print("B/");
  int p = per;
  if (p <= 20)
  {
    tft.setTextColor(ST77XX_RED);
  }
  if (p > 100)
  {
    tft.print("100");
  }
  else if (p < 0)
  {
    tft.print("0");
  }
  else
  {
    tft.print(p);
  }
  tft.setTextColor(ST77XX_WHITE);
  tft.print("% ");
  // Serial.println(powerBattery.getVoltage());
  // tft.print(powerBattery.getVoltage());
  // tft.print("V");
  // tft.print(" | ");
  tft.setCursor(3, 310);
  tft.print("P/");
  tft.print(globalPiecename);
  // tft.print(" | ");

  // tft.drawFastHLine(1, 20, 239, ST77XX_WHITE);
}

void beginPlayback(String Title)
{

  sqlite3_stmt *statement = prepbindStmt(db, queries[5], (char *)Title.c_str());
  // String Title = execComplexStmt(statement);

  tft.setCursor(20, 100);
  tft.print(Title);
  tft.setCursor(20, 130);
  // tft.print(Title);

  // call sql for file path
  // set audio host to that file path
  // call sql for rest of the metadata
  // fill the screen with pretty graphicsSuper goed, he?
  //
  // audio.connecttoFS(SD, title);
}

/*

void drawMenu(int yPos)
{
  tft.drawCircle(0, 160, 100, ST77XX_WHITE);
  tft.drawCircle(0, 160, 78, ST77XX_WHITE);
  tft.drawCircle(0, 160, 24, ST77XX_WHITE);
  tft.fillTriangle(83, 165, 83, 155, 95, 160, ST77XX_ORANGE);

  // drawStatusBar(100, 50);

  if (yPos == 1)
  {
    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("                    ");

    tft.setCursor(106, 141);
    tft.print("                    ");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Pieces");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Composers");

    tft.setCursor(94, 216);
    tft.print("Eras");

    tft.setCursor(77, 241);
    tft.print("Settings");

    tft.setTextSize(0);
  }
  else if (yPos == 2)
  {
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("                    ");

    tft.setCursor(106, 141);
    tft.print("Pieces");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Composers");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Eras");

    tft.setCursor(94, 216);
    tft.print("Settings");

    tft.setCursor(77, 241);
    tft.print("                    ");
  }
  else if (yPos == 3)
  {
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("Pieces");

    tft.setCursor(106, 141);
    tft.print("Composers");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Eras");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Settings");

    tft.setCursor(94, 216);
    tft.print("                    ");

    tft.setCursor(77, 241);
    tft.print("                    ");
  }
  else if (y == 4)
  {
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("Pieces");

    tft.setCursor(94, 116);
    tft.print("Composers");

    tft.setCursor(106, 141);
    tft.print("Eras");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Settings");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("                    ");

    tft.setCursor(94, 216);
    tft.print("                    ");

    tft.setCursor(77, 241);
    tft.print("                    ");
  }
}

void drawSubmenu(int lastY)
{
  drawStatusBar(100, 50);

  if (lastY == 1) // pieces
  {
    if (recalcDb == true)
    {
      argv = exec1byX(prepStmt(db, queries[0]));
      recalcDb = false;

      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.setTextSize(1);
      tft.setTextWrap(false);

      for (int i = 0; i < argv.size(); i++)
      {
        tft.setCursor(10, 20 + 24 * (i + 1));
        tft.print(argv[i]);
      }
    }
    tft.fillRect(2, 11 + 24 * x, 4, 4, ST77XX_ORANGE);
  }

  if (lastY == 2) // composers
  {
    if (recalcDb == true)
    {
      argv = exec1byX(prepStmt(db, queries[1]));
      recalcDb = false;

      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.setTextSize(1);
      tft.setTextWrap(false);

      for (int i = 0; i < argv.size(); i++)
      {
        tft.setCursor(10, 20 + 24 * (i + 1));
        tft.print(argv[i]);
      }
    }
    tft.fillRect(2, 11 + 24 * x, 4, 4, ST77XX_ORANGE);
  }

  if (lastY == 3) // eras
  {
    if (recalcDb == true)
    {
      argv = exec1byX(prepStmt(db, queries[2]));
      recalcDb = false;

      tft.setFont(&FreeSans9pt7b);
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.setTextSize(1);
      tft.setTextWrap(false);

      for (int i = 0; i < argv.size(); i++)
      {
        tft.setCursor(10, 20 + 24 * (i + 1));
        tft.print(argv[i]);
      }
    }
    tft.fillRect(2, 11 + 24 * x, 4, 4, ST77XX_ORANGE);
  }

  if (lastY == 4) // settings
  {
    argv = execXby1(prepbindStmt(db, queries[6], "/library/00000005.mp3"));
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    for (int i = 0; i < argv.size(); i++)
    {
      tft.setCursor(10, 20 + 24 * (i + 1));
      tft.print(argv[i]);
    }
  }
}

void drawFilterMenu(String filter)
{

  char *sqlitem = (char *)filter.c_str();
  argv = exec1byX(prepbindStmt(db, queries[3], sqlitem));
  recalcDb = false;

  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextWrap(false);

  for (int i = 0; i < argv.size(); i++)
  {
    tft.setCursor(10, 20 + 24 * (i + 1));
    tft.print(argv[i]);
  }
  tft.fillRect(2, 11 + 24 * x, 4, 4, ST77XX_ORANGE);
}

*/

void clearMenu()
{
  tft.fillRect(77, 71, 100, 40, ST77XX_BLACK);
  tft.fillRect(94, 96, 100, 40, ST77XX_BLACK);
  tft.fillRect(106, 121, 100, 40, ST77XX_BLACK);
  tft.fillRect(110, 146, 100, 40, ST77XX_BLACK);
  tft.fillRect(106, 171, 100, 40, ST77XX_BLACK);
  tft.fillRect(94, 196, 100, 40, ST77XX_BLACK);
  tft.fillRect(77, 221, 100, 40, ST77XX_BLACK);
}

void cleanScreen()
{
  tft.fillRect(0, 20, 240, 320, ST77XX_BLACK);
}

void cleanSubmenuCursor()
{
  tft.fillRect(2, 21, 4, 300, ST77XX_BLACK);
}

////////////////////////////////////

void screen1(int y) // menu
{
  argv.clear();

  tft.drawCircle(0, 160, 100, ST77XX_WHITE);
  tft.drawCircle(0, 160, 78, ST77XX_WHITE);
  tft.drawCircle(0, 160, 24, ST77XX_WHITE);
  tft.fillTriangle(83, 165, 83, 155, 95, 160, ST77XX_ORANGE);

  // drawStatusBar(100, 50);
  switch (y)
  {
  case 1:
    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("                    ");

    tft.setCursor(106, 141);
    tft.print("                    ");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Pieces");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Composers");

    tft.setCursor(94, 216);
    tft.print("Eras");

    tft.setCursor(77, 241);
    tft.print("Settings");

    tft.setTextSize(0);
    break;

  case 2:
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("                    ");

    tft.setCursor(106, 141);
    tft.print("Pieces");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Composers");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Eras");

    tft.setCursor(94, 216);
    tft.print("Settings");

    tft.setCursor(77, 241);
    tft.print("                    ");
    break;
  case 3:

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("                    ");

    tft.setCursor(94, 116);
    tft.print("Pieces");

    tft.setCursor(106, 141);
    tft.print("Composers");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Eras");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("Settings");

    tft.setCursor(94, 216);
    tft.print("                    ");

    tft.setCursor(77, 241);
    tft.print("                    ");
    break;
  case 4:
    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    tft.setCursor(77, 91);
    tft.print("Pieces");

    tft.setCursor(94, 116);
    tft.print("Composers");

    tft.setCursor(106, 141);
    tft.print("Eras");

    tft.setFont(&FreeSansBold9pt7b);

    tft.setCursor(110, 166);
    tft.print("Settings");

    tft.setFont(&FreeSans9pt7b);

    tft.setCursor(106, 191);
    tft.print("                    ");

    tft.setCursor(94, 216);
    tft.print("                    ");

    tft.setCursor(77, 241);
    tft.print("                    ");
    break;
  default:
    break;
  }
}

void screen2() // all pieces
{
  drawStatusBar(battery, volume);
  const char *query = "SELECT piecename FROM library ORDER BY composer";

  if (recalcDb == true)
  {
    argv = exec1byX(prepStmt(db, query));
    std::vector<std::vector<String>> twodargv((argv.size() / 12) + 1, std::vector<String>(12));

    Serial.print("argv size: ");
    Serial.println(argv.size() / 12 + 1);
    // twodargv[0][0] = "hello";

    for (int i = 0; i < (argv.size() / 10) + 1; i++)
    {
      for (int j = 1; j <= 10; j++)
      {
        // Serial.println(twodargv[i][j-1]);
        twodargv[i].at(j - 1) = argv[j - 1];
        // twodargv[i].set(argv[(j-1) * i]);
      }
    }

    /*
        for (int i = 0; i < (argv.size() / 12) + 1; i++)
        {
          Serial.println(i);
          for (int j = 0; j < 12; j++)
          {
            Serial.println(twodargv.at(i).at(j));
          }
        }
    */

    recalcDb = false;

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    for (int i = 0; i < 10; i++)
    {
      tft.setCursor(10, 20 + 24 * (i + 1));
      tft.print(argv[i]);
      // tft.print(twodargv[w - 1][i]);
    }
  }
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

int advanceScreen2()
{
  Serial.print("\n\nFLAG\n\n");
  cleanScreen();

  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextWrap(false);

  int limit;
  if (w == 1)
  {
    limit = 10;
  }
  else if (w * 10 > argv.size())
  {
    limit = argv.size() % 10;
  }
  else
  {
    limit = 10;
  }
  for (int i = 0; i < limit; i++)
  {
    tft.setCursor(10, 20 + 24 * (i + 1));
    tft.print(argv[i + ((w - 1) * 10)]);
    // tft.print(twodargv[w - 1][i]);
  }
  return limit;
}

void screen3() // composers
{
  const char *query = "SELECT DISTINCT composer FROM library";

  if (recalcDb == true)
  {

    argv.clear();
    argv = exec1byX(prepStmt(db, query));

    recalcDb = false;

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    for (int i = 0; i < argv.size(); i++)
    {
      tft.setCursor(10, 20 + 24 * (i + 1));
      tft.print(argv[i]);
    }
  }
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

void screen4() // eras
{
  if (recalcDb == true)
  {
    argv = exec1byX(prepStmt(db, queries[2]));
    recalcDb = false;

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    for (int i = 0; i < argv.size(); i++)
    {
      tft.setCursor(10, 20 + 24 * (i + 1));
      tft.print(argv[i]);
    }
  }
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

void screen5() // settings
{
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextWrap(false);

  tft.setCursor(10, 20 + 24);
  tft.print("RESET");

  tft.setCursor(10, 20 + 48);
  tft.print("SD RESCAN");

  tft.setCursor(10, 20 + 72);
  tft.print("POWER OFF");

  tft.setCursor(10, 20 + 96);
  tft.print("BRIGHTNESS");

  tft.fillRect(10, 120, 100, 100, ST77XX_BLACK);
  tft.setCursor(10, 20 + 120);
  tft.print(powerBattery.getVoltage());
  tft.print(" Volts");

  cleanSubmenuCursor();
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

void screen6(String condition, const char *sql)
{
  if (recalcDb == true)
  {
    Serial.println("\nPOINT THREE");

    argv.clear();
    y = 1;

    argv = exec1byX(prepbindStmt(db, sql, (char *)condition.c_str()));

    std::vector<String> smallList;

    recalcDb = false;

    tft.setFont(&FreeSans9pt7b);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);

    for (int i = 0; i < argv.size(); i++)
    {
      tft.setCursor(10, 20 + 24 * (i + 1));
      tft.print(argv[i]);
    }
  }
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

void screen7(String piecename) // playback screen
{
  // pieceInfo = getInfo(piecename);

  String Filepath = execSimpleStmt(prepbindStmt(db, queries[5], (char *)piecename.c_str()));
  char *filepath = (char *)Filepath.c_str();

  globalPiecename = piecename;

  drawStatusBar(battery, volume);

  // Serial.println(filepath);
  playbackStatus = audio.connecttoFS(SD_MMC, filepath);
  isPlayingScreen = true;

  String Composer = execSimpleStmt(prepbindStmt(db, "SELECT composer FROM library WHERE piecename = ?", (char *)piecename.c_str()));

  String l = execSimpleStmt(prepbindStmt(db, "SELECT length FROM library WHERE piecename = ?", (char *)piecename.c_str()));
  int length = l.toInt();

  /*
  Serial.print("\nlengths:");Serial.print(l);Serial.print(" and ");Serial.println(secondsToMin(length));
  */

  tft.setFont(&FreeSansBold9pt7b);

  // tft.setTextSize(2);

  int titleLength = piecename.length();
  // Serial.println(titleLength);
  String chopt = "";
  int d = titleLength / 20;
  if (titleLength > 20)
  {
    int divisions = titleLength / 20;
    // Serial.println(divisions);
    for (int i = 0; i < divisions; i++)
    {
      String piece = "";
      piece = piecename.substring(20 * i, 20 * (i + 1));
      
      // PRETTY STRING NEWLINE - to be figured out
      /*
      int spaceIndex;
      for (int j = 19; j >= 0  j--)
      {
        bool flag = true;
        if (flag)
        {
          if (piece.charAt(j) = " " && piece.charAt(19) != " ")
          piece.setCharAt(i, \n);
          flag = false;
        }
      }
      */
     
      chopt += piece;
      chopt += "\n    ";
    }
    chopt += piecename.substring(divisions * 20, divisions * 20 + titleLength % 20);
  }
  else
  {
    chopt = piecename;
  }

  tft.setTextWrap(false /*true*/);

  tft.setCursor(20, 50);
  tft.print(chopt);
  tft.setFont(&FreeSans9pt7b);

  tft.setCursor(20, 50 + (20 * d) + 24);
  tft.print(Composer);

  tft.setCursor(20, 270);
  globalLength = secondsToMin(length);
  // tft.print(audio.getAudioCurrentTime());
  // tft.print("/");
  // tft.print(secondsToMin(length));

  // tft.drawRect(20, 290, 200, 10, ST77XX_WHITE);

  // call sql for file path
  // set audio host to that file path
  // call sql for rest of the metadata
  // fill the screen with pretty graphicsSuper goed, he?
  //
  // audio.connecttoFS(SD, title);
}

void returnToScreen7()
{
  tft.setTextWrap(true);
  tft.setCursor(20, 100);
  tft.print(globalPiecename);
  tft.setCursor(20, 200);
  // tft.print(filepath);

  tft.setCursor(20, 270);
  tft.print(audio.getAudioFileDuration());
  tft.drawRect(20, 290, 200, 10, ST77XX_WHITE);
}

/*!
  @brief begin playback of subsequent track
*/
void advanceTrack()
{
  if (y + z <= argv.size())
  {
    cleanScreen();
    screen7(argv[y + z]);
  }
}

void updateProgress()
{
  static unsigned long lastUpdateTime = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= 100)
  {
    int cur = audio.getAudioCurrentTime();
    int dur = audio.getAudioFileDuration();
    tft.setFont(&FreeSans9pt7b);
    tft.fillRect(20, 263, 100, 20, ST77XX_BLACK); // clears timestamp

    tft.fillRect(20, 288, 200, 2, ST77XX_BLACK); // clears progress bar
    tft.fillRect(20, 300, 200, 3, ST77XX_BLACK);
    tft.fillRect(10, 280, 10, 25, ST77XX_BLACK);

    tft.setCursor(20, 278);
    tft.printf("%s/%s", secondsToMin(cur).c_str(), secondsToMin(dur).c_str());

    // Serial.printf("current time: %d \n", audio.getAudioCurrentTime());
    double prop;
    if (cur == 0)
    {
      prop = 1;
    }
    else
    {
      prop = ((double)cur / (double)dur) * 200;
    }
    // Serial.printf("cur: %d, dur: %d, prop: %f, prop_int: %d \n", cur, dur, prop, (int)prop);
    tft.drawRect(20, 290, 200, 10, ST77XX_WHITE);
    tft.fillRect(20, 290, (int)prop, 10, ST77XX_WHITE);
    tft.drawCircle((int)prop + 20, 295, 7, ST77XX_WHITE);
    tft.fillCircle((int)prop + 20, 295, 6, ST77XX_BLACK);

    lastUpdateTime = currentTime;
  }
}

String secondsToMin(int secs)
{
  String length = "";
  int minutes = secs / 60;
  int seconds = secs % 60;
  if (seconds < 10)
  {
    return String(minutes) + ":0" + String(seconds);
  }
  else
  {
    return String(minutes) + ":" + String(seconds);
  }
}

#endif
