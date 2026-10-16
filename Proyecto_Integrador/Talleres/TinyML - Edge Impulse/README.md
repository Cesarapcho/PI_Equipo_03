# 🟢 TinyML: Clasificación de objetos con Edge Impulse y SenseCraft AI

**Proyecto Integrador · Taller de TinyML · Universidad Peruana Cayetano Heredia (UPCH)**

## 1. Evidencia general del proyecto

![Evidencia general del proyecto](Imagenes/proyecto.png)

*Figura 1. Evidencia general del desarrollo del proyecto TinyML, incluyendo el trabajo realizado para la clasificación de celulares y mouse.*

Esta evidencia presenta una visión general del proyecto y de las actividades realizadas para desarrollar un sistema de clasificación de imágenes. El trabajo comprende la preparación del conjunto de datos, el entrenamiento del modelo mediante Transfer Learning, la evaluación de sus resultados y las pruebas de clasificación con objetos físicos.

El objetivo es comprobar si el modelo puede reconocer correctamente las dos categorías definidas y analizar su comportamiento tanto en las evaluaciones de Edge Impulse como en las pruebas realizadas mediante el dispositivo y SenseCraft AI.

## 2. Descripción del proyecto

Este proyecto consiste en desarrollar un sistema de clasificación de imágenes mediante técnicas de **TinyML (Tiny Machine Learning)**, utilizando Edge Impulse y SenseCraft AI.

El modelo permite distinguir entre dos categorías de objetos: **celular** y **mouse**. Para ello, se prepara un conjunto de imágenes etiquetadas, se entrena un modelo de aprendizaje automático y se realizan pruebas para observar su capacidad de reconocer cada objeto.

El objetivo es evaluar el funcionamiento del modelo, interpretar las métricas obtenidas durante el entrenamiento y la validación, y contrastar estos resultados con las predicciones generadas al presentar objetos reales.

Además, se busca comprender la relación entre los datos utilizados para entrenar el modelo, las métricas de evaluación y las salidas obtenidas durante las pruebas de clasificación.

## 3. Herramientas utilizadas

| Herramienta o recurso | Función dentro del proyecto |
|---|---|
| **Edge Impulse** | Permite gestionar las imágenes, entrenar el modelo, evaluar su capacidad de clasificación y analizar su rendimiento. |
| **Transfer Learning** | Permite adaptar un modelo previamente entrenado para reconocer las categorías celular y mouse. |
| **SenseCraft AI** | Se utiliza para realizar pruebas complementarias de clasificación y observar las predicciones obtenidas. |
| **Dataset de imágenes** | Contiene las imágenes etiquetadas que se utilizan para enseñar al modelo a distinguir entre las dos categorías. |
| **XIAO ESP32S3 Sense** | Dispositivo utilizado en las pruebas de clasificación documentadas mediante el Monitor Serial. |

## 4. Conjunto de datos

El conjunto de datos está compuesto por **100 imágenes en total**, distribuidas equitativamente entre las dos categorías que debe reconocer el modelo.

| Categoría | Cantidad de imágenes | Porcentaje del total |
|---|---:|---:|
| Celular | 50 | 50 % |
| Mouse | 50 | 50 % |
| **Total** | **100** | **100 %** |

- **Celular:** contiene 50 imágenes de teléfonos celulares.
- **Mouse:** contiene 50 imágenes de ratones de computadora.

![Dataset de imágenes y etiquetas](Imagenes/Dataset%28imagenes%20y%20etiquetados%29.png)

*Figura 2. Conjunto de datos y etiquetado de las imágenes utilizadas para las categorías celular y mouse.*

La distribución de 50 imágenes por categoría permite trabajar con un conjunto de datos equilibrado. Esto significa que ambas clases tienen la misma cantidad de ejemplos y que ninguna predomina numéricamente sobre la otra.

Este equilibrio es importante porque evita que la distribución de las imágenes favorezca de manera directa a una categoría por tener más ejemplos disponibles. Así, el modelo dispone de la misma cantidad de imágenes de celulares y mouse durante la preparación del conjunto de datos.

