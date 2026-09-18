# Análisis de NO₂ y predicción del AQI mediante regresión lineal

**Curso:** Taller de Inteligencia Artificial  
**Caso de estudio:** Phoenix-Mesa-Scottsdale, Arizona  
**Periodo analizado:** 2022  
**Fuente de datos:** United States Environmental Protection Agency (EPA)

---

## 1. Introducción

La contaminación del aire constituye un problema relevante para el monitoreo ambiental y la salud pública. Entre los contaminantes atmosféricos se encuentra el **dióxido de nitrógeno (NO₂)**, asociado principalmente a procesos de combustión.

En este trabajo se analizan registros diarios de calidad del aire correspondientes al año **2022** en el área de **Phoenix-Mesa-Scottsdale, Arizona**. El objetivo es analizar la relación entre la concentración máxima diaria de NO₂ y el **Air Quality Index (AQI)**, y construir un modelo de **regresión lineal** para estimar el valor diario del AQI.

---

## 2. Metodología

### 2.1. Fuente y preparación de los datos

El conjunto de datos contiene **2 157 registros diarios**. Durante la preparación se convirtió la variable `Date` a formato de fecha y se generó la variable `Month`.

Las variables utilizadas fueron:

| Variable | Tipo | Descripción |
|---|---|---|
| `Daily Max 1-hour NO2 Concentration` | Predictora | Concentración máxima diaria de NO₂ registrada durante una hora |
| `Site Latitude` | Predictora | Latitud del sitio de monitoreo |
| `Site Longitude` | Predictora | Longitud del sitio de monitoreo |
| `Month` | Predictora | Mes correspondiente a la observación |
| `Daily AQI Value` | Objetivo | Valor diario del índice de calidad del aire |

### 2.2. Análisis exploratorio

Se utilizaron estadísticas descriptivas, gráficos de dispersión, histogramas, curvas de densidad y una matriz de correlación para analizar el comportamiento de las variables antes del modelado.

### 2.3. División de los datos

El conjunto de datos se dividió en:

- **70 %** para entrenamiento.
- **30 %** para prueba.

Se utilizó `random_state=123` para mantener la reproducibilidad del experimento.

### 2.4. Modelo de regresión

Se empleó un modelo de **regresión lineal** utilizando `LinearRegression` de scikit-learn.

La evaluación se realizó mediante:

- comparación entre valores reales y predichos;
- análisis de residuos;
- evaluación gráfica de la homocedasticidad;
- **Mean Squared Error (MSE)**;
- análisis estadístico mediante **Ordinary Least Squares (OLS)**.

---

## 3. Resultados

### 3.1. Relación general entre las variables

<p align="center">
  <img src="./imagenes/01_relacion_variables.png" width="900">
</p>

**Figura 1. Relación entre las variables seleccionadas.**

**Interpretación:**  
El gráfico permite observar las relaciones entre las variables utilizadas en el análisis. La relación más clara aparece entre **Daily Max 1-hour NO2 Concentration** y **Daily AQI Value**, cuyos puntos siguen prácticamente una línea recta ascendente. Esto indica una relación positiva muy fuerte entre ambas variables.

En cambio, las variables **Site Latitude** y **Site Longitude** aparecen agrupadas en valores específicos debido a que corresponden a ubicaciones fijas de estaciones de monitoreo. La variable **Month** no muestra una relación lineal fuerte con el AQI.

---

### 3.2. Distribución del AQI diario

<p align="center">
  <img src="./imagenes/02_distribucion_aqi.png" width="700">
</p>

**Figura 2. Distribución de `Daily AQI Value`.**

**Interpretación:**  
La mayor cantidad de observaciones del AQI se concentra aproximadamente entre **15 y 45**, con una frecuencia especialmente alta alrededor de los valores de **30 a 40**. También se observan algunos valores superiores a 50 y pocos registros que llegan aproximadamente hasta 80.

La distribución presenta una **cola hacia la derecha**, lo que indica que los valores altos del AQI son menos frecuentes que los valores medios.

---

### 3.3. Densidad del AQI diario

<p align="center">
  <img src="./imagenes/03_densidad_aqi.png" width="700">
</p>

**Figura 3. Densidad de `Daily AQI Value`.**

**Interpretación:**  
La curva de densidad confirma que la mayor concentración de valores del AQI se encuentra aproximadamente entre **15 y 45**. La densidad disminuye progresivamente después de los valores cercanos a 40 y se extiende hacia valores más elevados.

