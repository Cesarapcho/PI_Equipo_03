# Taller 4 – Redes Neuronales: CNN, Perceptrón y Keras

## 1. Introducción

El notebook trabajado presenta tres conceptos principales de redes neuronales:

1. **CNN:** clasificación de imágenes de vidrio y plástico, transferencia de aprendizaje y Grad-CAM.
2. **Keras:** construcción de redes neuronales para clasificación de reseñas y análisis del sobreajuste.
3. **Perceptrón:** comprensión de una neurona artificial y de las compuertas AND, OR y XOR.

El recorrido permite pasar desde modelos simples hasta arquitecturas capaces de trabajar con datos más complejos.

---

# 2. CNN (Convolutional Neural Networks)

## 2.1. ¿Qué son?

Una CNN procesa imágenes mediante filtros o **kernels** que detectan patrones locales como bordes, texturas y formas. Estos patrones se combinan progresivamente hasta permitir la clasificación de la imagen.

## 2.2. Componentes principales

| Componente | Función |
|---|---|
| **Conv2D** | Extrae características mediante filtros. |
| **ReLU** | Introduce no linealidad en la red. |
| **MaxPool** | Reduce el tamaño de la información conservando características importantes. |
| **Fully Connected** | Utiliza las características extraídas para realizar la clasificación. |

## 2.3. CNN construida desde cero

```python
class SimpleCNN(nn.Module):
    def __init__(self, num_classes):
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(1, 16, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),

            nn.Conv2d(16, 32, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),

            nn.Conv2d(32, 64, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
        )
```

Cada bloque convolucional extrae características de la imagen y reduce progresivamente su tamaño.

## 2.4. Resultados de la CNN

### a) Dataset: vidrio y plástico

<div align="center">

![Ejemplos del dataset](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/dataset_glass_plastic.png)

</div>

**Interpretación:** las imágenes pertenecen a las clases vidrio y plástico. La variedad de formas y posiciones obliga al modelo a aprender características generales y no solamente memorizar ejemplos.

### b) Curvas de entrenamiento

<div align="center">

![Curva de pérdida](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/cnn_loss_curve.png)

</div>

<div align="center">

![Curva de métricas](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/cnn_metrics_curve.png)

</div>

**Interpretación:** la pérdida disminuye durante el entrenamiento y el accuracy alcanza aproximadamente 63 %. El ROC-AUC se mantiene alrededor de 0.67–0.69, lo que muestra que existe aprendizaje, aunque el desempeño todavía es moderado.

### c) Matriz de confusión

<div align="center">

![Matriz de confusión](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/confusion_matrix_cnn.png)

</div>

**Interpretación:** la matriz permite observar los aciertos y errores de cada clase. Es útil porque muestra directamente qué categorías está confundiendo el modelo.

### d) Grad-CAM

<div align="center">

![Grad-CAM](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/gradcam.png)

</div>

**Interpretación:** Grad-CAM muestra las regiones de la imagen que influyen más en la predicción. En este resultado, la atención se concentra principalmente en la zona central de la botella. Esta técnica permite comprobar si el modelo está utilizando características relevantes para tomar su decisión.

## 2.5. Transfer Learning

Se utilizó **ResNet18**, un modelo previamente entrenado, y se adaptaron sus últimas capas al problema de clasificación.

El resultado pasó de aproximadamente **57.7 % a 87.25 % de accuracy**, mientras que el ROC-AUC aumentó de **0.61 a 0.96**.

Esto muestra la utilidad de aprovechar conocimiento aprendido previamente cuando se dispone de una cantidad limitada de datos propios.

---

# 3. Perceptrón

## 3.1. ¿Qué es?

El perceptrón es una neurona artificial básica. Recibe entradas, las combina mediante pesos y un bias y posteriormente aplica una función de activación.

```python
def perceptron(inputs, weights, bias, activation_func):
    weighted_sum = np.dot(inputs, weights) + bias
    return activation_func(weighted_sum)
```

La operación puede expresarse en texto como:

**z = w1*x1 + w2*x2 + b**

**y = f(z)**

donde `x` representa las entradas, `w` los pesos, `b` el bias y `f` la función de activación.

