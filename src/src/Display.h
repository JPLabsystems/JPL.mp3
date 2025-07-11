/*
#ifndef Display_h
#define Display_h

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include "List.h"

#define backgroundColor ST77XX_BLACK
#define primaryColor ST77XX_WHITE
#define accentColor ST77XX_ORANGE


class Display
{
    public:
        Display(int RST, int CS, int DC, int backlightPin, int brightness);
        adjustBrightness(int newBrightness)

        drawScreen(int style, List* list);
        navigate(int direction);

        int brightness;

        void drawStatusBar(double b, double v);

    private:

}

#ifndef gui_h
#define gui_h

**************************************


volatile bool recalcDb = true;

volatile int screen = 1;

volatile bool piecemenuFlag = false;

volatile int filteredBy;


1 = home screen

2 = all pieces
3 = composers
4 = eras
5 = settings

6 = pieces, filtered

7 = playing

1 - 2 - 7
1 - 3, 4 - 6 - 7




void beginPlayback(String Title)
{
  drawStatusBar(100, 50);

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

//

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

//

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
  tft.fillRect(0, 21, 240, 299, ST77XX_BLACK);
}

void cleanSubmenuCursor()
{
  tft.fillRect(2, 21, 4, 300, ST77XX_BLACK);
}

////////////////////////////////////

void screen1(int y) // menu
{
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
  tft.fillRect(2, 11 + 24 * y, 4, 4, ST77XX_ORANGE);
}

void screen3() // composers
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
}

void screen6(String condition, const char *sql)
{
  if (recalcDb == true)
  {
    y = 1;
    argv = exec1byX(prepbindStmt(db, sql, (char *)condition.c_str()));
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

void screen7(String piecename)
{
  String Filepath = execSimpleStmt(prepbindStmt(db, queries[5], (char *)piecename.c_str()));
  char *filepath = (char *)Filepath.c_str();

  globalPiecename = piecename;

  Serial.println(filepath);
  Serial.println(audio.connecttoFS(SD_MMC, filepath));
  Serial.println(audio.getAudioFileDuration());
  isPlayingScreen = true;
  playbackStatus = true;

  // String Composer = execSimpleStmt(prepbindStmt(db, "SELECT composer WHERE piecename = ?", (char *)piecename.c_str()));

  tft.setTextWrap(true);

  tft.setCursor(20, 100);
  tft.print(piecename);
  tft.setCursor(20, 200);
  tft.print(filepath);

  tft.setCursor(20, 270);
  tft.print(audio.getAudioFileDuration());
 

  tft.drawRect(20, 290, 200, 10, ST77XX_WHITE);

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
41
  tft.setCursor(20, 100);
  tft.print(globalPiecename);
  tft.setCursor(20, 200);
  //tft.print(filepath);

  tft.setCursor(20, 270);
  tft.print(audio.getAudioFileDuration());

  tft.drawRect(20, 290, 200, 10, ST77XX_WHITE);
}

#endif

#endif
*/