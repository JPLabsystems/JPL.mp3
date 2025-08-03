**firmware for JPL.mp3 project!**\
libdeps: (thank you so much to all contributors)\
	`mathertel/RotaryEncoder@^1.5.3`\
	`adafruit/Adafruit GFX Library@^1.11.9`\
	`adafruit/Adafruit ST7735 and ST7789 Library@^1.10.4`\
	`siara-cc/Sqlite3Esp32@^2.5`\
	`esphome/ESP32-audioI2S @ ~2.0.7`

Built in VSCode using PlatformIO extension.

*I wrote this firmware before I knew how to code.*  
As such, `main.cpp` is monolithic and contains all control logic, making calls to funcitons defined in each respective header file. It's hard to debug and very glitchy (sorry!)...
