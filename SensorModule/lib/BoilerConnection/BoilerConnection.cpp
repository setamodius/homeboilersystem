#include "BoilerConnection.h"

uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x28, 0xC0, 0x80};
uint8_t defaultcountdown = 3;
uint8_t pingcountdown = defaultcountdown - 1;
esp_now_peer_info_t peerInfo;
int counter = 0;

void BoilerConnection::Start()
{
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

void BoilerConnection::TurnOnBoiler()
{
    Serial.println("Turn on boiler");
    BoilerConnection::Send(TURN_ON_COMMAND, defaultcountdown);
}

void BoilerConnection::TurnOffBoiler()
{
    Serial.println("Turn off boiler");
    BoilerConnection::Send(TURN_OFF_COMMAND, defaultcountdown);
}

void BoilerConnection::PingBoiler()
{
    BoilerConnection::Send(PING_COMMAND, defaultcountdown);
}

void BoilerConnection::InnerLoop()
{
    counter++;
    if (counter % (pingcountdown * 10) == 0)
    {
        PingBoiler();
    }

    if (counter == 255)
    {
        counter = 0;
    }
}

void BoilerConnection::Send(uint8_t message, uint8_t countdown)
{
    uint8_t x[2];
    x[0] = message;
    x[1] = countdown;

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&x, 2);

    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else
    {
        Serial.println("Error sending the data");
    }
}