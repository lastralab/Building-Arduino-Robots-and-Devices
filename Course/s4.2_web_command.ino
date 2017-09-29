//основная часть скетча - пример WebServer 
//из раздела Ethernet в образцах 

#include <SPI.h>
#include <Ethernet.h>

//добавлен пин для светодиода, 
//на котором проверяется получение команды
#define LED_PIN 7

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0xEA, 0x0F
};
IPAddress ip(192, 168, 0, 150);

//создание объекта типа String (строка)
//для хранения запроса
String request;

EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_PIN, OUTPUT);
 
  while (!Serial) {
    ; 
  }

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
   
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        //добавление очередного пришедшего символа к строке с запросом
        if (request.length() < 100) {
          request += c;
        }

        Serial.write(c);
        
        if (c == '\n' && currentLineIsBlank) {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  
          client.println("Refresh: 1;url=\"http://192.168.0.150\"");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
      
          for (int analogChannel = 0; analogChannel < 1; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          //добавлен вывод ссылок On и Off на страницу
          client.println("<br />");  
          client.println("<a href=\"/?on\"\">On</a>");
          client.println(" ");
          client.println("<a href=\"/?off\"\">Off</a><br />");       

          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(1);
    client.stop();
    //если в строке с запросом обнаруживается подстрока "?on",
    //светодиод будет включаться
    if (request.indexOf("?on") > 0) {
      digitalWrite(LED_PIN, HIGH);
    }
    //если в строке с запросом обнаруживается подстрока "?off",
    //светодиод будет выключаться
    if (request.indexOf("?off") > 0) {
      digitalWrite(LED_PIN, LOW);
    }
    //строка с запросом очищается
    request=""; 
    Serial.println("client disconnected");
  }
}

