//fisier cu functii auxiliare
//biblioteca a salva fisiere in memoria esp-ului
#include <FS.h>
#include <SPIFFS.h>
//biblioteca pentru EEPROM (memorie nonvolatila)
#include <EEPROM.h>

//structura de date pentru setari wifi
struct {
  char ssid[50];
  char pass[50];
  int valid;
} setari;

//citeste setarile din EEPROM
void read_eeprom() {
  EEPROM.begin(sizeof(setari));
  EEPROM.get(0, setari);
  EEPROM.end();
}
//scrie setarile in EEPROM
void write_eeprom() {
  EEPROM.begin(sizeof(setari));
  EEPROM.put(0, setari);
  EEPROM.commit();
}

//citeste fisierul cu calea specificata
String read_file(String path) {
  String continut;
  File file = SPIFFS.open(path);
  while (file.available())
    continut += (char)file.read();
  file.close();
  return continut;
}

String urldecode(String str);
unsigned char h2int(char c);
//extrage campul 'key' din url
String url_get(String url, String key) {
  //daca nu am gasit campul, returnam sirul vid
  if (url.indexOf(key + "=") == -1)
    return "";
  //extragem si returnam valoarea campului
  int index1 = url.indexOf(key + "=") + key.length() + 1;
  url = url.substring(index1);
  int index2 = url.indexOf("&");
  if(index2 == -1)
    index2 = url.indexOf(" HTTP");
  return urldecode(url.substring(0, index2));
}

//functiile sunt luate de pe
// https://github.com/zenmanenergy/ESP8266-Arduino-Examples/blob/master/helloWorld_urlencoded/urlencode.ino
String urldecode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == '+') {
      encodedString += ' ';
    } else if (c == '%') {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c = (h2int(code0) << 4) | h2int(code1);
      encodedString += c;
    } else {
      encodedString += c;
    }
    yield();
  }
  return encodedString;
}
unsigned char h2int(char c)
{
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}
