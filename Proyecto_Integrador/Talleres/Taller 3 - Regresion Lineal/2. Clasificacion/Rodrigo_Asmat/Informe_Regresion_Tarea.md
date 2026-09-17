# Informe Técnico: Predicción del Índice de Calidad del Aire mediante Regresión Lineal y Árbol de Decisión

**Asignatura:** Taller de Inteligencia Artificial  
**Dataset:** Monitoreo de Ozono (O₃) — Estación Connecticut Hill, Tompkins County, Nueva York, EE.UU. (2023)  
**Fecha:** 17 de septiembre de 2026

---

## 1. Introducción

La calidad del aire es un indicador crítico de salud pública y medioambiental. El ozono troposférico (O₃) es uno de los contaminantes regulados por la Agencia de Protección Ambiental de Estados Unidos (EPA), cuyo nivel de exposición se sintetiza a través del **Índice de Calidad del Aire (AQI, por sus siglas en inglés)**. Un AQI elevado indica mayor riesgo para la salud, especialmente en poblaciones vulnerables como niños, adultos mayores y personas con enfermedades respiratorias.

El presente informe documenta el análisis exploratorio y la modelización predictiva del AQI diario a partir de datos de monitoreo de ozono registrados durante el año 2023 en la estación "Connecticut Hill", ubicada en el condado de Tompkins, estado de Nueva York (lat. 42.4006°N, lon. -76.6538°O). El dataset fue obtenido del sistema AQS (*Air Quality System*) de la EPA y contiene **355 observaciones diarias**.

El objetivo principal es construir modelos de aprendizaje automático — específicamente **Regresión Lineal Múltiple** y **Árbol de Decisión Regresor** — capaces de estimar el AQI diario a partir de la concentración de ozono y variables temporales derivadas.

---

## 2. Metodología

### 2.1 Descripción del Dataset

El conjunto de datos original contiene 21 columnas, de las cuales se seleccionaron las variables con potencial predictivo. Las columnas constantes (e.g., `Site ID`, `Site Latitude`, `Site Longitude`, `POC`) fueron descartadas por aportar varianza nula.

| Variable | Tipo | Descripción |
|---|---|---|
| `Daily Max 8-hour Ozone Concentration` | Continua (ppm) | Concentración máxima de O₃ en ventana de 8 horas |
| `Daily Obs Count` | Discreta | Número de observaciones horarias válidas en el día |
| `Percent Complete` | Continua (%) | Porcentaje de completitud del monitoreo diario |
| `Daily AQI Value` | Discreta (objetivo) | Índice de Calidad del Aire calculado a partir de O₃ |

### 2.2 Ingeniería de Características (Feature Engineering)

Dado que la variable `Date` no es directamente interpretable por los modelos, se convirtió al tipo `datetime` y se extrajeron las siguientes variables temporales:

```python
df['Date']         = pd.to_datetime(df['Date'], format='%m/%d/%Y')
df['Mes']          = df['Date'].dt.month          # Mes del año (1–12)
df['Dia_del_Anio'] = df['Date'].dt.day_of_year    # Día del año (1–365)
df['Dia_Semana']   = df['Date'].dt.dayofweek      # Día de la semana (0=Lun, 6=Dom)
df['Trimestre']    = df['Date'].dt.quarter         # Trimestre (1–4)
```

Estas variables capturan la **estacionalidad** del ozono, cuya concentración varía significativamente a lo largo del año debido a factores meteorológicos (radiación solar, temperatura).

El conjunto de características final fue:

```python
cols_modelo = [
    'Daily Max 8-hour Ozone Concentration',
    'Daily Obs Count',
    'Percent Complete',
    'Mes', 'Dia_del_Anio', 'Dia_Semana', 'Trimestre',
    'Daily AQI Value'   # Variable objetivo Y
]
```

### 2.3 Análisis Exploratorio de Datos (EDA)

Se realizó un análisis estadístico descriptivo y visualizaciones para comprender la distribución de las variables y sus relaciones:

