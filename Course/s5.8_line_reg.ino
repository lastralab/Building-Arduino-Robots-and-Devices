#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define LEFT_SENSOR_PIN A1

//определена скорость, с которой будут
//вращаться моторы при отсутствии необходимости
//корректировать траекторию
#define BASE_SPEED 150

//вводится коэффициент, опеределяющий,
//насколько сильно изменение уровня серого под датчиком
//должно повлиять на изменение в скоростях колес
#define K 0.2

//переменная для хранения целевого значения,
//т.е. такого, которое датчик считывает на границе линии
int grey = 0;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  //сохранение целевого значения
  grey = analogRead(LEFT_SENSOR_PIN);
}

void loop() {
  //вычисление ошибки, т.е.отклонения текущего значения
  //датчика от целевого, может быть отрицательным
  int e = analogRead(LEFT_SENSOR_PIN) - grey;
  //вычисление управляющего воздействия,
  //которое будет прикладываться к скорости каждого колеса
  int u = K * e;
  
  //управление скоростями обоих колес
  //с учетом вычисленного воздействия
  drive(BASE_SPEED - u, BASE_SPEED + u);
  
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
