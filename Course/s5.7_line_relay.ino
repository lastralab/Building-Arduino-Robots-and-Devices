#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define LEFT_SENSOR_PIN A1
#define RIGHT_SENSOR_PIN A0

//создаются читаемые определения
//для вызова функции чтения датчиков линии
#define LEFT 1
#define RIGHT 0

//определяется граница между черным и белым
#define BLACK 150

//константами задаются два варианта скоростей
#define FRW 200
#define BCK 0

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.println(analogRead(A0));
  
  //возможные сочетания цветов поля под датчиками
  //описано серией условий с использованием lineSensor(),
  //которая возвращает логическое значение, соответствующее черному или белому
  if(lineSensor(LEFT) && lineSensor(RIGHT))
  //в зависимости от сочетания цветов под датчиками
  //задается сочетание скоростей левого и правого колес
    drive(FRW,FRW);
  else if(lineSensor(LEFT) && !lineSensor(RIGHT))
    drive(FRW,BCK);
  else if(!lineSensor(LEFT) && lineSensor(RIGHT))
    drive(BCK,FRW);
  else
    drive(0,0);
  
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

boolean lineSensor(int sensor)
{
  //в зависимости от того, какой датчик был запрошен
  //проверяется либо левый, либо правый датчик
  if(sensor == LEFT)
  {
     //в зависимости от того, превосходит ли значение,
     //полученное на датчике, пороговое значение
     //возвращается истина или ложь, т.е. "белое" или "черное"
     if(analogRead(LEFT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
  else if(sensor == RIGHT)
  {
     if(analogRead(RIGHT_SENSOR_PIN) > BLACK)
       return false;
     else
       return true;
  }
}
