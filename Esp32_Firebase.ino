/**********************************************************************************
 * TITULO: Código ESP32 - FIREBASE
 * AUTOR: Jhimmy Astoraque Durán
 * DESCRIPCION: Este es el código del capítulo 6 de la serie ESP32 del canal
 * CANAL YOUTUBE: https://www.youtube.com/c/jadsatv
 * © 2020
 * *******************************************************************************/

# include <WiFi.h>
# include <DHT.h>
# include "FirebaseESP32.h"

# define DHTPIN 4
# define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
// Credenciales wifi
const  char * ssid = "FAMILIA_RS" ;
const  char * password = "sergio.0822.1118" ;
float h;
float t;

// Credenciales Proyecto Firebase
const  char * FIREBASE_HOST = "https://esp32-fa1c9-default-rtdb.firebaseio.com/";
const  char * FIREBASE_AUTH = "wyOrElp4LWA9qtsnCivUPGcyAvXGlIDDelSpve1S";

// Firebase Data object
FirebaseData firebaseData;

// Si deseamos una ruta especifica
String nodo = "/Sensores";
bool iterar = true;

void sensor();

void setup(){
  dht.begin();
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}


void loop(){
    
    delay(200); //Es un sensor lento, por lo que hay que darle tiempo.
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print(F("Humedad: "));
    Serial.print(h);
    Serial.print(F("% Temperatura: "));
    Serial.print(t);
    Serial.println(F("°C "));
    //while(iterar){
        //leer datos
        //Firebase.getInt(firebaseData, nodo + "/Hum");
        //Serial.println(firebaseData.intData());
        //delay(250);
        //Firebase.getInt(firebaseData, nodo + "/Temp");
        //Serial.println(firebaseData.intData());
        //delay(250);
        //Firebase.getString(firebaseData, nodo + "/Venti");
        //Serial.println(firebaseData.stringData());
        //getJSON,  getFloat

        // escribir datos
        Firebase.setInt(firebaseData, nodo + "/Hum", h);       
        Firebase.setInt(firebaseData, nodo + "/Temp", t);
        Firebase.setString(firebaseData, nodo + "/Venti", "off");
        //Firebase.setBool(firebaseData, nodo + "/iterar", false);

        // push de datos
        Firebase.pushInt(firebaseData, nodo + "/Hum Lecturas", h);
        delay(100);
        //Firebase.pushInt(firebaseData, nodo + "/lecturas", 128);
        //delay(100);
        //Firebase.pushInt(firebaseData, nodo + "/lecturas", 64);
        //delay(100);
        //Firebase.pushInt(firebaseData, nodo + "/lecturas", 32);
        
        //iterar = false;
        //Firebase.end(firebaseData);
    }
 // End Loop

void sensor(){

}
