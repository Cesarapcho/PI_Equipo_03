# Taller de IoT con ESP32

## Descripción

En este taller se desarrollaron diferentes actividades prácticas de IoT utilizando un ESP32. Se trabajó con la lectura de un potenciómetro, conversión de señales ADC a voltaje, conexión WiFi, envío de datos a ThingSpeak, medición de distancia con un sensor HC-SR04 y control de un LED mediante una interfaz web.

El ESP32 permitió integrar la adquisición de datos, procesamiento, comunicación inalámbrica y control de dispositivos.

---

## Objetivos

- Realizar lecturas analógicas utilizando el ESP32.
- Convertir valores ADC a voltaje.
- Establecer una conexión WiFi.
- Enviar y visualizar datos mediante ThingSpeak.
- Medir distancia utilizando el sensor HC-SR04.
- Controlar un LED mediante una interfaz web.

---

## Materiales y herramientas

| Elemento | Uso |
|---|---|
| ESP32 | Procesamiento y comunicación |
| Potenciómetro | Entrada analógica |
| HC-SR04 | Medición de distancia |
| LED | Elemento de salida |
| Protoboard | Montaje de los circuitos |
| Cables Dupont | Conexiones |
| Arduino IDE | Programación |
| ThingSpeak | Visualización de datos |

---

# 1. Lectura del potenciómetro

Se conectó un potenciómetro a una entrada analógica del ESP32. Al modificar su posición, cambia la tensión de salida y el ADC del ESP32 transforma esta señal en un valor digital.

## Montaje

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/03_conexion_potenciometro.jpg" width="700">
</p>

## Lectura mediante el Monitor Serie

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/01_potenciometro_montaje.jpeg" width="700">
</p>

Los valores obtenidos fueron mostrados mediante el Monitor Serie, permitiendo comprobar la variación de la lectura al girar el potenciómetro.

```cpp
const int pinPot = 34;

void setup() {
  Serial.begin(115200);
  pinMode(pinPot, INPUT);
}

void loop() {

  int lecturaPot = analogRead(pinPot);

  Serial.print("Lectura del potenciometro: ");
  Serial.println(lecturaPot);

  delay(500);
}
```

---

# 2. Conversión ADC a voltaje

Después de obtener la lectura ADC, se realizó una conversión matemática para expresar el resultado como voltaje.

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/02_conversion_adc_voltaje.jpg" width="700">
</p>

Durante una de las pruebas se obtuvo:

```text
ADC promedio: 4095.00
Voltaje: 3.30 V
```

Esta conversión permitió relacionar el valor digital obtenido por el ESP32 con el nivel de tensión correspondiente.

```cpp
const int entradaAnalogica = 34;
const int cantidadMuestras = 10;

void setup() {
  Serial.begin(115200);
}

void loop() {

  long acumulador = 0;

  for (int muestra = 0; muestra < cantidadMuestras; muestra++) {

    acumulador += analogRead(entradaAnalogica);

    delay(10);
  }

  float promedioADC = acumulador / (float)cantidadMuestras;

  float tension = (promedioADC * 3.3) / 4095.0;

  Serial.print("ADC promedio: ");
  Serial.print(promedioADC, 2);

  Serial.print(" | Voltaje: ");
  Serial.print(tension, 2);

  Serial.println(" V");

  delay(500);
}
```

---

# 3. Conectividad WiFi

El ESP32 fue configurado para conectarse a una red inalámbrica. Una vez establecida la conexión, se mostró información sobre el estado de la comunicación y la dirección IP asignada.

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/04_conexion_wifi.jpg" width="700">
</p>

En la prueba se obtuvo una dirección IP similar a:

```text
Dirección IP asignada: 172.20.10.2
```

La conexión WiFi permitió utilizar posteriormente servicios de comunicación y plataformas IoT.

```cpp
#include <WiFi.h>

const char* nombreRed = "NOMBRE_DE_LA_RED";
const char* claveRed = "CONTRASEÑA_DE_LA_RED";

void setup() {

  Serial.begin(115200);

  Serial.println("Iniciando conexion WiFi...");

  WiFi.begin(nombreRed, claveRed);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi conectado correctamente");

  Serial.print("Direccion IP asignada: ");

  Serial.println(WiFi.localIP());
}

void loop() {

}
```

---

# 4. Comunicación con ThingSpeak

Con la conexión WiFi disponible, el ESP32 fue utilizado para enviar información hacia ThingSpeak.

El proceso general fue:

```text
Sensor
   ↓
ESP32
   ↓
WiFi
   ↓
ThingSpeak
   ↓
Gráfica
```

## 4.1. Datos del potenciómetro

