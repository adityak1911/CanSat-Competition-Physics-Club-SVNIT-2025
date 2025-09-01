#include <SPI.h>
#include <LoRa.h>

// Define LoRa pins for ESP32
#define NSS_PIN   5
#define RST_PIN   14
#define DIO0_PIN  2

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LoRa Receiver");

  // Setup LoRa transceiver module
  LoRa.setPins(NSS_PIN, RST_PIN, DIO0_PIN);

  // Initialize LoRa at 433 MHz, 868 MHz, or 915 MHz (match transmitter!)
  if (!LoRa.begin(915E6)) {   // Change frequency if needed
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa initialized successfully!");
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: '");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
