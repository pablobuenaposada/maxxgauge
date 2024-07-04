#include "ota.h"

const char* ssid = "MaxxGauge";
const char* password = "password";

void setOTA(){
  WiFi.softAP(ssid, password);
  ArduinoOTA.setHostname(ssid);
  ArduinoOTA.begin();
}