Este comportamiento confirma que la distribución no es completamente simétrica y presenta una ligera asimetría hacia valores altos.

---

### 3.4. Mapa de calor de correlaciones

<p align="center">
  <img src="./imagenes/04_mapa_calor_correlaciones.png" width="800">
</p>

**Figura 4. Matriz de correlación de las variables utilizadas.**

**Interpretación:**  
La concentración máxima diaria de NO₂ presenta una correlación de **0.9995** con `Daily AQI Value`, lo que representa una relación lineal positiva prácticamente perfecta.

Las demás variables presentan relaciones menores con el AQI:

| Variable | Correlación con AQI |
|---|---:|
| Daily Max 1-hour NO2 Concentration | 0.9995 |
| Site Longitude | 0.3905 |
| Site Latitude | 0.2838 |
| Month | -0.1375 |

`Site Longitude` y `Site Latitude` muestran relaciones positivas moderadas o débiles, mientras que `Month` presenta una relación negativa débil. Además, la correlación entre latitud y longitud es de aproximadamente **0.6487**, debido a la distribución geográfica de las estaciones de monitoreo.

---

### 3.5. Relación entre las variables predictoras y el AQI

<p align="center">
  <img src="./imagenes/05_variables_vs_aqi.png" width="900">
</p>

**Figura 5. Relación individual de cada variable predictora con `Daily AQI Value`.**

**Interpretación:**  
El primer gráfico muestra una relación lineal ascendente muy marcada entre la concentración máxima diaria de NO₂ y el AQI. A medida que aumenta la concentración de NO₂, también aumenta el valor del AQI.

En los gráficos de **Site Latitude** y **Site Longitude** se observan grupos verticales de puntos. Esto ocurre porque los registros pertenecen a un número limitado de estaciones con coordenadas fijas. Estas variables presentan una relación mucho menos directa con el AQI.

En el caso de **Month**, los valores del AQI se encuentran distribuidos durante todo el año sin mostrar una tendencia lineal fuerte. Esto coincide con la baja correlación obtenida para esta variable.

---

### 3.6. Comparación entre valores reales y predichos

<p align="center">
  <img src="./imagenes/06_real_vs_predicho.png" width="700">
</p>

**Figura 6. Valores reales frente a valores predichos por el modelo.**

**Interpretación:**  
Los puntos se encuentran muy próximos a una línea diagonal, lo que indica que las predicciones realizadas por el modelo son muy cercanas a los valores reales del AQI.

La coincidencia se mantiene tanto para los valores bajos como para los valores medios y altos. Esto muestra que el modelo presenta un **ajuste muy elevado** sobre el conjunto de prueba.

El modelo generó **648 predicciones**, correspondientes al 30 % de los datos utilizados como conjunto de prueba.

---

### 3.7. Distribución de los residuos

<p align="center">
  <img src="./imagenes/07_distribucion_residuos.png" width="700">
</p>

**Figura 7. Histograma de residuos del modelo de regresión.**

**Interpretación:**  
La mayoría de los residuos se encuentra concentrada alrededor de **0**, indicando que en gran parte de las observaciones las diferencias entre los valores reales y los predichos son pequeñas.

Sin embargo, la distribución no es perfectamente simétrica. Se observa una cola hacia valores positivos y un residuo atípico superior a 3. Esto indica que la normalidad de los residuos no se cumple de manera perfecta.

Este resultado también es consistente con el análisis OLS, donde las pruebas **Omnibus** y **Jarque-Bera** presentan valores de probabilidad cercanos a cero.

---

### 3.8. Residuos frente a valores predichos

<p align="center">
  <img src="./imagenes/08_residuos_vs_predichos.png" width="700">
</p>

**Figura 8. Residuos frente a los valores predichos.**

**Interpretación:**  
La mayoría de los residuos se encuentra alrededor de la línea horizontal de cero. Sin embargo, los puntos no forman una nube completamente aleatoria y uniforme, sino que aparecen agrupados en diferentes bandas.

También se observa que la dispersión de los residuos cambia ligeramente según el valor predicho y existe un valor atípico cercano a un AQI predicho de 80.

Por lo tanto, la condición de **homocedasticidad no se observa de manera completamente perfecta**. Aun así, la magnitud de la mayoría de los errores es reducida.

---

### 3.9. Error cuadrático medio

El modelo obtuvo:

**MSE = 0.123182**

