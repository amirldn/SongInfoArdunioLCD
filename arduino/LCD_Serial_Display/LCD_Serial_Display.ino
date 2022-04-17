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

void loop() {
  if (Serial.available()){
    String serialIn = Serial.readString();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.noAutoscroll();
    Serial.print("index of NAME: ");
    Serial.println(serialIn.indexOf("NAME:"));
    // Check if serialIn contains substring NAME:
      if(serialIn.indexOf("NAME:") >= 0){
        // Print the song name
        lcd.print(serialIn.substring(5, serialIn.length() - 1));
        // lcd.print(serialIn.substring(5));

        //  use the indexOf stuff to find out locations of stuff and split it out using substring (from, to)
      }
      else {
      // Print a message to the LCD.
      lcd.print("No song playing");
      lcd.setCursor(0, 1);
      lcd.print("(C) amirldn");
    }
    }
  }



  // // set the cursor to column 0, line 1
  // // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // // print the number of seconds since reset:
  // lcd.print(millis() / 1000);
  //   lcd.setCursor(5, 1);
  // // print the number of seconds since reset:
  // lcd.print(millis() / 10);


/* NOTES:
Cases:
1. Nothing playing, serial output : NONE, LCD: show time & date
2. Music playing, serial output: NAME:<songname> ARTIST:<artistname> TIME:<timeplaying>
3. 30 Secs left of current song, serial output 1: NEXTUP:<songname> - <artistname>, LCD row 0: NEXT UP, row1: Song - Artist Name
4. 25 secs left of current song, go back to CASE 2
5. Error with API, serial output: ERROR:<errorcode>, LCD: show error

*/