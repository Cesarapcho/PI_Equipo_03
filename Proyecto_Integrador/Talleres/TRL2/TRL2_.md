# TRL 2 – Formulación del Concepto Tecnológico de Ligura

## 1. Introducción

### 1.1 ¿Qué representa el TRL 2?

El TRL 2 corresponde a la etapa de investigación aplicada en la que los principios científicos identificados previamente se relacionan con una posible aplicación tecnológica. En este nivel se define el concepto de la solución, se describe su funcionamiento previsto y se sustenta su desarrollo mediante antecedentes científicos y tecnológicos.

Las principales evidencias consideradas son los artículos científicos relacionados con la propuesta, el análisis preliminar de patentabilidad y protección, y la formulación de un perfil o propuesta de proyecto.

En Ligura, esta etapa permite establecer cómo se combinarían la excitación vibratoria controlada, la medición de masa y el análisis de señales para investigar la condición interna de la granadilla.

### 1.2 Antecedentes provenientes del TRL 1

Durante el TRL 1 se revisaron los principios científicos relacionados con la evaluación no destructiva de frutos mediante su respuesta acústica y vibratoria. Se identificaron antecedentes que estudian la relación entre las características del espectro de frecuencia y determinadas propiedades o alteraciones internas de los frutos.

Asimismo, se consideraron los principios de transducción piezoeléctrica, medición de masa y procesamiento de señales mediante la transformada rápida de Fourier (FFT). Estos fundamentos orientan la selección de los elementos necesarios para aplicar una vibración, registrar la respuesta y analizar sus características.

A partir de esta revisión, Ligura plantea investigar si la respuesta vibroacústica de la granadilla (*Passiflora ligularis*), analizada junto con su masa, permite distinguir frutos con y sin zonas de oscurecimiento visible en la pulpa. La lectura de un sensor resistivo de fuerza (FSR) se considera para supervisar el contacto de la pinza durante la medición.

### 1.3 Objetivo del TRL 2

El objetivo de esta etapa es formular y sustentar el concepto tecnológico de **Ligura**, una propuesta de sistema para la evaluación no destructiva de granadillas mediante excitación vibratoria controlada, adquisición de la respuesta piezoeléctrica, medición de masa y análisis en frecuencia.

Para ello, se analizarán antecedentes científicos y tecnológicos relacionados con la evaluación de frutos, se definirá la arquitectura conceptual del sistema y se establecerán sus funciones y requisitos principales. También se documentarán las alternativas de diseño, se planteará la interfaz del dashboard en Figma y se desarrollará un análisis preliminar de patentabilidad y protección.

Como resultado, se obtendrá una propuesta que oriente las pruebas posteriores para investigar la relación entre las mediciones y el oscurecimiento observado en la pulpa de cada granadilla.

## 2. Estado del arte de la propuesta tecnológica

### 2.1 Evaluación no destructiva mediante respuesta acústica y vibratoria

La evaluación acústica y vibratoria de frutos permite investigar sus propiedades internas a partir de la respuesta que producen ante un estímulo mecánico. Los antecedentes seleccionados estudian cómo las características del espectro se relacionan con alteraciones internas o mediciones de firmeza.

