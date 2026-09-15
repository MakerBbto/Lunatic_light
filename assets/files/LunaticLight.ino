#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Bbto";
const char* password ="Wifipatodos";
const char* serverName = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/Puebla,Mexico/today?unitGroup=us&key=JBHZC6UVVTVFYAWCVFZXB8V59&include=current&elements=moonphase"; // URL de la API

float Fase; // Cambié el tipo de int a float para manejar valores decimales
const int buttonPin = 4; // Pin donde está conectado el botón
const int redLedPin = 2; // Pin donde está conectado el LED rojo
const int greenLedPin = 15; // Pin donde está conectado el LED verde
bool buttonPressed = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configurar el pin del botón como entrada con resistencia pull-up interna
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Configurar los pines de los LEDs como salidas
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Conectar a la red Wi-Fi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    Serial.println("");
    Serial.println("Conectado a WiFi");

    // Realizar la primera solicitud HTTP una vez al inicio
    updateFase();
  } else {
    Serial.println("Error de conexión WiFi");
  }
}

void loop() {
  // Leer el estado del botón
  if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressed = true;
    // Hacer la solicitud HTTP para actualizar la variable "Fase"
    updateFase();
  } else if (digitalRead(buttonPin) == HIGH) {
    buttonPressed = false;
  }

  // Aquí se puede realizar cualquier otra operación
  delay(100); // Añadir un pequeño delay para evitar sobrecargar el loop
}

void updateFase() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Conectar a la API
    http.begin(serverName);

    // Hacer la solicitud GET
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
    ;

      // Buscar la posición de "moonphase":" en el payload
      int index = payload.indexOf("\"moonphase\":");
      if (index != -1) {
        index += 12; // Mover el índice al final de "moonphase": (12 caracteres)
        int endIndex = index;

        // Encontrar el final del valor numérico (buscar el próximo carácter no numérico)
        while (endIndex < payload.length() && (isDigit(payload[endIndex]) || payload[endIndex] == '.')) {
          endIndex++;
        }

        String faseStr = payload.substring(index, endIndex);
        Fase = faseStr.toFloat(); // Convertir a float en lugar de int
        
        // Imprimir el valor de Fase
        Serial.print("Fase: ");
        Serial.println(Fase);
      } else {
        Serial.println("Error: no se encontró moonphase en el payload.");
      }
    } else {
      Serial.print("Error en la solicitud HTTP: ");
      Serial.println(httpResponseCode);
    }

    // Liberar recursos
    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }
}