Los valores obtenidos mediante el potenciómetro fueron enviados a ThingSpeak y representados mediante una gráfica.

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/05_thingspeak_potenciometro.jpg" width="700">
</p>

La gráfica permitió comprobar que los valores obtenidos físicamente podían ser transmitidos y visualizados mediante una plataforma IoT.

```cpp
#include <WiFi.h>
#include <ThingSpeak.h>

const char* redWiFi = "NOMBRE_DE_LA_RED";
const char* passwordWiFi = "CONTRASEÑA_DE_LA_RED";

unsigned long idCanal = TU_CHANNEL_ID;
const char* claveEscritura = "TU_WRITE_API_KEY";

WiFiClient conexion;

const int sensorPot = 34;

void setup() {

  Serial.begin(115200);

  WiFi.begin(redWiFi, passwordWiFi);

  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi conectado correctamente");

  Serial.print("IP del ESP32: ");

  Serial.println(WiFi.localIP());

  ThingSpeak.begin(conexion);
}

void loop() {

  int datoPot = analogRead(sensorPot);

  Serial.print("Potenciometro: ");

  Serial.println(datoPot);

  ThingSpeak.setField(1, datoPot);

  int estadoEnvio = ThingSpeak.writeFields(
    idCanal,
    claveEscritura
  );

  if (estadoEnvio == 200) {

    Serial.println("Dato enviado correctamente a ThingSpeak");

  } else {

    Serial.print("Error en el envio: ");

    Serial.println(estadoEnvio);
  }

  Serial.println("---------------------------");

  delay(20000);
}
```

---

# 5. Medición con HC-SR04

Se incorporó el sensor ultrasónico HC-SR04 para realizar mediciones de distancia.

El sensor fue conectado al ESP32 y las mediciones fueron procesadas para obtener la distancia correspondiente.

## 5.1. Montaje

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/11_conexion_hcsr04.jpg" width="700">
</p>

## 5.2. Lecturas obtenidas

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/06_hcsr04_monitor_serial.jpg" width="700">
</p>

Durante las pruebas se obtuvieron valores como:

```text
Distancia: 356.14 cm
Distancia: 12.62 cm
Distancia: 13.03 cm
```

El Monitor Serie también permitió comprobar que los datos fueron enviados correctamente hacia ThingSpeak.

## 5.3. Visualización en ThingSpeak

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/07_thingspeak_hcsr04.jpg" width="700">
</p>

La gráfica permite observar las variaciones de distancia registradas durante la prueba.

El flujo utilizado fue:

```text
HC-SR04
   ↓
ESP32
   ↓
WiFi
   ↓
ThingSpeak
   ↓
Gráfica
```

```cpp
#include <WiFi.h>
#include <ThingSpeak.h>

const char* wifiNombre = "NOMBRE_DE_LA_RED";
const char* wifiClave = "CONTRASEÑA_DE_LA_RED";

unsigned long numeroCanal = TU_CHANNEL_ID;
const char* apiThingSpeak = "TU_WRITE_API_KEY";

WiFiClient clienteIoT;

const int pinTrigger = 25;
const int pinEcho = 26;

float calcularDistancia() {

  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(pinTrigger, LOW);

  long tiempoEco = pulseIn(pinEcho, HIGH, 30000);

  if (tiempoEco == 0) {
    return 0;
  }

  float distanciaCm = (tiempoEco * 0.0343) / 2.0;

  return distanciaCm;
}

void setup() {

  Serial.begin(115200);

  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  WiFi.begin(wifiNombre, wifiClave);

  Serial.print("Conectando al WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi conectado");

  Serial.print("Direccion IP: ");

  Serial.println(WiFi.localIP());

  ThingSpeak.begin(clienteIoT);
}

void loop() {

  float medida = calcularDistancia();

  Serial.print("Distancia: ");
  Serial.print(medida, 2);
  Serial.println(" cm");

  ThingSpeak.setField(1, medida);

  int resultado = ThingSpeak.writeFields(
    numeroCanal,
    apiThingSpeak
  );

  if (resultado == 200) {

    Serial.println("Dato enviado correctamente a ThingSpeak");

  } else {

    Serial.print("Error al enviar datos: ");

    Serial.println(resultado);
  }

  delay(20000);
}
```

---

# 6. Control del LED mediante una interfaz web

En esta actividad se implementó una interfaz web para controlar el LED integrado del ESP32.

## ESP32 utilizado

<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/09_esp32.jpg" width="700">
</p>

## Interfaz web
<p align="center">
  <img src="https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/10_control_web_led.jpg" width="700">
</p>

La página permite ejecutar dos acciones:

```text
ENCENDER LED
APAGAR LED
```

