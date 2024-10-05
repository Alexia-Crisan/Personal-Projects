#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte chickenFront[8] = { 0b01000, 0b10100, 0b00011, 0b00100, 0b00100, 0b11000, 0b00000, 0b10000 };
byte chickenBack[8] = { 0b01000, 0b01100, 0b01011, 0b01000, 0b00100, 0b00011, 0b00001, 0b00001 };

byte mushroom1[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b11111, 0b00100, 0b00100 };
byte mushroom2[8] = { 0b00000, 0b00000, 0b00000, 0b01110, 0b11111, 0b00100, 0b00100, 0b00100 };
byte mushroom3[8] = { 0b00000, 0b00000, 0b01110, 0b11111, 0b00100, 0b00100, 0b00100, 0b00100 };

byte cloudFront[8] = { 0b00000, 0b00000, 0b00011, 0b00100, 0b01000, 0b11111, 0b00000, 0b00000 };
byte cloudBack[8] = { 0b00000, 0b00100, 0b01010, 0b10001, 0b00001, 0b11111, 0b00000, 0b00000 };

int elements_positions[10][3];
/*
  first_field = 0 for cloud / 1 for chicken
  second_field = column
  third_field = type of mushroom
*/
int number_of_elements;
int score = 0;

int mushroom_speed = 300;
int cloud_speed = 350;

int last_score_check = 0; // Track when the score was last updated for speed
unsigned long last_element_time = 0; // Tracks when the last element was created
unsigned long next_element_delay = 1000; // Time delay for next element appearance
unsigned long last_move_time = 0; // Tracks time of last element movement
unsigned long last_chicken_move_time = 0; // Tracks time of last chicken move
unsigned long chicken_move_interval = 400; // Chicken move delay

