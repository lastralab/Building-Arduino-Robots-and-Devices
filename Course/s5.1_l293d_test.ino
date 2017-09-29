#define EN 5
#define IN1 3
#define IN2 4

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  //комбинации HIGH и LOW на входах INPUT 
  //микросхемы L293 задают полярность напряжения
  //на соответствующих выходах OUTPUT
  //а следовательно - направление вращения мотора,
  //который подключен к этим выходам
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //регулирование напряжения на входе ENABLE
  //микросхемы позволяет регулировать скорость вращения мотора
  analogWrite(EN, 255);
  
  delay(2000);
  
  //обратная комбинация меняет направление
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN, 255);
  
  delay(2000);
  
  //комбинацией LOW, LOW мотор можно остановить
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN, 255);
  
  delay(2000);

}
