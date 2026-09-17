# Informe Técnico: Predicción del Índice de Calidad del Aire mediante Regresión Lineal y Árbol de Decisión

**Asignatura:** Taller de Inteligencia Artificial  
**Dataset:** Monitoreo de Ozono (O₃) — Estación Connecticut Hill, Tompkins County, Nueva York, EE.UU. (2023)  
**Fecha:** 17 de septiembre de 2026

---

## 1. Introducción

La calidad del aire es un indicador importante para evaluar las condiciones ambientales. En este trabajo se analiza el **Índice de Calidad del Aire (AQI)** a partir de datos de concentración de ozono (O₃).

El dataset corresponde a registros diarios de la estación **Connecticut Hill**, ubicada en Tompkins County, Nueva York, durante el año 2023, con un total de **355 observaciones**.

El objetivo es analizar el comportamiento del AQI y construir modelos predictivos utilizando **Regresión Lineal Múltiple** y **Árbol de Decisión Regresor**.

---

## 2. Metodología

### 2.1 Dataset

Se seleccionaron las variables con mayor utilidad para el análisis:

| Variable | Descripción |
|---|---|
| `Daily Max 8-hour Ozone Concentration` | Concentración máxima de O₃ en 8 horas |
| `Daily Obs Count` | Número de observaciones válidas del día |
| `Percent Complete` | Porcentaje de completitud del monitoreo |
| `Mes` | Mes del año |
| `Dia_del_Anio` | Día del año |
| `Dia_Semana` | Día de la semana |
| `Trimestre` | Trimestre del año |
| `Daily AQI Value` | AQI diario, variable objetivo |

### 2.2 Ingeniería de características

La fecha fue convertida a formato `datetime` y se extrajeron variables temporales para representar posibles patrones estacionales:

```python
df['Date'] = pd.to_datetime(df['Date'], format='%m/%d/%Y')

df['Mes'] = df['Date'].dt.month
df['Dia_del_Anio'] = df['Date'].dt.day_of_year
df['Dia_Semana'] = df['Date'].dt.dayofweek
df['Trimestre'] = df['Date'].dt.quarter
```

### 2.3 Análisis exploratorio

Se utilizaron histogramas, densidad de probabilidad, promedios mensuales y una matriz de correlación para conocer la distribución del AQI y la relación entre las variables.

### 2.4 División de datos

Los datos fueron divididos en:

- **70 % para entrenamiento:** 248 observaciones.
- **30 % para prueba:** 107 observaciones.
- `random_state = 123` para garantizar reproducibilidad.

### 2.5 Modelos

Se implementaron dos modelos:

**Regresión Lineal Múltiple**

```python
lm = LinearRegression()
lm.fit(X_train, y_train)
predictions = lm.predict(X_test)
```

**Árbol de Decisión Regresor**

```python
tree_model = tree.DecisionTreeRegressor(
    max_depth=5,
    random_state=10
)

tree_model.fit(X_train, y_train)
tree_pred = tree_model.predict(X_test)
```

### 2.6 Métricas

Para evaluar los modelos se utilizaron:

- **MAE:** error absoluto medio.
- **MSE:** error cuadrático medio.
- **RMSE:** raíz del error cuadrático medio.
- **R²:** proporción de variabilidad explicada por el modelo.

También se realizaron pruebas estadísticas de **Pearson, Shapiro-Wilk y Durbin-Watson**, además del reporte OLS mediante `statsmodels`.

---

# 3. Resultados

## 3.1 Estadísticos descriptivos

El dataset contiene **355 observaciones** de AQI.

| Estadístico | Valor |
|---|---:|
| Media | 36.35 |
| Desviación estándar | 11.72 |
| Mínimo | 17 |
| Mediana | 35 |
| Percentil 75 | 41 |
| Máximo | 100 |

---

## 3.2 Distribución del AQI

![Distribución del AQI](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/01_distribucion_aqi.jpg)

El histograma muestra que la mayoría de los valores de AQI se concentra aproximadamente entre **25 y 45 unidades**.

