# Redes Neuronales: CNN, Perceptrón y Keras

---

## 1. ¿Qué se realizó en este documento?

El notebook trabajado (*Redes_neuronales_ss*) es un recorrido práctico por tres formas distintas de "enseñarle" a una computadora a tomar decisiones a partir de datos:

1. **CNN (Redes Neuronales Convolucionales):** se construyó, entrenó y evaluó un modelo desde cero para clasificar imágenes de **vidrio vs. plástico** (dataset TrashNet), se probó *data augmentation*, luego **transfer learning** con ResNet18, y finalmente se interpretaron las decisiones del modelo con **Grad-CAM**.
2. **Keras:** se usó una librería de más alto nivel para resolver un problema distinto —clasificar **reseñas de películas (IMDB)** en positivas o negativas— explorando el sobreajuste (*overfitting*), la regularización L2 y el *dropout*.
3. **Perceptrón:** se programó desde cero la unidad más simple de una red neuronal, probando funciones de activación (escalón y tanh) y compuertas lógicas (AND, OR, XOR) para entender *por qué* existen las redes con varias capas.

En otras palabras: primero se vio "la neurona sola" (perceptrón), luego "muchas neuronas ya armadas por una librería" (Keras) y finalmente "neuronas especializadas en ver imágenes" (CNN). Es una progresión pensada para entender de lo simple a lo complejo.

---

## 2. CNN (Convolutional Neural Networks)

### 2.1. ¿Qué son?

Una CNN funciona parecido a como una persona reconoce un objeto: no mira el objeto entero de golpe, sino que va identificando **pequeños patrones locales** (bordes, texturas, curvas) y los combina progresivamente hasta reconocer la figura completa. Los **kernels** (filtros) son justamente esos "detectores de patrones" que recorren la imagen pixel por pixel.

### 2.2. Componentes clave usados en el notebook

| Componente | Qué hace | Analogía humana |
|---|---|---|
| **Conv2D** | Aplica filtros que detectan bordes, texturas y formas | Como entrecerrar los ojos y notar "aquí hay un borde" |
| **ReLU** | `ReLU(x) = max(0, x)`: apaga las activaciones negativas | Ignorar información irrelevante y quedarse con lo que "sí aporta" |
| **MaxPool** | Reduce la resolución conservando lo más importante | Resumir una imagen sin perder la idea principal |
| **Fully Connected (clasificador)** | Combina todas las características para decidir la clase final | Es la "conclusión" tras haber observado todos los detalles |

### 2.3. Código relevante: la CNN construida desde cero

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
        # ... capa clasificadora final (Fully Connected)
```

Cada bloque `Conv2D + ReLU + MaxPool` va "resumiendo" la imagen: empieza viendo 1 canal (escala de grises) y termina con 64 mapas de características mucho más pequeños pero mucho más ricos en información.

### 2.4. Imágenes importantes y su interpretación

**a) Muestra del dataset (vidrio vs. plástico)**

![Ejemplos del dataset](imgs/dataset_glass_plastic.png)

*Interpretación:* son las imágenes reales con las que la CNN aprendió. Nótese que están en escala de grises y con distintos ángulos/formas —esto obliga al modelo a aprender características **robustas** (brillo, transparencia, forma de botella aplastada) y no solo memorizar una foto puntual.

**b) Curvas de entrenamiento (CNN desde cero)**

![Curva de pérdida](imgs/cnn_loss_curve.png)
![Curva de métricas](imgs/cnn_metrics_curve.png)

*Interpretación:* la pérdida (*loss*) baja progresivamente, lo cual significa que el modelo se equivoca cada vez menos en el set de entrenamiento. El *accuracy* llega a ~63% y el ROC-AUC se mantiene entre 0.67–0.69: hay aprendizaje, pero es **moderado**, no espectacular —una CNN entrenada desde cero con pocos datos tiene un techo bajo.

**c) Matriz de confusión**

![Matriz de confusión](imgs/confusion_matrix_cnn.png)

*Interpretación:* muestra cuántas veces el modelo acertó y en cuáles casos confundió vidrio con plástico. Es la forma más honesta de ver el desempeño real, porque el *accuracy* solo puede esconder un modelo que "le atina" mucho a una clase y falla en la otra.

**d) Grad-CAM (interpretabilidad)**

![Grad-CAM](imgs/gradcam.png)

*Interpretación:* esta es, quizás, la imagen más importante del notebook porque responde la pregunta *"¿en qué se está fijando la red para decidir?"*. Las zonas amarillas/claras son las que más influyeron en la predicción; las moradas/oscuras casi no importaron. Aquí el modelo se concentró en el **cuerpo central de la botella**, lo cual tiene sentido humano: es donde está la mayor cantidad de textura/transparencia distintiva del vidrio.

### 2.5. Transfer Learning: el salto de calidad

Cuando se reemplazó la CNN "hecha a mano" por **ResNet18 preentrenada** (ya sabe reconocer bordes, texturas y formas generales de millones de imágenes) y solo se ajustaron sus últimas capas, el resultado saltó de **57.7% a 87.25% de accuracy**, y el ROC-AUC subió de 0.61 a 0.96. Esto demuestra en la práctica una idea clave: **no siempre hay que entrenar desde cero**; reutilizar conocimiento ya aprendido (por otro modelo, con otro dataset) puede ser mucho más eficiente que empezar de la nada, sobre todo cuando se tienen pocos datos propios.

---

## 3. Perceptrón

### 3.1. ¿Qué es?

El perceptrón es la **neurona artificial más simple**: toma varias entradas, las pondera (multiplica por "pesos" que indican qué tan importante es cada una), suma todo, le agrega un sesgo (*bias*) y aplica una función de activación para decidir una salida. Es, literalmente, la versión mínima de "tomar una decisión basada en varios factores con distinta importancia".

### 3.2. Código relevante

```python
def step_function(x):
    return 1 if x >= 0 else 0

