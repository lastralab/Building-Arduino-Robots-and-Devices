# Traffic Light
(Week 1):

Wiring:

<div style="text-align: center;"><img width="770" alt="screenshot 2017-02-13 09 12 14" src="https://cloud.githubusercontent.com/assets/22894897/22891611/2c9dab42-f1cd-11e6-829d-225f646ee905.png"></div>

Schematics:

<div style="text-align:center"><img width="951" alt="screenshot 2017-02-13 10 34 45" src="https://cloud.githubusercontent.com/assets/22894897/22894971/1176c082-f1d8-11e6-97c5-23aea8a8abf9.png"></div>

Code:

```C++
// Author: Niam Moltta
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  
}

void loop() {
  digitalWrite(8, HIGH);   //red on
  delay(5000);        //eight seconds       
  digitalWrite(8, LOW);    //red off
  digitalWrite(12, HIGH);    //green on           
  delay(5000); //three seconds
  digitalWrite(12, LOW); //green off
  delay(500);
  digitalWrite(12, HIGH); //green on
  delay(500); //one second
  digitalWrite(12, LOW); //green off
  delay(500);
  digitalWrite(12, HIGH); //green on
  delay(500); //one second
  digitalWrite(12, LOW); //green off
  delay(500);
  digitalWrite(12, HIGH); //green on
  delay(500); // one sec
  digitalWrite(12, LOW); //green off
  digitalWrite(10, HIGH); //yellow on
  delay(3000); //three sec
  digitalWrite(10, LOW); //yellow off
  //repeat from the beginning
  
                   
  
}
```
Demo:<br>

<div style="text-align:center"><img src="https://cloud.githubusercontent.com/assets/22894897/22892687/acc32664-f1d0-11e6-973f-0ef7ccfbf4c6.gif"></div>

# Radar
(Week 3)

Build a sonar using arduino, a servo, and a ping and visualize it as a radar with Processing.

it deserved its own repository:
https://github.com/TaniaMol/ArduinoRadar

# Ava's Traffic Intersection
(Week 4):

<div style="text-align:center"><img width="763" alt="screenshot 2017-02-10 10 54 37" src="https://cloud.githubusercontent.com/assets/22894897/22837781/5c92b02c-ef7f-11e6-998d-dff554c80a3c.png"></div>

Instructions:

Vehicle circulation can be blocked by the barrier if the train appears or the pedestrian presses the button for the green light.

The green light button is activated if there is no train approaching, and enough time (9 sec) has passed since the button was last activated.

The green light is activated for 5 seconds, which is followed by an intermittent beep. Then, the green light blinks for 3 seconds and the intermittent beep becomes more frequent. After that, the red light is activated again, and the timer counts the time from 0 to 9 seconds.

If the train appears when the green light is on for pedestrians, the red signal is activated urgently and a continuous beep of a different height can be heard.

You can imagine the intersection happening like this:

<div style="text-align:center"><img width="1033" alt="screenshot 2017-02-10 13 37 41" src="https://cloud.githubusercontent.com/assets/22894897/22843305/2dde1c5a-ef96-11e6-85d0-09387e4598bf.png"></div>

Black path is for cars, white & gray path is for the train and brown path is for people to cross.

While the train is passing, the switch cannot request a green light.

When the train comes again, the green light turns off and the red light turns on.

When the photoresistor is bright, that means the train is not passing but when you turn it dark, it means the train is passing. 

Wiring:

<div style="text-align:center"><img width="858" alt="screenshot 2017-02-12 22 09 27" src="https://cloud.githubusercontent.com/assets/22894897/22871636/f9f5580a-f16f-11e6-859c-548c69ba99ae.png"></div>

Schematics:

<div style="text-align:center"><img width="1088" alt="screenshot 2017-02-13 09 48 36" src="https://cloud.githubusercontent.com/assets/22894897/22892986/a333ee02-f1d1-11e6-96b3-1d132a369e1d.png"></div>

Code that didn't work and you are welcome to suggest any improvements:

