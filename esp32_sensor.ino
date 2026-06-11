/**
 * 🌾 FarmTech Solutions - IoT & Automação Inteligente (Fase 3 & 5)
 * Placa: ESP32 DevKit V1
 * Sensores: DHT22 (Temperatura e Umidade do Ar), Umidade de Solo (Simulado por Potenciômetro), LDR (Luz/pH simulado)
 * Atuadores: Módulo Relé (Bomba de Irrigação), Display LCD 16x2 I2C
 * Protocolo: HTTP POST (JSON) via Wi-Fi
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Configurações do Sensor DHT22
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuração do Display LCD 16x2 I2C (Endereço 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos Analógicos e Atuadores
#define PIN_SOIL_MOISTURE 34  // GPIO34 para Umidade do Solo
#define PIN_LDR 35           // GPIO35 para Sensor LDR
#define PIN_RELAY_PUMP 2     // GPIO2 para acionamento do Relé da Bomba

// Configurações Wi-Fi e API
const char* ssid = "Wokwi-GUEST"; // Rede virtual do Simulador Wokwi
const char* password = "";
const char* serverUrl = "http://[IP_SEU_PC_LOCAL]:5000/api/dados"; // Substitua pelo IP da máquina rodando o dashboard

// Intervalo de envio (em milissegundos)
unsigned long previousMillis = 0;
const long interval = 5000; // Envia a cada 5 segundos no simulador

void setup() {
  Serial.begin(115200);
  
  // Inicialização de Sensores e Atuadores
  dht.begin();
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  digitalWrite(PIN_RELAY_PUMP, LOW); // Inicia bomba desligada
  
  // Inicializa LCD com Backlight
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("FarmTech IoT");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  
  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi!");
  lcd.clear();
  lcd.print("Wi-Fi Conectado!");
  delay(1500);
}

void loop() {
  // Leitura dos sensores físicos/simulados
  float tempAr = dht.readTemperature();
  float umidAr = dht.readHumidity();
  
  // Umidade do Solo: Lê valor analógico (0-4095) e mapeia para 0-100%
  int rawSoil = analogRead(PIN_SOIL_MOISTURE);
  float umidSolo = map(rawSoil, 0, 4095, 0, 100);
  
  // LDR / pH: Lê valor analógico e mapeia de forma ilustrativa para pH (4.0 a 9.0) ou Luz (0-100%)
  int rawLDR = analogRead(PIN_LDR);
  float phSimulado = 4.0 + ((float)rawLDR / 4095.0) * 5.0; // Mapeia pH de 4.0 a 9.0
  float luminosidade = ((float)rawLDR / 4095.0) * 100.0;
  
  // Tratamento de falhas na leitura do DHT22
  if (isnan(tempAr) || isnan(umidAr)) {
    Serial.println("Falha ao ler o sensor DHT22!");
    tempAr = 25.0; // Fallback
    umidAr = 60.0;
  }
  
  // Lógica Autônoma e Dinâmica de Irrigação (Regras Inteligentes Locais)
  bool bombaAtiva = false;
  if (umidSolo < 30.0 || tempAr > 36.0) {
    digitalWrite(PIN_RELAY_PUMP, HIGH); // Liga bomba
    bombaAtiva = true;
  } else {
    digitalWrite(PIN_RELAY_PUMP, LOW);  // Desliga bomba
  }
  
  // Atualiza Display LCD 16x2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: " + String(tempAr, 1) + "C U:" + String(umidSolo, 0) + "%");
  lcd.setCursor(0, 1);
  lcd.print("pH:" + String(phSimulado, 1) + " Irrig:" + (bombaAtiva ? "ON" : "OFF"));
  
  // Exibição no Serial Plotter / Terminal
  Serial.print("TempAr:"); Serial.print(tempAr); Serial.print(",");
  Serial.print("UmidAr:"); Serial.print(umidAr); Serial.print(",");
  Serial.print("UmidSolo:"); Serial.print(umidSolo); Serial.print(",");
  Serial.print("pH:"); Serial.print(phSimulado); Serial.print(",");
  Serial.print("Bomba:"); Serial.println(bombaAtiva ? 1 : 0);
  
  // Envio de Dados via HTTP POST (Assíncrono via Intervalo)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");
      
      // Criação do JSON de payload
      StaticJsonDocument<200> doc;
      doc["temperatura"] = tempAr;
      doc["umidade_ar"] = umidAr;
      doc["umidade_solo"] = umidSolo;
      doc["ph"] = phSimulado;
      doc["luminosidade"] = luminosidade;
      
      String jsonPayload;
      serializeJson(doc, jsonPayload);
      
      Serial.print("Enviando POST: ");
      Serial.println(jsonPayload);
      
      int httpResponseCode = http.POST(jsonPayload);
      
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Resposta do Servidor (HTTP " + String(httpResponseCode) + "): ");
        Serial.println(response);
      } else {
        Serial.print("Erro no POST HTTP: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }
      http.end();
    } else {
      Serial.println("Erro: Wi-Fi desconectado!");
    }
  }
  
  delay(1000); // Aguarda 1 segundo por ciclo
}
