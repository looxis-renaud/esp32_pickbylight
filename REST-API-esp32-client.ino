/*
* demo of receiving JSON data from a web resource and processing it
* ESP acts as http client
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "your_ssid";
const char* password = "your_wifi_password";

String server = "http://www.loox.is/pickbylight/data.php";

#define builtIn_Led 2

DynamicJsonDocument doc(1024);

void fetch_data()
{
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      Serial.print("\n Making HTTP request to URL: ");
      Serial.println(server);
      
      http.begin(server.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode==200) {
        Serial.print("Success!!! HTTP Response code: ");
        Serial.println(httpResponseCode);
        String result = http.getString(); //this variable stores the json data returned by the server        
        Serial.println(result);
        
        deserializeJson(doc, result);
        JsonObject obj = doc.as<JsonObject>();

    // Retrieve values as strings
    String row = obj["row"].as<String>();
    int col = obj["col"];
    String action = obj["action"].as<String>();
    String status = obj["status"].as<String>();

    Serial.print("\nRow: ");
    Serial.println(row);
    Serial.print("Column: ");
    Serial.println(col);
    Serial.print("Action: ");
    Serial.println(action);
    Serial.print("Status: ");
    Serial.println(status);
        
      }
      else {
        Serial.print("Server not reachable. Error code: ");
        Serial.println(httpResponseCode);
        blink_led(3); //blink the built-in led thrice to show server error
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      setup_wifi();
    }
}
void setup_wifi(){
  delay(50);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int c=0;
  while (WiFi.status() != WL_CONNECTED) {
    blink_led(2); //blink LED twice to indicate that wifi not connected
    delay(1000); //
    Serial.print(".");
    c=c+1;
    if(c>10){
        ESP.restart(); //restart ESP after 10 seconds if not connected to wifi
    }
  }

  Serial.println("");
  Serial.print("connected to Wifi with IP address: ");
  Serial.println(WiFi.localIP());
}

void blink_led(unsigned int n){
  for (int i = 0; i < n; i++) {
    digitalWrite(builtIn_Led, HIGH);
    delay(200);
    digitalWrite(builtIn_Led, LOW); 
    delay(200);
  }
}

void setup() {
  Serial.begin(115200); 
  pinMode(builtIn_Led, OUTPUT);
  
  setup_wifi();
 
}

void loop() {
  // 15 seconds delay
  for (int i = 0; i < 15; i++) {
    delay(1000);
    Serial.print("-");
  }
  
  fetch_data();
  
}
