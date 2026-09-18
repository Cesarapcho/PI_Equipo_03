# Informe Técnico: Regresión de la concentración de CO

**Asignatura:** Taller de Inteligencia Artificial 

**Dataset:** Monitoreo de Monóxido de Carbono (CO) — Estación PARR (2023) 

**Fecha:** 17 de septiembre de 2026 

---

## 1. Introducción

La calidad del aire es un aspecto importante para evaluar las condiciones ambientales. En este trabajo se analiza la concentración diaria de monóxido de carbono (`CO_ppm`).

El dataset corresponde a registros diarios de mediciones de calidad del aire en la estación **PARR**, durante el año 2023, con un total de **364 observaciones**.

El objetivo es analizar el comportamiento de la concentración de CO y estimar sus valores construyendo modelos predictivos utilizando **Regresión Lineal**, **Árbol de Decisión** y **Random Forest**. El desempeño se evaluó mediante MAE, MSE, RMSE y $R^2$.

---


# 2. Metodología

## 2.1. Datos utilizados

El conjunto de datos contiene **364 registros y 21 columnas** correspondientes a mediciones de calidad del aire.

La variable objetivo del estudio es:

- `CO_ppm`: concentración de monóxido de carbono en partes por millón.

Para el modelado se utilizaron las siguientes variables predictoras:

- `Mes`
- `Dia_Semana`
- `Fin_Semana`
- `Sen_Anual`
- `Cos_Anual`
- `Num_Observaciones`

La variable `AQI` no se utilizó como predictor debido a su relación directa con la información de calidad del aire y para evitar introducir información relacionada directamente con la variable objetivo.

## 2.2. Modelos utilizados

### Regresión Lineal

Se utilizó como modelo base para analizar la relación lineal entre las variables predictoras y la concentración de CO.

### Árbol de Decisión

Se utilizó para representar relaciones no lineales mediante divisiones sucesivas de los datos y realizar predicciones de la concentración de CO.

### Random Forest

Se utilizó un conjunto de árboles de decisión para realizar las predicciones y capturar relaciones más complejas presentes en los datos.

## 2.3. Métricas de evaluación

Para evaluar los modelos se utilizaron las siguientes métricas:

- **MAE:** representa el error absoluto promedio entre los valores reales y predichos.
- **MSE:** calcula el promedio de los errores al cuadrado.
- **RMSE:** representa la raíz cuadrada del MSE.
- **$R^2$:** indica la proporción de variabilidad de la variable objetivo explicada por el modelo.

---

# 3. Resultados

## 3.1. Histograma de la concentración de CO

![Histograma de la concentración de CO](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/01_histograma_co.png)

### Interpretación

El histograma muestra cómo se distribuyen las concentraciones diarias de CO. La mayor cantidad de observaciones se encuentra aproximadamente entre **0.3 y 0.8 ppm**. También se observan algunos valores superiores a 1.0 ppm, aunque aparecen con menor frecuencia.

Esto indica que la mayoría de los registros de concentración de CO se encuentran dentro de un rango intermedio, mientras que los valores más altos son menos frecuentes.

---

## 3.2. Densidad de la concentración de CO

![Densidad de la concentración de CO](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/02_densidad_co.png)

### Interpretación

La gráfica de densidad permite observar las zonas donde existe una mayor concentración de valores de CO.

Se observa una mayor concentración alrededor de **0.5 y 0.7 ppm**, mientras que los valores superiores a 1.0 ppm presentan una densidad mucho menor. También se observa una segunda concentración alrededor de 0 ppm.

La distribución no presenta una forma completamente simétrica, lo que indica que los valores de CO no se distribuyen de manera uniforme.

---

## 3.3. Matriz de correlación

![Matriz de correlación](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/03_matriz_correlacion.png)

### Interpretación

La matriz de correlación permite analizar la relación lineal entre las variables utilizadas en el estudio.

Con respecto a la variable objetivo `CO_ppm`, las relaciones más destacadas son:

- `Mes` y `CO_ppm`: **-0.35**
- `Cos_Anual` y `CO_ppm`: **-0.30**
- `Sen_Anual` y `CO_ppm`: **0.057**
- `Dia_Semana` y `CO_ppm`: **-0.025**
- `Num_Observaciones` y `CO_ppm`: **-0.017**

