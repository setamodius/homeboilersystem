#include <WiFi.h>
#include <esp_now.h>
#include <BoilerConnection.h>

BoilerConnection *boiler;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
  delay(1000);
  boiler = new BoilerConnection();
  boiler->Start();
  boiler->TurnOnBoiler();
}

void loop()
{
  boiler->InnerLoop();
  delay(1000);
}