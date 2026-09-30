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


## Conexión

El potenciómetro se conectó al ESP32 utilizando el pin GPIO 34 como entrada analógica.

| Potenciómetro | ESP32 |
|---|---|
| VCC | 3.3 V |
| Señal | GPIO 34 |
| GND | GND |

La conexión permite que el ESP32 lea la variación de voltaje generada al girar el potenciómetro.

## Funcionamiento

El ESP32 realiza la lectura analógica del potenciómetro mediante el pin GPIO 34.  
El valor obtenido por el convertidor ADC varía entre 0 y 4095.

Para obtener una lectura más estable, se toman varias muestras consecutivas y se calcula el promedio de los valores obtenidos.

Posteriormente, el valor promedio del ADC se convierte a voltaje utilizando la siguiente expresión:

\[
V = \frac{ADC \times 3.3}{4095}
\]

donde:

- `ADC` representa el valor promedio leído.
- `3.3 V` corresponde al voltaje de referencia.
- `4095` es el valor máximo del ADC de 12 bits.

Finalmente, tanto el valor promedio del ADC como el voltaje calculado se muestran en el monitor serial.

