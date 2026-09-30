# Taller de Internet de las Cosas (IoT)

## Introducción

El presente taller tiene como finalidad desarrollar una comprensión práctica y teórica sobre el **Internet de las Cosas (IoT)** mediante el uso del **ESP32** y diferentes sensores y actuadores.

A lo largo de las actividades se trabajó con la adquisición y procesamiento de datos, la conexión del ESP32 a redes Wi-Fi, el envío de información a plataformas IoT en la nube y la visualización de datos en tiempo real. Asimismo, se realizaron pruebas de control remoto de dispositivos mediante interfaces web.

Estas actividades permitieron aplicar conceptos relacionados con sensores, conversión analógica-digital, conectividad inalámbrica, monitoreo remoto y control de dispositivos, integrando hardware y software dentro de una arquitectura IoT.

# Actividad 01 - Lectura de un potenciómetro con ESP32

## Objetivo

Mejorar la lectura de un potenciómetro conectado al ESP32 mediante el promediado de varias muestras y convertir los valores obtenidos por el ADC a valores de voltaje.

## Componentes utilizados

Para el desarrollo de esta actividad se utilizaron los siguientes componentes:

| Componente | Descripción | Imagen |
|---|---|---|
| ESP32 DevKit V1 | Tarjeta de desarrollo utilizada para realizar la lectura analógica del potenciómetro y procesar los datos obtenidos. | <img src="./imagenes/esp32_devkit.png" width="140"> |
| Potenciómetro | Componente resistivo variable cuya posición modifica el voltaje de salida que será leído por el ESP32. | <img src="./imagenes/potenciometro.png" width="140"> |
| Protoboard | Permite realizar las conexiones del circuito sin necesidad de soldadura. | <img src="./imagenes/protoboard.png" width="140"> |
| Cables jumper | Se utilizan para realizar las conexiones entre el ESP32, el potenciómetro y la protoboard. | <img src="./imagenes/cables_jumper.png" width="140"> |


