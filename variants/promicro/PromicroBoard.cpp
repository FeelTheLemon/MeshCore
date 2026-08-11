#include <Arduino.h>
#include <Wire.h>

#include "PromicroBoard.h"

void PromicroBoard::begin() {    
    NRF52Board::begin();
    btn_prev_state = HIGH;

    // Detect Faketec pull-up on RX_EN, on DTQSYS pin is floating
    pinMode(SX126X_RXEN, INPUT_PULLDOWN);
    delay(1);
    if (digitalRead(SX126X_RXEN) == LOW)
        rxen_controls_swctrl = true;

    pinMode(PIN_VBAT_READ, INPUT);

    #ifdef BUTTON_PIN
      pinMode(BUTTON_PIN, INPUT_PULLUP);
    #endif

    #if defined(PIN_BOARD_SDA) && defined(PIN_BOARD_SCL)
      Wire.setPins(PIN_BOARD_SDA, PIN_BOARD_SCL);
    #endif
    
    Wire.begin();

    pinMode(SX126X_POWER_EN, OUTPUT);
    digitalWrite(SX126X_POWER_EN, HIGH);
    delay(10);   // give sx1262 some time to power up
}