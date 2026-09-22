# Redes Neuronales: CNN, Perceptrón y Keras

Este resumen recoge lo trabajado en el notebook de redes neuronales, explicado con mis propias palabras para entender no solo el "qué" sino el "para qué" de cada técnica.

---

## 🧩 CNN (Redes Neuronales Convolucionales)

### Qué son y por qué importan

Una CNN es básicamente una red pensada para "mirar" imágenes de la misma forma en que lo haría un ojo humano: no analiza cada píxel de forma aislada, sino que revisa grupos de píxeles vecinos buscando patrones (bordes, texturas, formas). Eso se logra con los **kernels**, pequeños filtros que recorren la imagen entera.

Lo importante de esto es que una red normal (solo capas densas) trataría cada píxel como un dato independiente, perdiendo toda la información espacial. Una CNN, en cambio, conserva esa relación de vecindad, que es justo lo que hace que una imagen tenga sentido para nosotros.

### Piezas clave

- **Convolución (Conv2D):** aplica los filtros y genera "mapas de características". Las primeras capas detectan cosas simples (bordes), las capas más profundas detectan combinaciones más complejas (texturas, formas, objetos).
- **Activación (ReLU):** decide qué información "vale la pena" seguir pasando. Si el valor es negativo lo apaga (0), si es positivo lo deja pasar igual. Es simple pero funciona sorprendentemente bien.
- **Pooling (MaxPool):** reduce el tamaño de la imagen sin perder lo importante. Ayuda a que el modelo no memorice detalles innecesarios y a que el cálculo sea más liviano.
- **Capas densas finales:** toman toda la información ya procesada y la usan para decidir la clasificación final.

### Código relevante

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

Esta CNN se entrenó desde cero para clasificar imágenes de **vidrio vs. plástico** (dataset TrashNet). Sola, sin ayuda de ningún modelo previo, llegó a un 63% de exactitud aproximadamente, con un ROC-AUC alrededor de 0.67-0.69. No es un resultado espectacular, pero muestra que sí está aprendiendo algo real, solo que de forma limitada por lo pequeño del dataset.

### Transfer Learning: la mejora real

Aquí está uno de los aprendizajes más importantes del notebook: en vez de entrenar una CNN desde cero, se puede aprovechar un modelo ya entrenado en millones de imágenes (ResNet18) y solo ajustar la última capa a nuestro problema.

```python
resnet = models.resnet18(weights=models.ResNet18_Weights.DEFAULT)
resnet.fc = nn.Linear(resnet.fc.in_features, num_classes)

for name, param in resnet.named_parameters():
    param.requires_grad = False
for param in resnet.fc.parameters():
    param.requires_grad = True
```

Después se hizo **fine-tuning**, descongelando las últimas capas (`layer4`) para que el modelo se ajustara un poco más a nuestras imágenes específicas. El resultado fue notoriamente mejor que la CNN entrenada desde cero, lo cual tiene sentido: ResNet ya "sabe" reconocer bordes, texturas y formas generales, y solo tuvo que aprender a aplicar ese conocimiento a distinguir vidrio de plástico.

### Interpretabilidad: Grad-CAM

Uno de los puntos más interesantes es que un modelo no debería ser una "caja negra". Con Grad-CAM se puede generar un mapa de calor que muestra **qué zonas de la imagen influyeron más en la predicción**.

```python
def grad_cam(model, image_tensor, target_class=None):
    ...
    weights = torch.mean(grad, dim=(1, 2))
    cam = torch.sum(weights[:, None, None] * act, dim=0)
    cam = torch.relu(cam)
    cam = cam - cam.min()
    cam = cam / (cam.max() + 1e-8)
    return cam.detach().cpu().numpy(), target_class
```

En las imágenes resultantes, las zonas más claras/amarillas indican mayor peso en la decisión del modelo, mientras que las zonas oscuras aportaron poco. Esto es clave porque permite confirmar (o desmentir) si el modelo realmente está "mirando" el objeto correcto, y no aprendiendo atajos raros del fondo de la imagen.

**Imagen: Grad-CAM (`images/grad_cam.png`)**

Muestra tres paneles: la imagen original, el mapa de calor y la superposición de ambos. Es la imagen más importante de esta sección porque es la que explica *por qué* el modelo decidió lo que decidió.

**Imagen: Matriz de confusión (`images/matriz_confusion.png`)**

Resume en una sola tabla visual cuántas predicciones fueron correctas y cuántas se confundieron entre vidrio y plástico.

---

## 🔵 Perceptrón

### Qué es y por qué importa

