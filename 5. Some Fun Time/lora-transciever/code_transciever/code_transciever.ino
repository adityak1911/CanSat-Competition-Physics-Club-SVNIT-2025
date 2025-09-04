#include <LoRa.h>
#include <SPI.h>

#define ss 5
#define rst 14
#define dio0 2

String teamName = "TeamA";   // Change this to set your team name
String message = "";

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Chat System");

  LoRa.setPins(ss, rst, dio0); // setup LoRa transceiver module

  while (!LoRa.begin(433E6))   // 433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
  Serial.println("Type your message and press Enter to send:");
}

void loop() {
  // ================== RECEIVING ==================
  int packetSize = LoRa.parsePacket();    
  if (packetSize) {
    Serial.println("\n📩 New Message:");
    String receivedMessage = "";

    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    Serial.println(receivedMessage);
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
    Serial.println("--------------------");
  }

  // ================== SENDING ==================
  if (Serial.available()) {
    message = Serial.readStringUntil('\n');  // Read input until Enter key

    if (message.length() > 0) {
      String fullMessage = "[" + teamName + "]: " + message;

      Serial.print("📤 Sending: ");
      Serial.println(fullMessage);

      // Send via LoRa
      LoRa.beginPacket();
      LoRa.print(fullMessage);
      LoRa.endPacket();

      Serial.println("✅ Message sent!");
      Serial.println("--------------------");
    }
  }
}
