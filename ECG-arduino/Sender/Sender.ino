#include <SoftwareSerial.h>
#include <SimpleKalmanFilter.h>

#define BT_RX 10
#define BT_TX 11

// ECG
#define LO_Pos -1
#define LO_Ne -1
#define ECG_Read -1

SoftwareSerial BTSerial(BT_RX, BT_TX);
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);

long randNumber;
long fil;

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);

  pinMode(LO_Pos, INPUT);
  pinMode(LO_Ne, INPUT);

  randomSeed(analogRead(0));
}

void loop()
{
  unsigned long now = millis() / 1e3;
  static uint32_t preTime;

  randNumber = random(501);

  if (millis() - preTime >= 1001)
  {
    fil = simpleKalmanFilter.updateEstimate(randNumber);
    BTSerial.print(", " + String(fil) + ", " + String(now) + "\n"); // Send data to the slave module
    Serial.println(String(randNumber) + ", " + String(fil) + ", " + String(now));
    preTime += 1000;
  }
}
