#define EN 5
#define IN 4

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(IN, OUTPUT);
}

void loop() {
  //motor shield позволяет задавать направление
  //изменением сигнала всего лишь на одном пине INPUT
  digitalWrite(IN, HIGH);
  
  //управление скоростью происходит так же -
  //через изменение ШИМ на ENABLE
  for(int spd = 0; spd < 256; spd++)
  {
    analogWrite(EN, spd);
    delay(50);
  }
  
  digitalWrite(IN, LOW);

  for(int spd = 255; spd >=0; spd--)
  {
    analogWrite(EN, spd);
    delay(50);
  }
}
