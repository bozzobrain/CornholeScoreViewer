

void selectRawTeamColor(uint8_t teamNum, uint8_t r, uint8_t g, uint8_t b);
uint8_t t1_score = 0;
uint8_t t2_score = 0;
#include "Timers.h"
#include "Communications.h"
#include "DigitController.h"
#include "ButtonInputs.h"
#include "ErrorStates.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLE.h"

#define BLE_NAME SCOREVIEWER

Adafruit_BluefruitLE_UART ble(Serial, -1);

void initBLE();

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  initDigits();
  initButtons();
  initBLE();
  
  // Clear input serial buffer
  while (Serial.available())
  {
    Serial.read();
  }
}

void loop() {
  
  rxPacket();
  updateButtons();
  updateTeamScores();
  
  delay(5); // Delay for a period of time (in milliseconds).
}

void initBLE()
{  
  if ( !ble.begin(false, true) ) errorState(ERROR_BLE_BEGIN);
  ble.setMode(BLUEFRUIT_MODE_COMMAND);
  //if (! ble.factoryReset() ) errorState(ERROR_BLE_RESET);
  ble.echo(false);
  //ble.info();
  if (! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=ScoreViewer")) ) errorState(ERROR_BLE_NAME);
  if (! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=ScoreViewer")) ) errorState(ERROR_BLE_NAME);
  ble.reset();
  /* Wait for connection */
  while (! ble.isConnected()) {
    // Without BT operate on button only system
    updateButtons();
    updateTeamScores();
    delay(5);
  }
  ble.setMode(BLUEFRUIT_MODE_DATA);
}
