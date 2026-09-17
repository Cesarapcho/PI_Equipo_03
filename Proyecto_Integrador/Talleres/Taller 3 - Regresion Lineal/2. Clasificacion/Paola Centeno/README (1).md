# Análisis de NO₂ y predicción del AQI mediante regresión lineal

**Curso:** Taller de Inteligencia Artificial  
**Caso de estudio:** Phoenix-Mesa-Scottsdale, Arizona  
**Periodo analizado:** 2022  
**Fuente de datos:** United States Environmental Protection Agency (EPA)

---

## 1. Introducción

La calidad del aire constituye un aspecto importante del monitoreo ambiental debido a su relación con la salud de la población. Entre los contaminantes atmosféricos se encuentra el **dióxido de nitrógeno (NO₂)**, generado principalmente por procesos de combustión.

En este trabajo se analizan registros diarios de calidad del aire correspondientes al año **2022** en el área de **Phoenix-Mesa-Scottsdale, Arizona**. Los datos fueron obtenidos del sistema **Air Quality System (AQS)** de la United States Environmental Protection Agency (EPA).

El objetivo del trabajo es analizar la relación entre la concentración máxima diaria de NO₂ y el **Air Quality Index (AQI)**, y construir un modelo de **regresión lineal** para estimar el valor diario del AQI a partir de las variables seleccionadas.

---

## 2. Metodología

### 2.1. Fuente y preparación de los datos

El conjunto de datos contiene **2 157 registros diarios** correspondientes al año 2022. Durante la preparación se convirtió la variable `Date` a formato de fecha y se generó la variable `Month`.

Las variables predictoras utilizadas fueron:

| Variable | Descripción |
|---|---|
| `Daily Max 1-hour NO2 Concentration` | Concentración máxima diaria de NO₂ registrada durante una hora |
| `Site Latitude` | Latitud del sitio de monitoreo |
| `Site Longitude` | Longitud del sitio de monitoreo |
| `Month` | Mes correspondiente a la observación |

La variable objetivo fue **`Daily AQI Value`**.

### 2.2. Análisis exploratorio

Se utilizaron estadísticas descriptivas, gráficos de dispersión, histogramas, curvas de densidad y una matriz de correlación para examinar el comportamiento de las variables.

### Relación entre las variables

<p align="center">
  <img src="./imagenes/01_relacion_variables.png" width="850">
</p>

**Figura 1.** Relación entre las variables seleccionadas.

### Distribución del AQI diario

<p align="center">
  <img src="./imagenes/02_distribucion_aqi.png" width="700">
</p>

**Figura 2.** Distribución de `Daily AQI Value`.

La mayor parte de los valores del AQI se concentra aproximadamente entre **15 y 45**, aunque se observan algunos valores superiores con menor frecuencia.

### Densidad del AQI diario

<p align="center">
  <img src="./imagenes/03_densidad_aqi.png" width="700">
</p>

**Figura 3.** Densidad de `Daily AQI Value`.

### Mapa de calor de correlaciones

<p align="center">
  <img src="./imagenes/04_mapa_calor_correlaciones.png" width="800">
</p>

**Figura 4.** Mapa de calor de la matriz de correlación.

La variable **Daily Max 1-hour NO2 Concentration** presentó la mayor correlación con el AQI diario, con un valor aproximado de **0.9995**.

### 2.3. División de los datos

El conjunto de datos se dividió en:

- **70 %** para entrenamiento.
- **30 %** para prueba.

Se utilizó `random_state=123` para mantener la reproducibilidad del experimento.

### 2.4. Modelo utilizado

Se empleó un modelo de **regresión lineal** utilizando `LinearRegression` de scikit-learn.

Las variables predictoras fueron:

- Daily Max 1-hour NO2 Concentration
- Site Latitude
- Site Longitude
- Month

La variable objetivo fue:

- Daily AQI Value

### 2.5. Evaluación

El modelo fue evaluado mediante:

- comparación entre valores reales y predichos;
- análisis de residuos;
- gráfico de residuos frente a predicciones;
- **Mean Squared Error (MSE)**;
- análisis estadístico mediante **Ordinary Least Squares (OLS)**.

---

## 3. Resultados

### 3.1. Coeficientes del modelo

