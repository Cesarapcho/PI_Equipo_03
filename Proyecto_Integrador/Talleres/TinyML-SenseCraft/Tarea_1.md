# 🟢 TinyML con SenseCraft AI
### Reconocimiento visual y activación de salidas GPIO

**Proyecto Integrador · Taller de TinyML**

Este proyecto consiste en implementar un modelo de inteligencia artificial en la plataforma SenseCraft AI y ejecutarlo en el dispositivo **XIAO ESP32S3 Sense**. Se realizan pruebas de reconocimiento visual con integrantes del equipo y se configura una salida GPIO para activar un LED cuando se cumple una condición de detección.

---

## 🎯 1. Objetivos

- Implementar un modelo diferente de inteligencia artificial en SenseCraft AI.
- Desplegar el modelo en el dispositivo XIAO ESP32S3 Sense.
- Evaluar el reconocimiento visual mediante pruebas con integrantes del equipo.
- Configurar una regla de activación a través de GPIO.
- Verificar el encendido del LED según la condición establecida.

## 🧰 2. Herramientas y componentes

| Recurso | Descripción |
|---|---|
| SenseCraft AI | Plataforma para gestionar y ejecutar modelos de IA. |
| XIAO ESP32S3 Sense | Dispositivo con cámara para inferencia en el borde. |
| Gender Detection | Modelo de detección visual seleccionado. |
| GPIO | Interfaz para controlar una salida digital. |
| LED amarillo | Indicador visual de la activación. |
| USB | Conexión del dispositivo con la computadora. |

## 🤖 3. Implementación del modelo

Se seleccionó el modelo **Gender Detection**, basado en Swift-YOLO y disponible en la biblioteca de SenseCraft AI. El modelo permite realizar inferencias sobre imágenes capturadas por la cámara y visualizar las detecciones mediante recuadros, etiquetas y valores de confianza.

### Modelo en ejecución

![Modelo Gender Detection en ejecución](Imagenes/02-modelo-en-ejecucion.jpg)

### Selección del modelo en la biblioteca

![Biblioteca de modelos de SenseCraft AI](Imagenes/03-biblioteca-modelo.jpg)

## 🔌 4. Conexión y configuración del dispositivo

Se utilizó el dispositivo XIAO ESP32S3 Sense para ejecutar el modelo de visión artificial. La conexión se realizó mediante USB, siguiendo el procedimiento de conexión y configuración del dispositivo.

![Conexión del XIAO ESP32S3 Sense](Imagenes/04-conexion-dispositivo.jpg)

Una vez conectado el dispositivo, se verificó la vista previa de la cámara y el funcionamiento del modelo.

![Vista previa del modelo](Imagenes/05-vista-previa-modelo..jpg)

## 🧪 5. Pruebas de reconocimiento visual

Se realizaron pruebas con dos integrantes del equipo para comprobar el funcionamiento del modelo **Gender Detection**. Se analizaron las etiquetas generadas y sus valores de confianza para interpretar los resultados obtenidos.

### Prueba 1: Rodrigo Sebastián Asmat Mendoza

![Prueba de reconocimiento de Rodrigo Sebastián Asmat Mendoza](Imagenes/08-prueba-reconocimiento-integrante-1.jpg)

**Integrante:** RODRIGO SEBASTIAN ASMAT MENDOZA.

**Resultado obtenido:** el modelo detectó la etiqueta `male` con un valor de confianza de **86**.

**Interpretación:** el resultado fue correcto, ya que la clasificación como hombre coincidió con el resultado esperado para la persona evaluada. La captura muestra el reconocimiento realizado por el modelo y el valor de confianza asociado a la detección.

### Prueba 2: Paola Andrea Centeno Bazán

![Prueba de reconocimiento de Paola Andrea Centeno Bazan](Imagenes/09-prueba-reconocimiento-integrante-2.jpg)

**Integrante:** PAOLA ANDREA CENTENO BAZAN.

**Resultado obtenido:** el modelo detectó la etiqueta `female` con un valor de confianza de **80**.

**Interpretación:** el resultado fue correcto, ya que la clasificación como mujer coincidió con el resultado esperado para la persona evaluada. La captura muestra la detección realizada por el modelo y el valor de confianza asociado.

### Conclusión de las pruebas

En ambos casos, las etiquetas generadas por el modelo coincidieron con los resultados esperados. Esto demuestra un funcionamiento adecuado durante las pruebas realizadas, aunque estos dos casos no permiten determinar la precisión general del modelo.

## ⚙️ 6. Configuración de la salida GPIO

Se accedió a la sección GPIO de SenseCraft AI para establecer una regla que vincule el resultado de la inferencia con una acción física.

### Parámetros de configuración

| Parámetro | Valor configurado |
|---|---|
| Objeto detectado | `male` |
| Condición | Mayor que |
| Umbral de confianza | 53 |
| Salida GPIO | LED amarillo |
| Estado predeterminado | LED apagado |
| Estado activo | LED encendido |


### Regla de activación registrada

![Regla GPIO configurada](Imagenes/07-regla-gpio-configurada.jpg)

La regla se configuró para activar el LED cuando la detección del objeto `male` supera el umbral de confianza establecido en 53. De esta manera, el resultado de la inferencia puede desencadenar una acción física a través de GPIO.

## 📸 7. Evidencias fotográficas e interpretación de los integrantes

Se realizaron pruebas con los integrantes del equipo para comprobar el funcionamiento del modelo **Gender Detection** y su integración con la salida GPIO. La regla se configuró para encender el LED amarillo cuando se detecta la etiqueta `male` con una confianza superior al **54 %**.