Las etiquetas permiten asociar cada imagen con su categoría correspondiente. Durante el entrenamiento, el modelo utiliza estas imágenes para aprender características visuales que ayuden a diferenciar ambos objetos. Posteriormente, se evalúa si puede reconocer esas categorías en imágenes que se le presentan.

Sin embargo, tener la misma cantidad de imágenes no garantiza por sí solo una clasificación correcta. También influyen la variedad de los ejemplos, la calidad de las imágenes, los ángulos de captura, la iluminación y la separación adecuada entre los datos de entrenamiento y validación.

## 5. Entrenamiento y evaluación del modelo

### 5.1. Transfer Learning

Se utiliza Transfer Learning para adaptar un modelo previamente entrenado a la clasificación de las dos categorías definidas: `Celular` y `Mouse`.

![Resultados de Transfer Learning](Imagenes/Transfer_learning_prueba.png)

*Figura 3. Resultados de la evaluación del modelo adaptado mediante Transfer Learning.*

La captura muestra un **accuracy del 100.00 %**. Asimismo, las métricas de área bajo la curva ROC, precisión ponderada, recall ponderado y F1 score ponderado presentan un valor de **1.00**.

Estos resultados indican que, en la evaluación presentada, el modelo logró clasificar correctamente todos los ejemplos evaluados, sin errores reflejados en la matriz de confusión mostrada.

Para interpretar estos indicadores, es necesario comprender qué mide cada uno:

- **Accuracy (exactitud): 100.00 %.** Representa la proporción de predicciones correctas respecto al total de ejemplos evaluados. Un resultado del 100 % significa que todos los ejemplos de esa evaluación fueron clasificados correctamente.
- **Área bajo la curva ROC (AUC): 1.00.** Indica una capacidad de discriminación perfecta entre las clases en la evaluación presentada. En términos prácticos, el modelo distingue claramente entre las categorías evaluadas.
- **Precisión ponderada (Weighted Precision): 1.00.** Significa que las predicciones positivas realizadas para las clases presentan una precisión del 100 % en la evaluación mostrada, considerando la ponderación utilizada por la plataforma.
- **Recall ponderado (Weighted Recall): 1.00.** Indica que el modelo identificó correctamente todos los ejemplos reales de las clases evaluadas, de acuerdo con el cálculo ponderado.
- **F1 score ponderado: 1.00.** Resume el equilibrio entre precisión y recall. El valor obtenido representa un resultado perfecto en esa evaluación.

La matriz de confusión permite observar la correspondencia entre las clases reales y las predicciones del modelo. En la captura, los ejemplos de `Celular` y `Mouse` aparecen clasificados correctamente, sin confusiones visibles entre ambas categorías.

En conjunto, estos resultados muestran que el modelo presenta un desempeño excelente en los datos evaluados. No obstante, un accuracy del 100 % no demuestra por sí solo que el modelo reconocerá cualquier celular o mouse en condiciones reales. Para confirmar su capacidad de generalización, es importante utilizar datos de validación independientes y comprobar su funcionamiento con imágenes nuevas.

### 5.2. Resultados del modelo cuantizado en Edge Impulse

![Resultados del modelo en Edge Impulse](Imagenes/Resultados_del_modelo.png)

*Figura 4. Métricas de evaluación, matriz de confusión y rendimiento del modelo cuantizado INT8 en Edge Impulse.*

La evaluación del modelo cuantizado presenta los siguientes resultados:

| Métrica | Resultado | Interpretación |
|---|---:|---|
| Versión del modelo | Quantized (INT8) | El modelo utiliza una representación numérica de 8 bits para sus parámetros, lo que favorece su implementación en dispositivos con recursos limitados. |
| Accuracy | 100.0 % | Todos los ejemplos de la evaluación mostrada fueron clasificados correctamente. |
| Área bajo la curva ROC | 1.00 | El modelo presenta una capacidad de discriminación perfecta entre las clases evaluadas. |
| Weighted Precision | 1.00 | La precisión ponderada de las predicciones es del 100 % en la evaluación mostrada. |
| Weighted Recall | 1.00 | El recall ponderado indica que se identificaron correctamente todos los ejemplos evaluados de las clases reales. |
| Weighted F1 score | 1.00 | Existe un equilibrio perfecto entre precisión y recall en la evaluación presentada. |
| F1 score de Celular | 1.00 | La clasificación de la categoría celular presenta un resultado perfecto en los datos evaluados. |
| F1 score de Mouse | 1.00 | La clasificación de la categoría mouse presenta un resultado perfecto en los datos evaluados. |