## 3.2. Funciones de activación

- **Escalón:** produce una salida binaria, 0 o 1.
- **tanh:** produce valores entre -1 y 1 y permite una respuesta gradual.

## 3.3. AND, OR y XOR

<div align="center">

![Frontera de decisión OR/AND](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/perceptron_plano.png)

</div>

**Interpretación:** AND y OR pueden separarse mediante una línea recta, por lo que un solo perceptrón puede resolver estos problemas.

<div align="center">

![XOR no es separable linealmente](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/perceptron_xor.png)

</div>

**Interpretación:** en XOR no existe una única línea que separe correctamente las clases. Por ello, un solo perceptrón no es suficiente y se necesitan varias capas.

---

# 4. Keras

## 4.1. ¿Qué es?

Keras facilita la construcción y entrenamiento de redes neuronales, permitiendo definir capas, funciones de pérdida, optimizadores y métricas con pocas líneas de código.

## 4.2. Clasificación de reseñas IMDB

```python
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

model.compile(
    optimizer='rmsprop',
    loss='binary_crossentropy',
    metrics=['accuracy']
)
```

El modelo utiliza capas densas, ReLU en las capas ocultas y sigmoid para la clasificación binaria.

## 4.3. Sobreajuste y regularización

### a) Modelo original

<div align="center">

![Pérdida modelo original](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/keras_loss_original.png)

</div>

**Interpretación:** la pérdida de entrenamiento continúa disminuyendo mientras la validación deja de mejorar y aumenta. Este comportamiento indica **sobreajuste**, porque el modelo aprende demasiado los datos de entrenamiento y pierde capacidad de generalización.

### b) Modelo más pequeño

<div align="center">

![Modelo más pequeño vs original](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/keras_loss_smaller.png)

</div>

**Interpretación:** reducir el número de neuronas disminuye la capacidad del modelo para memorizar los datos y retrasa el sobreajuste.

### c) Regularización L2

<div align="center">

![Regularización L2](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/keras_loss_regularization.png)

</div>

**Interpretación:** L2 penaliza pesos demasiado grandes y ayuda a mantener un modelo más controlado, favoreciendo la generalización.

### d) Dropout

<div align="center">

![Dropout](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Rodrigo%20Asmat/Imagenes/keras_loss_dropout.png)

</div>

**Interpretación:** Dropout desactiva aleatoriamente parte de las neuronas durante el entrenamiento. Esto evita que la red dependa demasiado de determinadas neuronas y puede reducir el sobreajuste.

---

# 5. Funciones principales utilizadas

| Función / clase | Propósito |
|---|---|
| `nn.Conv2d`, `nn.MaxPool2d`, `nn.ReLU` | Construcción de capas convolucionales. |
| `DataLoader` | Organización de los datos en lotes. |
| `train_one_epoch` / `evaluate` | Entrenamiento y evaluación. |
| `grad_cam()` | Interpretación de las predicciones. |
| `models.Sequential`, `layers.Dense` | Construcción de modelos en Keras. |
| `model.compile`, `model.fit`, `model.evaluate`, `model.predict` | Entrenamiento y uso del modelo. |
| `regularizers.l2`, `layers.Dropout` | Control del sobreajuste. |
| `perceptron()` | Implementación de una neurona artificial. |

---

# 6. ¿Qué aprendimos?

- Un perceptrón puede resolver problemas linealmente separables como AND y OR, pero no XOR.
- Las CNN permiten extraer automáticamente características de imágenes.
- El **Transfer Learning** puede mejorar el rendimiento cuando se cuenta con pocos datos.
- **Grad-CAM** permite observar qué regiones influyen en una predicción.
- La matriz de confusión permite analizar aciertos y errores por clase.
- El **sobreajuste** aparece cuando el modelo mejora en entrenamiento pero empeora en validación.
- **Dropout** y **regularización L2** ayudan a controlar el sobreajuste.
- Keras facilita la construcción y entrenamiento de redes neuronales.

---

# 7. Aplicación al proyecto de evaluación de granadillas

## 7.1. Problema

El proyecto busca realizar una **evaluación no destructiva de la condición interna de la granadilla** mediante excitación vibratoria controlada.