Diezma-Iglesias, Ruiz-Altisent y Barreiro desarrollaron un procedimiento para detectar alteraciones internas en sandías sin semillas mediante respuesta acústica a un impacto. Su dispositivo integró un generador de impacto mecánico, un micrófono y elementos estructurales de soporte. Los parámetros obtenidos al sumar la magnitud del espectro dentro de determinadas bandas de frecuencia mostraron capacidad para identificar alteraciones internas [[1]](#ref1).

Este antecedente respalda la decisión de explorar características espectrales en Ligura. En particular, orienta el análisis de la magnitud por bandas de frecuencia, además de la identificación del pico dominante. Las bandas que resulten pertinentes para la granadilla deberán determinarse mediante mediciones propias.

### 2.2 Análisis espectral y control de las condiciones de medición

Tian, Wang y Xu desarrollaron un dispositivo para estimar la firmeza del kiwi mediante tecnología de vibración acústica. Para mantener condiciones de excitación comparables, calibraron la fuerza del impacto. Posteriormente, transformaron las señales al dominio de frecuencia y extrajeron diez características estadísticas. Varias de ellas presentaron correlación con las mediciones de referencia de firmeza [[2]](#ref2).

El estudio muestra la importancia de controlar el estímulo y contrastar las características espectrales con una referencia obtenida del fruto. Para Ligura, esto se traduce en dos decisiones conceptuales: establecer condiciones reproducibles de excitación y conservar la correspondencia entre la señal y la granadilla evaluada.

Ligura propone aplicar un barrido de frecuencias mediante un piezoeléctrico emisor y registrar la respuesta con otro piezoeléctrico situado en el brazo opuesto de la pinza. La lectura del FSR permitirá supervisar el cierre. Será necesario estudiar cuánto cambia la señal cuando una misma granadilla se retira y se vuelve a colocar.

### 2.3 Caracterización de la granadilla y registro de masa

Espinosa et al. estudiaron granadillas (*Passiflora ligularis*) procedentes de tres localidades de Colombia. Registraron características como peso fresco, dimensiones, firmeza, sólidos solubles, pH y acidez. Encontraron diferencias de peso fresco y composición relacionadas con la procedencia de los frutos [[3]](#ref3).

Este trabajo aporta información específica de la especie y orienta el registro de masa y procedencia en Ligura. Considerar estas variables permitirá estudiar si parte de las diferencias observadas en las señales se relaciona con la variabilidad entre frutos.

La masa se utilizará como información complementaria al análisis espectral. Su aporte a la clasificación deberá evaluarse comparando resultados obtenidos con y sin esta variable.

### 2.4 Comparación de soluciones existentes

La siguiente tabla relaciona los antecedentes revisados con las decisiones de diseño de Ligura.

| Solución / antecedente | Fruto estudiado | Excitación o medición | Información analizada | Aporte a Ligura |
|---|---|---|---|---|
| Diezma-Iglesias et al. [[1]](#ref1) | Sandía sin semillas | Impacto mecánico y registro con micrófono | Magnitud del espectro por bandas para identificar alteraciones internas | Explorar bandas de frecuencia y características asociadas a diferencias internas. |
| Tian et al. [[2]](#ref2) | Kiwi | Impacto calibrado y adquisición de respuesta vibratoria | Características espectrales relacionadas con mediciones de firmeza | Controlar la excitación y asociar cada señal con una referencia del mismo fruto. |
| Espinosa et al. [[3]](#ref3) | Granadilla | Caracterización física y bioquímica | Peso fresco, firmeza, composición y variación según procedencia | Registrar masa y trazabilidad de las muestras. |
| **Ligura — propuesta conceptual** | **Granadilla** | **Barrido de frecuencias, recepción piezoeléctrica y pesaje** | **Características espectrales y masa, contrastadas con una etiqueta visual de la pulpa** | **Investigar la distinción entre frutos con y sin zonas de oscurecimiento visible.** |

La propuesta de Ligura integra una celda de carga con HX711 para registrar la masa y una pinza accionada por servomotor cuyo cierre se supervisa mediante un FSR. El AD9833 y el amplificador LM386 alimentarían el piezoeléctrico emisor, mientras que el receptor registraría la respuesta. El ESP32 coordinaría el ciclo y el procesamiento, y el dashboard permitiría consultar el registro individual.

### 2.5 Aplicación de los antecedentes y brecha de investigación

Los antecedentes revisados orientan el análisis espectral, el control de las condiciones de medición y el registro de variables físicas del fruto. La aplicación específica que plantea Ligura es investigar si estas mediciones permiten distinguir granadillas con y sin zonas de oscurecimiento visible en la pulpa.

Para comprobarlo, se propone medir cada granadilla intacta y abrirla posteriormente para obtener una referencia visual. La fotografía y la etiqueta se asociarán al identificador de esa misma unidad.

La principal pregunta pendiente es si las diferencias entre ambas clases superan la variación producida por el contacto, la recolocación y las características individuales de los frutos. Esta cuestión orientará las pruebas de concepto del TRL 3.