La cuantización INT8 representa los valores numéricos del modelo utilizando enteros de 8 bits. Esta técnica puede reducir los requerimientos de almacenamiento y facilitar la ejecución en dispositivos integrados, aunque su efecto exacto depende de la arquitectura y de la implementación del modelo.

En este caso, la evaluación mostrada conserva métricas de clasificación perfectas después de la cuantización. Esto indica que no se observan errores de clasificación en el conjunto evaluado y que la representación cuantizada mantiene el desempeño reflejado en la captura.

La matriz de confusión refuerza esta interpretación: las imágenes de celulares se asignan a la categoría `Celular` y las de mouse a `Mouse`, sin confusiones visibles entre las dos clases.

Es importante distinguir entre el resultado obtenido en esta evaluación y el comportamiento del modelo en cualquier situación posible. Las métricas describen los datos evaluados en Edge Impulse; por ello, no deben interpretarse automáticamente como una garantía de exactitud del 100 % para todos los objetos, fondos o condiciones de iluminación.

### 5.3. Rendimiento del modelo

Edge Impulse muestra los siguientes indicadores de rendimiento:

| Indicador | Resultado | Interpretación |
|---|---:|---|
| Motor de ejecución | EON Compiler | Herramienta de Edge Impulse que permite optimizar la implementación del modelo para dispositivos con recursos limitados. |
| Optimización | RAM optimized | La configuración de compilación prioriza la optimización del uso de memoria RAM. |
| Tiempo de inferencia | 972 ms | El modelo tarda aproximadamente 0.972 segundos en realizar una inferencia, según el resultado reportado por la plataforma. |
| Uso máximo de RAM | 228.0K | Cantidad de memoria RAM máxima reportada durante la ejecución del modelo. |
| Uso de memoria Flash | 545.9K | Espacio de memoria Flash estimado para almacenar los componentes del modelo y su implementación, según el reporte de la plataforma. |

El **tiempo de inferencia de 972 ms** representa el tiempo que tarda el modelo en procesar una entrada y producir una predicción, de acuerdo con la medición reportada. Esto equivale aproximadamente a un segundo por inferencia, por lo que resulta relevante considerar este valor al evaluar aplicaciones que necesitan responder rápidamente.

El uso máximo de RAM de 228.0K indica la memoria de trabajo que necesita el modelo durante su ejecución. La RAM se utiliza para almacenar datos temporales, tensores y otros elementos necesarios durante el procesamiento. Este requisito debe compararse con la memoria disponible en el dispositivo donde se implementará el modelo.

Por otro lado, los 545.9K de memoria Flash representan el espacio de almacenamiento reportado para el modelo y su implementación. La Flash permite conservar el programa y los componentes necesarios para ejecutar la clasificación incluso cuando el dispositivo se apaga.

El uso del EON Compiler y la optimización de RAM muestran que Edge Impulse proporciona una configuración orientada a la implementación en sistemas con recursos limitados. Sin embargo, para determinar si el modelo puede ejecutarse adecuadamente en un dispositivo concreto, también deben considerarse el espacio ocupado por el firmware, las bibliotecas adicionales y los demás componentes del programa.

Estos indicadores evalúan aspectos diferentes del sistema: las métricas de clasificación describen qué tan bien reconoce los objetos, mientras que el tiempo de inferencia y el consumo de memoria describen los recursos necesarios para realizar ese reconocimiento.

## 6. Pruebas de clasificación en el dispositivo

### 6.1. Prueba de clasificación con celular

Se presenta un teléfono celular durante la demostración del proyecto. La prueba permite relacionar el objeto físico utilizado con la salida generada por el modelo en el Monitor Serial.

**Evidencia de la prueba física**

![Demostración física de la prueba con celular](Imagenes/edge_impulse_prueba_celular.jpeg)

