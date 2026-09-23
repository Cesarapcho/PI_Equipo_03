# 1. Redes Neuronales: CNN, Perceptrón y Keras

---

## 1.1 CNN (Redes Neuronales Convolucionales)

### 1.1. Qué son y por qué importan

Una CNN es una red pensada para analizar imágenes. No analiza cada píxel de forma aislada, sino que revisa grupos de píxeles vecinos buscando patrones como bordes, texturas y formas. Esto se logra mediante los **kernels**, pequeños filtros que recorren la imagen.

Una red normal, utilizando únicamente capas densas, trataría cada píxel como un dato independiente y podría perder parte de la información espacial. Una CNN, en cambio, conserva la relación entre los píxeles vecinos, lo que permite identificar patrones dentro de una imagen.

### 1.2. Piezas clave

- **Convolución (Conv2D):** aplica filtros y genera mapas de características.
- **Activación (ReLU):** permite trabajar con relaciones no lineales.
- **Pooling (MaxPool):** reduce el tamaño de la información procesada conservando características importantes.
- **Capas densas finales:** utilizan las características extraídas para realizar la clasificación.

### 1.3. Código relevante

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
            nn.AdaptiveAvgPool2d((1, 1))
        )

        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(64, num_classes)
        )
```

### 1.4. Dataset utilizado

<div align="center">

![Ejemplos vidrio y plástico](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/ejemplos_vidrio_plastico.png)

</div>

**Clases del conjunto de datos:**

- 0 = glass
- 1 = plastic

El conjunto de datos utilizado contiene imágenes correspondientes a las clases **vidrio** y **plástico**. El objetivo de la CNN es aprender características visuales que permitan diferenciar ambas categorías.

---

## 1.6 Transfer Learning

En vez de entrenar una CNN desde cero, se puede aprovechar un modelo previamente entrenado con millones de imágenes. En este caso se utilizó **ResNet18**, reemplazando su última capa para adaptarla al problema de clasificación.

```python
resnet = models.resnet18(weights=models.ResNet18_Weights.DEFAULT)

resnet.fc = nn.Linear(
    resnet.fc.in_features,
    num_classes
)

for name, param in resnet.named_parameters():
    param.requires_grad = False

for param in resnet.fc.parameters():
    param.requires_grad = True
```

Después se realizó **fine-tuning**, descongelando las últimas capas (`layer4`) para permitir que el modelo se adapte mejor a las imágenes utilizadas.

La ventaja del transfer learning es que ResNet18 ya posee características aprendidas previamente, como detección de bordes, texturas y formas. Por ello, no es necesario aprender todo desde cero.

---

# 2. Interpretabilidad: Grad-CAM

Grad-CAM permite visualizar las regiones de una imagen que tuvieron mayor influencia en la predicción.

```python
def grad_cam(model, image_tensor, target_class=None):
    ...
