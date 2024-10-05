#include <Wire.h>
#include <Tiny4kOLED.h>
#include <Keypad.h>

#define VERT_PIN 27
#define HORZ_PIN 28
#define SEL_PIN  15

const int pins[] = {0, 1, 6, 7, 8, 9, 10, 11, 12, 13};

const char* quotesMotivation[] = 
{
  "Act now.", "Stay beautiful.", "Push limits.", "Dream big.", "Go for it.",
  "Never stop.", "Rise and grind.", "Seize the day.", "Believe and achieve.", "Make it happen."
};

const char* quotesWisdom[] = 
{
  "Less is more.", "Think deep.", "Know thyself.", "Stay curious.", "Act with integrity.",
  "Seek the truth.", "Knowledge is power.", "Wisdom comes with age.", "Listen more, talk less.", "Embrace simplicity."
};

const char* quotesPositivity[] = 
{
  "Choose joy.", "Smile often.", "Believe in you.", "Shine bright.", "Spread kindness.",
  "Stay positive.", "Good vibes only.", "Happiness is a choice.", "Live, laugh, love!", "Embrace the good."
};

const char* quotesSuccess[] = 
{
  "Aim high.", "Work hard.", "Never quit.", "Make it happen.", "Dream big, work hard.",
  "Success is a journey.", "Chase your dreams.", "Stay focused.", "Overcome challenges.", "Believe in you."
};

const uint8_t ROWS = 4;
const uint8_t COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t rowPins[ROWS] = { 26, 22, 21, 20 }; // Pins connected to R1, R2, R3, R4
uint8_t colPins[COLS] = { 19, 18, 17, 16 }; // Pins connected to C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() 
{
  Serial1.begin(115200);
  Serial1.println("Feeling down? Try this product!");
  Serial1.println("Follow the steps on the LED screen:");
  Serial1.println("Press A, B, C or D to choose a category and then, a number to receive a message\nfrom the stars.\nGet inspired!");

  oled.begin();
  oled.clear();
  oled.on();
  oled.setFont(FONT6X8);  
  oled.setCursor(0, 0);

  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

  for (int i = 0; i < 10; i++) 
    pinMode(pins[i], OUTPUT);
}

void loop() 
{
  for (int i = 0; i < 10; i++) 
    digitalWrite(pins[i], HIGH);

  char category, number;
  char key = keypad.getKey(); 
  while (key != 'A' && key != 'B' && key != 'C' && key != 'D') 
  {
    key = keypad.getKey(); 
    oled.setCursor(0, 0);   
    oled.print("A - Motivation quotes\nB - Wisdom quotes\nC - Positivity quotes\nD - Success quotes");
  }
  category = key;
  oled.clear();
  key = keypad.getKey(); 
  while (key != '0' && key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != '8' && key != '9') 
  {
    key = keypad.getKey(); 
    oled.setCursor(0, 0);   
    oled.print("Choose a number:");
  }
  number = key;
  oled.clear(); oled.setCursor(0, 0); 

  int vert = analogRead(VERT_PIN);
  int horz = analogRead(HORZ_PIN);
  bool selPressed = digitalRead(SEL_PIN) == LOW;

  while(vert != 511 || horz != 0)
  {
    vert = analogRead(VERT_PIN);
    horz = analogRead(HORZ_PIN);
    oled.setCursor(0, 0); 

    switch(category)
    {
      case('A'): oled.print(quotesMotivation[number - '0']); break;
      case('B'): oled.print(quotesWisdom[number - '0']); break;
      case('C'): oled.print(quotesPositivity[number - '0']); break;
      case('D'): oled.print(quotesSuccess[number - '0']); break;
      default: break;
    }
  }

  for (int i = 0; i < 10; i++) 
    digitalWrite(pins[i], LOW);
  delay(2000);
}