La distribución presenta **asimetría positiva**, debido a la existencia de algunos valores elevados, especialmente superiores a 60. Esto indica que, aunque la mayoría de los días presenta valores moderados, existen episodios puntuales con AQI considerablemente mayor.

---

## 3.3 AQI promedio por mes

![AQI promedio por mes](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/02_aqi_promedio_mensual.jpg)

El comportamiento mensual muestra una variación estacional:

| Mes | AQI Promedio |
|---|---:|
| Enero | 28.19 |
| Febrero | 34.79 |
| Marzo | 39.90 |
| **Abril** | **49.03** |
| Mayo | 45.42 |
| Junio | 43.33 |
| Julio | 40.39 |
| Agosto | 31.70 |
| Septiembre | 32.60 |
| Octubre | 30.81 |
| Noviembre | 30.60 |
| Diciembre | 27.65 |

El mayor promedio se presenta en **abril con 49.03**, mientras que diciembre presenta el menor valor con **27.65**. Se observa una tendencia de incremento durante los primeros meses y una disminución posterior.

---

## 3.4 Matriz de correlación

![Matriz de correlación](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/03_matriz_correlacion.jpg)

La matriz permite identificar las relaciones lineales entre las variables.

Los principales resultados son:

| Variables | Correlación |
|---|---:|
| Ozono ↔ AQI | **0.95** |
| Mes ↔ AQI | -0.22 |
| Día del Año ↔ AQI | -0.23 |
| Día de la Semana ↔ AQI | -0.01 |
| Daily Obs Count ↔ Percent Complete | **1.00** |

La concentración de ozono presenta una correlación de **0.95 con el AQI**, mostrando una relación lineal positiva muy fuerte.

También se observa una correlación perfecta entre `Daily Obs Count` y `Percent Complete`, lo que representa un posible problema de **multicolinealidad** para el modelo de regresión.

---

## 3.5 AQI Real vs. Predicho

![AQI Real vs Predicho](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/04_aqi_real_vs_predicho.jpg)

El gráfico compara los valores reales del AQI con las predicciones de la regresión lineal.

La mayoría de los puntos se encuentra cerca de la línea diagonal, especialmente para valores entre **17 y 65 de AQI**, indicando que el modelo representa adecuadamente gran parte de las observaciones.

Sin embargo, los valores extremos presentan mayores diferencias. En particular, los casos con AQI superior a 80 son subestimados por el modelo.

---

## 3.6 Análisis de residuos

![Análisis de residuos](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/05_analisis_residuos.jpg)

Los residuos se concentran principalmente alrededor de **0**, y la mayoría se encuentra aproximadamente entre **-5 y +5 unidades de AQI**.

No obstante, aparecen algunos residuos positivos elevados, llegando aproximadamente hasta **+28 unidades**. Estos corresponden principalmente a observaciones donde el modelo subestima valores altos de AQI.

La presencia de estos valores extremos explica el resultado obtenido en la prueba de normalidad de los residuos.

---

## 3.7 Resultados del modelo OLS

![Resultados OLS](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Rodrigo_Asmat/Imagenes/06_resultados_ols.jpg)

El modelo OLS obtuvo:

| Indicador | Resultado |
|---|---:|
| R² | **0.912** |
| R² ajustado | **0.911** |
| F-statistic | **603.2** |
| Prob. F-statistic | **1.59 × 10⁻¹⁸⁰** |
| Observaciones | **355** |

La concentración de ozono es la variable con mayor relación con el AQI, presentando un **p-valor < 0.001**.

El reporte también muestra una advertencia de **multicolinealidad**, relacionada principalmente con la correlación entre `Daily Obs Count` y `Percent Complete`, además de las variables temporales.

---

## 3.8 Pruebas estadísticas

| Prueba | Resultado | Interpretación |
|---|---|---|
| Pearson | r = 0.9542 | Relación lineal muy fuerte entre O₃ y AQI |
| Shapiro-Wilk | p = 1.12 × 10⁻¹⁶ | Los residuos no presentan normalidad |
| Durbin-Watson | DW = 2.104 | No se evidencia autocorrelación significativa |
| F-statistic | p = 1.59 × 10⁻¹⁸⁰ | El modelo es significativo globalmente |

