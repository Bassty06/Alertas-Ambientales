# Sistema de Monitoreo Ambiental con Arduino

Este proyecto implementa un sistema integral de monitoreo ambiental utilizando una placa Arduino. El sistema permite medir y detectar niveles de humedad del suelo, temperatura del aire, luminosidad ambiental, y proximidad de objetos. Además, responde a diferentes condiciones con alertas acústicas mediante un buzzer.

## 📦 Componentes Utilizados

- **Arduino UNO (o compatible)**
- **Sensor de Humedad del Suelo** (entrada analógica A0)
- **Sensor de Temperatura y Humedad DHT11** (pin digital 4)
- **Sensor de Luz**:
  - Salida analógica (A1)
  - Salida digital (pin 2)
- **Sensor Ultrasónico HC-SR04** (trig: pin 9, echo: pin 10)
- **Potenciómetro** (A2)
- **LED** (pin 6)
- **Buzzer** (pin 8)

## 🧠 Funcionalidades Principales

### 🔎 Monitoreo de Sensores

- **Humedad del Suelo**: Se mide mediante un sensor analógico. El valor es interpretado como _Alto_, _Medio_ o _Bajo_ y se dispara una alarma en caso de humedad alta.
- **Temperatura del Aire**: Se obtiene mediante el sensor DHT11. Si la temperatura está por fuera del rango [20°C - 30°C], se activan alarmas diferenciadas.
- **Luminosidad**: Medida desde la entrada analógica. Si la luminosidad supera el 80%, se activa una alerta sonora.
- **Proximidad**: Detecta objetos a una distancia menor o igual a 10 cm usando el sensor ultrasónico HC-SR04.

### 🚨 Alarmas

- **Sirena de Emergencia**: Activada por humedad alta.
- **Alarma de Temperatura Alta**: Pitidos rápidos.
- **Alarma de Temperatura Baja**: Pitidos más lentos y graves.
- **Alarma de Proximidad o Luz Alta**: Tono constante durante 2 segundos.

### 💡 Control de Brillo

El brillo del LED se ajusta en tiempo real con un potenciómetro.

### 🎵 Función Extra

Una función `cantarReggaeton()` (opcional) reproduce una melodía sencilla con el buzzer, aunque no se llama en el flujo principal (`loop()`).

## 📋 Código Estructurado

- **`setup()`**: Inicializa los pines y sensores.
- **`loop()`**: Lee sensores, determina alarmas, emite sonidos y muestra datos por el puerto serial.
- **Funciones auxiliares**:
  - `sirenaEmergencia()`
  - `alarmaTemperaturaAlta()`
  - `alarmaTemperaturaBaja()`
  - `cantarReggaeton()`

## 📈 Salida Serial

Muestra información cada 9 segundos:

Humedad del suelo: Medio - 45% - Valor: 670
Temperatura del aire: 26.00 °C
Luminosidad: 70%
Distancia: 15.2 cm

## 🚀 Cómo Usar

1. Carga el código en tu placa Arduino mediante el IDE de Arduino.
2. Conecta los sensores en los pines indicados.
3. Abre el monitor serial a 9600 baudios para visualizar los datos.
4. Observa cómo se activan las alarmas en función del entorno.

## 📎 Notas Adicionales

- El sensor de humedad tiene un valor mínimo ajustado para evitar errores.
- La función `cantarReggaeton()` es decorativa y no interfiere con el funcionamiento principal.
- Puedes modificar los umbrales de temperatura, luz o proximidad fácilmente en el código.

## 🛠 Requisitos

- Arduino IDE
- Librería **DHT sensor library** (puede instalarse desde el Administrador de Librerías del IDE)

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Siéntete libre de modificar y distribuir.
