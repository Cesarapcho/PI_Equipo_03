# Informe Técnico: Regresión de la concentración de CO

**Curso:** Taller de Inteligencia Artificial  
**Caso de estudio:** Estación PARR  
**Periodo analizado:** 2023  
**Componente:** Monóxido de carbono (CO)  
**Fuente de datos:** United States Environmental Protection Agency (EPA)

---

# 1. Introducción

La calidad del aire es un aspecto importante para conocer las condiciones ambientales de un determinado lugar. Entre los contaminantes que pueden ser monitoreados se encuentra el monóxido de carbono (CO), cuya concentración puede variar de acuerdo con diferentes factores temporales y ambientales.

En este trabajo se analiza la concentración diaria de monóxido de carbono, representada por la variable `CO_ppm`, utilizando un conjunto de datos correspondiente a registros de calidad del aire de la estación **PARR durante el año 2023**. El conjunto de datos utilizado contiene **364 observaciones y 21 variables**.

El objetivo del trabajo es analizar el comportamiento de la concentración de CO y construir modelos capaces de estimar sus valores a partir de variables predictoras relacionadas principalmente con el tiempo. Para ello, se utilizaron tres modelos de regresión: **Regresión Lineal, Árbol de Decisión y Random Forest**.

Finalmente, el desempeño de los modelos fue evaluado mediante las métricas **MAE, MSE, RMSE y $R^2$**, con el propósito de comparar sus resultados y analizar qué tan bien representan los datos disponibles.

---

# 2. Metodología

## 2.1. Datos utilizados

El conjunto de datos utilizado contiene **364 registros y 21 columnas**, correspondientes a mediciones de calidad del aire realizadas en la estación PARR durante el año 2023.

La variable objetivo seleccionada para el estudio es:

- `CO_ppm`: concentración de monóxido de carbono expresada en partes por millón.

Para construir los modelos se utilizaron las siguientes variables predictoras:

- `Mes`
- `Dia_Semana`
- `Fin_Semana`
- `Sen_Anual`
- `Cos_Anual`
- `Num_Observaciones`

Las variables `Sen_Anual` y `Cos_Anual` permiten representar la variación cíclica asociada al transcurso del año.

Por otro lado, `Num_Observaciones` corresponde al número correlativo de cada registro dentro del periodo analizado, por lo que permite conservar información relacionada con el orden temporal de las observaciones.

La variable `AQI` no se utilizó como predictor debido a que es un indicador construido a partir de información relacionada con la calidad del aire. Incluirla podría introducir información directamente relacionada con la variable objetivo y generar una estimación menos independiente de la concentración de CO.

---

## 2.2. Modelos utilizados

### Regresión Lineal

La **Regresión Lineal** se utilizó como modelo base para analizar si existe una relación aproximadamente lineal entre las variables predictoras seleccionadas y la concentración de CO.

Este modelo permite establecer una referencia para posteriormente comparar su desempeño con modelos capaces de representar relaciones más complejas.

### Árbol de Decisión

El **Árbol de Decisión** permite realizar predicciones mediante divisiones sucesivas de los datos según las características de entrada.

A diferencia de la regresión lineal, este modelo puede representar relaciones no lineales entre las variables predictoras y la concentración de CO.

### Random Forest

El **Random Forest** utiliza múltiples árboles de decisión para realizar las predicciones.

La combinación de varios árboles permite representar relaciones más complejas y reducir la dependencia de un único árbol, proporcionando un modelo más flexible para los datos analizados.

---

## 2.3. Métricas de evaluación

Para evaluar el desempeño de los modelos se utilizaron cuatro métricas:

- **MAE (Mean Absolute Error):** representa el error absoluto promedio entre los valores reales y los valores predichos.
- **MSE (Mean Squared Error):** calcula el promedio de los errores elevados al cuadrado, dando mayor peso a errores grandes.
- **RMSE (Root Mean Squared Error):** corresponde a la raíz cuadrada del MSE y permite expresar el error en las mismas unidades de la variable objetivo.
- **$R^2$ (coeficiente de determinación):** indica la proporción de la variabilidad de la variable objetivo que es explicada por el modelo.