El perceptrón es la unidad más básica de una red neuronal: toma varias entradas, las multiplica por unos pesos, suma un sesgo (bias) y pasa ese resultado por una función de activación. Es literalmente el "ladrillo" con el que se construyen redes mucho más complejas, así que entenderlo bien ayuda a entender todo lo demás.

```python
def perceptron(inputs, weights, bias, activation_func):
    weighted_sum = np.dot(inputs, weights) + bias
    output = activation_func(weighted_sum)
    return output
```

### Ejemplo aplicado: alerta de sobrecalentamiento

Se probó el perceptrón con un caso concreto: decidir si un equipo industrial está en riesgo de sobrecalentamiento según su temperatura y vibración.

```python
temperatura = 100
vibracion = 50
weights = np.array([0.5, -0.5])
bias = -30
inputs = np.array([temperatura, vibracion])
```

Aquí se ve algo importante: la función de activación cambia por completo cómo se interpreta la salida. Con la función escalón el resultado es binario (alerta sí/no), mientras que con tanh el resultado queda entre -1 y 1, dando una especie de "intensidad" de la alerta en vez de solo un sí o no.

### Compuertas lógicas: AND, OR y el límite del perceptrón (XOR)

Probando distintos pesos, un solo perceptrón puede comportarse como una compuerta **AND** (solo activa si ambas entradas son 1) o **OR** (activa si al menos una entrada es 1). Esto se puede visualizar como una línea recta que separa los casos positivos de los negativos.

**Imagen: fronteras de decisión OR/AND (`images/xor_or_and.png`)**

Pero con **XOR** (activa solo cuando las entradas son diferentes) un solo perceptrón no alcanza, porque no existe ninguna línea recta capaz de separar correctamente esos cuatro puntos. Este es probablemente el aprendizaje más importante de toda la sección: **un perceptrón solo resuelve problemas linealmente separables**. Para XOR se necesitan al menos dos perceptrones combinados en una capa de salida.

**Imagen: dos fronteras necesarias para XOR (`images/xor_perceptrones.png`)**

Y aquí se entiende, de forma muy intuitiva, por qué existen las redes neuronales con múltiples capas: no es solo "para hacerlo más complejo", sino porque hay problemas que un solo perceptrón simplemente no puede resolver.

---

## 🟠 Keras

### Qué es y por qué importa

Keras es una librería que permite construir y entrenar redes neuronales sin tener que programar manualmente cada operación matemática (como sí se hace con PyTorch a bajo nivel). Esto vuelve el proceso mucho más rápido de prototipar, algo muy útil cuando se está probando distintas arquitecturas.

### Caso de uso: clasificación de reseñas de IMDB

Se trabajó con reseñas de películas para clasificarlas como positivas o negativas.

```python
from keras.datasets import imdb
(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000, index_from=3)
```

Las reseñas vienen como secuencias de números (cada número representa una palabra), así que primero hay que transformarlas en vectores que el modelo pueda entender:

```python
def vectorizar(sequences, dim=10000):
    restults = np.zeros((len(sequences), dim))
    for i, sequences in enumerate(sequences):
        restults[i, sequences] = 1
    return restults
```

Cada reseña se convierte en un vector de 10,000 posiciones donde un 1 indica que esa palabra apareció y un 0 que no. Es una simplificación, pero suficiente para este problema.

### El modelo base

```python
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

model.compile(optimizer='rmsprop',
              loss='binary_crossentropy',
              metrics=['accuracy'])
```

Con este modelo se llegó a una exactitud de 86.1% en test, aunque con un problema claro: **sobreajuste**. Se ve en la gráfica de pérdida cuando la curva de entrenamiento sigue bajando pero la de validación deja de mejorar (o incluso empeora).

**Imagen: pérdida en entrenamiento vs. validación (`images/loss_original.png`)**

### Probando soluciones al sobreajuste

Se probaron tres estrategias distintas, y comparar sus resultados es de lo más valioso del notebook:

1. **Reducir el tamaño del modelo** (menos neuronas): el sobreajuste sigue existiendo pero es menos pronunciado.
   `images/loss_comparacion_tamano.png`
2. **Regularización L2**: penaliza a la red por tener pesos muy grandes, obligándola a generalizar mejor en vez de memorizar.
   `images/loss_regularizacion.png`
3. **Dropout**: apaga aleatoriamente el 50% de las neuronas durante el entrenamiento, forzando a la red a no depender de combinaciones específicas de neuronas.
   `images/loss_dropout.png`

Ninguna de estas tres técnicas elimina el sobreajuste por completo, pero cada una lo controla de una manera distinta. Esto deja una idea clara: no existe una solución única, sino un conjunto de herramientas que se combinan según el problema.

