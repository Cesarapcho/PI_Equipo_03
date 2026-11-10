# Pruebas individuales del sensor FSR

Documentación de las pruebas matemáticas, sintéticas, experimentales y simulaciones del sensor **FSR RFP-602**, correspondientes al **TRL 3** del proyecto **Ligura**.

## 1. Objetivo

Evaluar el comportamiento del sensor FSR ante variaciones de presión, con el propósito de determinar su viabilidad para monitorear la fuerza de sujeción ejercida por el gripper sobre la granadilla.

## 2. Actividades desarrolladas

| N.º | Actividad | Descripción |
|---|---|---|
| 01 | Fundamento matemático | Análisis de la resistencia del FSR, divisor de voltaje y conversión ADC. |
| 02 | Prueba sintética en Python | Simulación de la respuesta eléctrica del sensor y visualización de resultados. |
| 03 | Prueba experimental con ESP32 | Lectura de valores ADC mediante la aplicación manual de presión. |
| 04 | Simulación en Tinkercad | Evaluación virtual de la respuesta del sensor ante diferentes fuerzas. |
| 05 | Calibración con masas conocidas | Diseño del montaje y análisis ilustrativo de calibración mediante cargas. |

## 3. Análisis general de resultados

Las pruebas permitieron analizar el comportamiento del sensor FSR ante variaciones de presión.

En la prueba experimental con ESP32 se registraron valores ADC entre **0 y 149**, observándose cambios en la señal durante la aplicación y liberación de presión.

La simulación en Tinkercad mostró una respuesta no lineal, con lecturas crecientes conforme aumentaba la fuerza aplicada.

Asimismo, se desarrolló un procedimiento de calibración mediante masas conocidas y un soporte diseñado en Onshape.

## 4. Conclusiones

- El FSR permite detectar variaciones de presión mediante cambios en su respuesta eléctrica.
- La relación entre fuerza aplicada y lectura ADC no es lineal.
- El sensor presenta potencial para monitorear la fuerza de sujeción del gripper de Ligura.

## 5. Aplicación en Ligura

El sensor FSR se ubicará en uno de los brazos del gripper para monitorear la presión durante la sujeción de la granadilla.

Las lecturas del sensor serán procesadas por el ESP32 y utilizadas como referencia para detener el cierre del servomotor cuando se alcance un umbral previamente establecido, con el objetivo de evitar daños en la fruta.
