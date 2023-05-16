#include <SoftwareSerial.h>

// Define the RX and TX pins for the Bluetooth module
#define BT_RX 10
#define BT_TX 11

SoftwareSerial BTSerial(BT_RX, BT_TX); // Create a SoftwareSerial object for the Bluetooth module

long randNumber;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  BTSerial.begin(38400); // initialize Bluetooth communication

  randomSeed(analogRead(0));
}

void loop() {
  unsigned long now = millis() / 1e3;
  static uint32_t preTime;
  randNumber = random(300);
  if (millis() - preTime >= 1001)
  {
    BTSerial.print(String(randNumber) + ", " + String(now) + "\n"); // Send data to the slave module
    Serial.println(String(now));
    preTime += 1000;
  }
}
