#include <SimpleDHT.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";
WiFiClient  client;
unsigned long myChannelNumber = NUMERO_CANAL;
const char* myWriteAPIKey = "API_KEY"; // API Key del canal
int pinDHT11 = 16; // Puerto D0 entrada de datos
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); //Establece el módulo como cliente wifi
  WiFi.disconnect(); //Se desconecta de cualquier WiFi conectado
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {   // wait for WiFi
    delay(500);
    Serial.print(".");
  }
  ThingSpeak.begin(client);
}

void loop() {
  byte t = 0;
  byte h = 0;
  if (dht11.read(pinDHT11, &t, &h, NULL)) {
    Serial.print("Error en la lectura.");
    return;
  }
  // Muestra por el puerto serie las medidas obtenidas
  Serial.print("Humedad relativa: ");
  Serial.print((int)h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print((int)t);
  Serial.println(" *C");
  // Envía los datos a ThinkSpeak
  ThingSpeak.setField(1, (int)t);
  ThingSpeak.setField(2, (int)h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
  delay(20000);
}