*Figura 5. Demostración física de la prueba de clasificación utilizando un teléfono celular.*

La imagen documenta el objeto presentado durante la prueba. Esta evidencia es importante porque permite identificar qué objeto se utilizó y contrastarlo con la predicción producida por el sistema.

**Resultado del Monitor Serial**

![Predicción del celular en el Monitor Serial](Imagenes/prediccion_celular.png)

*Figura 6. Resultado de la clasificación del celular en el Monitor Serial; se destaca la lectura seleccionada para el análisis.*

En la línea resaltada en rojo, registrada a las **16:04:37.150**, se muestran los siguientes valores:

| Clase | Valor registrado | Equivalencia aproximada |
|---|---:|---:|
| Celular | 0.94922 | 94.92 % |
| Mouse | 0.05078 | 5.08 % |

El valor de `Celular` es 0.94922, equivalente aproximadamente al 94.92 %. Por su parte, el valor de `Mouse` es 0.05078, equivalente aproximadamente al 5.08 %.

Estos valores representan las puntuaciones de salida que el modelo asigna a las dos categorías para la entrada evaluada. La puntuación de `Celular` es considerablemente mayor que la de `Mouse`, lo que indica que el modelo favorece la primera categoría al clasificar la imagen presentada.

La diferencia entre ambas puntuaciones es de aproximadamente 89.84 puntos porcentuales. Esto muestra que, en esta lectura, la predicción no está dividida de manera similar entre las dos clases, sino que existe una preferencia marcada por `Celular`.

La predicción coincide con el objeto físico presentado durante la prueba. Por tanto, la evidencia muestra un resultado de clasificación coherente con el objetivo del proyecto: reconocer un teléfono celular como perteneciente a la categoría correspondiente.

Debe tenerse en cuenta que estas puntuaciones no equivalen necesariamente a probabilidades calibradas de que la predicción sea correcta. Se interpretan como los valores de salida del modelo para esa entrada específica.

### 6.2. Prueba de clasificación con mouse

Se presenta un mouse de computadora durante la demostración del proyecto. A continuación, se muestra la evidencia física junto con la salida correspondiente del Monitor Serial.

**Evidencia de la prueba física**

![Demostración física de la prueba con mouse](Imagenes/edge_impulse_prueba_mouse.jpeg)

*Figura 7. Demostración física de la prueba de clasificación utilizando un mouse de computadora.*

La imagen muestra el objeto utilizado durante la prueba. Su finalidad es relacionar la entrada física con la salida generada por el modelo y verificar si la categoría identificada corresponde al objeto presentado.

**Resultado del Monitor Serial**

![Predicción del mouse en el Monitor Serial](Imagenes/prediccion_mouse.png)

*Figura 8. Resultado de la clasificación del mouse en el Monitor Serial; se destaca la lectura seleccionada para el análisis.*

En la línea resaltada en rojo, registrada a las **16:07:25.260**, se muestran los siguientes valores:

| Clase | Valor registrado | Equivalencia aproximada |
|---|---:|---:|
| Celular | 0.08594 | 8.59 % |
| Mouse | 0.91406 | 91.41 % |

El valor de `Mouse` es 0.91406, equivalente aproximadamente al 91.41 %. En cambio, el valor de `Celular` es 0.08594, equivalente aproximadamente al 8.59 %.

El modelo asigna una puntuación mayor a la clase `Mouse`. La diferencia entre ambas puntuaciones es de aproximadamente 82.81 puntos porcentuales, lo que muestra una preferencia clara por esta categoría en la lectura seleccionada.

Este resultado es coherente con el objeto físico presentado. El modelo identifica al mouse como la clase predominante en lugar de confundirlo con un celular, lo que constituye una evidencia favorable de su funcionamiento en esta prueba.

Al igual que en la prueba anterior, los valores representan las puntuaciones de salida del modelo para una entrada concreta. No deben interpretarse como una garantía de que todas las futuras predicciones de mouse tendrán exactamente el mismo porcentaje.

### 6.3. Interpretación conjunta de las pruebas en el dispositivo

Las dos lecturas seleccionadas del Monitor Serial muestran que el modelo asigna la puntuación más alta a la categoría correspondiente al objeto presentado.

