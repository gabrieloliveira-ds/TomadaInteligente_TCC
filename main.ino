#include <WiFi.h>
#include <HTTPClient.h>

String serverName = "https://jsonplaceholder.typicode.com/todos/1";


unsigned long lastTime = 0;
unsigned long lastDelay = 50000;


void setupwifi() {
  char* ssid = "AP_1008_2.4";
  char* password = "j981891415";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  callApi();
}

void callApi() {
  Serial.println("--callApi");
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    String serverPath = serverName;
    http.begin(serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();
    Serial.print(httpResponseCode);
    Serial.print("httpResponseCode");

    if (httpResponseCode>0){
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } 
    else {
      Serial.print("Error Code: ");
      Serial.print(httpResponseCode);
    }
    // Free resource
    http.end();
  }
  else {
    Serial.println("Wifi Disconnected");
  }

  lastTime = millis();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupwifi();
}

void loop() {
  // put your main code here, to run repeatedly:

  sleep(2);
}
