// // receiver.ino
// // ESP32 test code to simulate LoRa data reception and send formatted packets over Serial

// // Example format:
// // CAN-TI-34; A-450; T-27.5; P-1; X-200; Y-500; Z-450; YX-1; YY-1; YZ-1;

// unsigned long prevMillis = 0;
// int counter = 0;

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   unsigned long currentMillis = millis();
//   if (currentMillis - prevMillis >= 1000) { // send every 1 second
//     prevMillis = currentMillis;
//     counter++;

//     // Generate some dummy data (simulate sensors)
//     int TI = counter;                          // time index
//     float altitude = random(400, 500);         // meters
//     float temperature = random(200, 350) / 10.0; // °C
//     float pressure = random(90, 110);          // kPa
//     int x = random(-500, 500);
//     int y = random(-500, 500);
//     int z = random(-500, 500);
//     int yawX = random(-10, 10);
//     int yawY = random(-10, 10);
//     int yawZ = random(-10, 10);

//     // Print in the required format
//     Serial.print("CAN-TI-");
//     Serial.print(TI);
//     Serial.print("; A-");
//     Serial.print(altitude);
//     Serial.print("; T-");
//     Serial.print(temperature);
//     Serial.print("; P-");
//     Serial.print(pressure);
//     Serial.print("; X-");
//     Serial.print(x);
//     Serial.print("; Y-");
//     Serial.print(y);
//     Serial.print("; Z-");
//     Serial.print(z);
//     Serial.print("; YX-");
//     Serial.print(yawX);
//     Serial.print("; YY-");
//     Serial.print(yawY);
//     Serial.print("; YZ-");
//     Serial.print(yawZ);
//     Serial.println(";");
//   }
// }




#include <LoRa.h>
#include <SPI.h>
 
#define ss 5
#define rst 14
#define dio0 2
 
void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
 
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
  int packetSize = LoRa.parsePacket();    // try to parse packet
  if (packetSize) 
  {
    
    Serial.println("Received packet '");
 
    while (LoRa.available())              // read packet
    {
      String LoRaData = LoRa.readString();
      Serial.println(LoRaData); 
    }
    Serial.println("' with RSSI ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }
}