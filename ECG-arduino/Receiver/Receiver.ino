#include <SoftwareSerial.h>

#define BT_RX 10
#define BT_TX 11

SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop()
{
  static uint32_t preTime;
  if (millis() - preTime >= 1001)
  {
    while (BTSerial.available())
    {
      String data = BTSerial.readStringUntil('\n');
      // Serial.print("Received data from master: ");
      Serial.println(data);
    }
    preTime += 1000;
  }
}
