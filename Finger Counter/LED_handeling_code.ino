
void setup() 
{
  for(int i = 10; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  Serial.begin(115200);
  Serial.setTimeout(1); 
}

void loop() 
{
  if(Serial.available() > 0)
  {
    int value = Serial.readString().toInt();

    for(int i = 10; i <= 13; i++)
      digitalWrite(i, LOW);

    if(value > 4) value = 4;
    for(int i = 10; i <= 9 + value; i++)
      digitalWrite(i, HIGH);
  }
}
