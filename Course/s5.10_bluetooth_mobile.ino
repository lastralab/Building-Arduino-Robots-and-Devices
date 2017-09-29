//стандартная библиотека для создания
//последовательного порта на любых пинах
#include <SoftwareSerial.h>

#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define SPD 150

//создание программного последовательного порта
//на пинах, к которым подключен bluetooth-модуль
SoftwareSerial bluetoothModule(10,11);

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  //запуск порта
  bluetoothModule.begin(9600);
 
}

void loop() {
  //чтение порта такое же, как с обычным Serial
  if (bluetoothModule.available() > 0) {
     char control = bluetoothModule.read();
     //таким образом, можно получать различные символы
     //и в зависимости от того, какой из них пришел, 
     //запускать моторы с соответствующими скоростями
     switch(control)
     {
       case 'S':
         drive(0,0);
       break;
       case 'F':
         drive(SPD,SPD);
       break;
       case 'B':
         drive(-SPD,-SPD);
       break;
       case 'L':
         drive(-SPD,SPD);
       break;
       case 'R':
         drive(SPD,-SPD);
       break;
     }
  }
  
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
