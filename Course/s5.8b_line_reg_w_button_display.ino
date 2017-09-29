#include <QuadDisplay.h>

#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define RIGHT_SENSOR_PIN A1

#define BUTTON_PIN 2
#define DISPLAY_PIN 3

#define BASE_SPEED 150

#define K 0.4

int grey = 0;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  //добавлено ожидание нажатия кнопки
  //и вывод показаний датчика на экран
  //для более точной установки перед стартом
  while(digitalRead(BUTTON_PIN))
  {
    displayInt(DISPLAY_PIN, grey);
    delay(10);
    grey = analogRead(RIGHT_SENSOR_PIN);
  }
  delay(500);
}

void loop() {

  int e = analogRead(RIGHT_SENSOR_PIN) - grey;
  int u = K * e;
  
  drive(BASE_SPEED + u, BASE_SPEED - u);
  displayInt(DISPLAY_PIN, analogRead(RIGHT_SENSOR_PIN));
}

void drive(int left, int right)
{
  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);
  
  if(left >= 0)
    digitalWrite(IN2, HIGH);
  else
    digitalWrite(IN2, LOW);
  
  if(right >= 0)
    digitalWrite(IN1, HIGH);
  else
    digitalWrite(IN1, LOW);
    
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));

}