```C++
//Ava's TRAFFIC INTERSECTION
//Author: Niam Moltta

#include <Servo.h>
#define SENSOR A0
#define BUZZER 10
#define BUTTON 9
#define BARRIER 11
#define GREEN 13
#define RED 12
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int count;

Servo myservo;

void setup() {
  
  pinMode(SENSOR, INPUT); //photoresistor
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BARRIER, OUTPUT); //servo
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  
  pinMode(a, OUTPUT); //DISPLAY FROM 2 TO 9
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  digitalWrite(BUTTON, HIGH);
  
  myservo.attach(BARRIER);
  
  Serial.begin(9600);
}
void loop() {
  
  int Train = analogRead(A0); // Value of photoresistor.
  int Button = digitalRead(BUTTON); // Request for crossing
  
  Serial.println(Train); 
  delay(5);  //print value to serial 
  
  switch (count) {
    
    case 0:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  delay(1000);
    break;

  case 1:
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
    delay(1000);
    break;

  case 2:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
    delay(1000);
  break;

  case 3:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
    delay(1000);
  break;
    
    case 4:
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
    delay(1000);
  break;

  case 5:
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
    delay(1000);
  break;

  case 6:
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
    delay(1000);
  break;

  case 7:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
    delay(1000);
  break;

  case 8:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
    delay(1000);
  break;

  case 9:
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
    delay(1000);
    break;
    
   break;
   
  }
  
  if (Train > 628) { //Train passing by.
   
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    tone(BUZZER, 1000, 500); 
    myservo.write(0); //barrier down
   
  }
  else {
    
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    myservo.write(90); //barrier up
    
  }
    
  if (Train < 628 && Button == LOW) { //Button pressed.
   
    Walker();
  
  }
}
  
int Walker() {
    
    myservo.write(0); //barrier down
    delay(1000);
    digitalWrite(RED, LOW);
    delay(50);
    digitalWrite(GREEN, HIGH);
    count = 1;
    delay(5000);
      tone(BUZZER, 380, 500); //starts blinking and beeping
    digitalWrite(GREEN, LOW); 
    delay(500);
    digitalWrite(GREEN, HIGH);
    delay(500);
      tone(BUZZER, 380, 500);
    digitalWrite(GREEN, LOW);
    delay(500);
    digitalWrite(GREEN, HIGH);
    delay(500);
      tone(BUZZER, 380, 500);
    digitalWrite(GREEN, LOW);
    delay(500);
    digitalWrite(GREEN, HIGH);
    delay(500);
      tone(BUZZER, 380, 500);
    digitalWrite(GREEN, LOW); //blinking becomes more frequent
    delay(150);
    digitalWrite(GREEN, HIGH);
    delay(150);
      tone(BUZZER, 580, 150); //tone goes higher
    digitalWrite(GREEN, LOW);
    delay(150);
    digitalWrite(GREEN, HIGH);
    delay(150); 
      tone(BUZZER, 580, 150);
    digitalWrite(GREEN, LOW);
    delay(150);
    digitalWrite(GREEN, HIGH);
    delay(150);
      tone(BUZZER, 580, 150);
    digitalWrite(GREEN, LOW);
    delay(50);
    digitalWrite(GREEN, HIGH);
    delay(50);
    count = 9;
      tone(BUZZER, 580, 50);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    myservo.write(90); //barrier up 
  
}
```
Demo:<br>
<div style="text-align:center"><img src="https://cloud.githubusercontent.com/assets/22894897/22894632/f0f684f6-f1d6-11e6-856a-ccdddac89cad.gif"></div>

# Coward Robot example
(Week 5)

A robot who runs from the enemy as soon as he finds it in front of him.

Wiring:

<div style="text-align:center"><img width="991" alt="screenshot 2017-02-13 15 42 31" src="https://cloud.githubusercontent.com/assets/22894897/22906836/a30e75e6-f203-11e6-9e39-838de975d99c.png"></div>

Schematics:

<div style="text-align:center"><img width="1135" alt="screenshot 2017-02-13 21 23 30" src="https://cloud.githubusercontent.com/assets/22894897/22915202/aee18780-f232-11e6-8754-7d3841fa9821.png"></div>

Code:
```C++
//Coward Robot
//Author: Niam Moltta
//this coward Starts reversing when it founds something close.

#define E1 10  // Enable Pin for motor 1
#define I2 8  // Control pin 1 for motor 1
#define I1 9  // Control pin 2 for motor 1
const int Ping = A0; //Ultrasonic sensor

void setup() {
    
    Serial.begin(9600);
    pinMode(E1, OUTPUT);
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
}

void loop() {

//analogWrite(E1, 255); // Run in half speed
  
 long duration, inches, cm;
   
  pinMode(Ping, OUTPUT);
  digitalWrite(Ping, LOW);
  delayMicroseconds(2);
  digitalWrite(Ping, HIGH);
  delayMicroseconds(5);
  digitalWrite(Ping, LOW);

  pinMode(Ping, INPUT);
  duration = pulseIn(Ping, HIGH);
  
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  
  // Serial monitor
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(15);
 
  if (cm <= 30) {
  
  delay(1000);
  digitalWrite(E1, HIGH);
  digitalWrite(I1, LOW); //ccw
  digitalWrite(I2, HIGH);
  
  }
  
  else {
    
  digitalWrite(E1, HIGH); //cw
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  
  }  

} 

long microsecondsToInches(long microseconds) {
  
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
 
  return microseconds / 29 / 2;
}
```
Demo:<br>
<div style="text-align:center"><img src="https://cloud.githubusercontent.com/assets/22894897/22916363/4619335c-f23b-11e6-815d-a0d056923a6d.gif"></div>
<br><br>

<br>
<br>
<p align="center"><a href="https://lastralab.github.io/website/" target="_blank"><br><button><img src="http://i.imgur.com/ERyS5Xn.png" alt="l'astra lab icon" width="50px" background="transparent" opacity="0.5" padding="0;"/></button></a></p><br><br>
