#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SEU_WIFI";
const char* password = "SENHA";

String serverName = "http://SEU_SERVIDOR:3000/dados";

// Pinos dos sensores
int pHPin = 34;
int turbidezPin = 35;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    float phValue = analogRead(pHPin) * (14.0 / 4095.0);
    float turbidez = analogRead(turbidezPin);

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"ph\":" + String(phValue) +
                  ",\"turbidez\":" + String(turbidez) + "}";

    int httpResponseCode = http.POST(json);

    Serial.println(httpResponseCode);
    http.end();
  }

  delay(5000);
}