def tanh_activation(x):
    return np.tanh(x)

def perceptron(inputs, weights, bias, activation_func):
    weighted_sum = np.dot(inputs, weights) + bias
    return activation_func(weighted_sum)
```

**Ejemplo aplicado: detección de sobrecalentamiento industrial**

```python
temperatura = 100
vibracion = 50
weights = np.array([0.5, -0.5])
bias = -30
inputs = np.array([temperatura, vibracion])

output_step = perceptron(inputs, weights, bias, step_function)
output_tanh = perceptron(inputs, weights, bias, tanh_activation)
```

*Interpretación:* este ejemplo es clave porque es exactamente el tipo de problema que se busca resolver con las granadillas: **combinar dos variables físicas (temperatura y vibración) con pesos distintos para tomar una decisión binaria (alerta / no alerta)**.

### 3.3. Funciones de activación: la diferencia importa

- **Función escalón:** da una respuesta *dura* (0 o 1). Útil cuando se necesita una decisión tajante ("hay alerta" / "no hay alerta").
- **Función tanh:** da una respuesta *suave*, entre -1 y 1. Permite matices ("qué tan cerca está del límite"), no solo un sí/no.

### 3.4. Compuertas lógicas: por qué un perceptrón no basta

![Frontera de decisión OR/AND](imgs/perceptron_plano.png)

*Interpretación:* aquí se ven los 4 posibles puntos (0,0), (0,1), (1,0), (1,1). Con distintos pesos y sesgos, un solo perceptrón logra separar estos puntos con **una línea recta** para simular una compuerta AND o una OR.

![XOR no es separable linealmente](imgs/perceptron_xor.png)

*Interpretación:* esta imagen es la más importante de la sección de perceptrón. Los círculos blancos son los casos XOR = 0 y los puntos azules XOR = 1. **Ninguna línea recta puede separar estos puntos** correctamente —por eso 1 solo perceptrón no puede resolver XOR. Se necesitan **2 perceptrones + una capa de salida**, es decir, una red con más de una capa. Esta es la razón histórica y conceptual por la que existen las redes neuronales *multicapa*: hay problemas que simplemente no son resolubles con una sola neurona, sin importar qué pesos se usen.

---

## 4. Keras

### 4.1. ¿Qué es?

Si el perceptrón es "programar una neurona a mano" y la CNN en PyTorch es "armar capa por capa con más control", **Keras** es la herramienta que permite construir y entrenar redes neuronales **sin tener que programar cada operación matemática**. Es como pasar de construir un mueble con herramientas manuales a usar una fábrica con piezas prearmadas: se pierde algo de control fino, pero se gana muchísima velocidad y menos errores.

### 4.2. Código relevante: clasificación binaria de reseñas (IMDB)

```python
from keras import models, layers

model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

model.compile(optimizer='rmsprop',
              loss='binary_crossentropy',
              metrics=['accuracy'])

model.fit(partial_x_train, partial_y_train,
          epochs=20, batch_size=512,
          validation_data=(x_val, y_val))