---

## 3.9 Comparación de modelos

| Modelo | MAE | RMSE | R² |
|---|---:|---:|---:|
| Regresión Lineal | 1.809 | 3.550 | 0.913 |
| Árbol de Decisión | 0.685 | 1.289 | 0.989 |

Los resultados muestran diferencias en el desempeño de ambos modelos. El Árbol de Decisión obtiene menores errores y un mayor R² en este conjunto de prueba, mientras que la Regresión Lineal proporciona una interpretación más directa de la relación entre las variables.

---

# 4. Discusión

Los resultados muestran que la **concentración de ozono es la variable más relacionada con el AQI**, con una correlación de 0.95. Esto es consistente con la relación existente entre la concentración de O₃ y el cálculo del índice.

El análisis mensual evidencia un comportamiento estacional, alcanzando el mayor AQI promedio en abril.

La regresión lineal presenta un buen ajuste general, pero tiene dificultades para representar algunos valores extremos. Esto se refleja en el gráfico de valores reales frente a predichos y en el análisis de residuos.

Además, se identificó **multicolinealidad** entre algunas variables, especialmente `Daily Obs Count` y `Percent Complete`. Para mejorar el modelo podría considerarse eliminar variables redundantes o reducir las variables temporales altamente relacionadas.

Finalmente, en este conjunto de datos, el Árbol de Decisión presenta menores valores de MAE y RMSE y un mayor R² que la Regresión Lineal, lo que muestra su capacidad para representar relaciones más complejas.

---

# 5. Conclusiones

- El AQI presenta una distribución principalmente concentrada entre **25 y 45 unidades**, con algunos valores extremos.
- El mayor AQI promedio se registró en **abril (49.03)**.
- La concentración de ozono presenta una correlación muy fuerte con el AQI (**r = 0.95**).
- La Regresión Lineal obtuvo un **R² de 0.913** en el conjunto de prueba.
- El Árbol de Decisión obtuvo un **R² de 0.989**, con menores errores de predicción.
- Los residuos presentan valores extremos y no cumplen completamente el supuesto de normalidad.
- Se detectó multicolinealidad entre algunas variables predictoras.

---

# 6. Referencias

[1] U.S. Environmental Protection Agency, *Air Quality System (AQS) Data Mart*, 2023.

[2] F. Pedregosa et al., “Scikit-learn: Machine Learning in Python,” *Journal of Machine Learning Research*, vol. 12, pp. 2825–2830, 2011.

[3] W. McKinney, “Data Structures for Statistical Computing in Python,” *Proceedings of the 9th Python in Science Conference*, 2010.

[4] J. D. Hunter, “Matplotlib: A 2D Graphics Environment,” *Computing in Science & Engineering*, vol. 9, no. 3, pp. 90–95, 2007.

[5] M. Waskom, “seaborn: Statistical Data Visualization,” *Journal of Open Source Software*, vol. 6, no. 60, p. 3021, 2021.

[6] U.S. Environmental Protection Agency, *Technical Assistance Document for the Reporting of Daily Air Quality — the Air Quality Index (AQI)*, EPA-454/B-18-007, 2018.

[7] T. Hastie, R. Tibshirani and J. Friedman, *The Elements of Statistical Learning*, 2nd ed., Springer, 2009.

[8] S. S. Shapiro and M. B. Wilk, “An analysis of variance test for normality,” *Biometrika*, vol. 52, no. 3–4, pp. 591–611, 1965.

[9] J. Durbin and G. S. Watson, “Testing for serial correlation in least squares regression,” *Biometrika*, vol. 37, no. 3–4, pp. 409–428, 1950.

[10] S. Seabold and J. Perktold, “Statsmodels: Econometric and Statistical Modeling with Python,” *Proceedings of the 9th Python in Science Conference*, 2010.
