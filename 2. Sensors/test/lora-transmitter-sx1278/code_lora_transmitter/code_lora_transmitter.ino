#include <SPI.h>
#include <LoRa.h>

// Define LoRa pins for ESP32
#define NSS_PIN   5
#define RST_PIN   14
#define DIO0_PIN  2

int counter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LoRa transmitter test");

  // Setup LoRa transceiver module
  LoRa.setPins(NSS_PIN, RST_PIN, DIO0_PIN);

  // Initialize LoRa at 433 MHz or 868 MHz or 915 MHz (depending on module/region)
  if (!LoRa.begin(915E6)) {   // Change frequency if needed
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa initialized successfully!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Send packet
  LoRa.beginPacket();
  LoRa.print("Hello LoRa - packet ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(2000);  // Send every 2 seconds
}