```text
Navegador
   ↓
Red WiFi
   ↓
ESP32
   ↓
LED
```

Al seleccionar una opción desde la interfaz, el ESP32 recibe la solicitud y modifica el estado del LED.

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssidWeb = "NOMBRE_DE_LA_RED";
const char* passwordWeb = "CONTRASEÑA_DE_LA_RED";

const int salidaLed = 23;

WebServer servidor(80);

String crearPagina() {

  String pagina = R"rawliteral(

  <!DOCTYPE html>

  <html>

  <head>

    <meta charset="UTF-8">

    <meta name="viewport"
    content="width=device-width, initial-scale=1.0">

    <title>ESP32 - Control Web</title>

    <style>

      body {
        font-family: Arial;
        text-align: center;
        margin-top: 50px;
      }

      button {
        width: 200px;
        padding: 15px;
        margin: 10px;
        font-size: 18px;
        color: white;
        border: none;
        border-radius: 8px;
      }

      .on {
        background-color: green;
      }

      .off {
        background-color: red;
      }

    </style>

  </head>

  <body>

    <h1>ESP32 - Control Web</h1>

    <h2>Actividad 05 - IoT</h2>

    <p>Control del LED integrado del ESP32</p>

    <a href="/on">

      <button class="on">

        ENCENDER LED

      </button>

    </a>

    <br>

    <a href="/off">

      <button class="off">

        APAGAR LED

      </button>

    </a>

  </body>

  </html>

  )rawliteral";

  return pagina;
}

void mostrarInicio() {

  servidor.send(
    200,
    "text/html",
    crearPagina()
  );
}

void activarLed() {

  digitalWrite(salidaLed, HIGH);

  Serial.println("LED encendido");

  servidor.send(
    200,
    "text/html",
    crearPagina()
  );
}

void desactivarLed() {

  digitalWrite(salidaLed, LOW);

  Serial.println("LED apagado");

  servidor.send(
    200,
    "text/html",
    crearPagina()
  );
}

void setup() {

  Serial.begin(115200);

  pinMode(salidaLed, OUTPUT);

  digitalWrite(salidaLed, LOW);

  WiFi.begin(ssidWeb, passwordWeb);

  Serial.print("Conectando al WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi conectado correctamente");

  Serial.print("IP del ESP32: ");

  Serial.println(WiFi.localIP());

  servidor.on("/", mostrarInicio);

  servidor.on("/on", activarLed);

  servidor.on("/off", desactivarLed);

  servidor.begin();

  Serial.println("Servidor web iniciado");
}

void loop() {

  servidor.handleClient();
}
```

---

# 7. Arquitectura general

Las actividades realizadas pueden representarse mediante el siguiente esquema:

```text
                     RED WiFi
                        |
                        v
                 +-------------+
                 |    ESP32    |
                 +------+------+
                        |
          +-------------+-------------+
          |             |             |
          v             v             v
   Potenciómetro     HC-SR04         LED
          |             |             ^
          |             |             |
          +------+------+             |
                 |                    |
                 v                    |
            ThingSpeak          Interfaz Web
                 |
                 v
              Gráficas
```

El ESP32 actúa como elemento central del sistema, encargándose de adquirir información, procesar datos, comunicarse mediante WiFi y responder a solicitudes de control.

---

# 8. Resultados

| Actividad | Resultado |
|---|---|
| Potenciómetro | Lectura de valores analógicos |
| Conversión ADC | Obtención del voltaje |
| WiFi | Conexión y asignación de IP |
| ThingSpeak | Envío y visualización de datos |
| HC-SR04 | Medición de distancia |
| Interfaz web | Control del LED |

---

# 9. Conclusiones

El taller permitió comprender de forma práctica el funcionamiento de un sistema IoT utilizando un ESP32.

Primero se trabajó con la adquisición de señales mediante un potenciómetro y la conversión de sus valores ADC a voltaje. Posteriormente se estableció la conexión WiFi, permitiendo enviar información hacia ThingSpeak y visualizarla mediante gráficas.

La incorporación del HC-SR04 permitió realizar mediciones de distancia y transmitir los resultados utilizando el mismo sistema de comunicación.

Finalmente, mediante una interfaz web se implementó el control del LED desde un navegador. Esto permitió comprobar que el ESP32 puede utilizarse tanto para adquirir información del entorno como para ejecutar acciones sobre dispositivos físicos.

En conjunto, el taller permitió integrar los principales elementos de una aplicación IoT:

```text
Dispositivo físico
       ↓
    ESP32
       ↓
Procesamiento
       ↓
Comunicación WiFi
       ↓
Visualización / Control
```

---