```

*Interpretación:* en apenas 6 líneas se define una red completa (2 capas ocultas de 16 neuronas + 1 capa de salida), se configura cómo va a aprender (optimizador, función de pérdida) y se entrena. Esto sería mucho más largo de programar "a mano" como se hizo con el perceptrón.

### 4.3. Imágenes importantes y su interpretación

**a) Sobreajuste (overfitting) — modelo original**

![Pérdida modelo original](imgs/keras_loss_original.png)

*Interpretación:* la curva azul (entrenamiento) sigue bajando, pero la naranja (validación) deja de mejorar e incluso empeora. Esto es **sobreajuste**: el modelo está memorizando las reseñas de entrenamiento en vez de aprender patrones generales del lenguaje, por lo que pierde capacidad de generalizar a datos nuevos.

**b) Reducir el tamaño del modelo**

![Modelo más pequeño vs original](imgs/keras_loss_smaller.png)

*Interpretación:* con menos neuronas (4 en vez de 16), el sobreajuste sigue existiendo, pero tarda más en aparecer y es menos pronunciado. Un modelo más simple tiene menos "capacidad de memorizar", así que se ve obligado a aprender patrones más generales.

**c) Regularización L2**

![Regularización L2](imgs/keras_loss_regularization.png)

*Interpretación:* la regularización penaliza los pesos muy grandes, obligando al modelo a mantener explicaciones "más simples". Por eso el error de validación se mantiene más estable, aunque a veces se ve un pico porque el modelo tiene que balancear ajustarse a los datos vs. mantenerse simple.

**d) Dropout**

![Dropout](imgs/keras_loss_dropout.png)

*Interpretación:* al apagar aleatoriamente el 50% de las neuronas durante el entrenamiento, la red no puede depender de una combinación específica de neuronas y se ve forzada a aprender representaciones redundantes y más generales. Es, en términos humanos, como entrenar a un equipo donde cualquier persona puede faltar un día y el trabajo igual debe salir bien.

---

## 5. Funciones importantes usadas en el notebook

| Función / clase | Propósito |
|---|---|
| `nn.Conv2d`, `nn.MaxPool2d`, `nn.ReLU` (PyTorch) | Construcción de capas convolucionales |
| `DataLoader` | Maneja el *batching* y el mezclado (*shuffle*) de los datos |
| `train_one_epoch` / `evaluate` | Funciones propias para entrenar y medir el desempeño (accuracy, ROC-AUC, matriz de confusión) |
| `grad_cam()` | Genera el mapa de calor de interpretabilidad |
| `models.Sequential`, `layers.Dense` (Keras) | Construcción rápida de redes neuronales densas |
| `model.compile`, `model.fit`, `model.evaluate`, `model.predict` | Ciclo completo de entrenamiento y uso del modelo en Keras |
| `regularizers.l2`, `layers.Dropout` | Técnicas para reducir el sobreajuste |
| `perceptron()`, `step_function()`, `tanh_activation()` | Implementación manual de una neurona con distintas activaciones |

---

## 6. ¿Qué aprendimos?

- Una sola neurona (perceptrón) puede resolver problemas **linealmente separables** (AND, OR), pero **no** problemas como XOR; para eso se necesitan varias capas.
- La función de activación cambia completamente el tipo de respuesta que da un modelo: **dura** (escalón) vs. **suave/gradual** (tanh/sigmoide).
- Entrenar una CNN desde cero con pocos datos da resultados limitados (~58–63% accuracy); usar **transfer learning** con un modelo preentrenado puede disparar el rendimiento (hasta 87% en este caso) con mucho menos esfuerzo.
- El **sobreajuste** es uno de los mayores riesgos al entrenar redes neuronales, y existen técnicas concretas para combatirlo: reducir el tamaño del modelo, regularización L2 y dropout.
- **Grad-CAM** permite "abrir la caja negra" y verificar si el modelo se está fijando en zonas razonables de la imagen, lo cual es clave para confiar (o no) en sus predicciones.
- **Keras** permite construir y entrenar redes neuronales con muchísimo menos código que hacerlo manualmente, ideal para prototipar rápido.

## 7. ¿Por qué es importante usarlo?

Porque estas herramientas permiten pasar de **datos crudos** (imágenes, señales, números) a **decisiones automatizadas y consistentes**, sin necesidad de programar reglas manuales para cada caso posible. Además:

- Permiten **cuantificar la confianza** de una predicción (probabilidades, no solo un sí/no).
- Ofrecen formas de **verificar que el modelo no está "haciendo trampa"** (Grad-CAM, matriz de confusión, curvas de validación).
- Escalan bien: lo mismo que se usa para clasificar reseñas de cine o basura reciclable, se puede adaptar a **cualquier otro problema de clasificación**, incluyendo señales físicas de sensores.

---

## 8. Aplicación al proyecto de las granadillas 🍈

### 8.1. El problema

El objetivo es **determinar la calidad de una granadilla** combinando dos tipos de información:

1. **Peso** de la fruta (variable numérica simple).
2. **Vibraciones acústicas** captadas por sensores **piezoeléctricos** al golpear o excitar la fruta (una señal más compleja, tipo onda).

### 8.2. ¿Dónde encaja cada concepto del notebook?

**a) Perceptrón — primera aproximación, simple e interpretable**

Así como en el notebook se combinó *temperatura* y *vibración* para decidir una alerta de sobrecalentamiento, se puede construir un primer perceptrón que combine:

```python
inputs = np.array([peso, energia_vibracion])
weights = np.array([w1, w2])   # a aprender o calibrar
bias = b

