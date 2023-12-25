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
        
        // Remove the brackets from the string
        Stringreq.remove(0, 1);
        Stringreq.remove(Stringreq.length() - 1);
        
        // Split the string into parts
        int partsCount = 0;
        float parts[4];
        int index = 0;
        for (int i = 0; i < Stringreq.length(); i++) {
          if (Stringreq[i] == ' ') {
            String part = Stringreq.substring(index, i);
            if (part.length() > 0 && partsCount < 4) {  // Ignore empty parts
              parts[partsCount++] = part.toFloat();
            }
            index = i + 1;
          }
        }
        String part = Stringreq.substring(index);
        if (part.length() > 0 && partsCount < 4) {  // Ignore empty parts
          parts[partsCount++] = part.toFloat();
        }
        
        // Now parts[0] and parts[1] are the x and y values
        Serial.print("x: ");
        Serial.println(parts[0]);
        Serial.print("y: ");
        Serial.println(parts[1]);
        
        Stringreq = "";
        delay(200);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}


