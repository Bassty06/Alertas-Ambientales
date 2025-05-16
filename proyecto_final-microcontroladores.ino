#include <DHT.h>

// === Pines y configuración ===
const int pinHumedad = A0;
const int pinBuzzer = 8;
const int pinDHT = 4;
#define DHTTYPE DHT11
DHT dht(pinDHT, DHTTYPE);

// Sensor de luminosidad
const int pinLuzAO = A1;     // Salida analógica del sensor de luz
const int pinLuzDO = 2;      // Salida digital del sensor de luz

// Sensor SRF05 (proximidad)
const int trigPin = 9;
const int echoPin = 10;
const float umbralDistancia = 10.0; // cm

const int potPin = A2; 
const int ledPin = 6; 

// Notas musicales (frecuencias en Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Variables de estado alarma
bool alarmaHumedad = false;
bool alarmaTempAlta = false;
bool alarmaTempBaja = false;
bool alarmaLuzAlta = false;
bool alarmaProximidad = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLuzDO, INPUT);

  pinMode(ledPin, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  dht.begin();
}

void loop() {

  int potValue = analogRead(potPin);          // Leer valor del potenciómetro (0–1023)
  int ledBrightness = map(potValue, 0, 1023, 0, 255); // Convertir a valor PWM (0–255)
  analogWrite(ledPin, ledBrightness);   

  // === HUMEDAD DEL SUELO ===
  int valorSensor = analogRead(pinHumedad);
  int valorAjustado = max(valorSensor, 400);
  int porcentajeHumedad = map(valorAjustado, 400, 1023, 100, 0);

  String nivel;
  if (valorAjustado <= 599) {
    nivel = "Alto";
    alarmaHumedad = true;
  } else if (valorAjustado <= 799) {
    nivel = "Medio";
    alarmaHumedad = false;
  } else {
    nivel = "Bajo";
    alarmaHumedad = false;
  }

  Serial.print("Humedad del suelo: ");
  Serial.print(nivel);
  Serial.print(" - ");
  Serial.print(porcentajeHumedad);
  Serial.print("% - Valor: ");
  Serial.println(valorSensor);

  // === TEMPERATURA DHT11 ===
  float tempC = dht.readTemperature();
  alarmaTempAlta = false;
  alarmaTempBaja = false;

  if (isnan(tempC)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    Serial.print("Temperatura del aire: ");
    Serial.print(tempC);
    Serial.println(" °C");

    if (tempC > 30.0) {
      Serial.println("¡Temperatura alta!");
      alarmaTempAlta = true;
    } else if (tempC < 20.0) {
      Serial.println("¡Temperatura baja!");
      alarmaTempBaja = true;
    }
  }

  // === SENSOR DE LUMINOSIDAD ===
  int valorLuz = analogRead(pinLuzAO);
  int porcentajeLuz = map(valorLuz, 1023, 0, 0, 100);

  Serial.print("Luminosidad: ");
  Serial.print(porcentajeLuz);
  Serial.println("%");

  alarmaLuzAlta = porcentajeLuz > 80;

  // === SENSOR SRF05 (Proximidad) ===
  long duration;
  float distanceCm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceCm = (duration * 0.0343) / 2;

  Serial.print("Distancia: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  alarmaProximidad = (distanceCm > 0 && distanceCm <= umbralDistancia);

  // === CONTROL DE BUZZER SEGÚN PRIORIDAD ===
  // Prioridad: Humedad > Temp alta > Temp baja > Proximidad > Luz alta

  if (alarmaHumedad) {
    sirenaEmergencia(5);
  } 
  else if (alarmaTempAlta) {
    alarmaTemperaturaAlta();
  } 
  else if (alarmaTempBaja) {
    alarmaTemperaturaBaja();
  } 
  else if (alarmaProximidad) {
    tone(pinBuzzer, 1500); // Buzzer proximidad
    delay(2000);
    noTone(pinBuzzer);
  } 
  else if (alarmaLuzAlta) {
    tone(pinBuzzer, 1000); // Buzzer luz alta
    delay(2000);
    noTone(pinBuzzer);
  } 
  else {
    noTone(pinBuzzer); // Apagar buzzer si no hay alarmas
  }

  delay(2000);

}


// Funciones buzzer

void sirenaEmergencia(int repeticiones) {
  for (int r = 0; r < repeticiones; r++) {
    for (int f = 500; f <= 1000; f += 10) {
      tone(pinBuzzer, f);
      delay(5);
    }
    for (int f = 1000; f >= 500; f -= 10) {
      tone(pinBuzzer, f);
      delay(5);
    }
  }
  noTone(pinBuzzer);
}

void alarmaTemperaturaAlta() {
  for (int i = 0; i < 5; i++) {
    tone(pinBuzzer, 1000);
    delay(200);
    noTone(pinBuzzer);
    delay(100);
  }
}

void alarmaTemperaturaBaja() {
  for (int i = 0; i < 3; i++) {
    tone(pinBuzzer, 400);
    delay(500);
    noTone(pinBuzzer);
    delay(500);
  }
}

void cantarReggaeton() {
  int beat = 100;
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_E4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  delay(beat / 2);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_E4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_C5, beat); delay(beat);
  delay(300);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_E4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  delay(beat / 2);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_E4, beat); delay(beat);
  tone(pinBuzzer, NOTE_G4, beat); delay(beat);
  tone(pinBuzzer, NOTE_C5, beat); delay(beat);
  noTone(pinBuzzer);
}