```python
# Estadísticos descriptivos
df.describe().round(4)

# Matriz de correlación de Pearson
numeric_df.corr().round(4)

# Mapa de calor
sns.heatmap(numeric_df.corr(), annot=True, cmap='RdYlGn', vmin=-1, vmax=1)

# Histograma y función de densidad de probabilidad (KDE)
df['Daily AQI Value'].plot.hist(bins=25)
df['Daily AQI Value'].plot.density()

# AQI promedio por mes
df.groupby('Mes')['Daily AQI Value'].mean().plot.bar()
```

### 2.4 División de los Datos

Los datos se dividieron en conjuntos de **entrenamiento (70%)** y **prueba (30%)** utilizando una semilla aleatoria fija para garantizar reproducibilidad:

```python
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=123
)
# Resultado: 248 muestras de entrenamiento, 107 muestras de prueba
```

### 2.5 Modelos Implementados

#### A) Regresión Lineal Múltiple

```python
from sklearn.linear_model import LinearRegression
from sklearn import metrics

lm = LinearRegression()
lm.fit(X_train, y_train)
predictions = lm.predict(X_test)
```

La ecuación del modelo tiene la forma:

$$\hat{y} = \beta_0 + \beta_1 x_1 + \beta_2 x_2 + \cdots + \beta_p x_p$$

donde $\hat{y}$ es el AQI predicho, $x_1$ es la concentración de ozono y $x_2, \ldots, x_p$ son las variables temporales y de monitoreo.

#### B) Árbol de Decisión Regresor

```python
from sklearn import tree

tree_model = tree.DecisionTreeRegressor(max_depth=5, random_state=10)
tree_model.fit(X_train, y_train)
tree_pred = tree_model.predict(X_test)
```

### 2.6 Métricas de Evaluación

Se emplearon cuatro métricas estándar para comparar el desempeño de los modelos:

```python
mae  = metrics.mean_absolute_error(y_test, predictions)
mse  = metrics.mean_squared_error(y_test, predictions)
rmse = np.sqrt(mse)
r2   = metrics.r2_score(y_test, predictions)
```

| Métrica | Fórmula | Interpretación |
|---|---|---|
| MAE | $\frac{1}{n}\sum |y_i - \hat{y}_i|$ | Error promedio en unidades del AQI |
| MSE | $\frac{1}{n}\sum (y_i - \hat{y}_i)^2$ | Penaliza errores grandes |
| RMSE | $\sqrt{MSE}$ | Error típico en unidades del AQI |
| R² | $1 - \frac{SS_{res}}{SS_{tot}}$ | Varianza explicada por el modelo (0–1) |

### 2.7 Pruebas Estadísticas de Validación

Se aplicaron las siguientes pruebas para verificar los supuestos del modelo de regresión lineal:

#### 2.7.1 Correlación de Pearson

Evalúa la relación lineal entre la concentración de ozono y el AQI:

```python
from scipy import stats
r, p = stats.pearsonr(
    df['Daily Max 8-hour Ozone Concentration'],
    df['Daily AQI Value']
)
```

**Hipótesis:** H₀: no existe correlación lineal (r = 0) vs. H₁: existe correlación (r ≠ 0).

#### 2.7.2 Test de Shapiro-Wilk (normalidad de residuos)

Evalúa si los residuos del modelo se distribuyen normalmente, supuesto fundamental de la regresión OLS:

```python
from scipy import stats
sw_stat, sw_p = stats.shapiro(residuos)
```

**Hipótesis:** H₀: los residuos siguen distribución normal vs. H₁: no siguen distribución normal.

#### 2.7.3 Estadístico de Durbin-Watson (autocorrelación)

Detecta autocorrelación serial en los residuos. Un valor cercano a 2 indica ausencia de autocorrelación:

```python
dw = np.sum(np.diff(residuos)**2) / np.sum(residuos**2)
```

