#include <LiquidCrystal.h>
#include<AFMotor.h>
#include <SoftwareSerial.h>


SoftwareSerial BT(0, 1); 
String readvoice;

#define LCD_RS_PIN A5
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9



LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,
                  LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);



int cursorLine = 0;

void printUserTextOnDisplay(String text)
{
  // validate text
  if (text.length() > 16) {
    text = "Text too long.";
  }
  for (int i = text.length(); i < 16; i++ ) {
    text += " ";
  }
  // set cursor line O or 1
  lcd.setCursor(0, cursorLine);
  // print text
  lcd.print(text);
  if (cursorLine == 0) {
    cursorLine = 1;
  }
  else {
    cursorLine = 0;
  }
}

void setup() {
  Serial.begin(115200);
    BT.begin(9600);
  Serial.setTimeout(10);
 
  lcd.begin(16, 2);
}

void loop() {
 while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read and store it to char C 
  readvoice += c; //build the string- with ANY WORDS that is sent by the app
  }

    if (readvoice.length() > 0) {
       printUserTextOnDisplay(readvoice);
       Serial.println(readvoice);
}
}
