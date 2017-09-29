#define EN1 5
#define IN1 4
#define EN2 6
#define IN2 7

#define TRIG 2
#define ECHO 3

#define LASH 15

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  int distance = measure();
  
  //направление вращения моторов будет меняться
  //в зависимости от дистанции до препятствия
  
  if(distance < LASH)
    drive(-128, -128);
  else
    drive(128, 128);
  
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

int measure()
{
  digitalWrite(TRIG, HIGH);
  digitalWrite(TRIG, LOW);
  
  int dist = pulseIn(ECHO, HIGH) / 50;
  
  return dist;
}