El valor reducido del MSE indica que, en general, las predicciones se encuentran muy próximas a los valores reales. Este resultado coincide con la fuerte alineación observada en la Figura 6.

---

### 3.10. Resumen estadístico del modelo OLS

<p align="center">
  <img src="./imagenes/09_resumen_ols.png" width="900">
</p>

**Figura 9. Resumen estadístico del modelo mediante mínimos cuadrados ordinarios (OLS).**

**Interpretación:**  
El modelo obtuvo un **R² de 0.999** y un **R² ajustado de 0.999**, por lo que explica aproximadamente el **99.9 % de la variabilidad** de `Daily AQI Value`.

La prueba F presenta un valor de **5.750 × 10⁵** con una probabilidad cercana a cero, lo que indica que el modelo, considerado en conjunto, presenta significancia estadística.

Los resultados por variable fueron:

| Variable | Coeficiente | p-value | Interpretación |
|---|---:|---:|---|
| Daily Max 1-hour NO2 Concentration | 0.9537 | < 0.001 | Relación positiva y estadísticamente significativa |
| Site Latitude | -2.7620 | < 0.001 | Relación negativa y estadísticamente significativa |
| Site Longitude | 0.0883 | 0.075 | No significativa al nivel de 0.05 |
| Month | 0.0054 | 0.014 | Relación positiva pequeña y estadísticamente significativa |

La concentración de NO₂ es la variable que presenta la relación más clara con el AQI. `Site Longitude` no presenta evidencia suficiente para considerarse significativa utilizando un nivel de significancia de 0.05.

Por otro lado, las pruebas de normalidad de residuos muestran `Prob(Omnibus) = 0.000` y `Prob(JB) = 0.00`, por lo que los residuos no presentan una distribución perfectamente normal. El **Condition Number = 1.86 × 10⁵** también es elevado, por lo que puede existir un problema relacionado con las escalas de las variables o con relaciones entre variables predictoras.

---

## 4. Discusión

Los resultados muestran que el modelo de regresión lineal presenta un ajuste muy elevado. La principal explicación es la fuerte relación entre la concentración máxima diaria de NO₂ y el valor del AQI.

La correlación entre estas dos variables fue de **0.9995**, mientras que el análisis OLS obtuvo un **R² de 0.999**. Asimismo, el modelo presentó un **MSE de 0.123182**, indicando errores de predicción reducidos.

Sin embargo, el análisis de residuos muestra que los supuestos estadísticos del modelo no se cumplen perfectamente. El histograma presenta cierta asimetría y valores atípicos, mientras que el gráfico de residuos frente a predicciones muestra agrupamientos y cambios en la dispersión.

Además, las variables geográficas y temporales presentan una contribución mucho menor que la concentración de NO₂. En particular, `Site Longitude` no resulta estadísticamente significativa al nivel de 0.05.

Por lo tanto, aunque el modelo posee una capacidad de ajuste muy alta para este conjunto de datos, los resultados deben interpretarse considerando la estructura específica de los datos y las características de las variables utilizadas.

---

## 5. Referencias

[1] U.S. Environmental Protection Agency, “Basic Information about NO₂,” *EPA*. [Online]. Available: https://www.epa.gov/no2-pollution/basic-information-about-no2. [Accessed: Sep. 17, 2026].

[2] U.S. Environmental Protection Agency, “Air Quality System (AQS),” *EPA*. [Online]. Available: https://www.epa.gov/aqs. [Accessed: Sep. 17, 2026].

[3] Scikit-learn Developers, “LinearRegression,” *Scikit-learn Documentation*. [Online]. Available: https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.LinearRegression.html. [Accessed: Sep. 17, 2026].

[4] Statsmodels Developers, “Linear Regression,” *Statsmodels Documentation*. [Online]. Available: https://www.statsmodels.org/stable/regression.html. [Accessed: Sep. 17, 2026].

---

## 6. Estructura del repositorio

```text
Regresion_NO2_Phoenix_2022/
│
├── README.md
├── Regresion_NO2_Phoenix_2022.ipynb
└── imagenes/
    ├── 01_relacion_variables.png
    ├── 02_distribucion_aqi.png
    ├── 03_densidad_aqi.png
    ├── 04_mapa_calor_correlaciones.png
    ├── 05_variables_vs_aqi.png
    ├── 06_real_vs_predicho.png
    ├── 07_distribucion_residuos.png
    ├── 08_residuos_vs_predichos.png
    └── 09_resumen_ols.png
```