| Objeto presentado | Puntuación de la clase correcta | Puntuación de la otra clase | Interpretación |
|---|---:|---:|---|
| Celular | 94.92 % | 5.08 % | El modelo identifica `Celular` como la clase predominante. |
| Mouse | 91.41 % | 8.59 % | El modelo identifica `Mouse` como la clase predominante. |

En la prueba con celular, el modelo asigna aproximadamente el 94.92 % de su puntuación de salida a `Celular`. En la prueba con mouse, asigna aproximadamente el 91.41 % a `Mouse`.

Ambas lecturas presentan una diferencia clara entre la clase correcta y la alternativa. Esto indica que, para las entradas seleccionadas, el modelo no muestra una competencia estrecha entre las dos categorías, sino una preferencia marcada por la categoría esperada.

Los resultados son coherentes con la evaluación realizada en Edge Impulse y respaldan el funcionamiento del sistema en las pruebas documentadas. Sin embargo, las dos lecturas corresponden a ejemplos individuales y no permiten calcular por sí solas la exactitud global del dispositivo.

Para obtener una evaluación más representativa, sería conveniente realizar múltiples pruebas con distintos celulares y mouse, cambiar los ángulos de captura, modificar las condiciones de iluminación y registrar tanto los aciertos como los posibles errores de clasificación.

## 7. Pruebas complementarias con SenseCraft AI

### 7.1. Prueba con celular

Se presenta un teléfono celular en la interfaz de SenseCraft AI para observar el resultado de clasificación.

![Clasificación del celular en SenseCraft AI](Imagenes/prueba-celular-sensecraft.png)

*Figura 9. Resultado de la prueba de clasificación del celular en SenseCraft AI.*

La interfaz muestra los siguientes resultados:

| Clase | Resultado mostrado |
|---|---:|
| Celular | 89 % |
| Mouse | 0 % |

La interfaz muestra un resultado del 89 % para `Celular` y un 0 % para `Mouse`. La categoría celular presenta el valor superior, coincidiendo con el objeto mostrado en la prueba.

Esto significa que, para la entrada utilizada, SenseCraft AI identifica al celular como la categoría predominante. El resultado es coherente con el objetivo del sistema, que consiste en distinguir los teléfonos celulares de los mouse.

La puntuación del 89 % refleja la salida mostrada por la plataforma en esa prueba concreta. No debe confundirse con el accuracy global del modelo ni compararse directamente con las métricas de validación de Edge Impulse como si fueran el mismo indicador.

### 7.2. Prueba con mouse

Se presenta un mouse de computadora en la interfaz de SenseCraft AI para observar el resultado de clasificación.

![Clasificación del mouse en SenseCraft AI](Imagenes/prueba-mouse-sensecraft.png)

*Figura 10. Resultado de la prueba de clasificación del mouse en SenseCraft AI.*

La interfaz muestra los siguientes resultados:

| Clase | Resultado mostrado |
|---|---:|
| Celular | 0 % |
| Mouse | 100 % |

El resultado muestra un 100 % para `Mouse` y un 0 % para `Celular`. La categoría mouse presenta el valor más alto, coincidiendo con el objeto utilizado durante la prueba.

En esta entrada, la plataforma identifica al mouse como la categoría predominante y no muestra puntuación para la clase celular. Esto representa un resultado coherente con la clasificación esperada.

La salida documentada demuestra que la plataforma distingue correctamente el mouse en esta prueba individual. Sin embargo, para determinar el rendimiento general del sistema, sería necesario realizar más pruebas con diferentes objetos y condiciones.

### 7.3. Comparación de las pruebas realizadas

| Objeto presentado | Monitor Serial | SenseCraft AI |
|---|---:|---:|
| Celular | 94.92 % para Celular | 89 % para Celular |
| Mouse | 91.41 % para Mouse | 100 % para Mouse |

La comparación muestra que ambas plataformas identifican la categoría correspondiente al objeto presentado en las pruebas documentadas.

En el caso del celular, el Monitor Serial registra una puntuación de aproximadamente 94.92 % para `Celular`, mientras que SenseCraft AI muestra un 89 % para esa misma categoría.

