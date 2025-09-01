// Define LED pin
#define LED_PIN 2   // GPIO2 (D2)

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Blink Test");

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // LED ON
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(LED_PIN, LOW);   // LED OFF
  Serial.println("LED OFF");
  delay(1000);
}
