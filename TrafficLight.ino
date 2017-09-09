//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// Semáforo Arduino
// 
// Author: Niam Moltta
// License: MIT
// Downloaded from: https://circuits.io/circuits/3642162-semaforo-arduino

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
