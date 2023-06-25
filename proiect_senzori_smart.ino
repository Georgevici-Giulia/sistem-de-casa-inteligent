//biblioteca necesare pentru comunicarea WiFi
#include <WiFi.h>
//biblioteca pentru senzorul BME280
#include <Adafruit_BME280.h>
//biblioteca pentru comunicarea I2C
#include <Wire.h>
//biblioteca pentru servomotor
#include <ESP32Servo.h>
//biblioteca pentru senzorul de gaz
#include <MQUnifiedsensor.h>
//fisierul cu functiile auxiliare
#include "auxiliare.h"
//headerul paginii html
#define header "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"

//pinii la care sunt conectati senzorii
const int PIN_BEC[] = {13, 15};
const int PIN_LUMINA = 35;
const int PIN_PIR = 5;
const int PIN_GAZ = 34;
const int PIN_SERVO = 18;

//variabile globale
Adafruit_BME280 bme;
TwoWire Wire2 = TwoWire(0);
Servo servo;
WiFiServer server(80);
MQUnifiedsensor MQ4("ESP-32", 3.3, 12, PIN_GAZ, "MQ-4");


float temperature, humidity, pressure, light, gas;
int miscare;
int bec[2], usa;

//functia setup ruleaza o data, la inceput
void setup() {
  //comunicarea Seriala pentru debug
  Serial.begin(115200);
  //initializarea portului I2C
  Wire2.begin(12, 14);
  //initializarea senzorului bme280
  bme.begin(0x76, &Wire2);
  //initializarea pinilor
  initializare_pini();
  //citim ssid si parola din eeprom
  read_eeprom();
  //daca sunt ssid si parola valide
  if (setari.valid == 1) {
    //se porneste wifi in mod AP + STA
    WiFi.mode(WIFI_AP_STA);
    // se realizeaza conectarea la wifi
    WiFi.begin(setari.ssid, setari.pass);
    //se asteapta 60s pentru a se conecta
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      //se incearca 60s conectarea
      if (millis() > 60000) {
        //doar modul AP
        WiFi.mode(WIFI_AP);
        WiFi.softAP("Smart home", "12345678");
        break;
      }
    }
  } else {
    //modul AP
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Smart home", "12345678");
  }
  if (WiFi.status() == WL_CONNECTED) {
    //m-am conectat la wifi, pornesc si AP-ul
    WiFi.softAP("Smart home", "12345678");
  }
  //se porneste serverul
  server.begin();
  //se initializeaza memoria SPIFFS
  SPIFFS.begin(true);
  //se afiseaza adresa ip
  Serial.println(WiFi.localIP());
}
//functia setup ruleaza la infinit
void loop() {
  //periodic, se citesc senzorii
  citire();
  //rulare server
  rulare_server();
}
//functia care se ocupa de serverul web
void rulare_server() {
  //verificare clientii disponibili
  WiFiClient client = server.available();
  //daca nu avem client
  if (!client) {
    client.flush();
    return;
  }
  //avem un client, se asteapta conectarea
  uint64_t current_millis = millis();
  while (!client.available()) {
    delay(1);
    if (millis() - current_millis > 3000) {
      return;
    }
  }
  current_millis = millis();
  //dupa ce s-a conectat, se citeste requestul
  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.indexOf("/bec") != -1) {//am apasat pe buton la bec
    client.println(header);
    client.stop();
    //iau nr becului
    int nr = url_get(request, "n").toInt();
    //aprindere/stingere bec
    toggle_bec(nr);
  } else if (request.indexOf("/garaj") != -1) {//am apasat pe buton la usa
    client.println(header);
    client.stop();
    //inchidere/deschidere usa
    toggle_usa();
  } else if (request.indexOf("?s=") != -1) {//modifica setarile wifi
    client.println(header);
    client.stop();
    //extragere date din url
    String ssid = url_get(request, "s");
    String pass = url_get(request, "p");
    //le transform din String in sir de char
    ssid.toCharArray(setari.ssid, 50);
    pass.toCharArray(setari.pass, 50);
    setari.valid=1;
    // salvez setarile
    write_eeprom();
    delay(1000);
    //restartez esp-ul
    ESP.restart();
  } else if (request.indexOf("/settings") != -1) {//clientul cere pagina de setari
    String page = header;
    //citire pagina
    page += read_file("/settings.html");
    //punere in pagina setarile actuale si adresa IP
    page.replace("&SSID", String(setari.ssid));
    page.replace("&PASS", String(setari.pass));
    if(WiFi.status() == WL_CONNECTED){
      page.replace("&IP", WiFi.localIP().toString());
    }else{
      page.replace("&IP", " --- ");
    }
    client.println(page);
  }  else {//trimit pagina principala
    String page = header;
    //citire pagina
    page += read_file("/index.html");
    //setez valorile in pagina
    page.replace("&TEMPERATURA", String(temperature, 2));
    page.replace("&UMIDITATE", String(humidity, 2));
    page.replace("&PRESIUNE", String(pressure, 2));
    page.replace("&LUMINA", String(light, 2));
    page.replace("&GAZ", String(gas));
    page.replace("&MISCARE", String(miscare? "⚠️ Miscare detectata": "Nu a fost detectata miscare"));

    page.replace("&BEC0", String((bec[0]) ? "Oprire" : "Pornire"));
    page.replace("&BEC1", String((bec[1]) ? "Oprire" : "Pornire"));
    page.replace("&USA", String((usa) ? "Inchide" : "Deschide"));

    client.println(page);
  }
}
//functia care face citirea senzorilor
uint32_t ultima_citire;
void citire() {  
  //citirea senzorului de miscare
  if(digitalRead(PIN_PIR))
    miscare = millis();
  else if(millis() - miscare  > 5000)
    miscare = 0;
  //citire senzorii o data pe secunda
  if (millis() - ultima_citire < 1000)
    return;
  //citirea senzorului BME280
  temperature =  bme.readTemperature();
  pressure = bme.readPressure() / 100.0;
  humidity = bme.readHumidity();
  //citirea senzorului de lumina
  light = analogRead(PIN_LUMINA)/40.96;
  //citirea senzorului de gaz
  MQ4.update();
  gas = MQ4.readSensor();
  if(gas > 50000 || isinf(gas))
    gas = 50000;
  
  ultima_citire = millis();
}
//functia de initializare a pinilor
void initializare_pini(){
  //pinii care sunt INPUT
  pinMode(PIN_LUMINA, INPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_GAZ, INPUT);

  //pinii care sunt OUTPUT (scriu HIGH pt a opri releele)
  pinMode(PIN_BEC[0], OUTPUT);
  digitalWrite(PIN_BEC[0], HIGH);
  pinMode(PIN_BEC[1], OUTPUT);
  digitalWrite(PIN_BEC[1], HIGH);

  //initializare servomotor
  servo.attach(PIN_SERVO);
  servo.write(0);

  //initializare senzor MQ4
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setA(1012.7); MQ4.setB(-2.786);
  MQ4.init(); 
  //rutina de calibrare
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ4.update(); 
    calcR0 += MQ4.calibrate(4.4);
  }
  MQ4.setR0(calcR0/10);
}
//functie care comuta becul
void toggle_bec(int index){
  //comutez starea becului
  bec[index] = !bec[index];
  //pornire/oprire releu
  digitalWrite(PIN_BEC[index], !bec[index]);
  Serial.print("bec ");
  Serial.print(index);
  Serial.print(" ");
  Serial.println(bec[index]);
}
//functie care comuta starea usii
void toggle_usa(){
  //comut starea
  usa = !usa;
  //deschid/inchid usa
  servo.write(90*usa);
}
