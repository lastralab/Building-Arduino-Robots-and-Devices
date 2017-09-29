#include <QuadDisplay.h>

#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define RIGHT_SENSOR_PIN A1

#define BUTTON_PIN 2
#define DISPLAY_PIN 3

#define BASE_SPEED 125

#define K 0.4

//определены названия двух "слоев" программы,
//которые можно включать поочередно или одновременно
//#define COMM - таким образом можно 
//"выключить" часть программы, 
//отвечающей за вывод данных в последовательный порт,
//т.е. соответствующие фрагменты не будут скомпилированы (см. ниже)
#define COMM
#define DRIVE

int grey = 0;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  while(digitalRead(BUTTON_PIN))
  {
    displayInt(DISPLAY_PIN, grey);
    delay(10);
    grey = analogRead(RIGHT_SENSOR_PIN);
  }
  delay(500);
  
  //код, который будет скомпилирован, 
  //только если есть макроопределение COMM
  #ifdef COMM
    Serial.begin(9600);
  #endif
}

void loop() {

  int e = analogRead(RIGHT_SENSOR_PIN) - grey;
  int u = K * e;
  
  //управляющее воздействие будет вычисляться в любом случае,
  //но колеса будут вращаться, если будет скомпилирован вызов drive(), 
  //т.е. только если присутствует макроопределение DRIVE
  #ifdef DRIVE
  drive(BASE_SPEED + u, BASE_SPEED - u);
  #endif
  
  //если не определен COMM, вывода в порт не будет
  #ifdef COMM
  Serial.print(e);
  Serial.print("\t");
  Serial.println(u);
  delay(100);
  #endif
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
