#include <esp_now.h>
#include <WiFi.h>

#define LED 2
#define BUZZER 25
#define RELAY 26
#define TURN_ON_COMMAND 247
#define TURN_OFF_COMMAND 248

int Countdown = 0;
bool BoilerStatus = false;

void Bebeep()
{
  digitalWrite(BUZZER, LOW);
  delay(150);
  digitalWrite(BUZZER, HIGH);
  delay(75);
  digitalWrite(BUZZER, LOW);
  delay(150);
  digitalWrite(BUZZER, HIGH);
}
void Beep()
{
  digitalWrite(BUZZER, LOW);
  delay(1000);
  digitalWrite(BUZZER, HIGH);
}
void TurnOnBoiler()
{
  digitalWrite(RELAY, LOW);
  BoilerStatus = true;
}
void TurnOffBoiler()
{
  digitalWrite(RELAY, HIGH);
  BoilerStatus = false;
}

void onReceiveData(const uint8_t *mac, const uint8_t *data, int len)
{
  if (data[0] == TURN_ON_COMMAND)
  {
    TurnOnBoiler();
    Bebeep();
  }
  else if (data[0] == TURN_OFF_COMMAND)
  {
    TurnOffBoiler();
    Bebeep();
  }

  Countdown = data[1] * 10;
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);

  digitalWrite(BUZZER, HIGH);
  digitalWrite(RELAY, HIGH);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onReceiveData);
}

void loop()
{
  Countdown--;
  if (Countdown <= 0)
  {
    if (BoilerStatus)
    {
      TurnOffBoiler();
      Beep();
    }
    Countdown = 0;
  }
  delay(1000);
}