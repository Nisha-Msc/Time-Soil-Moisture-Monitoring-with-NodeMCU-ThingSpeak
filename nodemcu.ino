#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Wi-Fi credentials
const char* ssid = "realme";
const char* password = "rathipriya";

// ThingSpeak settings
unsigned long channelID = 2708684;         // Replace with your ThingSpeak Channel ID
const char* writeAPIKey = "9QVAYJXC2EHK8DF9";    // Replace with your ThingSpeak Write API Key

WiFiClient client;

void setup() {
  Serial.begin(9600);  // Initialize Serial communication at 9600 baud
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  int sensorValue = analogRead(A0); // Read analog value from soil moisture sensor

  // Map the sensor value to a percentage (0% dry to 100% wet)
  int moisturePercentage = map(sensorValue, 1023, 0, 0, 100);

  // Print the sensor reading and moisture percentage
  Serial.print("Soil Moisture (Raw Value): ");
  Serial.print(sensorValue);
  Serial.print("\tSoil Moisture (%): ");
  Serial.print(moisturePercentage);
  Serial.println(" %");

  // Send data to ThingSpeak
  ThingSpeak.setField(1, moisturePercentage); // Sending soil moisture to Field 1
  int x = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (x == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(x);
  }

  delay(20000); // Delay for 20 seconds before sending the next reading
}