Para **MAE, MSE y RMSE**, valores menores representan menor error de predicción. En el caso de **$R^2$**, un valor más cercano a 1 indica una mayor proporción de variabilidad explicada por el modelo.

---

# 3. Resultados

## 3.1. Histograma de la concentración de CO

![Histograma de la concentración de CO](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/01_histograma_co.png)

### Interpretación

El histograma muestra la distribución de las concentraciones diarias de CO registradas en el conjunto de datos.

Se observa que una parte importante de las observaciones se encuentra aproximadamente entre **0.3 y 0.8 ppm**. También aparecen algunos valores superiores a **1.0 ppm**, aunque con menor frecuencia.

Esto permite observar que los registros no se distribuyen de manera uniforme, ya que algunas concentraciones aparecen con mayor frecuencia que otras.

---

## 3.2. Densidad de la concentración de CO

![Densidad de la concentración de CO](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/02_densidad_co.png)

### Interpretación

La gráfica de densidad permite observar de manera suavizada las zonas donde se concentra una mayor cantidad de valores de `CO_ppm`.

Se observa una mayor concentración de valores aproximadamente entre **0.5 y 0.7 ppm**, mientras que los valores superiores a **1.0 ppm** presentan una menor densidad.

También se aprecia concentración de valores cercanos a **0 ppm**. En general, la distribución presenta cierta asimetría, lo que indica que los valores de CO no siguen una distribución perfectamente simétrica.

---

## 3.3. Matriz de correlación

![Matriz de correlación](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/03_matriz_correlacion.png)

### Interpretación

La matriz de correlación permite analizar las relaciones lineales entre las variables utilizadas en el estudio.

Con respecto a la variable objetivo `CO_ppm`, se observan las siguientes correlaciones:

- `Mes` y `CO_ppm`: **-0.35**
- `Cos_Anual` y `CO_ppm`: **-0.30**
- `Sen_Anual` y `CO_ppm`: **0.057**
- `Dia_Semana` y `CO_ppm`: **-0.025**
- `Num_Observaciones` y `CO_ppm`: **-0.017**

Las correlaciones de `Mes` y `Cos_Anual` son las más destacadas en comparación con las demás variables. Sin embargo, sus valores no indican por sí solos una relación fuerte con la concentración de CO.

Por otro lado, `Dia_Semana` y `Num_Observaciones` presentan relaciones lineales muy bajas con `CO_ppm`.

También se observa una correlación de aproximadamente **0.79 entre `Dia_Semana` y `Fin_Semana`**, debido a que ambas variables representan información relacionada con los días de la semana.

Asimismo, `Mes` y `Sen_Anual` presentan una correlación aproximada de **-0.78**, relacionada con la forma en que fueron construidas las variables temporales.

> **Nota:** una correlación describe una relación estadística entre variables, pero **no implica necesariamente una relación causal**.

---

## 3.4. Valores reales vs. predichos del Árbol de Decisión

![Árbol de Decisión: valores reales vs. predichos](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/04_real_vs_predicho.png)

### Interpretación

La gráfica compara los valores reales de `CO_ppm` con los valores predichos por el **Árbol de Decisión**.

Se observa que varias predicciones se encuentran relativamente próximas a los valores reales, aunque también existen diferencias en determinados puntos.

El modelo obtuvo un **$R^2$ de aproximadamente 0.68**, lo que indica que, sobre el conjunto de evaluación utilizado, el modelo explica aproximadamente el **68 % de la variabilidad observada en `CO_ppm`**.

A pesar de ello, todavía existe una parte de la variabilidad que no es explicada por el modelo, por lo que las predicciones no coinciden completamente con los valores reales.

---

## 3.5. Análisis de residuos

![Histograma de residuos](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%203%20-%20Regresion%20Lineal/2.%20Clasificacion/Juan_Berrocal/Imagenes/05_residuos.png)

### Interpretación

