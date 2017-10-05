#include <SoftwareSerial.h>
#include <ESP8266.h>
#include "private.h"

SoftwareSerial mySerial(2, 3); // RX, TX
ESP8266 wifi(mySerial);

#define HOST_NAME "checkip.dyndns.org"
void setup()
{
  Serial.begin(9600);
  Serial.println("[setup()]: Start!!");

  Serial.print("ver = ");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.println("to station ok");
  } else {
    Serial.println("to station error");
  }
  if (wifi.joinAP(SSID, PASS)) {
    Serial.println("connect success");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.println("connect error");
  }
  if (wifi.disableMUX()) {
    Serial.println("disable mux success");
  } else {
    Serial.println("disable mux error");
  }

  Serial.println("[setup()]: Finish!!");
}

void loop()
{
  char request[128];
  uint8_t buffer[512] = {0};
  
  Serial.println("[loop()]: Start!!");
  
  wifi.createTCP(HOST_NAME, 80);
  sprintf(request, "GET / HTTP/1.0\r\nHost: %s\r\nUser-Agent: arduino\r\n\r\n", HOST_NAME);
  wifi.send((const uint8_t*)request, strlen(request));

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.print("Received:[");
    for(uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }

  Serial.println("[loop()]: Finish!!");
  delay(1000 * 60 * 5);
}

/*
void setup() {
  Serial.begin(115200);
  Serial.println("Start!!");
  while (!Serial) {
  }
  Serial.println("Goodnight moon!");

  mySerial.begin(115200);
  while (!mySerial) {
  }
  mySerial.println("HELLO");
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }  
}
*/
