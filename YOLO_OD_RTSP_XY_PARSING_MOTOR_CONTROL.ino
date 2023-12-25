#include <WiFi.h>

int TARGET_X = 320;
int TARGET_Y = 240;

int IN1 = 14;
int IN2 = 26;
int IN3 = 32;
int IN4 = 25;
int ENA = 12;
int ENB = 33;

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

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start the server
  server.begin();
}

void stop() {
  Serial.println("Stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void backward() {
  Serial.println("Backward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void forward() {
  Serial.println("Forward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void left() {
  Serial.println("Left");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void right() {
  Serial.println("Right");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void controlMotor(float x, float y, int speed) {
  Serial.println("Control motor function called");
  int xDiff = TARGET_X - x;
  int yDiff = TARGET_Y - y;

  if (xDiff > 0) {
    // Object is on the left
    left();
  } else if (xDiff < 0) {
    // Object is on the right
    right();
  } else {
    // Horizontal position is aligned, stop horizontal movement
    stop();
  }

  delay(50);

  if (yDiff > 0) {
    // Object is on the left
    forward();
//  } else if (yDiff < 0) {
    // Object is on the right
    // backward();
  } else {
    // Horizontal position is aligned, stop horizontal movement
    stop();
  }

  int pwmSpeed = map(speed, 0, 100, 0, 255);

  // Control the left and right motors
  analogWrite(ENA, pwmSpeed);
  analogWrite(ENB, pwmSpeed);
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
        
        Serial.print("Stringreq: ");
        Serial.println(Stringreq);

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

        // Control the motor based on the object's position
        controlMotor(parts[0], parts[1], 20);

        int xDiff = TARGET_X - parts[0];
        int yDiff = TARGET_Y - parts[1];
        Serial.print("xDiff: ");
        Serial.println(xDiff);
        Serial.print("yDiff: ");
        Serial.println(yDiff);

        Stringreq = "";
        delay(50);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}


