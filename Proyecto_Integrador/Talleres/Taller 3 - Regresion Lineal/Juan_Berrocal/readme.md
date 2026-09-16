
# Taller de Inteligencia Artificial

## Análisis de Datos y Modelos de Regresión

En este laboratorio se trabajó con un conjunto de datos relacionado con el **consumo de energía**, considerando variables como la temperatura, horas de operación, carga y humedad.

El desarrollo del trabajo comprende diferentes etapas del proceso de análisis y modelado de datos. Primero se analizó el comportamiento del consumo de energía y la relación entre las variables. Posteriormente, se implementó un modelo de **Regresión Lineal** para realizar predicciones y comparar los valores obtenidos con los valores reales.

---

## Implementación del modelo de Regresión Lineal

**Creación del modelo `LinearRegression`**

En esta etapa se implementó el modelo de **Regresión Lineal** utilizando la librería `scikit-learn`.

La imagen muestra la creación del objeto `LinearRegression()`, que posteriormente será utilizado para entrenar el modelo con las variables de entrada y la variable objetivo.

La Regresión Lineal busca establecer una relación matemática entre las variables utilizadas como entrada, como `Temperatura`, `Horas_Operacion`, `Carga` y `Humedad`, y la variable que se desea predecir, `Consumo_Energia`.

Esta etapa es importante porque representa el inicio de la construcción del modelo predictivo utilizado posteriormente para estimar el consumo de energía.

![Modelo de Regresión Lineal](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/Juan_Berrocal/imagenes/Entrenamiento_prueba.png?raw=true)

---

## Relación entre las Variables

**Matriz de Correlación y Mapa de Calor**

La matriz de correlación permite analizar la relación existente entre las diferentes variables del conjunto de datos.

Los valores cercanos a **1** indican una relación positiva fuerte, mientras que los valores cercanos a **0** representan una relación lineal débil.

En los resultados destaca la relación entre `Horas_Operacion` y `Consumo_Energia`, con una correlación aproximada de **0.84**. Esto indica una relación positiva fuerte: dentro de los datos analizados, cuando aumentan las horas de operación, también existe una tendencia a que aumente el consumo de energía.

También se observa una relación positiva entre `Carga` y `Consumo_Energia`, aunque es menor, aproximadamente **0.34**.

Por otro lado, `Temperatura` y `Humedad` presentan correlaciones bajas con el consumo, aproximadamente **0.098** y **0.063**, respectivamente. Esto indica que su relación lineal con el consumo es menor en comparación con las horas de operación.

![Matriz de Correlación](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/Juan_Berrocal/imagenes/Matriz_correlaci%C3%B3n_mapa_calor.png?raw=true)

---

## Distribución del Consumo de Energía

**Histograma del Consumo de Energía**

El histograma permite observar cómo se distribuyen los valores de `Consumo_Energia` dentro del conjunto de datos.

Se puede observar que la mayor cantidad de registros se concentra aproximadamente entre **20 y 32 unidades de consumo**, mientras que los valores extremos presentan una menor frecuencia.

La distribución presenta una forma aproximadamente similar a una campana, con mayor concentración de observaciones alrededor de los valores intermedios. Esto permite conocer el comportamiento general de la variable objetivo antes de utilizarla en el modelo de regresión.

Esta visualización también ayuda a identificar posibles valores extremos y a comprender el rango en el que normalmente se encuentra el consumo de energía.

![Histograma del Consumo de Energía](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/Juan_Berrocal/imagenes/Histograma_Consumo_Energia.png?raw=true)

---

## Comparación de los Valores Reales y Predichos

**Consumo de Energía Real vs. Predicho**

Después de entrenar el modelo de Regresión Lineal, se generaron predicciones utilizando los datos de prueba.

El gráfico permite comparar el **consumo de energía real** con el **consumo de energía predicho** por el modelo. Cada punto representa una observación del conjunto de prueba.

Se puede observar una tendencia claramente creciente: a medida que aumenta el consumo real, también aumentan los valores predichos. Además, la mayoría de los puntos se encuentran relativamente cerca de la tendencia principal, lo que indica que el modelo logra seguir de manera razonable el comportamiento de los datos.

Sin embargo, también existen diferencias entre los valores reales y predichos. Estas diferencias representan los **errores o residuos de las predicciones**.

En general, esta gráfica permite evaluar visualmente qué tan bien el modelo consigue aproximarse a los valores reales del consumo de energía.

![Valores Reales vs. Valores Predichos](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/Juan_Berrocal/imagenes/valor_real_predicho.png?raw=true)

---

# Resumen del laboratorio

Durante el laboratorio se desarrolló un proceso de análisis y modelado de datos aplicado al **consumo de energía**.

Primero se analizó la distribución de la variable `Consumo_Energia` mediante un histograma, identificando que la mayor cantidad de datos se encuentra en valores intermedios.

Posteriormente, mediante la matriz de correlación se analizaron las relaciones entre las variables. Uno de los resultados más importantes fue la correlación de aproximadamente **0.84 entre `Horas_Operacion` y `Consumo_Energia`**, mostrando que esta variable presenta una relación lineal importante con el consumo dentro del conjunto de datos.

Luego se implementó un modelo de **Regresión Lineal** utilizando las variables disponibles como características de entrada. Finalmente, se generaron predicciones y se compararon con los valores reales mediante un gráfico de dispersión.

En conjunto, el laboratorio permitió seguir las principales etapas de un problema de aprendizaje automático:

**Análisis de datos → Visualización → Correlación → Construcción del modelo → Predicción → Evaluación**
