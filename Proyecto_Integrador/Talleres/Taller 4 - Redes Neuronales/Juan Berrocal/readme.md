# Redes Neuronales: CNN, Perceptrón y Keras
---

## CNN (Redes Neuronales Convolucionales)

### Qué son y por qué importan

Una CNN es básicamente una red pensada para "mirar" imágenes de una forma similar a como lo haría un ojo humano: no analiza cada píxel de forma aislada, sino que revisa grupos de píxeles vecinos buscando patrones como bordes, texturas y formas. Esto se logra mediante los **kernels**, pequeños filtros que recorren la imagen.

Lo importante es que una red normal, utilizando únicamente capas densas, trataría cada píxel como un dato independiente y podría perder parte de la información espacial. Una CNN, en cambio, conserva la relación entre los píxeles vecinos, lo que permite identificar patrones dentro de una imagen.

### Piezas clave

- **Convolución (Conv2D):** aplica los filtros y genera "mapas de características". Las primeras capas pueden detectar patrones simples, como bordes, mientras que las capas más profundas pueden identificar combinaciones más complejas, como texturas y formas.
- **Activación (ReLU):** permite que la red trabaje con relaciones no lineales. Los valores negativos se convierten en 0 y los positivos se mantienen.
- **Pooling (MaxPool):** reduce el tamaño de la información procesada, conservando las características más importantes y haciendo más liviano el cálculo.
- **Capas densas finales:** utilizan la información extraída por la CNN para realizar la clasificación final.

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
**Imagen del dataset**

![Ejemplos vidrio y plástico](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/ejemplos_vidrio_plastico.png)

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

**Imagen: Grad-CAM**

![Grad-CAM](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/grad_cam.png)

Muestra tres paneles: la imagen original, el mapa de calor y la superposición de ambos. Es la imagen más importante de esta sección porque es la que explica *por qué* el modelo decidió lo que decidió.

**Imagen: Matriz de confusión**

![Matriz de confusión](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/matriz_confusion.png)

### Interpretación

La matriz muestra cómo se comportó la CNN al clasificar las imágenes de **vidrio y plástico**:

- **54:** clasificó correctamente 54 imágenes de la clase 0.
- **22:** 22 imágenes de la clase 0 fueron clasificadas incorrectamente como clase 1.
- **36:** 36 imágenes de la clase 1 fueron clasificadas incorrectamente como clase 0.
- **37:** clasificó correctamente 37 imágenes de la clase 1.

En total, el modelo acertó **91 de 149 imágenes**, aproximadamente un **61 % de exactitud**.

**Interpretación:** el modelo logra reconocer algunos patrones para diferenciar vidrio y plástico, pero todavía presenta bastantes confusiones entre ambas clases. Esto indica que la CNN está aprendiendo, aunque todavía puede mejorar su capacidad de clasificación.

---

##  Perceptrón

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

**Imagen: fronteras de decisión OR/AND**

![Fronteras OR/AND](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/xor_or_and.png)

Pero con **XOR** (activa solo cuando las entradas son diferentes) un solo perceptrón no alcanza, porque no existe ninguna línea recta capaz de separar correctamente esos cuatro puntos. Este es probablemente el aprendizaje más importante de toda la sección: **un perceptrón solo resuelve problemas linealmente separables**. Para XOR se necesitan al menos dos perceptrones combinados en una capa de salida.

**Imagen: dos fronteras necesarias para XOR**

![Dos fronteras para XOR](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/xor_perceptrones.png)

Y aquí se entiende, de forma muy intuitiva, por qué existen las redes neuronales con múltiples capas: no es solo "para hacerlo más complejo", sino porque hay problemas que un solo perceptrón simplemente no puede resolver.

---

## Keras

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

**Imagen: pérdida en entrenamiento vs. validación**

![Pérdida entrenamiento vs. validación](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/loss_original.png)

### Probando soluciones al sobreajuste

Se probaron tres estrategias distintas, y comparar sus resultados es de lo más valioso del notebook:

1. **Reducir el tamaño del modelo** (menos neuronas): el sobreajuste sigue existiendo pero es menos pronunciado.
2. **Regularización L2**: penaliza a la red por tener pesos muy grandes, obligándola a generalizar mejor en vez de memorizar.
3. **Dropout**: apaga aleatoriamente el 50% de las neuronas durante el entrenamiento, forzando a la red a no depender de combinaciones específicas de neuronas.

![Efecto del Dropout](https://raw.githubusercontent.com/Cesarapcho/PI_Equipo_03/main/Proyecto_Integrador/Talleres/Taller%204%20-%20Redes%20Neuronales/Juan%20Berrocal/Imagenes/loss_dropout.png)

Ninguna de estas tres técnicas elimina el sobreajuste por completo, pero cada una lo controla de una manera distinta. Esto deja una idea clara: no existe una solución única, sino un conjunto de herramientas que se combinan según el problema.


## Qué aprendimos

- Una CNN no analiza píxeles sueltos, analiza vecindarios de píxeles, y eso es justo lo que la hace útil para imágenes.
- Entrenar desde cero funciona, pero **transfer learning** (aprovechar un modelo ya entrenado) da mejores resultados con muchísimo menos esfuerzo y datos.
- Un modelo que "acierta" no es suficiente: herramientas como Grad-CAM permiten confirmar si acierta por las razones correctas.
- Un perceptrón individual tiene un límite matemático real: no puede resolver problemas que no sean separables con una línea recta (como XOR). Por eso existen las redes con varias capas.
- El sobreajuste es casi inevitable en algún punto del entrenamiento, pero hay varias formas de mitigarlo (reducir el modelo, regularización, dropout), cada una con un efecto distinto.
- Keras permite iterar y comparar arquitecturas mucho más rápido que programar todo manualmente, lo cual es valioso justamente para hacer este tipo de comparaciones.

## Por qué es importante usarlo

Estas herramientas no son solo ejercicios académicos: representan el flujo real de trabajo en un proyecto de machine learning. Se empieza con un modelo simple para tener una base de comparación, se prueba si conviene reutilizar conocimiento ya existente (transfer learning), se revisa que el modelo esté aprendiendo por las razones correctas (interpretabilidad) y se ajustan técnicas para que el modelo generalice bien y no solo memorice (regularización, dropout). Sin este proceso, es fácil terminar con un modelo que parece funcionar bien en las pruebas pero falla apenas se usa con datos nuevos.

## Cómo implementarlo en nuestro proyecto

Pensando en aplicar lo aprendido en este taller a nuestro proyecto de **evaluación no destructiva de la calidad interna de la granadilla**, podemos utilizar Machine Learning para analizar las señales obtenidas mediante la excitación vibratoria/acústica y la medición de masa.

1. **Obtener los datos de las granadillas**, registrando la respuesta acústica generada por la excitación controlada y la masa de cada fruto.

2. **Procesar las señales obtenidas**, extrayendo características que puedan estar relacionadas con las diferencias en la condición interna de la granadilla.

3. **Entrenar un modelo de Machine Learning** utilizando las características obtenidas para identificar patrones y clasificar la condición interna del fruto.

4. **Evaluar diferentes modelos**, incluyendo redes neuronales, para determinar cuál puede adaptarse mejor a las características de nuestros datos.

5. **Analizar e interpretar los resultados**, verificando si las características de la señal realmente permiten diferenciar las distintas condiciones internas de la granadilla.

6. **Integrar el modelo al sistema**, de manera que las mediciones obtenidas por el hardware puedan ser procesadas por el software y generar una clasificación de la condición interna sin necesidad de abrir o dañar el fruto.
