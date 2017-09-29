#include <SoftwareSerial.h>
#include <QuadDisplay.h>

#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

//определение номера ПРЕРЫВАНИЯ 
//(см. соответствие пинов и прерываний 
//на https://www.arduino.cc/en/Reference/AttachInterrupt )
#define ENCODER_INTERRUPT 0

#define DISPLAY_PIN 8

//определние количества спиц в колесе
#define SPOKES 5

#define SPD 200

SoftwareSerial bluetoothModule(10,11);

//создание переменной для подсчета оборотов (спиц)
//к которой в т.ч. будут обращения из функции, 
//срабатывающей по внешнему прерыванию,
//поэтому используется volatile
volatile int spinCount = 0;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  bluetoothModule.begin(9600);
  //включение внешнего прерывания
  //номер прерывания определен выше
  //указание имени функции, которая будет вызываться
  //по наступлении события FALLING 
  //(переход сигнала с высокого на низкий уровень)
  attachInterrupt(ENCODER_INTERRUPT, counter, FALLING);

}

void loop() {
  if (bluetoothModule.available() > 0) {
     char control = bluetoothModule.read();
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
  
  //на экран выводится подсчитанное количество спиц,
  //деленное на количество спиц в колесе,
  //т.е. количество оборотов колеса
  displayInt(DISPLAY_PIN, spinCount/SPOKES);
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

//функция, которая будет вызвана
//по внешнему прерыванию
void counter()
{
  spinCount++;
}
