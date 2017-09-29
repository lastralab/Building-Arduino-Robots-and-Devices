#define EN 5
#define IN1 3
#define IN2 4

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  //передача счетчика как параметра,
  //регулирующего ШИМ,
  //позволяет наращивать скорость
  for(int spd = 0; spd < 256; spd++)
  {
    analogWrite(EN, spd);
    delay(50);
  }
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  for(int spd = 255; spd >=0; spd--)
  {
    analogWrite(EN, spd);
    delay(50);
  }
}