---

## 🖼️ Imágenes importantes y cómo guardarlas

Todas las imágenes usadas en este resumen ya están guardadas en la carpeta `images/` junto a este documento. Estas son las más relevantes y por qué:

| Imagen | Qué muestra | Por qué es importante |
|---|---|---|
| `grad_cam.png` | Mapa de calor sobre una imagen real | Explica en qué se fijó el modelo para decidir |
| `matriz_confusion.png` | Aciertos y errores del modelo CNN | Resume el desempeño real, no solo un número |
| `ejemplos_vidrio_plastico.png` | Muestras del dataset TrashNet | Contexto de qué está viendo el modelo |
| `xor_or_and.png` | Fronteras de decisión de AND/OR | Muestra el límite lineal de un perceptrón |
| `xor_perceptrones.png` | Solución de XOR con dos rectas | Explica por qué se necesitan varias capas |
| `loss_original.png` | Sobreajuste del modelo Keras base | Punto de partida para comparar mejoras |
| `loss_dropout.png` | Efecto del Dropout sobre la pérdida | Muestra una técnica anti-sobreajuste en acción |

Si se quiere volver a generar o guardar estas imágenes desde el propio notebook, basta con correr las celdas que llaman a `plt.show()` y, justo antes, agregar una línea como:

```python
plt.savefig("images/nombre_de_la_imagen.png", dpi=150, bbox_inches="tight")
```

Eso guarda la figura en disco antes de mostrarla, sin cambiar nada más del código.

---

## 📚 Qué aprendimos

- Una CNN no analiza píxeles sueltos, analiza vecindarios de píxeles, y eso es justo lo que la hace útil para imágenes.
- Entrenar desde cero funciona, pero **transfer learning** (aprovechar un modelo ya entrenado) da mejores resultados con muchísimo menos esfuerzo y datos.
- Un modelo que "acierta" no es suficiente: herramientas como Grad-CAM permiten confirmar si acierta por las razones correctas.
- Un perceptrón individual tiene un límite matemático real: no puede resolver problemas que no sean separables con una línea recta (como XOR). Por eso existen las redes con varias capas.
- El sobreajuste es casi inevitable en algún punto del entrenamiento, pero hay varias formas de mitigarlo (reducir el modelo, regularización, dropout), cada una con un efecto distinto.
- Keras permite iterar y comparar arquitecturas mucho más rápido que programar todo manualmente, lo cual es valioso justamente para hacer este tipo de comparaciones.

## 🎯 Por qué es importante usarlo

Estas herramientas no son solo ejercicios académicos: representan el flujo real de trabajo en un proyecto de machine learning. Se empieza con un modelo simple para tener una base de comparación, se prueba si conviene reutilizar conocimiento ya existente (transfer learning), se revisa que el modelo esté aprendiendo por las razones correctas (interpretabilidad) y se ajustan técnicas para que el modelo generalice bien y no solo memorice (regularización, dropout). Sin este proceso, es fácil terminar con un modelo que parece funcionar bien en las pruebas pero falla apenas se usa con datos nuevos.

## 🏗️ Cómo implementarlo en nuestro proyecto

Pensando en aplicar esto a un proyecto propio, el camino natural sería:

1. **Definir el problema como clasificación de imágenes o de texto**, según el caso, y preparar los datos en el mismo formato que se usó aquí (tensores normalizados para imágenes, o vectorización one-hot para texto).
2. **Empezar con un modelo base simple** (como la `SimpleCNN` o el modelo Keras de 2 capas) solo para tener un punto de referencia de qué tan difícil es el problema.
3. **Si hay pocos datos, usar transfer learning** en vez de entrenar desde cero, tal como se hizo con ResNet18, ajustando solo las últimas capas a nuestro caso específico.
4. **Aplicar técnicas anti-sobreajuste** (dropout, regularización, o reducir el tamaño del modelo) apenas se detecte que la curva de validación se separa de la de entrenamiento.
5. **Agregar interpretabilidad** (Grad-CAM u otra técnica similar) antes de confiar en el modelo para algo importante, para verificar que las predicciones tengan sentido y no sean casualidad.
6. **Guardar los modelos entrenados** con `torch.save()` (o el equivalente en Keras) para no tener que reentrenar cada vez que se quiera usar el modelo.

En resumen: no se trata de copiar el código tal cual, sino de replicar el proceso completo —modelo base, mejora con transfer learning, control de sobreajuste e interpretación de resultados— adaptado a los datos específicos de nuestro proyecto.