**Interpretación:** Valores en [1.5, 2.5] son aceptables; valores < 1.5 indican autocorrelación positiva.

#### 2.7.4 Reporte OLS con statsmodels

Se obtuvo el reporte estadístico completo del modelo (coeficientes, intervalos de confianza, estadístico F, p-valores) mediante la librería `statsmodels`:

```python
import statsmodels.api as sm
Xs = sm.add_constant(X)
stat_model = sm.OLS(y, Xs)
stat_result = stat_model.fit()
print(stat_result.summary())
```

---

## 3. Resultados

### 3.1 Estadísticos Descriptivos del AQI

| Estadístico | Valor |
|---|---|
| Observaciones | 355 |
| Media | 36.35 |
| Desv. estándar | 11.72 |
| Mínimo | 17 |
| Percentil 25 | 29 |
| Mediana (P50) | 35 |
| Percentil 75 | 41 |
| Máximo | 100 |

La concentración media de ozono fue de **0.0362 ppm**, con valores que oscilan entre 0.013 y 0.100 ppm a lo largo del año.

### 3.2 Distribución del AQI (Imagen 1)

El histograma y la curva de densidad muestran que el AQI diario sigue una distribución **asimétrica positiva (sesgada a la derecha)**, con la mayor concentración de valores entre 25 y 45 unidades. La moda se sitúa alrededor de 28-30 unidades, mientras que la cola derecha refleja eventos puntuales de mayor contaminación (AQI > 60), posiblemente asociados a episodios de incendios forestales o condiciones meteorológicas extremas.

> **Función utilizada:** `plot.hist(bins=25)` y `plot.density()` de pandas sobre la serie `Daily AQI Value`.

### 3.3 Estacionalidad del AQI (Imagen 2)

| Mes | AQI Promedio |
|---|---|
| Enero | 28.19 |
| Febrero | 34.79 |
| Marzo | 39.90 |
| **Abril** | **49.03** ← Máximo |
| Mayo | 45.42 |
| Junio | 43.33 |
| Julio | 40.39 |
| Agosto | 31.70 |
| Septiembre | 32.60 |
| Octubre | 30.81 |
| Noviembre | 30.60 |
| Diciembre | 27.65 |

El AQI alcanza su valor máximo en **abril (49.03)** y disminuye progresivamente hacia el invierno. Este patrón refleja la **estacionalidad del ozono troposférico**, que se forma principalmente mediante reacciones fotoquímicas en presencia de radiación solar y temperatura elevada, características de la primavera y principios del verano en el noreste de EE.UU.

> **Función utilizada:** `groupby('Mes')['Daily AQI Value'].mean().plot.bar()`.

### 3.4 Análisis de Correlación (Imagen 3)

Los valores más relevantes de la matriz de correlación de Pearson son:

| Par de Variables | Correlación r |
|---|---|
| Ozono ↔ AQI | **0.95** (muy alta positiva) |
| Mes ↔ AQI | -0.22 (baja negativa) |
| Trimestre ↔ AQI | -0.22 (baja negativa) |
| Día del Año ↔ AQI | -0.23 (baja negativa) |
| Día Semana ↔ AQI | -0.01 (prácticamente nula) |
| Daily Obs Count ↔ Percent Complete | **1.00** (colinealidad perfecta) |

La correlación de **r = 0.95 (p = 4.06×10⁻¹⁸⁷)** entre la concentración de ozono y el AQI confirma que el AQI se deriva casi directamente de la concentración medida. La colinealidad perfecta entre `Daily Obs Count` y `Percent Complete` es una señal de alerta sobre **multicolinealidad** en el modelo.

> **Función utilizada:** `numeric_df.corr()` y `sns.heatmap()`. La correlación de Pearson individual fue calculada con `scipy.stats.pearsonr()`.

### 3.5 Pruebas Estadísticas

