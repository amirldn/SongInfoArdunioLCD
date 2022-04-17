/*

 The LiquidCrystal library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver.

 Display information on the LCD display sent from serial input.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Uses example code from
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#include <LiquidCrystal.h>

// Init LCD with interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Starting...");
  lcd.setCursor(0, 1);
  lcd.print("(C) amirldn");
  Serial.begin(9600);
  Serial.println("Starting SongInfoArduino...");
}

// Create functions for each 'mode' that the LCD will display
void notPlaying(String serialIn) {
  lcd.setCursor(0, 0);
  if (serialIn.indexOf("TIME:") == -1) {
    error(serialIn, "TIME = -1");
  }
  lcd.print(serialIn.substring(7, serialIn.indexOf("DATE:")));
  lcd.print((serialIn.substring(serialIn.indexOf("DATE:") + 5, serialIn.length() - 1)));
  lcd.setCursor(0, 1);
  lcd.print("(C) amirldn");
}

void nowPlaying(String serialIn) {
  // Displays the track name, artist name and current playback time
  lcd.setCursor(0, 0);
  // lcd.autoscroll();
  Serial.print("index of NAME: ");
  Serial.println(serialIn.indexOf("NAME:"));

  // Check a name: was passed
  if (serialIn.indexOf("NAME:") == -1) {
    error(serialIn, "NAME = -1");
  }
  else {
    lcd.print(serialIn.substring(7, serialIn.indexOf("ARTIST:")));
  }
  lcd.setCursor(0, 1);
  lcd.print(serialIn.substring(serialIn.indexOf("ARTIST:") + 7, serialIn.indexOf("MIN:")));

  lcd.setCursor(12, 1);
  lcd.print(serialIn.substring(serialIn.indexOf("MIN:") + 4, serialIn.indexOf("SEC:") - 1));
  int second = serialIn.substring(serialIn.indexOf("SEC:") + 4, serialIn.length() - 1).toInt();
  Serial.print(second);
  if (second % 2 == 0) {
    lcd.print(":");
  }
  else {
    lcd.print(" ");
  }
  lcd.print(second);
}
void nextUp(String serialIn) {
  // Displays the track name, artist name of the song playing next
  lcd.setCursor(0, 0);
  // lcd.autoscroll();

  // Check a name was passed
  if (serialIn.indexOf("NAME:") == -1) {
    error(serialIn, "next up NAME = -1");
  }

  lcd.print("Next Up: ");
  lcd.setCursor(0, 1);
  lcd.print(serialIn.substring(serialIn.indexOf("ARTIST:") + 7, serialIn.length() - 1));
  lcd.print(" - ");
  lcd.print(serialIn.substring(7, serialIn.indexOf("ARTIST:")));
}

void error(String serialIn, String error) {
  // Displays when an error occurs (either from Python or Arduino)
  lcd.setCursor(0, 0);
  // lcd.autoscroll();
  lcd.print("ERROR:");
  lcd.setCursor(0, 1);
  if (error.length() > 0) {
    lcd.print(error);
  } else {
    lcd.print(serialIn.substring(7, serialIn.length() - 1));
  }
}

// Main loop - checks mode & calls to display functions
void loop() {
  if (Serial.available()){
    String serialIn = Serial.readString();
    int mode = serialIn.substring(0, 1).toInt();
    Serial.print("mode: ");
    Serial.println(mode);

    lcd.clear();
    lcd.noAutoscroll();

    // Switch Case for Modes
    switch (mode) {
      case 1:
        nowPlaying(serialIn);
        break;
      case 2:
        nextUp(serialIn);
        break;
      case 3:
        error(serialIn, "");
        break;
      default:
        notPlaying(serialIn);
        break;
    }
  }
}

/*
MODES:
  1. Nothing playing - 0
    0 TIME:<24h time> DATE:<DD/MM/YYYY>
    0 TIME:12:38 DATE:17/04/2022
  2. Playing - 1
    1 NAME:<songname> ARTIST:<artistname> MIN:<minute> SEC:<second>
    1 NAME:Hold It Down ARTIST:Digga D MIN:2 SEC:31
  3. Next Up - 2
    2 NAME:<songname> ARTIST:<artistname>
    2 NAME:2AM ARTIST:Loski
  4. Error - 3
    3 ERROR:<errorcode>

TODO:
1. Figure out why autoscroll does not work (check the length of something and then start printing/adding the chars 1 by 1?)
*/