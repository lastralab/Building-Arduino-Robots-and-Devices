//этот скетч лежит здесь на случай,
//если вы забыли про Blink :)
#define POWER 7

void setup() {
  pinMode(POWER, OUTPUT);
}

void loop() {
  digitalWrite(POWER, HIGH);
  delay(2000);
  digitalWrite(POWER, LOW);
  delay(2000);
}