### 👤 Rodrigo Sebastián Asmat Mendoza

![Prueba de reconocimiento de Rodrigo Sebastián Asmat Mendoza](Imagenes/foto_asmat.jpg)

**Nombre completo:** RODRIGO SEBASTIAN ASMAT MENDOZA.

**Resultado obtenido:**
- **Etiqueta detectada:** `male`.
- **Confianza del modelo:** 86 %.
- **Umbral de activación GPIO:** mayor al 53 %.
- **Estado del LED:** 🟡 Encendido.

**Interpretación:** el modelo identificó a Rodrigo con la etiqueta `male` y una confianza del 86 %, superando el umbral del 54 % configurado en la regla GPIO. Como se cumple tanto la condición de la etiqueta como la condición de confianza, el sistema activa la salida GPIO y el LED amarillo se enciende. Este resultado demuestra que la regla de activación responde correctamente ante una detección que cumple los parámetros establecidos.

### 👤 Paola Andrea Centeno Bazán

![Prueba de reconocimiento de Paola Andrea Centeno Bazán](Imagenes/foto_paola.jpg)

**Nombre completo:** PAOLA ANDREA CENTENO BAZAN.

**Resultado obtenido:**
- **Etiqueta detectada:** `female`.
- **Confianza del modelo:** 80 %.
- **Umbral de activación GPIO:** mayor al 53 %.
- **Estado del LED:** ⚫ Apagado.

**Interpretación:** el modelo identificó a Paola con la etiqueta `female` y una confianza del 80 %. Aunque este valor supera el umbral del 54 %, la regla GPIO está configurada específicamente para detectar la etiqueta `male`. Por esta razón, la condición de activación no se cumple y el LED permanece apagado. Este comportamiento demuestra que la salida GPIO depende tanto de la etiqueta detectada como del umbral de confianza configurado.

### 📊 Resumen de resultados

| Integrante | Etiqueta | Confianza | ¿Cumple la regla GPIO? | Estado del LED |
|---|---|---:|---|---|
| Rodrigo Sebastián Asmat Mendoza | `male` | 86 % | Sí | 🟡 Encendido |
| Paola Andrea Centeno Bazán | `female` | 80 % | No, la etiqueta no coincide | ⚫ Apagado |

**Conclusión:** las pruebas muestran que el sistema integra correctamente la inferencia del modelo con una respuesta física mediante GPIO. El LED amarillo se enciende cuando se detecta `male` con una confianza superior al 54 %, mientras que permanece apagado cuando la etiqueta detectada es `female`, aunque su confianza también supere dicho umbral.

## 💡 8. Interpretación del funcionamiento del LED amarillo

Durante las pruebas se observó que el **LED amarillo se enciende cuando la detección cumple el umbral de confianza establecido** en la regla GPIO.

El funcionamiento del sistema se desarrolla de la siguiente manera:

1. La cámara del XIAO ESP32S3 Sense captura la imagen.
2. El modelo procesa la imagen y genera una etiqueta con su valor de confianza.
3. SenseCraft AI evalúa si la detección cumple la condición configurada.
4. Cuando se supera el umbral establecido, se activa la salida GPIO y se enciende el LED amarillo.

**Interpretación:** el encendido del LED amarillo evidencia la interacción entre el modelo de inteligencia artificial y el hardware. De esta manera, el sistema no solo realiza una detección visual, sino que también puede generar una respuesta física según la condición configurada.

La regla documentada corresponde a la etiqueta `male`; por tanto, no debe asumirse que la detección de `female` active el LED mediante esa misma regla.

## 📊 9. Resultados y observaciones

Los resultados obtenidos durante las pruebas fueron los siguientes:

| Prueba | Integrante | Etiqueta obtenida | Confianza | Interpretación |
|---|---|---|---:|---|
| 1 | Rodrigo Sebastián Asmat Mendoza | `male` | 86 | Clasificación coincidente con el resultado esperado. |
| 2 | Paola Andrea Centeno Bazán | `female` | 80 | Clasificación coincidente con el resultado esperado. |

En ambas pruebas, las clasificaciones coincidieron con los resultados esperados para las personas evaluadas. Además, se configuró la salida GPIO para relacionar la detección de `male` con el encendido del LED amarillo cuando se cumple el umbral de confianza.

Los valores de confianza corresponden a las detecciones mostradas en las capturas y no representan la precisión global del modelo.

## ✅ 10. Conclusiones

- Se implementó un modelo de visión artificial mediante SenseCraft AI.
- Se utilizó el dispositivo XIAO ESP32S3 Sense para realizar inferencias visuales.
- Se realizaron pruebas con dos integrantes del equipo, obteniendo las etiquetas `male` y `female`, respectivamente.
- Los resultados de ambas pruebas coincidieron con los resultados esperados.
- Se configuró una regla de activación mediante GPIO con un umbral de confianza de 53.
- El encendido del LED amarillo permite observar la respuesta física del sistema cuando se cumple la condición configurada.

## 📚 11. Referencias

- [SenseCraft AI](https://sensecraft.seeed.cc/)
- [Documentación oficial de Seeed Studio](https://wiki.seeedstudio.com/)
- [XIAO ESP32S3 Sense](https://wiki.seeedstudio.com/xiao_esp32s3_sense/)

---

**Proyecto Integrador · TinyML · SenseCraft AI · XIAO ESP32S3 Sense**
