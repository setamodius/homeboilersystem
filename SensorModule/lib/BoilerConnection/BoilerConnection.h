#ifndef BoilerConn_h
#define BoilerConn_h

#include <WiFi.h>
#include <esp_now.h>

#define PING_COMMAND 248
#define TURN_ON_COMMAND 247
#define TURN_OFF_COMMAND 248

class BoilerConnection
{
public:
    void Start();
    void TurnOnBoiler();
    void TurnOffBoiler();
    void PingBoiler();
    void InnerLoop();

private:
    void Send(uint8_t message, uint8_t countdown);
};

#endif