Los residuos representan la diferencia entre los valores reales y los valores predichos por el modelo de **Regresión Lineal**.

En la gráfica se observa que una parte importante de los residuos se concentra alrededor de **0**, lo que indica que varias de las predicciones presentan errores relativamente pequeños.

También se observan residuos positivos que se alejan de 0, lo que indica que en algunas observaciones el modelo presenta errores de mayor magnitud.

En general, la distribución de los residuos muestra que el modelo presenta errores de predicción y que existen variaciones en la concentración de CO que no son explicadas completamente por las variables utilizadas.

---

## 3.6. Comparación de los modelos

| Modelo | MAE | MSE | RMSE | $R^2$ |
|---|---:|---:|---:|---:|
| Regresión Lineal | 0.1853 | 0.0561 | 0.2369 | 0.2956 |
| Árbol de Decisión | 0.1075 | 0.0252 | 0.1588 | 0.6836 |
| Random Forest | 0.0727 | 0.0127 | 0.1127 | 0.8406 |

Los resultados muestran diferencias en el desempeño de los tres modelos evaluados.

La Regresión Lineal obtuvo un **$R^2$ de 0.2956**, mientras que el Árbol de Decisión alcanzó un **$R^2$ de 0.6836**.

Por su parte, Random Forest obtuvo un **$R^2$ de 0.8406** y un **RMSE de 0.1127**.

En términos de error, los valores de MAE, MSE y RMSE disminuyeron al pasar de la Regresión Lineal al Árbol de Decisión y posteriormente a Random Forest.

Estos resultados muestran que, **para el conjunto de datos y la configuración utilizada**, los modelos basados en árboles lograron representar mejor los datos evaluados que la Regresión Lineal.

---

# 4. Discusión

A partir del análisis exploratorio se observa que la concentración de CO presenta principalmente valores comprendidos entre **0.3 y 0.8 ppm**, aunque también existen registros con concentraciones superiores.

La matriz de correlación permitió identificar que `Mes` y `Cos_Anual` presentan las relaciones lineales más destacadas con `CO_ppm`. Sin embargo, las correlaciones individuales no permiten explicar por sí solas todo el comportamiento de la variable objetivo, especialmente cuando pueden existir relaciones no lineales entre las variables.

La comparación de los modelos muestra que la **Regresión Lineal** presentó un menor coeficiente de determinación que el **Árbol de Decisión** y **Random Forest**. Además, los modelos basados en árboles obtuvieron menores valores de error.

En particular, Random Forest obtuvo un **$R^2$ de 0.8406**, mientras que el Árbol de Decisión obtuvo **0.6836** y la Regresión Lineal **0.2956**.

El análisis de residuos muestra que una parte importante de los errores se concentra alrededor de cero, aunque también existen algunos valores alejados. Esto indica que el modelo presenta errores de predicción y que no explica completamente todas las variaciones presentes en los datos.

En conjunto, los resultados muestran que los modelos de aprendizaje automático utilizados pueden emplearse para **aproximar la concentración de CO a partir de las variables seleccionadas**. Sin embargo, el desempeño obtenido corresponde específicamente al conjunto de datos y a las variables utilizadas en este trabajo, por lo que sería necesario incorporar otras variables ambientales para evaluar si se puede mejorar la capacidad predictiva.

---

# 5. Referencias

[1] F. Pedregosa *et al.*, “Scikit-learn: Machine Learning in Python,” *Journal of Machine Learning Research*, vol. 12, pp. 2825–2830, 2011.

[2] Scikit-learn, “DecisionTreeRegressor,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeRegressor.html. [Accedido: 17-sep-2026].

[3] Scikit-learn, “RandomForestRegressor,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/1.8/modules/generated/sklearn.ensemble.RandomForestRegressor.html. [Accedido: 17-sep-2026].

[4] Scikit-learn, “Metrics and scoring: quantifying the quality of predictions,” *Scikit-learn Documentation*. [En línea]. Disponible en: https://scikit-learn.org/stable/modules/model_evaluation.html. [Accedido: 17-sep-2026].