```

Las zonas más claras o amarillas representan regiones con mayor influencia en la decisión del modelo, mientras que las zonas oscuras representan una menor contribución.

### 2.0. Resultado obtenido

<div align="center">

![Grad-CAM](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/grad_cam.png)

</div>

### 2.1. Interpretación

La figura contiene tres paneles:

1. **Imagen original:** muestra el objeto clasificado.
2. **Mapa Grad-CAM:** muestra las regiones que tuvieron mayor influencia.
3. **Superposición:** combina la imagen con el mapa de calor.

En este resultado, las zonas de mayor intensidad se concentran principalmente en la región central del objeto. Esto indica que el modelo está utilizando características visuales presentes en esa zona para realizar la clasificación.

Grad-CAM no demuestra por sí solo que la decisión sea correcta, pero permite comprobar visualmente qué regiones están influyendo en el modelo y detectar posibles problemas, como que la red esté utilizando el fondo en lugar del objeto.

---

# 3. Matriz de confusión

<div align="center">

![Matriz de confusión](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/matriz_confusion.png)

</div>

### 3.0. Interpretación

La matriz muestra el comportamiento de la CNN para las dos clases:

| Real | Predicción 0 | Predicción 1 |
|---|---:|---:|
| Clase 0 | 54 | 22 |
| Clase 1 | 36 | 37 |

Por lo tanto:

- **54** imágenes de la clase 0 fueron clasificadas correctamente como clase 0.
- **22** imágenes de la clase 0 fueron clasificadas incorrectamente como clase 1.
- **36** imágenes de la clase 1 fueron clasificadas incorrectamente como clase 0.
- **37** imágenes de la clase 1 fueron clasificadas correctamente como clase 1.

El número total de aciertos es 54 + 37 = 91.

El número total de imágenes es 54 + 22 + 36 + 37 = 149.

Por tanto:

Accuracy = 91 / 149 ≈ 0.611

La exactitud es aproximadamente 61.1 %.

### 3.1. Análisis

El modelo consigue aprender ciertos patrones para diferenciar vidrio y plástico, pero todavía presenta una cantidad considerable de errores.

El mayor grupo de errores corresponde a las **36 imágenes de la clase 1 clasificadas como clase 0**. También existen 22 casos de la clase 0 clasificados como clase 1.

Esto indica que el modelo todavía tiene dificultades para separar completamente ambas categorías y que sería necesario continuar trabajando en aspectos como los datos, el preprocesamiento, la arquitectura y la regularización.

---

# 4. Perceptrón

## 4.1 Qué es y por qué importa

El perceptrón es una unidad fundamental de una red neuronal. Recibe entradas, las multiplica por pesos, agrega un sesgo y aplica una función de activación.

```python
def perceptron(inputs, weights, bias, activation_func):
    weighted_sum = np.dot(inputs, weights) + bias
    output = activation_func(weighted_sum)
    return output
```

Matemáticamente:

* **z** = w₁x₁ + w₂x₂ + b
* **y** = f(z)

donde:
- **xᵢ** son las entradas
-  **wᵢ** los pesos
-  **b** el bias
-  **f** la función de activación.

---

# 5. Compuertas lógicas: AND, OR y XOR

<div align="center">

![Fronteras OR/AND](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/xor_or_and.png)

</div>

### 5.0. Interpretación

La gráfica muestra las fronteras de decisión para las funciones **AND** y **OR**.

En ambos casos es posible utilizar una línea recta para separar los casos positivos de los negativos.

### Valores de las compuertas

| X₁ | X₂ | **AND** | **OR** |
|:--:|:--:|:------:|:-----:|
| 0 | 0 |  0 | 0 |
| 0 | 1 |  0 | 1 |
| 1 | 0 |  0 | 1 |
| 1 | 1 |  1 | 1 |

Para **AND**, únicamente:

**(1,1) → 1**

produce una salida positiva.

Para **OR**, las combinaciones:

**(0,1), (1,0), (1,1) → 1**

producen una salida positiva.

Por esta razón, un solo perceptrón puede resolver estos problemas, ya que son linealmente separables.

---

# 6. El problema XOR

<div align="center">

![Dos fronteras para XOR](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/xor_perceptrones.png)

</div>

La función XOR produce:

| X1 | X2 | XOR |
|---:|---:|---:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

No existe una única línea recta capaz de separar correctamente los valores 1 de los valores 0.

Por ello:

> **Un único perceptrón no puede resolver XOR.**

Se necesitan varios perceptrones organizados en capas para construir fronteras de decisión más complejas.

Esto explica por qué las redes neuronales utilizan múltiples capas: permiten representar relaciones que un único perceptrón no puede representar.

---

# 7. Keras

## 7.1 Qué es y por qué importa

Keras es una librería que facilita la construcción y entrenamiento de redes neuronales. Permite definir arquitecturas, funciones de pérdida, optimizadores y métricas sin implementar manualmente todas las operaciones matemáticas.

---

# 8. Caso de uso: clasificación de reseñas de IMDB

Se utilizó el dataset IMDB para clasificar reseñas de películas como positivas o negativas.

```python
from keras.datasets import imdb

(train_data, train_labels), (test_data, test_labels) = imdb.load_data(
    num_words=10000,
    index_from=3
)
```

Las reseñas se transforman en vectores numéricos para que puedan ser procesadas por la red.

---

# 9. Modelo base

```python
model = models.Sequential()

model.add(
    layers.Dense(
        16,
        activation='relu',
        input_shape=(10000,)
    )
)

model.add(
    layers.Dense(
        16,
        activation='relu'
    )
)

model.add(
    layers.Dense(
        1,
        activation='sigmoid'
    )
)

