#include <SPI.h>
#include <Ethernet.h>
#include <QuadDisplay.h>

#define PUMP_PIN 7
#define BUZZ_PIN 6
#define DISPLAY_PIN 5

//пины для самодельного датчика наличия воды
#define WATER_OUT_PIN 4
#define WATER_IN_PIN 3

#define SOIL_PIN A0
#define TEMP_PIN A1
#define LIGHT_PIN A2

#define STATE_STANDBY 0
#define STATE_WATERING 1
#define STATE_NOWATER 2
#define STATE_SENDPAGE 3

//ответам функции webRequest() даны имена
#define WEB_NO_CLIENT 0
#define WEB_FORCED_WATERING 1
#define WEB_CLIMATE_REQUEST 2

//настройка длительности полива, мс
#define WATERING_MILLIS 1000

//настройка пороговых значений для климатических показателей
#define SOIL_THRESHOLD 100
#define TEMP_THRESHOLD 100
#define LIGHT_THRESHOLD 800

int state = STATE_STANDBY;

//переменные для хранения климатических показателей
int soil_humidity;
int temperature;
int lightness;
boolean gotWater;

//УПРАЖНЕНИЕ! Переделайте код так, чтобы всё работало по-прежнему, 
//но без глобальной gotWater

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xEA, 0x0F};
IPAddress ip(192, 168, 0, 150);
EthernetServer server(80);

EthernetClient client;

String request;

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(DISPLAY_PIN, OUTPUT);
  pinMode(WATER_OUT_PIN, OUTPUT);
  //входящий пин от датчика воды будет подтянут к питанию
  //т.е. срабатывание будет, если есть контакт при исходящем пине в состоянии LOW
  pinMode(WATER_IN_PIN, INPUT_PULLUP);
  pinMode(PUMP_PIN, OUTPUT);
  
  digitalWrite(WATER_OUT_PIN, HIGH);

  Ethernet.begin(mac, ip);
  server.begin();

}

void loop() {
  //отображение текущего состояния на дисплее
  displayInt(DISPLAY_PIN, state);
  
  switch (state)
  {
    case STATE_STANDBY:
      checkWater();
      if (webRequest() == WEB_FORCED_WATERING && gotWater)
        state = STATE_WATERING;
      else if (webRequest() == WEB_CLIMATE_REQUEST)
        state = STATE_SENDPAGE;
      if(checkClimate() && gotWater)
        state = STATE_WATERING;
      if(!gotWater)
        state = STATE_NOWATER;
      break;

    case STATE_WATERING:
        watering();
        state = STATE_STANDBY;
      break;

    case STATE_NOWATER:
      alarm();
      if(webRequest() == WEB_CLIMATE_REQUEST)
        state = STATE_SENDPAGE;
      else if(checkWater())
        state = STATE_STANDBY;
      break;

    case STATE_SENDPAGE:
      sendPage();
      state = STATE_STANDBY;
      break;
  }
}

//элементарная сигнализация писком
void alarm()
{
  tone(BUZZ_PIN, 3000, 1000);
}

//полив: включение помпы и ее выключение
//после заданного в настройках времени
void watering()
{
  digitalWrite(PUMP_PIN, HIGH);
  delay(WATERING_MILLIS);
  digitalWrite(PUMP_PIN, LOW);
}

//проверка климата вернет true если условия для полива наступили
//и false - если нет
boolean checkClimate()
{
  //считывание датчиков
  soil_humidity = analogRead(SOIL_PIN);
  temperature = analogRead(TEMP_PIN);
  lightness = analogRead(LIGHT_PIN);
  //сама проверка, в данном случае элементарная
  if (soil_humidity < SOIL_THRESHOLD && temperature > TEMP_THRESHOLD && lightness < LIGHT_THRESHOLD)
    return true;
  else return false;
}

//проверка воды вернет true, если вода есть
//и false - если воды нет
boolean checkWater()
{
  digitalWrite(WATER_OUT_PIN, LOW);
  //если после переключения исходящего пина датчика воды в LOW
  //контакта со входящим пином нет, на входящем будет HIGH
  if (digitalRead(WATER_IN_PIN))
    //значит, воды нет
    gotWater = false;
  else
    //в противном случае - есть
    gotWater = true;
  digitalWrite(WATER_OUT_PIN, HIGH);
  //несмотря на глобальность gotWater,
  //вернем ее значение, чтобы в состоянии "нет воды"
  //проверять наличие воды и сразу на него реагировать
  return gotWater;
}

//проверка запроса должна вернуть один вариант, если есть запрос на полив
//другой вариант, если есть запрос на данные
int webRequest()
{
  client = server.available();
  request = "";
  if (client) {

    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (request.length() < 100) {
          request += c;
        }
        //если в запросе находится подстрока "?water",
        //которая может там появиться, если была нажата 
        //ссылка Forced watering на странице,
        //webRequest() возвращает соответствующий ответ
        if (request.indexOf("?water") > 0) {
          return WEB_FORCED_WATERING;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
        if (c == '\n' && currentLineIsBlank)
        //если просто пришел запрос, то webRequest() 
        //возвращает значение "запрос данных";
        //если в запросе содержалась подстрока "?water",
        //это было обнаружено ранее, было возвращено другое значение,
        //а функция уже прекратила работу и до этого места не дошла
          return WEB_CLIMATE_REQUEST;
      }
    }
    delay(1);
    client.stop();
  }
  //если запросов не было, функция вернет соответствующее значение
  return WEB_NO_CLIENT;
}

//просто отправка страницы клиенту
void sendPage()
{
  if (client) {
    while (client.connected()) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");  
      client.println("Refresh: 1;url=\"http://192.168.0.150\"");  
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Soil humidity: ");
      client.println(soil_humidity);
      client.println("<br />Temperature: ");
      client.println(temperature);
      client.println("<br />Lightness: ");
      client.println(lightness);
      client.println("<br />");
      //в зависимости от значения gotWater
      if (gotWater)
      {
        //либо сообщение о том, что вода есть
        //и ссылка Forced watering будут отправлены
        client.println("Water ok");
        client.println("<br />");
        client.println("<a href=\"/?water\"\">Forced watering</a>");
      }
      else
      //либо будет отправлен текст об отсутсвии воды
        client.println("No water!");

      client.println("</html>");
      break;
    }
  }

  delay(1);
  client.stop();
}