Los coeficientes obtenidos fueron:

| Variable | Coeficiente |
|---|---:|
| Daily Max 1-hour NO2 Concentration | 0.953660 |
| Site Latitude | -2.680513 |
| Site Longitude | 0.076662 |
| Month | 0.004319 |

La concentración máxima diaria de NO₂ presentó una relación positiva marcada con el AQI.

### Relación de las variables predictoras con el AQI

<p align="center">
  <img src="./imagenes/05_variables_vs_aqi.png" width="900">
</p>

**Figura 5.** Relación entre cada variable predictora y `Daily AQI Value`.

### 3.2. Comparación entre valores reales y predichos

<p align="center">
  <img src="./imagenes/06_real_vs_predicho.png" width="700">
</p>

**Figura 6.** Valores reales y predichos del AQI.

Se observa una fuerte alineación entre los valores reales y los valores predichos, lo que indica un buen ajuste del modelo sobre el conjunto de prueba.

### 3.3. Análisis de residuos

<p align="center">
  <img src="./imagenes/07_distribucion_residuos.png" width="700">
</p>

**Figura 7.** Distribución de los residuos.

Los residuos se concentran principalmente alrededor de cero.

### Homocedasticidad de los residuos

<p align="center">
  <img src="./imagenes/08_residuos_vs_predichos.png" width="700">
</p>

**Figura 8.** Residuos frente a valores predichos.

Este gráfico permite evaluar si la dispersión de los errores se mantiene aproximadamente constante en el rango de predicciones.

### 3.4. Error cuadrático medio

El modelo obtuvo:

**MSE = 0.123182**

Este valor indica una diferencia cuadrática promedio reducida entre los valores reales y los valores estimados.

### 3.5. Análisis mediante OLS

El modelo ajustado mediante mínimos cuadrados ordinarios obtuvo:

**R² = 0.999**

Por lo tanto, el modelo explica aproximadamente el **99.9 % de la variabilidad** de `Daily AQI Value` dentro del conjunto de datos analizado.

Los principales resultados fueron:

| Variable | Coeficiente OLS | p-value |
|---|---:|---:|
| Daily Max 1-hour NO2 Concentration | 0.9537 | < 0.001 |
| Site Latitude | -2.7620 | < 0.001 |
| Site Longitude | 0.0883 | 0.075 |
| Month | 0.0054 | 0.014 |

---

## 4. Discusión

Los resultados muestran que la concentración máxima diaria de NO₂ presenta una relación muy fuerte con el valor diario del AQI. Esto se refleja tanto en la matriz de correlación como en el desempeño obtenido por el modelo de regresión.

El valor de **R² = 0.999** y el **MSE = 0.123182** indican que el modelo presenta un ajuste elevado para los datos analizados. Sin embargo, los resultados deben interpretarse considerando que el AQI se encuentra directamente relacionado con las concentraciones de contaminantes atmosféricos.

Las variables de ubicación geográfica y el mes presentan una contribución menor en comparación con la concentración de NO₂. Además, en el análisis OLS, `Site Longitude` presentó un valor `p = 0.075`, superior al nivel de significancia de 0.05.

En conjunto, el modelo permite representar adecuadamente la relación observada entre las variables seleccionadas y el AQI para los registros analizados de Phoenix-Mesa-Scottsdale durante 2022.

---

## 5. Referencias

[1] U.S. Environmental Protection Agency, “Air Quality System (AQS),” *EPA*. [Online]. Available: https://www.epa.gov/aqs. [Accessed: Sep. 17, 2026].

[2] U.S. Environmental Protection Agency, “Basic Information about NO₂,” *EPA*. [Online]. Available: https://www.epa.gov/no2-pollution/basic-information-about-no2. [Accessed: Sep. 17, 2026].

[3] Scikit-learn Developers, “LinearRegression,” *Scikit-learn Documentation*. [Online]. Available: https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.LinearRegression.html. [Accessed: Sep. 17, 2026].

[4] Statsmodels Developers, “Linear Regression,” *Statsmodels Documentation*. [Online]. Available: https://www.statsmodels.org/stable/regression.html. [Accessed: Sep. 17, 2026].

---

## Estructura del repositorio

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
    └── 08_residuos_vs_predichos.png
```