model.compile(
    optimizer='rmsprop',
    loss='binary_crossentropy',
    metrics=['accuracy']
)
```

El modelo utiliza:

- **ReLU** en las capas ocultas.
- **Sigmoid** en la salida para clasificación binaria.
- **Binary Crossentropy** como función de pérdida.
- **Accuracy** como métrica de evaluación.

---

# 10. Pérdida de entrenamiento y validación

<div align="center">

![Pérdida entrenamiento vs. validación](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/loss_original.png)

</div>

### 10.0. Interpretación

La curva de **training** disminuye progresivamente desde aproximadamente 0.55 hasta valores cercanos a 0.01. Esto indica que el error sobre los datos de entrenamiento disminuye de manera continua.

En cambio, la curva de **validación** disminuye inicialmente, pero posteriormente comienza a aumentar y termina cerca de 0.55.

Este comportamiento es característico del **sobreajuste (overfitting)**.

El modelo continúa mejorando sobre los datos de entrenamiento, pero su rendimiento sobre datos de validación comienza a empeorar.

Esto significa que el modelo está aprendiendo cada vez mejor los ejemplos utilizados durante el entrenamiento, pero pierde capacidad de generalización.

Por ello, aumentar indefinidamente el número de épocas no necesariamente mejora el modelo.

---

# 11. Estrategias para reducir el sobreajuste

Se probaron diferentes estrategias:

1. **Reducir el tamaño del modelo:** disminuye el número de parámetros y limita la capacidad de memorizar.
2. **Regularización L2:** penaliza pesos demasiado grandes.
3. **Dropout:** desactiva aleatoriamente una proporción de neuronas durante el entrenamiento.

---

# 12. Dropout

<div align="center">

![Efecto del Dropout](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/loss_dropout.png)

</div>

### 12.0. Interpretación

La gráfica compara la pérdida de validación del modelo con **Dropout** frente al modelo original.

La curva con Dropout presenta inicialmente una pérdida menor y posteriormente comienza a aumentar. Esto indica que Dropout ayuda a reducir el sobreajuste durante parte del entrenamiento, aunque no lo elimina completamente.

Dropout obliga a la red a no depender demasiado de determinadas neuronas y favorece que el aprendizaje se distribuya entre diferentes partes de la red.

Por lo tanto, esta técnica puede mejorar la generalización, pero debe combinarse con otras decisiones de diseño y entrenamiento.

---

# 13. Qué aprendimos

- Una CNN analiza grupos de píxeles y conserva relaciones espaciales importantes.
- Las primeras capas pueden aprender bordes y patrones simples, mientras que capas posteriores pueden aprender características más complejas.
- El **transfer learning** permite aprovechar conocimiento aprendido previamente.
- **Grad-CAM** permite visualizar las regiones que influyen en una predicción.
- La matriz de confusión permite analizar aciertos y errores por clase.
- Un perceptrón individual puede resolver problemas linealmente separables como AND y OR, pero no XOR.
- Las redes multicapa permiten representar relaciones más complejas.
- El sobreajuste aparece cuando el modelo mejora sobre entrenamiento pero empeora sobre validación.
- **Dropout** y la regularización pueden ayudar a controlar el sobreajuste.
- Keras facilita la construcción y comparación de modelos de redes neuronales.

---

# 14. Aplicación al proyecto: evaluación no destructiva de la condición interna de la granadilla

### 14.0. ¿Cómo utilizaríamos Machine Learning en nuestro proyecto?

En nuestro proyecto de evaluación no destructiva de la condición interna de la granadilla mediante excitación vibratoria controlada, utilizaremos Machine Learning mediante aprendizaje supervisado.

La idea es que el sistema pueda aprender a partir de datos obtenidos experimentalmente. Primero se aplicará una excitación vibratoria controlada sobre la granadilla y se registrará su respuesta vibroacústica. A partir de esta señal se obtendrán diferentes características, como frecuencia, amplitud, energía y otras características relacionadas con su comportamiento vibratorio. También podemos incorporar la masa del fruto como una variable adicional.

Estas mediciones serán utilizadas como entradas del modelo:

`X = (X_vib, m)`

donde:
* X_vib representa las características de la respuesta vibroacústica.
* m representa la masa de la granadilla.

El modelo será entrenado utilizando granadillas cuya condición interna ya haya sido determinada experimentalmente. De esta manera, el algoritmo podrá aprender qué patrones de las señales están asociados a cada condición.

---

### 14.1. Funciones de Machine Learning en nuestro proyecto

1. **Aprendizaje de patrones:** El modelo analizará las características de las señales obtenidas y aprenderá relaciones entre el comportamiento vibroacústico y la condición interna de la granadilla.
2. **Clasificación:** Una vez entrenado, el modelo podrá clasificar una granadilla dentro de las categorías que definamos experimentalmente:
   * **0** → Condición A
   * **1** → Condición B
3. **Predicción:** Cuando se analice una nueva granadilla, el modelo recibirá sus características vibroacústicas y su masa para estimar su condición interna:

`ŷ = f(X_vib, m)`

donde ŷ (y con sombrero) representa la condición interna estimada.

4. **Evaluación:** El modelo será evaluado utilizando métricas como accuracy, precision, recall, F1-score y matriz de confusión, para determinar qué tan correctamente clasifica las diferentes condiciones.
5. **Generalización:** Una parte importante será comprobar que el modelo no solamente memorice las granadillas utilizadas durante el entrenamiento, sino que pueda reconocer correctamente nuevas granadillas que no haya visto anteriormente.

---

### 14.2. Modelos que utilizaríamos

Como primera etapa, utilizaríamos modelos de Machine Learning supervisado, como:
* **Random Forest**
* **SVM**
* **Regresión Logística**

Estos modelos nos permitirán establecer una línea base y determinar si las características vibroacústicas realmente permiten diferenciar las condiciones internas.

Posteriormente, si contamos con suficientes datos, podríamos comparar estos resultados con Deep Learning mediante una **CNN 1D**, que aprendería automáticamente patrones directamente de las señales vibroacústicas.

---

### 14.3. Flujo del proyecto
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
Procesamiento
   │
   ▼
Extracción de características + masa
   │
   ▼
Machine Learning supervisado
   │
   ▼
Aprendizaje de patrones
   │
   ▼
Clasificación / Predicción
   │
   ▼
Condición interna estimada
```


