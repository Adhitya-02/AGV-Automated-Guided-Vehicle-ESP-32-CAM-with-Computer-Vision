#include <WiFi.h>

const char* ssid = "LaptopAdhit";
const char* password = "12345678";

WiFiServer server(81);
String Stringreq = ""; 

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        while (client.available()) {
          Stringreq += (char)client.read();
        }
        Serial.println(Stringreq);
        Stringreq = "";
        delay(200);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
