#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int vizitat[16][2];

void setup() 
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
}

void win_lose(int win_or_lose)
{
  for(int k = 0; k<3; k++)
  {
    for(int i=0; i<16; i++)
      for(int j=0; j<2; j++)
      {
        lcd.setCursor(i, j);
        lcd.write(255);
      }
    delay(500);
    lcd.clear();
    delay(500);
  }
  if(win_or_lose == 1)
    lcd.print("You won!");
  else
    lcd.print("You lost :(");
  delay(5000);
}

int read_LCD_buttons() 
{
  int buton = analogRead(0);
  if (buton > 1000) return 0; //none
  if (buton < 50)   return 1; //right
  if (buton < 250)  return 2; //up
  if (buton < 450)  return 3; //down
  if (buton < 600)  return 4; //left
  if (buton < 920)  return 5; //select
  return 0; //none
}

int blink(int i, int j)
{
  if(vizitat[i][j] != 1)
  {
    lcd.setCursor(i, j);
    lcd.write(255); delay(250);
    lcd.setCursor(i, j);
    lcd.print(" "); delay(250);
  }
  else
  {
    lcd.setCursor(i, j);
    lcd.print(" "); delay(250);
    lcd.setCursor(i, j);
    lcd.print("0"); delay(250);
  }
}

void move(int *i, int *j)
{
  if(read_LCD_buttons() == 1) //right
  {
    if((*i) == 15) (*i) = 0;
    else (*i) ++;
  }  
  else if(read_LCD_buttons() == 4) //left
  {
    if((*i) == 0) (*i) = 15;
    else (*i) --;
  }
  else if(read_LCD_buttons() == 2) //up
  {
    if((*j) == 0) (*j) = 1;
    else (*j) --;
  }
  else if(read_LCD_buttons() == 3) //down
  {
    if((*j) == 1) (*j) = 0;
    else (*j) ++;
  }
}

int sunt_toate_vizitate()
{
  int suma = 0;
  for(int i=0; i<16; i++)
      for(int j=0; j<2; j++)
        if(vizitat[i][j] == 1) suma++;

  if(suma == 31) return 0;
  else return 1;
}

int game(int bomb_i, int bomb_j)
{
  int i = 0, j = 0, win = 1;
  while(1)
  {
    blink(i, j);
    move(&i, &j);
    if(read_LCD_buttons() == 5)
    {
      if(i == bomb_i && j == bomb_j)
        {win = 0; break;}
      else {lcd.setCursor(i, j); lcd.print("0"); vizitat[i][j] = 1;}
    }
    if(sunt_toate_vizitate() == 0) break;
  }
  win_lose(win);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  lcd.clear(); delay(1000);
  lcd.print("Let's play!"); delay(4000);
  lcd.clear(); delay(500);

  for(int i=0; i<16; i++)
      for(int j=0; j<2; j++)
        vizitat[i][j] = 0;

  int seed = random(10000000);
  randomSeed(seed);

  int bomb_i = random(1024) % 16; delay(50);
  int bomb_j = random(1024) % 2; delay(50);

  game(bomb_i, bomb_j);
}
