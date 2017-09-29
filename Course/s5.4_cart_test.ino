#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
  //скорости в этом примере заданы единственный раз
  analogWrite(EN1, 255);
  analogWrite(EN2, 255);

  //комбинации сигналов, 
  //определяющих направление,
  //меняются каждые 1,5 секунды
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  
  delay(1500);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  delay(1500);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  delay(1500);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  delay(1500);
  

}