Los valores de `Mes` y `Cos_Anual` muestran una relación negativa con `CO_ppm`, mientras que las demás variables presentan relaciones lineales muy bajas con la concentración de CO.

También se observa una correlación de **0.79 entre `Dia_Semana` y `Fin_Semana`**, debido a que ambas variables están relacionadas con la información temporal de los días.

De manera similar, `Mes` y `Sen_Anual` presentan una correlación de **-0.78**, relacionada con la forma en que fueron construidas las variables temporales.

> **Nota:** una correlación muestra una relación entre variables, pero no significa necesariamente que una variable sea la causa de otra.

---

## 3.4. Valores reales vs. predichos del Árbol de Decisión

![Árbol de Decisión: valores reales vs. predichos](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/04_real_vs_predicho.png)

### Interpretación

La gráfica compara los valores reales de `CO_ppm` con los valores predichos por el **Árbol de Decisión**.

Se observa que varias predicciones se encuentran relativamente cerca de los valores reales, aunque también existen diferencias en determinados puntos. Esto indica que el modelo consigue representar parte del comportamiento de la concentración de CO, pero todavía presenta errores en algunas predicciones.

El resultado obtenido por el modelo fue un **$R^2$ de aproximadamente 0.68**, lo que indica que el modelo explica una parte importante de la variabilidad de los datos.

---

## 3.5. Análisis de residuos

![Histograma de residuos](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/05_residuos.png)

### Interpretación

Los residuos representan la diferencia entre los valores reales y los valores predichos por el modelo.

En la gráfica se observa que una parte importante de los residuos se concentra alrededor de **0**, lo cual indica que muchos errores de predicción son relativamente pequeños.

Sin embargo, también se observa una distribución hacia valores positivos y algunos residuos alejados del centro. Por ello, los residuos no presentan una distribución perfectamente simétrica o normal.

Esta gráfica permite identificar que todavía existen errores de predicción y que el modelo no consigue explicar completamente todos los patrones presentes en los datos.

---

# 3.6. Comparación de los modelos

| Modelo | MAE | MSE | RMSE | $R^2$ |
|---|---:|---:|---:|---:|
| Regresión Lineal | 0.1853 | 0.0561 | 0.2369 | 0.2956 |
| Árbol de Decisión | 0.1075 | 0.0252 | 0.1588 | 0.6836 |
| Random Forest | 0.0727 | 0.0127 | 0.1127 | 0.8406 |

Los resultados muestran diferencias en el desempeño de los tres modelos. La Regresión Lineal obtuvo un $R^2$ de **0.2956**, mientras que el Árbol de Decisión alcanzó **0.6836**.

El Random Forest obtuvo un $R^2$ de **0.8406**, junto con un RMSE de **0.1127**.

En los datos analizados, los modelos basados en árboles presentaron menores errores y mayores valores de $R^2$ que la Regresión Lineal.

---

# 4. Discusión

A partir de los resultados obtenidos, se observa que la concentración de CO presenta principalmente valores entre **0.3 y 0.8 ppm**, aunque también existen algunos registros con valores superiores.

La matriz de correlación permitió identificar que `Mes` y `Cos_Anual` presentan las relaciones lineales más destacadas con `CO_ppm`. Sin embargo, las correlaciones no explican por sí solas todo el comportamiento de la variable objetivo.

Al comparar los modelos, la Regresión Lineal presentó un menor $R^2$ que los modelos basados en árboles. El Árbol de Decisión y Random Forest obtuvieron mejores resultados en las métricas utilizadas.

El análisis de residuos muestra que una parte importante de los errores se concentra alrededor de cero, aunque también existen algunos valores alejados y cierta asimetría.

En conjunto, los resultados muestran que los modelos utilizados permiten realizar una aproximación de la concentración de CO a partir de las variables seleccionadas.

---

# 5. Referencias

[1] F. Pedregosa *et al.*, “Scikit-learn: Machine Learning in Python,” *Journal of Machine Learning Research*, vol. 12, pp. 2825–2830, 2011.

[2] Scikit-learn, “DecisionTreeRegressor,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeRegressor.html

[3] Scikit-learn, “RandomForestRegressor,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/1.8/modules/generated/sklearn.ensemble.RandomForestRegressor.html

[4] Scikit-learn, “Metrics and scoring: quantifying the quality of predictions,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/stable/modules/model_evaluation.html