Las principales entradas del sistema serán:

1. **Respuesta vibroacústica** obtenida mediante sensores.
2. **Masa de la granadilla** como variable adicional.

A partir de estas mediciones se busca determinar la condición interna del fruto sin necesidad de abrirlo o destruirlo.

## 7.2. Aplicación de Machine Learning

En el proyecto utilizaremos principalmente **Machine Learning mediante aprendizaje supervisado**.

Primero se realizará la medición de diferentes granadillas. Para cada fruto se registrará su respuesta vibroacústica y su masa. Después, la condición interna será determinada experimentalmente para generar las etiquetas del conjunto de datos.

El modelo aprenderá la relación entre las características medidas y la condición interna conocida.

Las entradas pueden representarse en texto como:

**X = (X_vib, m)**

donde:

- **X_vib:** características obtenidas de la respuesta vibroacústica.
- **m:** masa de la granadilla.

## 7.3. Funciones del Machine Learning

El modelo tendrá las siguientes funciones:

1. **Aprender patrones:** identificar relaciones entre las características vibroacústicas y la condición interna.
2. **Clasificar:** asignar una nueva granadilla a una de las categorías definidas experimentalmente.
3. **Predecir:** estimar la condición interna de frutos que no fueron utilizados durante el entrenamiento.
4. **Evaluar:** utilizar métricas como accuracy, precision, recall, F1-score y matriz de confusión.
5. **Generalizar:** comprobar que el modelo funcione correctamente con nuevas granadillas.

La predicción puede expresarse en texto como:

**ŷ = f(X_vib, m)**

donde **ŷ** representa la condición interna estimada.

## 7.4. Modelos propuestos

Como primera etapa se evaluarán modelos de **Machine Learning supervisado**:

- **Random Forest**
- **SVM**
- **Regresión Logística**

Estos modelos permitirán establecer una línea base y comprobar si las características vibroacústicas permiten diferenciar las condiciones internas.

Posteriormente, si se obtiene suficiente cantidad de datos, se podrá comparar el resultado con **Deep Learning mediante una CNN 1D**, utilizando directamente las señales vibroacústicas.

## 7.5. Relación con lo aprendido en el taller

Los conceptos estudiados pueden incorporarse progresivamente:

**Perceptrón → modelos de Machine Learning → redes neuronales → CNN 1D**

En una etapa posterior también podría utilizarse un **espectrograma** de la señal vibroacústica para representar la información como una imagen y aplicar una CNN 2D.

## 7.6. Flujo del proyecto

```text
Granadilla
    │
    ▼
Excitación vibratoria controlada
    │
    ▼
Respuesta vibroacústica
    │
    ▼
Adquisición de la señal
    │
    ▼
Procesamiento y extracción de características
    │
    ├── Características vibroacústicas
    └── Masa
    │
    ▼
Machine Learning supervisado
    │
    ▼
Clasificación / Predicción
    │
    ▼
Condición interna estimada
```

---

# 8. Conclusión

El taller permitió comprender cómo evolucionan los modelos de redes neuronales desde un **perceptrón** hasta arquitecturas más complejas como las **CNN**, además de estudiar técnicas para mejorar y analizar su comportamiento, como **Transfer Learning, Grad-CAM, Dropout y regularización**.

Estos conocimientos pueden aplicarse directamente al proyecto de evaluación no destructiva de granadillas. En una primera etapa, se utilizará **Machine Learning supervisado** para aprender la relación entre las características de la respuesta vibroacústica, la masa y la condición interna determinada experimentalmente.

La función principal del modelo será **aprender patrones, clasificar, predecir, evaluar y generalizar** la condición de nuevas granadillas.

Como primera alternativa se evaluarán **Random Forest, SVM y Regresión Logística**. Si posteriormente se dispone de suficientes datos, se podrá comparar su desempeño con una **CNN 1D** capaz de trabajar directamente con las señales vibroacústicas.

De esta manera, el proyecto integra:

**excitación vibratoria → adquisición de señales → procesamiento → Machine Learning supervisado → clasificación/predicción → evaluación no destructiva**