En el caso del mouse, el Monitor Serial registra aproximadamente 91.41 % para `Mouse`, mientras que SenseCraft AI muestra un 100 %.

Las diferencias entre los valores no significan necesariamente que una plataforma sea mejor que la otra. Las salidas pueden variar según el modelo utilizado, el procesamiento de las imágenes, la implementación y las condiciones específicas de cada prueba.

Además, las puntuaciones del Monitor Serial y los porcentajes mostrados por SenseCraft AI no deben asumirse como métricas directamente equivalentes sin confirmar que ambas plataformas utilizan el mismo modelo, la misma configuración y el mismo método de cálculo.

Por ello, la comparación permite comprobar la coherencia de las predicciones en los ejemplos presentados, pero no establecer una clasificación definitiva de cuál plataforma tiene mayor exactitud global.

## 8. Conclusiones técnicas

- El proyecto desarrolla un sistema TinyML para clasificar imágenes en dos categorías: celular y mouse, utilizando Edge Impulse y SenseCraft AI.

- El conjunto de datos contiene 100 imágenes en total: 50 de celulares y 50 de mouse. Esta distribución equilibrada permite que ambas categorías tengan la misma representación numérica durante la preparación de los datos.

- El uso de Transfer Learning permite adaptar un modelo previamente entrenado a las dos categorías definidas, aprovechando características visuales aprendidas previamente.

- La evaluación mostrada en Edge Impulse presenta un accuracy del 100 %, un AUC de 1.00 y valores de precisión, recall y F1 score ponderados de 1.00. Estos resultados indican una clasificación correcta de todos los ejemplos incluidos en la evaluación presentada.

- La evaluación del modelo cuantizado INT8 también presenta métricas perfectas en la captura analizada. Esto indica que no se observan errores de clasificación en ese conjunto evaluado después de la cuantización.

- El reporte de rendimiento indica un tiempo de inferencia de 972 ms, un uso máximo de RAM de 228.0K y un uso de memoria Flash de 545.9K. Estos valores permiten evaluar los recursos necesarios para implementar el modelo en un dispositivo con memoria y capacidad de procesamiento limitadas.

- En la prueba física con celular, el Monitor Serial registra una puntuación de 0.94922 para `Celular`, equivalente aproximadamente al 94.92 %. Esta puntuación es superior al valor asignado a `Mouse`, por lo que la predicción coincide con el objeto presentado.

- En la prueba física con mouse, el Monitor Serial registra una puntuación de 0.91406 para `Mouse`, equivalente aproximadamente al 91.41 %. El modelo asigna una puntuación menor a `Celular`, mostrando una preferencia clara por la categoría correcta.

- En SenseCraft AI, la prueba con celular muestra un 89 % para `Celular`, mientras que la prueba con mouse muestra un 100 % para `Mouse`. Ambas salidas son coherentes con los objetos utilizados en las pruebas.

- Las pruebas individuales del Monitor Serial y SenseCraft AI complementan la evaluación de Edge Impulse porque permiten observar el comportamiento del sistema frente a entradas concretas. Sin embargo, no sustituyen una evaluación sistemática con múltiples ejemplos independientes.

- Las métricas de validación, las puntuaciones de salida del modelo y los indicadores de rendimiento describen aspectos diferentes del proyecto. Interpretarlos por separado permite comprender tanto la capacidad de clasificación como los recursos necesarios para ejecutar el modelo.

- Como mejora futura, se recomienda ampliar las pruebas con distintas imágenes, modelos de celulares y mouse, variaciones de iluminación y fondos diferentes. Esto permitiría analizar la capacidad de generalización del sistema y detectar posibles errores que no aparecen en las evaluaciones actuales.

En conclusión, las evidencias documentadas muestran que el modelo distingue correctamente entre celulares y mouse en las evaluaciones y pruebas seleccionadas. Los resultados constituyen una base favorable para continuar con la implementación de TinyML, manteniendo la necesidad de realizar pruebas adicionales para evaluar su comportamiento en condiciones más variadas.

---


**Proyecto Integrador · Taller de TinyML**  
Universidad Peruana Cayetano Heredia (UPCH)
