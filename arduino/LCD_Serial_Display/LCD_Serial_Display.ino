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

void nowPlaying(String serialIn) {
  // Displays the track name, artist name and current playback time
  lcd.setCursor(0, 0);
  // lcd.autoscroll();
  Serial.print("index of NAME: ");
  Serial.println(serialIn.indexOf("NAME:"));
  lcd.print(serialIn.substring(5, serialIn.length() - 1));
}

void loop() {
  if (Serial.available()){
    String serialIn = Serial.readString();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.noAutoscroll();

     //  use the indexOf stuff to find out locations of stuff and split it out using substring (from, to)

    // CASES
    // Check if serialIn contains substring NAME:
      if(serialIn.indexOf("NAME:") >= 0){
        nowPlaying(serialIn);
      }
      else {
      // Print a message to the LCD.
      lcd.print("No song playing");
      lcd.setCursor(0, 1);
      lcd.print("(C) amirldn");
    }
    }
  }

/* NOTES:
Cases:
1. Nothing playing, serial output : NONE, LCD: show time & date
2. Music playing, serial output: PLAYING NAME:<songname> ARTIST:<artistname> TIME:<timeplaying>
3. 30 Secs left of current song, serial output 1: NEXTUP NAME:<songname> - <artistname>, LCD row 0: NEXT UP, row1: Song - Artist Name
4. 25 secs left of current song, go back to CASE 2
5. Error with API, serial output: ERROR ISSUE:<errorcode>, LCD: show error

TODO:
1. Figure out why autoscroll does not work (check the length of something and then start printing/adding the chars 1 by 1?)
2. Make a mode variable and use that for the switch statemenet

*/