| Prueba | Estadístico | p-valor | Interpretación |
|---|---|---|---|
| **Pearson r** (Ozono vs. AQI) | r = 0.9542 | 4.06×10⁻¹⁸⁷ | Correlación lineal muy fuerte y altamente significativa (se rechaza H₀) |
| **Shapiro-Wilk** (residuos) | W = 0.5432 | 1.12×10⁻¹⁶ | Se rechaza H₀ de normalidad: los residuos **no son normales** (presencia de outliers en la cola derecha) |
| **Durbin-Watson** (autocorrelación) | DW = 2.104 | — | Valor en rango aceptable [1.5, 2.5]: **no hay autocorrelación** serial significativa |
| **F-estadístico** (OLS global) | F = 603.2 | 1.59×10⁻¹⁸⁰ | El modelo en conjunto es **altamente significativo** |

> **Nota sobre Shapiro-Wilk:** El rechazo de la normalidad de residuos se debe principalmente a los valores extremos observados en días de alta contaminación (AQI > 80), que generan residuos positivos grandes (hasta +28 unidades). Esto no invalida el modelo, pero sugiere que la regresión lineal puede subestimar el AQI en episodios extremos.

### 3.6 Coeficientes del Modelo de Regresión Lineal

El modelo ajustado tiene la siguiente ecuación:

$$\widehat{AQI} = -7.009 + 1143.30 \cdot [O_3] - 0.0017 \cdot ObsCount - 0.010 \cdot PctComplete$$
$$\quad - 0.832 \cdot Mes + 0.027 \cdot DiaAnio + 0.071 \cdot DiaSemana + 0.310 \cdot Trimestre$$

| Variable | Coeficiente | t-estadístico (OLS) | P>|t| | Significancia |
|---|---|---|---|---|
| Intercepto | -7.009 | -0.722 | 0.471 | No significativo |
| **Ozono (ppm)** | **1143.30** | **58.29** | **< 0.001** | **★★★ Muy significativo** |
| Daily Obs Count | -0.002 | -0.726 | 0.468 | No significativo |
| Percent Complete | -0.010 | 0.583 | 0.560 | No significativo |
| Mes | -0.832 | -1.741 | 0.083 | Marginalmente significativo |
| Día del Año | 0.027 | 1.699 | 0.090 | Marginalmente significativo |
| Día Semana | 0.071 | 1.265 | 0.207 | No significativo |
| Trimestre | 0.310 | 0.792 | 0.429 | No significativo |

El coeficiente de la concentración de ozono (1143.30) indica que por cada incremento de 0.001 ppm en O₃, el AQI aumenta aproximadamente **1.14 unidades**, lo cual es coherente con la fórmula de cálculo del AQI para ozono establecida por la EPA.

### 3.7 Evaluación del Modelo de Regresión Lineal (Imágenes 4 y 5)

**Imagen 4 — AQI Real vs. Predicho:**  
Los puntos se distribuyen muy cerca de la línea de predicción perfecta (diagonal roja), especialmente en el rango de AQI entre 17 y 65. Se observan dos puntos con AQI real > 80 que se desvían de la diagonal, correspondientes a eventos extremos de contaminación que el modelo lineal subestima.

**Imagen 5 — Histograma de Residuos:**  
La distribución de residuos está centrada en 0, con la gran mayoría de los errores entre -5 y +5 unidades. Sin embargo, existen residuos positivos grandes (hasta +28) que corresponden a los eventos extremos mencionados, lo que explica el rechazo de la normalidad por el test de Shapiro-Wilk.

### 3.8 Comparación de Modelos

| Modelo | MAE | RMSE | R² |
|---|---|---|---|
| **Regresión Lineal** | 1.809 | 3.550 | 0.913 |
| **Árbol de Decisión** | 0.685 | 1.289 | 0.989 |

El **Árbol de Decisión** supera significativamente a la Regresión Lineal en todas las métricas. Con un R² = 0.989, captura casi el 99% de la varianza del AQI, frente al 91.3% de la regresión lineal. El RMSE del árbol (1.29 unidades de AQI) es 2.75 veces menor que el de la regresión (3.55 unidades), lo que indica una capacidad superior para manejar las relaciones no lineales y los valores extremos del dataset.