void setup() 
{
  lcd.begin(16, 2);

  lcd.createChar(0, chickenFront);  
  lcd.createChar(1, chickenBack); 
  lcd.createChar(2, mushroom1);  
  lcd.createChar(3, mushroom2);  
  lcd.createChar(4, mushroom3); 
  lcd.createChar(5, cloudFront);  
  lcd.createChar(6, cloudBack); 
 
  lcd.clear();
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

int element_appear(int *number_of_elements)
{
  int seed = random(10000000);
  randomSeed(seed);

  int mushroom_or_cloud = random(1026) % 4;

  if(mushroom_or_cloud == 0)
  {
    lcd.setCursor(12, 0); lcd.write(byte(5));
    lcd.setCursor(13, 0); lcd.write(byte(6)); 

    elements_positions[(*number_of_elements)][0] = 0;
    elements_positions[(*number_of_elements)][1] = 12; 
  }
  else 
  { 
    lcd.setCursor(15, 1); lcd.write(byte(mushroom_or_cloud + 1)); 

    elements_positions[(*number_of_elements)][0] = 1;
    elements_positions[(*number_of_elements)][1] = 15;
    elements_positions[(*number_of_elements)][2] = mushroom_or_cloud + 1;
  }

  (*number_of_elements) += 1;
}

void element_move(int *number_of_elements, int *score, int mushroom_speed, int cloud_speed)
{
  for(int i = 0; i < (*number_of_elements); i++)
  {
    if(elements_positions[i][0] == 0 && elements_positions[i][1] != 0)
    {
      lcd.setCursor(elements_positions[i][1], 0); lcd.print("  ");
      elements_positions[i][1] -= 1;
      lcd.setCursor(elements_positions[i][1], 0); lcd.write(byte(5));
      lcd.setCursor(elements_positions[i][1] + 1, 0); lcd.write(byte(6));
    }
    else if(elements_positions[i][0] == 1 && elements_positions[i][1] != 0)
    {
      lcd.setCursor(elements_positions[i][1], 1); lcd.print(" ");
      elements_positions[i][1] -= 1;
      lcd.setCursor(elements_positions[i][1], 1); lcd.write(byte(elements_positions[i][2]));
    }
    else if(elements_positions[i][1] == 0)
    {    
      if(elements_positions[i][0] == 0) 
      {
        lcd.setCursor(0, 0); lcd.print(" ");
        lcd.setCursor(1, 0); lcd.print(" "); 
      }
      else { lcd.setCursor(0, 1); lcd.print(" "); }

      for (int j = i; j < (*number_of_elements) - 1; j++) { elements_positions[j][0] = elements_positions[j + 1][0]; elements_positions[j][1] = elements_positions[j + 1][1]; elements_positions[j][2] = elements_positions[j + 1][2];}
      (*number_of_elements) -= 1;
      i--;
      (*score) += 1;
    }
  }
}

int hit(int chicken_position, int number_of_elements)
{
  for(int i = 0; i < number_of_elements; i++)
  {
    if(chicken_position == 0 && (elements_positions[i][0] == 0 && (elements_positions[i][1] == 1 || elements_positions[i][1] == 2 || elements_positions[i][1] == 3)))
      return 1;
    else if(chicken_position == 1 && (elements_positions[i][0] == 1 && (elements_positions[i][1] == 2 || elements_positions[i][1] == 3)))
      return 1;
  }
  return 0;
}

void game(int chicken_position)
{
  lcd.setCursor(3, 1); lcd.write(byte(0));  
  lcd.setCursor(2, 1); lcd.write(byte(1)); 

  while(1)
  {
    unsigned long current_time = millis();
    int button_state = read_LCD_buttons(); 

    if(button_state == 2 || button_state == 3)
    {
      if(current_time - last_chicken_move_time > chicken_move_interval)
      {
        last_chicken_move_time = current_time;
        if(chicken_position == 1)
        {
          chicken_position = 0;
          lcd.setCursor(3, 1); lcd.print(" ");
          lcd.setCursor(2, 1); lcd.print(" ");

          lcd.setCursor(3, 0); lcd.write(byte(0));  
          lcd.setCursor(2, 0); lcd.write(byte(1)); 
        }
        else if(chicken_position == 0)
        {
          chicken_position = 1;
          lcd.setCursor(3, 0); lcd.print(" ");
          lcd.setCursor(2, 0); lcd.print(" ");

          lcd.setCursor(3, 1); lcd.write(byte(0));  
          lcd.setCursor(2, 1); lcd.write(byte(1)); 
        }
      }
    }

    if (current_time - last_element_time > next_element_delay) 
    {
      element_appear(&number_of_elements);
      last_element_time = current_time;
      randomSeed(random(10000000));
      next_element_delay = random(3000, 4000);
    }

    if(hit(chicken_position, number_of_elements) == 1) 
    {
       lcd.clear(); delay(1000); lcd.setCursor(2, 0); lcd.print("You lost :("); delay(5000);
       break;
    } 

    if(current_time - last_move_time > min(mushroom_speed, cloud_speed))
    {
      last_move_time = current_time;
      element_move(&number_of_elements, &score, mushroom_speed, cloud_speed);
    }

    lcd.setCursor(14, 0); lcd.print("  ");
    lcd.setCursor(14, 0); lcd.print(score); delay(100);

    if(score % 10 == 0 && score != 0 && score != last_score_check) 
    { 
      mushroom_speed = max(100, mushroom_speed - 20); 
      cloud_speed = max(100, cloud_speed - 30); 
      last_score_check = score;
    }

    if(score == 100)
    {
       lcd.clear(); delay(1000); lcd.setCursor(0, 0); lcd.print("You are so cool!"); delay(5000);
       break;
    }  
  }
}

void loop() 
{
  lcd.clear(); delay(1000);
  lcd.setCursor(2, 0);
  lcd.print("Let's play!"); delay(4000);
  lcd.clear(); delay(500);

  game(1);

  for(int i = 0; i < number_of_elements; i++) { elements_positions[i][0] = 0; elements_positions[i][1] = 0; elements_positions[i][2] = 0; } //reset
  number_of_elements = 0; score = 0; //reset
}