---

En resumen, Machine Learning será el encargado de aprender la relación entre la respuesta vibroacústica de la granadilla y su condición interna, para posteriormente clasificar y predecir la condición de nuevos frutos sin necesidad de abrirlos o destruirlos.

---

# 15. Conclusión

El taller permitió comprender diferentes conceptos fundamentales de las redes neuronales, desde el funcionamiento del perceptrón hasta arquitecturas más complejas como las CNN. También se analizaron técnicas como **Transfer Learning, Grad-CAM, regularización y Dropout**, que permiten mejorar el entrenamiento, evaluar el comportamiento del modelo e interpretar sus resultados.

En nuestro proyecto de **evaluación no destructiva de la condición interna de la granadilla**, aplicaremos **Machine Learning mediante aprendizaje supervisado**. El objetivo será aprender la relación entre las características obtenidas de la respuesta vibroacústica del fruto, junto con variables como su masa, y la condición interna determinada experimentalmente.

La función del Machine Learning será **aprender patrones, clasificar, predecir, evaluar y generalizar** la condición de nuevas granadillas a partir de las mediciones obtenidas.

La función del modelo puede representarse como:

`ŷ = f(X_vib, m)`

donde:

* **X_vib** representa las características de la respuesta vibroacústica.
* **m** representa la masa de la granadilla.
* **ŷ** representa la condición interna estimada.

Como primera etapa se evaluarán modelos de **Machine Learning supervisado**, como Random Forest, SVM y Regresión Logística, con el objetivo de establecer una línea base y determinar si las características vibroacústicas permiten diferenciar las condiciones internas.

Posteriormente, si la cantidad de datos obtenidos experimentalmente lo permite, se podrá comparar el rendimiento de estos modelos con una solución de **Deep Learning mediante una CNN 1D**, capaz de aprender automáticamente patrones directamente de las señales vibroacústicas.

De esta manera, los conocimientos adquiridos en el taller se relacionan directamente con el proyecto, permitiendo integrar:

**adquisición de señales → procesamiento → Machine Learning supervisado → clasificación/predicción → evaluación no destructiva**