### 3.9 Reporte OLS — statsmodels (Imagen 6)

El reporte OLS confirma un **R² = 0.912** (Adj. R² = 0.911), con un F-estadístico de 603.2 y p < 1.59×10⁻¹⁸⁰, lo que valida la significancia global del modelo. Sin embargo, se emite una advertencia de **SingularMatrixWarning**, indicando multicolinealidad severa en el conjunto de predictores, especialmente entre `Daily Obs Count` y `Percent Complete` (correlación perfecta = 1.00), y entre las variables temporales `Mes`, `Dia_del_Anio` y `Trimestre` (correlaciones de 0.97). El número de condición (1.17×10¹⁶) confirma que la matriz de diseño es casi singular.

---

## 4. Discusión

Los resultados muestran que la concentración de ozono es, con diferencia, el predictor más informativo del AQI, con un coeficiente de correlación de Pearson de r = 0.95 y un t-estadístico de 58.29 en el modelo OLS. Esto tiene sentido físico-matemático: la EPA calcula el AQI directamente a partir de la concentración medida mediante una función lineal por tramos, por lo que la relación entre ambas variables es cuasi-determinística.

Las variables temporales aportan información marginal al modelo (el mes tiene un p-valor de 0.083), reflejando la estacionalidad de la fotoquímica del ozono, con máximos en primavera (abril) cuando la radiación solar aumenta pero la vegetación aún no ha alcanzado su máximo de absorción de precursores.

La violación del supuesto de normalidad de los residuos se debe a eventos atípicos de alta contaminación (AQI > 80), probablemente asociados a incendios forestales o episodios de transporte de masas de aire contaminado. En estos casos, modelos no paramétricos como el Árbol de Decisión son más adecuados.

El problema de multicolinealidad detectado podría resolverse eliminando una de las variables redundantes (`Daily Obs Count` o `Percent Complete`, y reduciendo las variables temporales a una o dos), lo que mejoraría la interpretabilidad de los coeficientes sin sacrificar poder predictivo.

---

## 5. Referencias

[1] U.S. Environmental Protection Agency, "Air Quality System (AQS) Data Mart," *AQS Data*, 2023. [Online]. Available: https://www.epa.gov/aqs

[2] F. Pedregosa *et al.*, "Scikit-learn: Machine Learning in Python," *Journal of Machine Learning Research*, vol. 12, pp. 2825–2830, 2011.

[3] W. McKinney, "Data Structures for Statistical Computing in Python," in *Proc. 9th Python in Science Conf.*, 2010, pp. 51–56.

[4] J. D. Hunter, "Matplotlib: A 2D Graphics Environment," *Computing in Science & Engineering*, vol. 9, no. 3, pp. 90–95, 2007.

[5] M. Waskom, "seaborn: Statistical Data Visualization," *Journal of Open Source Software*, vol. 6, no. 60, p. 3021, 2021, doi: 10.21105/joss.03021.

[6] U.S. Environmental Protection Agency, "Technical Assistance Document for the Reporting of Daily Air Quality — the Air Quality Index (AQI)," EPA-454/B-18-007, 2018.

[7] T. Hastie, R. Tibshirani, and J. Friedman, *The Elements of Statistical Learning*, 2nd ed. New York, NY, USA: Springer, 2009.

[8] S. S. Shapiro and M. B. Wilk, "An analysis of variance test for normality (complete samples)," *Biometrika*, vol. 52, no. 3–4, pp. 591–611, 1965.

[9] J. Durbin and G. S. Watson, "Testing for serial correlation in least squares regression: I," *Biometrika*, vol. 37, no. 3–4, pp. 409–428, 1950.

[10] Seabold, S. and Perktold, J., "Statsmodels: Econometric and Statistical Modeling with Python," in *Proc. 9th Python in Science Conf.*, 2010, pp. 92–96.
