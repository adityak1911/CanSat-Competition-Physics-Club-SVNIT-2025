//Transmitter Module

#include <LoRa.h>
#include <SPI.h>
#include <string.h>
 
#define ss 5
#define rst 14
#define dio0 2
 
//int counter = 0;
String message= "";
 
void setup() 
{
  Serial.begin(115200); 
  while (!Serial);
  Serial.println("LoRa Sender");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
  
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
  Serial.println("Type your Message Here (and hit enter):");
}
 
void loop() 
{
  if (Serial.available()) {
    message = Serial.readStringUntil('\n');  // Read the whole line

    if (message.length() > 0) {
      Serial.print("Sending message: ");
      Serial.println(message);

      // Send custom message via LoRa
      LoRa.beginPacket();
      LoRa.print(message);
      LoRa.endPacket();

      Serial.println("Message sent!");
    }
  }

  delay(100);
}