calidad = perceptron(inputs, weights, bias, step_function)
# 1 = granadilla de buena calidad / 0 = mala calidad
```

Esto sirve como **prueba de concepto rápida y explicable**: cada peso indica literalmente "qué tan importante es el peso" vs. "qué tan importante es la vibración" para decidir la calidad. Si luego se necesitan más de 2 categorías de calidad (por ejemplo: primera, segunda, descarte) o la relación entre peso/vibración y calidad no es linealmente separable —igual que el caso XOR—, será necesario pasar a una red con más capas (Keras).

**b) Keras — cuando el problema crece en complejidad**

Si se agregan más variables (peso, varias métricas de la señal acústica: frecuencia dominante, amplitud, duración del eco, etc.) o más categorías de calidad, conviene migrar del perceptrón a una red Keras tipo:

```python
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(n_variables,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(n_categorias, activation='softmax'))  # varias clases de calidad

model.compile(optimizer='rmsprop',
              loss='categorical_crossentropy',
              metrics=['accuracy'])
```

Aquí también aplican directamente las lecciones del notebook: vigilar el **sobreajuste** comparando la curva de entrenamiento vs. validación (más relevante aún porque en campo se tendrán pocos datos etiquetados de granadillas), y usar **dropout** o **regularización L2** si el modelo empieza a memorizar en vez de generalizar.

**c) CNN — si se trabaja la señal acústica como "imagen"**

La señal de vibración captada por el piezoeléctrico se puede transformar en un **espectrograma** (una imagen que representa cómo varía la frecuencia de la vibración en el tiempo). Convertido a imagen, se le puede aplicar exactamente el mismo enfoque de CNN visto con vidrio/plástico:

- Cada espectrograma sería una "imagen" de entrada (como las fotos de botellas).
- La CNN aprendería a detectar patrones de frecuencia/textura asociados a fruta madura, verde o dañada, igual que aprendió a distinguir texturas de vidrio y plástico.
- Al ser pocos datos propios de granadillas, **transfer learning** (como se hizo con ResNet18) sería especialmente útil: partir de un modelo ya entrenado en audio o imágenes generales y solo ajustar las últimas capas con los datos propios del proyecto.
- **Grad-CAM** permitiría verificar en qué parte del espectrograma se está fijando el modelo para decidir la calidad —por ejemplo, confirmar que se fija en las frecuencias asociadas a golpes internos o cavidades, y no en ruido de fondo del sensor.

### 8.3. Resumen de la propuesta

| Etapa del proyecto | Herramienta sugerida | Por qué |
|---|---|---|
| Prototipo inicial rápido (peso + 1-2 métricas de vibración) | **Perceptrón** | Simple, explicable, pocos datos necesarios |
| Modelo con varias variables/categorías de calidad | **Keras (red densa)** | Rápido de construir, permite controlar sobreajuste |
| Análisis de la señal acústica como espectrograma | **CNN (+ transfer learning)** | Aprovecha patrones espaciales/frecuenciales complejos |
| Validar que el modelo decide por razones correctas | **Grad-CAM / matriz de confusión** | Da confianza para usarlo en producción con fruta real |

En conjunto, el notebook trabajado no solo enseña "cómo se programa" cada técnica, sino que deja una **ruta de decisión clara**: empezar simple (perceptrón), escalar en complejidad cuando el problema lo exige (Keras), y usar CNN cuando los datos tienen una estructura espacial o de patrón (como un espectrograma de vibraciones), siempre verificando el desempeño real con métricas honestas y, cuando sea posible, interpretando visualmente las decisiones del modelo.
