#include <SoftwareSerial.h>

// Define the RX and TX pins for the Bluetooth module
#define BT_RX 10
#define BT_TX 11

SoftwareSerial BTSerial(BT_RX, BT_TX);  // Create a SoftwareSerial object for the Bluetooth module

void setup() {
  Serial.begin(9600);     // initialize Serial communication
  BTSerial.begin(38400);  // initialize Bluetooth communication
}

void loop() {
  static uint32_t preTime;
  if (millis() - preTime >= 1001) {
    while (BTSerial.available()) {                   // Check for incoming data from the master module
      String data = BTSerial.readStringUntil('\n');  // Read the incoming data
      // Serial.print("Received data from master: ");
      Serial.println(data);  // Print the incoming data to the Serial monitor
    }
    preTime += 1000;
  }
}
