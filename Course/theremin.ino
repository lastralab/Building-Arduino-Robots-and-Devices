const int redPin = 2 ;
const int yellowPin1 = 3 ;
const int yellowPin2 = 4 ;
const int yellowPin3 = 5 ;
const int greenPin1 = 6 ;
const int greenPin2 = 7 ;
const int photoPin = A0 ;


void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(greenPin2, OUTPUT);  
  pinMode(yellowPin1, OUTPUT);  
  pinMode(yellowPin2, OUTPUT);   
  pinMode(yellowPin3, OUTPUT);    
}

void loop(){
  // default to LED's off
  ledState(LOW,LOW,LOW,LOW,LOW,LOW);
  Serial.println(analogRead(photoPin));
    if(analogRead(photoPin)>100){
      ledState(LOW,LOW,LOW,LOW,LOW,HIGH);
      }
    if(analogRead(photoPin)>200){
      ledState(LOW,LOW,LOW,LOW,HIGH,HIGH);
      }
     if(analogRead(photoPin)>300){
      ledState(LOW,LOW,LOW,HIGH,HIGH,HIGH);
      }
      if(analogRead(photoPin)>400){
      ledState(LOW,LOW,HIGH,HIGH,HIGH,HIGH);
      }
      if(analogRead(photoPin)>500){
      ledState(LOW,HIGH,HIGH,HIGH,HIGH,HIGH);
      }
      if(analogRead(photoPin)>600){
      ledState(HIGH,HIGH,HIGH,HIGH,HIGH,HIGH);
      }
 }
 
 boolean ledState(boolean r,boolean y1,boolean y2,boolean y3,boolean g1,boolean g2){
    digitalWrite(redPin, r);
    digitalWrite(yellowPin1, y1);
    digitalWrite(yellowPin2, y2);
    digitalWrite(yellowPin3, y3);
    digitalWrite(greenPin1, g1);
    digitalWrite(greenPin2, g2);
 }
