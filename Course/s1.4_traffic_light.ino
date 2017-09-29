#define RED_PIN 8
#define YELLOW_PIN 10
#define GREEN_PIN 12

int red_on = 3000;
int red_yellow_on = 1000;
int green_on = 3000;
int green_blink = 500;
int yellow_on = 1000;

void setup() {
  //порты, к которым подключены светодиоды - выходы
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

}

void loop() {
  //включаем напряжение на RED_PIN выходе (туда подключен красный)
  digitalWrite(RED_PIN, HIGH);
  //ждем, пока красный горит
  delay(red_on);
  //включаем напряжение на YELLOW_PIN выходе (желтый)
  digitalWrite(YELLOW_PIN, HIGH);
  delay(red_yellow_on);
  
  //выключаем RED_PIN и YELLOW_PIN, включаем GREEN_PIN (зеленый)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(green_on);
  digitalWrite(GREEN_PIN, LOW);
  
  //трижды включаем и выключаем зеленый с помощью цикла
  //у которого есть счетчик i, который изменяется по указанному правилу: на каждой итерации увеличивается на 1
  //цикл будет выполняться до тех пор, пока верно указанное условие (здесь: i < 3)
  for(int i = 0; i < 3; i = i+1)
  {
    delay(green_blink);
    digitalWrite(GREEN_PIN, HIGH);
    delay(green_blink);
    digitalWrite(GREEN_PIN, LOW);
  }
    //одинокий желтый
    digitalWrite(YELLOW_PIN, HIGH);
    delay(yellow_on);
    digitalWrite(YELLOW_PIN, LOW); 
 
}
