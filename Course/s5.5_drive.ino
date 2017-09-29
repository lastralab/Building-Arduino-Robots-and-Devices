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
  //управление скоростью и направлением обоих колес
  //сводится к единственному вызову drive()
  //где знаки параметров определяют направление
  //а абсолютные значения - скорости
  
  drive(255, 255);
  delay(1000);
  drive(-80, -255);
  delay(1000);
  drive(200, -100);
  delay(1000);
  
}

//функция для управления моторами не будет возвращать значение
//и будет принимать два целочисленных параметра, 
//определяющих и скорость, и направление для каждого мотора
void drive(int left, int right)
{
  //значение скорости может быть вычислено автоматически
  //поэтому следует убедиться, что оно лежит в допустимом диапазоне
  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);
  
  //проверяется знак первого параметра
  //и в зависимости от него задается направление левого мотора
  if(left >= 0)
    digitalWrite(IN2, HIGH);
  else
    digitalWrite(IN2, LOW);
  
  //аналогично для правого мотора
  if(right >= 0)
    digitalWrite(IN1, HIGH);
  else
    digitalWrite(IN1, LOW);
  
  //для задания скоростей используются те же параметры,
  //но с помощью abs() берется их абсолютное значение
  analogWrite(EN2, abs(left));
  analogWrite(EN1, abs(right));

}
