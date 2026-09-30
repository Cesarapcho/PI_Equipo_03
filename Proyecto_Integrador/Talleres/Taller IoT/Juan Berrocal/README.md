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

### Montaje

![Conexión del potenciómetro](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/03_conexion_potenciometro.jpg)

### Lectura mediante el Monitor Serie

![Lectura del potenciómetro](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/01_potenciometro_montaje.jpeg)

Los valores obtenidos fueron mostrados mediante el Monitor Serie, permitiendo comprobar la variación de la lectura al girar el potenciómetro.

---

# 2. Conversión ADC a voltaje

Después de obtener la lectura ADC, se realizó una conversión matemática para expresar el resultado como voltaje.

![Conversión ADC a voltaje](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/02_conversion_adc_voltaje.jpg)

Durante una de las pruebas se obtuvo:

```text
ADC promedio: 4095.00
Voltaje: 3.30 V
```

Esta conversión permitió relacionar el valor digital obtenido por el ESP32 con el nivel de tensión correspondiente.

---

# 3. Conectividad WiFi

El ESP32 fue configurado para conectarse a una red inalámbrica. Una vez establecida la conexión, se mostró información sobre el estado de la comunicación y la dirección IP asignada.

![Conexión WiFi](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/04_conexion_wifi.jpg)

En la prueba se obtuvo una dirección IP similar a:

```text
Dirección IP asignada: 172.20.10.2
```

La conexión WiFi permitió utilizar posteriormente servicios de comunicación y plataformas IoT.

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

![Potenciómetro en ThingSpeak](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/05_thingspeak_potenciometro.jpg)

La gráfica permitió comprobar que los valores obtenidos físicamente podían ser transmitidos y visualizados mediante una plataforma IoT.

---

# 5. Medición con HC-SR04

Se incorporó el sensor ultrasónico HC-SR04 para realizar mediciones de distancia.

El sensor fue conectado al ESP32 y las mediciones fueron procesadas para obtener la distancia correspondiente.

## 5.1. Montaje

![Conexión del HC-SR04](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/11_conexion_hcsr04.jpg)

## 5.2. Lecturas obtenidas

![Lectura del HC-SR04](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/06_hcsr04_monitor_serial.jpg)

Durante las pruebas se obtuvieron valores como:

```text
Distancia: 356.14 cm
Distancia: 12.62 cm
Distancia: 13.03 cm
```

El Monitor Serie también permitió comprobar que los datos fueron enviados correctamente hacia ThingSpeak.

## 5.3. Visualización en ThingSpeak

![Gráfica del HC-SR04](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/07_thingspeak_hcsr04.jpg)

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

---

# 6. Control del LED mediante una interfaz web

En esta actividad se implementó una interfaz web para controlar el LED integrado del ESP32.

La página permite ejecutar dos acciones:

```text
ENCENDER LED
APAGAR LED
```

![Control web del LED](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%20IoT/Juan%20Berrocal/Imagenes/10_control_web_led.jpg)

El funcionamiento general es:

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


Ingeniería Informática  
Universidad Peruana Cayetano Heredia
