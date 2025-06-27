#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include "pagina_html.h"

// Config DHT11
#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);  // DHT global

#define SENSOR_SOLO 34

// Wifi e servidor
const char* ssid = "teste_esp";
const char* senha = "teste123";
AsyncWebServer server(80);

// Variáveis globais
int umidade_solo = 0;
int umidade_ar = 0;
int temperatura_ar = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nInicializando DHT11...");
  dht.begin();
  delay(4000); 
  
  WiFi.softAP(ssid, senha);
  Serial.print("IP da rede: ");
  Serial.println(WiFi.softAPIP());
  
  // Página principal
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });
  
  // Dados
  server.on("/dados", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Lê o sensor de umidade do solo
    int leitura_solo = analogRead(SENSOR_SOLO);
    // Cálculo manual da porcentagem
    if (leitura_solo >= 4095) {
      umidade_solo = 0;  // Totalmente seco
    } else if (leitura_solo <= 3400) {
      umidade_solo = 100; // Totalmente úmido
    } else {
      // Interpolação linear entre os valores
      umidade_solo = 100 - ((leitura_solo - 3400) * 100) / (4095 - 3400);
    }
    
    // Lê o DHT11
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    Serial.print("Leitura bruta DHT11 -> Umidade: "); Serial.print(h); Serial.print("% Temp: "); Serial.println(t); 
    Serial.print("Leitura bruta solo: "); Serial.println(leitura_solo);
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Falha ao ler DHT11! Revisar a conexão.");
      umidade_ar = 0;
      temperatura_ar = 0;
    } else {
      umidade_ar = (int)h;
      temperatura_ar = (int)t;
    }
    
    Serial.print("Umidade solo: "); Serial.print(umidade_solo); Serial.println("%");
    Serial.print("Umidade ar: "); Serial.print(umidade_ar); Serial.println("%");
    Serial.print("Temperatura ar: "); Serial.print(temperatura_ar); Serial.println("°C");
    Serial.println("----------------------------");
    
    // Monta JSON
    String json = "{\"umidade_solo\":";
    json += umidade_solo;
    json += ",\"umidade_ar\":";
    json += umidade_ar;
    json += ",\"temperatura_ar\":";
    json += temperatura_ar;
    json += "}";
    
    request->send(200, "application/json", json);
  });
  
  server.begin();
}

void loop() {
  
}