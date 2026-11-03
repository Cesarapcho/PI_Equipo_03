<div align="center">

# LIGURA

### Principios científicos de la tecnología propuesta · TRL 1

**Proyecto Integrador 2026-2 | Universidad Peruana Cayetano Heredia**  
**Equipo 03 | Octubre de 2026**

</div>

---

## Ficha del proyecto

| Campo | Información |
|---|---|
| Proyecto | LIGURA — Sistema mecatrónico no destructivo para el estudio de la condición interna de la granadilla |
| Especie de interés | *Passiflora ligularis* |
| Institución | Universidad Peruana Cayetano Heredia |
| Curso | Proyecto Integrador |
| Nivel documentado | TRL 1 — Principios básicos reportados de la tecnología propuesta |
| Alcance | Revisión bibliográfica y fundamento científico, sin validación experimental del sistema |

## Contenido

1. [Artículos científicos y principios tecnológicos](#1-artículos-científicos-y-principios-tecnológicos)
2. [Estado del arte](#2-estado-del-arte)
3. [Bases de datos científicas](#3-bases-de-datos-científicas)
4. [Libros científicos](#4-libros-científicos)
5. [Tesis académicas](#5-tesis-académicas)
6. [Conclusiones](#6-conclusiones)
7. [Referencias bibliográficas](#referencias-bibliográficas)

---

## Presentación del proyecto

LIGURA es un proyecto orientado al estudio de los principios científicos que sustentan la evaluación no destructiva de la granadilla (*Passiflora ligularis*) mediante excitación vibratoria controlada y análisis de su respuesta vibroacústica. La investigación busca comprender cómo se generan, propagan y registran las vibraciones en el fruto, considerando la influencia de sus propiedades físicas y estructurales.

Para ello, se estudia el efecto piezoeléctrico, que permite transformar señales eléctricas en deformaciones mecánicas y convertir deformaciones mecánicas en señales eléctricas. Asimismo, se analizan los fundamentos del procesamiento digital de señales, particularmente la transformada rápida de Fourier (FFT), utilizada para examinar las componentes de frecuencia de una señal registrada.

De manera complementaria, se investigan los principios de funcionamiento de las celdas de carga, que permiten estimar la masa a partir de la fuerza ejercida sobre un elemento deformable, y de los sensores resistivos FSR (*Force Sensing Resistor*), cuya resistencia eléctrica varía ante una fuerza de contacto. En LIGURA, **un FSR estará ubicado en uno de los brazos del gripper**, para supervisar el contacto durante la sujeción de la granadilla.

En esta etapa TRL 1 se estudian **principios básicos documentados por investigaciones, libros, tesis y fuentes técnicas**, sin asumir que el conjunto propuesto ha demostrado experimentalmente su capacidad para clasificar la condición interna de granadillas intactas.

**Pregunta de investigación:** ¿Qué principios físicos y electrónicos sustentan la generación y medición de respuestas vibroacústicas en la granadilla, así como la medición de su masa y la detección de fuerzas de contacto mediante sensores?

### Enfoque metodológico de CONCYTEC

La **Directiva N.° 001-2022-CONCYTEC-P**, aprobada por Resolución de Presidencia N.° 020-2022-CONCYTEC-P, denomina TRL 1 a los «principios básicos reportados de la nueva tecnología propuesta». Su **Anexo 1** presenta como evidencias referenciales los artículos científicos, el estado del arte, las bases de datos, los libros y las tesis. El **Anexo 2** añade, para ingeniería y software, documentos técnicos y el conocimiento de propiedades de arquitecturas, formulaciones matemáticas y algoritmos generales. Las pruebas de concepto y la validación experimental pertenecen a niveles posteriores (TRL 3 y superiores).

**Alcance de esta revisión:** se documenta la cadena con **transductores piezoeléctricos de contacto**, celda de carga y FSR. Algunas versiones previas del README general también mencionan un micrófono; no se atribuyen las características de los piezoeléctricos a esa alternativa. El modelo exacto de la placa ESP32 y la compatibilidad eléctrica de la etapa de potencia deben mantenerse coherentes con el diseño electrónico finalmente adoptado.

---

## 1. Artículos científicos y principios tecnológicos

### 1.1. Sensores piezoeléctricos para excitación y medición vibroacústica

Los transductores piezoeléctricos se fundamentan en el **efecto piezoeléctrico**, una propiedad electromecánica de ciertos materiales, entre ellos algunas cerámicas y cristales. El **efecto directo** produce una respuesta eléctrica ante una deformación mecánica; el **efecto inverso** produce una deformación mecánica al aplicar un campo eléctrico. Lay y colaboradores (2021) revisan estos mecanismos y sus fundamentos materiales [1].

En LIGURA se consideran dos transductores piezoeléctricos en contacto con la granadilla a través de los brazos del gripper. El **emisor** empleará el efecto inverso para provocar una excitación vibratoria; el **receptor** aprovechará el efecto directo para convertir las vibraciones recibidas en una señal eléctrica. Esa señal reflejará el comportamiento del conjunto formado por el fruto, el transductor y las condiciones de contacto, por lo que no se interpreta como lectura directa de pulpa, azúcar o pH.

Macrelli y colaboradores (2013) estudiaron transductores piezoeléctricos en contacto con kiwis para evaluar su firmeza. Compararon índices relacionados con resonancia y propagación acústica y evaluaron diferentes posiciones de contacto. En sus condiciones experimentales, los índices de propagación ofrecieron resultados más fiables que los basados en resonancia [2].

Zhang y colaboradores (2018) investigaron un método vibroacústico en peras con un actuador piezoeléctrico y dos sensores receptores. Construyeron un índice de doble frecuencia con correlación **r = 0,951** respecto a la medición de firmeza de referencia Magness–Taylor [3]. Este resultado demuestra una relación observada **en las peras evaluadas**, no una precisión esperada de LIGURA.

Estos antecedentes sustentan el principio de excitación y medición mediante piezoeléctricos. También muestran que el acoplamiento, la ubicación de los sensores y las propiedades del fruto influyen en la respuesta adquirida.

### 1.2. Celda de carga y módulo HX711 para la medición de masa

Las celdas de carga extensométricas utilizan **deformación elástica y variación de resistencia eléctrica**. Al actuar una fuerza sobre su elemento metálico, las galgas extensométricas adheridas se deforman ligeramente y cambian su resistencia. Un **puente de Wheatstone** transforma esas pequeñas variaciones de resistencia en una diferencia de voltaje. Al-Dahiree y colaboradores (2022) estudiaron el diseño y la sensibilidad de celdas de carga utilizando galgas, análisis por elementos finitos y comprobaciones experimentales [4].

El **HX711** no pesa por sí mismo: amplifica la pequeña señal diferencial procedente de la celda y la convierte a un valor digital mediante un ADC de resolución nominal de **24 bits**. Su documentación especifica dos canales diferenciales seleccionables y tasas nominales de 10 y 80 lecturas por segundo. La resolución nominal no equivale a una exactitud de masa garantizada [5].

Benkek y colaboradores (2022) desarrollaron un equipo didáctico de calibración que integra celda de carga, HX711 y microcontrolador; su estudio muestra el papel de las **masas de referencia** para relacionar lecturas digitales y masa [6]. Kok y colaboradores (2024) estudiaron un sistema de pesaje con calibración dentro de un equipo de infusión; constituye un antecedente sobre compensación y estabilidad de lecturas, no sobre medición de frutas [7].

Oveisi y colaboradores (2014) estudiaron la firmeza de peras con vibración forzada, vibrometría láser y análisis FFT, combinando características físicas y vibratorias en modelos de predicción [8]. Este trabajo fundamenta considerar la masa como **variable física auxiliar** al interpretar respuestas vibratorias.

En LIGURA, la granadilla se colocará sobre una cuna conectada a la celda. Se tomará una lectura de **tara** sin el fruto y se aplicará una calibración con masas conocidas; la fuerza asociada al peso se convertirá en una estimación de masa. Este registro se realizará antes de la sujeción del gripper para minimizar la influencia de fuerzas ajenas al pesaje. La masa no determina por sí sola la condición interna de la granadilla.

### 1.3. Sensor resistivo FSR para la detección de fuerza de contacto

Un **FSR** (*Force Sensing Resistor*) cambia su resistencia eléctrica cuando se aplica una fuerza sobre su zona sensible. En modelos de película delgada, la presión modifica el contacto eléctrico entre materiales conductores y resistivos; por lo general, **al aumentar la fuerza disminuye la resistencia**. Mediante un divisor de tensión se convierte esa variación en un voltaje que puede digitalizarse. Esta descripción corresponde al principio de una familia de sensores: la curva específica depende del modelo y del montaje [9].

Jung y colaboradores (2024) compararon sensores de película delgada, entre ellos el **Interlink FSR-402**, mediante cargas conocidas y calibraciones. Mostraron la importancia de seleccionar el circuito de lectura y caracterizar la linealidad y repetibilidad dentro del intervalo de operación [10].

Cong y colaboradores (2024) desarrollaron un gripper con **sensores FSR** distribuidos en superficies de contacto y una estrategia de percepción mediante umbrales para contribuir al control del agarre [11]. Kargar y Berselli (2026) integraron sensores FSR y superficies flexibles en un gripper para productos agrícolas; reportaron pruebas con distintas hortalizas y frutas delicadas [12]. Estos trabajos respaldan el uso de retroalimentación táctil, pero sus resultados no validan el gripper de LIGURA.

En LIGURA se colocará **un FSR en uno de los brazos**. Su salida permitirá detectar fuerza local de contacto durante el cierre y proporcionar una señal para aplicar una condición de detención. Una lectura en un brazo **no equivale necesariamente a la fuerza total sobre la fruta**. La distribución del contacto, histéresis, deriva temporal y eventual calibración condicionarán la interpretación de la medición. El umbral de cierre seguro deberá determinarse mediante experimentos posteriores, no por la ficha técnica solamente.

### 1.4. Generación y adquisición electrónica de señales vibratorias

**Síntesis digital directa (DDS).** Es un método que genera señales periódicas a partir de una referencia de reloj, un acumulador de fase y conversión digital-analógica. Rifai y colaboradores (2025) compararon arquitecturas DDS implementadas en FPGA y evaluaron precisión de frecuencias y calidad de señal [13]. El **AD9833** emplea DDS y permite generar formas de onda sinusoidales, triangulares y cuadradas de frecuencia programable [14]. En LIGURA suministrará una señal eléctrica de excitación: **no es el sensor receptor ni genera por sí solo la vibración mecánica del fruto**.

**Amplificación de potencia.** El **PAM8403** es un amplificador de audio clase D, diseñado y especificado principalmente para altavoces de baja impedancia [15]. El principio de amplificación permite aumentar la potencia eléctrica entregada a una carga. Sin embargo, un piezoeléctrico es predominantemente **capacitivo**, por lo que las especificaciones de potencia del PAM8403 para altavoces **no prueban** que sea adecuado para excitar el transductor de LIGURA sin diseño y comprobación de compatibilidad. El fabricante lo señala como *Not Recommended for New Design*.

**Acondicionamiento de la respuesta.** La señal del piezoeléctrico receptor puede requerir adaptación de impedancia, amplificación, filtrado y protección antes de entrar a un convertidor analógico-digital. La nota técnica **CN0350** de Analog Devices muestra un ejemplo de adquisición de señales de sensores piezoeléctricos con acondicionamiento y ADC [16].

El ADC de un microcontrolador transforma voltajes en muestras numéricas; sus prestaciones dependen de la variante del chip, del ruido y del circuito. La documentación de **Espressif** describe los periféricos ADC de sus dispositivos y los aspectos de calibración para el ESP32 clásico [17]. Esta cadena electrónica documenta cómo **podría registrarse** una respuesta de vibración, sin afirmar que una etapa de adquisición específica ya haya sido validada por el equipo.

### 1.5. Procesamiento digital de señales y transformada rápida de Fourier (FFT)

La **transformada discreta de Fourier (DFT)** representa una secuencia de muestras como componentes de frecuencia. La **transformada rápida de Fourier (FFT)** es una familia de algoritmos eficientes para calcular esa DFT; la contribución clásica de Cooley y Tukey (1965) estableció una base de su uso computacional [18].

En el espectro obtenido, el **eje horizontal** representa frecuencia en hercios (Hz) y el **eje vertical** la magnitud de las componentes en la escala correspondiente al procesamiento. La magnitud espectral **no equivale directamente a energía mecánica**, ni mide °Brix, pH o madurez sin un modelo y referencias experimentales.

La frecuencia correspondiente a un índice del espectro puede calcularse mediante:

\[
f_k = \frac{k\,f_s}{N}
\]

Donde **fₖ** es la frecuencia del índice **k**, **fₛ** es la frecuencia de muestreo y **N** la cantidad de muestras analizadas. Esta relación indica dónde se ubica una componente del espectro; no sustituye el análisis del muestreo, filtrado, duración de registro o ruido [20].

Oveisi y colaboradores estudiaron la respuesta vibratoria de peras mediante FFT y parámetros mecánicos [8]. Abbaszadeh y colaboradores (2015) analizaron señales vibratorias de sandías, extrajeron características espectrales y utilizaron clasificación KNN para distinguir madurez en las muestras experimentales [19]. Los resultados publicados no permiten inferir automáticamente un porcentaje de clasificación para granadillas intactas.

En LIGURA, la FFT permitirá **examinar frecuencias predominantes y magnitudes relativas de la señal registrada**. Para interpretar diferencias será necesario considerar el método de excitación, la fuerza de contacto, la masa del fruto, la estructura de soporte y la posibilidad de ruido o vibraciones externas.

### 1.6. Microcontrolador ESP32 para adquisición, procesamiento y control

Un **microcontrolador** integra procesador, memoria y periféricos para recibir datos, ejecutar instrucciones y generar acciones de control. La familia **ESP32** incorpora interfaces digitales, conectividad inalámbrica y, según el modelo, conversión analógico-digital y generación de señales de control [21]. La documentación del **ESP32 clásico** no debe confundirse con las especificaciones de otras variantes, como el ESP32-S3.

Espinosa-Gavira y colaboradores (2024) estudiaron el comportamiento del ESP32 en redes sincronizadas de sensores y los límites de su adquisición analógica, resaltando aspectos de caracterización y calidad de medición [22]. Kolok y colaboradores (2025) integraron un microcontrolador ESP32-C6 con sensores de vibración MEMS en un sistema de mantenimiento predictivo; este antecedente muestra la relación entre adquisición, comunicación y análisis, sin representar pruebas con piezoeléctricos en granadillas [23]. Por otra parte, la biblioteca **ESP-DSP** de Espressif contiene implementaciones de operaciones de procesamiento digital y FFT para plataformas compatibles [24].

En LIGURA, el microcontrolador coordinará **la lectura digital del HX711**, **la adquisición de la señal del FSR mediante un circuito apropiado**, **el control del generador de frecuencias**, **la lectura de la respuesta vibroacústica previamente acondicionada** y **la comunicación de información a una interfaz externa**. Ni el ESP32 ni la conectividad inalámbrica mejoran por sí solos la exactitud física de los sensores.

---

## 2. Estado del arte

La evaluación no destructiva de frutas mediante estímulos acústicos y vibratorios cuenta con antecedentes que estudian firmeza, madurez o defectos internos **en especies y condiciones concretas**. La comparación de sus métodos es necesaria porque no todos utilizan la misma fuente de excitación ni el mismo tipo de sensor.

Macrelli y colaboradores (2013) investigaron kiwis mediante transductores piezoeléctricos **de contacto**. Su comparación de índices de propagación y resonancia muestra la influencia de la ubicación de los transductores [2]. Zhang y colaboradores (2018) estudiaron peras mediante un actuador piezoeléctrico y dos sensores receptores; su índice de doble frecuencia registró una correlación **r = 0,951** con la firmeza de referencia en ese estudio [3].

Oveisi y colaboradores (2014) utilizaron **vibración forzada, vibrometría láser Doppler y FFT** en peras. Reportaron relaciones entre características de vibración, propiedades físicas y firmeza medida experimentalmente [8]. Abbaszadeh y colaboradores (2015) aplicaron análisis espectral y KNN sobre señales vibratorias de sandías para estudiar su madurez, con resultados correspondientes a su propio conjunto de muestras [19].

Respecto a la especie de interés, Puyana-Romero y colaboradores (2026) estudiaron materiales fabricados **a partir de la cáscara de granadilla** y midieron propiedades de absorción y aislamiento acústico mediante tubo de impedancia. Una muestra procesada de 50 mm presentó un máximo de absorción de **0,98 a 500 Hz** [25]. El resultado **no describe una granadilla entera** ni demuestra que su cáscara bloquee, transmita o preserve determinada información interna en la configuración de LIGURA.

Por otra parte, Kargar y Berselli (2026) estudiaron un gripper con superficies flexibles y retroalimentación FSR para manipular productos agrícolas sin daños observables en sus pruebas [12]. Es un antecedente de **control de sujeción**, no de detección vibroacústica de calidad interna.

### Comparación de investigaciones

| Referencia | Fruto / aplicación | Método estudiado | Principal aporte y límite |
|---|---|---|---|
| Macrelli et al. (2013) [2] | Kiwi | Transductores piezoeléctricos de contacto | Propagación, resonancia y posición de contacto; no granadilla |
| Zhang et al. (2018) [3] | Pera | Actuador piezoeléctrico y dos receptores | Índice vibratorio correlacionado con firmeza; no calidad interna de granadilla |
| Oveisi et al. (2014) [8] | Pera | Vibración forzada, láser Doppler y FFT | Parámetros vibratorios y físicos; sensores distintos a LIGURA |
| Abbaszadeh et al. (2015) [19] | Sandía | Vibraciones, FFT y KNN | Características espectrales y madurez; especie diferente |
| Puyana-Romero et al. (2026) [25] | Cáscara procesada de granadilla | Ensayos en tubo de impedancia | Acústica de material fabricado; no fruto intacto |
| Kargar y Berselli (2026) [12] | Productos agrícolas | Gripper con sensores FSR | Retroalimentación de contacto; no adquisición vibroacústica |

### Antecedente de patente

La patente estadounidense **US6276536B1**, de Terasaki y Wada (2001), divulga un método para evaluar textura y madurez de frutas mediante **excitación vibratoria variable, información de peso y análisis de frecuencia** [26]. Es un antecedente de la combinación conceptual y no una evidencia de funcionamiento de LIGURA ni una conclusión de patentabilidad. Una búsqueda de anterioridad más amplia, una evaluación de patentabilidad o un estudio de libertad de operación requerirían un análisis separado.

### Síntesis del estado del arte

Las investigaciones revisadas muestran que la vibración, la propagación acústica y el análisis espectral pueden aportar información sobre propiedades mecánicas de ciertas frutas. También muestran que el **contacto entre sensor y fruto, la geometría, el método de excitación y las condiciones de medición** son importantes para interpretar la respuesta.

**Brecha científica identificada:** los antecedentes aquí examinados no demuestran una relación reproducible entre las características vibroacústicas captadas mediante el sistema propuesto y la condición interna de **granadillas enteras**. Esa relación debe investigarse posteriormente mediante protocolos de medición y referencias independientes.

---

## 3. Bases de datos científicas

La revisión se apoyó en **registros académicos identificables** y documentación original de fabricantes. Se distinguen las fuentes de artículos completos de los **índices bibliográficos**, los **repositorios universitarios** y los **documentos de patentes**.

| Fuente | Tipo de contenido | Evidencia identificada o utilidad para LIGURA |
|---|---|---|
| **ScienceDirect (Elsevier)** | Artículos de revistas | Estudios de Macrelli [2] y Zhang [3] sobre mediciones acústicas en frutas |
| **PubMed / PubMed Central** | Referencias y artículos científicos de texto completo | Registros de Oveisi [8] y Abbaszadeh [19] |
| **Springer Nature / Scientific Reports** | Artículos revisados por pares | Estudio sobre materiales de cáscara de granadilla [25] y gripper con FSR [12] |
| **MDPI** | Artículos científicos | Calibración de FSR [10], gripper táctil [11], celdas de carga [4] |
| **Repositorio Universidad de Concepción** | Tesis | Soto Chávez [33] |
| **Dialnet** | Registros de tesis y publicaciones | Diezma Iglesias [32] y Homer [34] |
| **Google Patents** | Documentos de propiedad industrial | Patente US6276536B1 [26] |
| **Documentación oficial de fabricantes** | Fichas técnicas y notas de aplicación | HX711 [5], FSR [9], AD9833 [14], PAM8403 [15], adquisición piezoeléctrica [16], ESP32 [17], [21], [24] |

**Plataformas pertinentes para ampliar la revisión:** IEEE Xplore, Web of Science, Scopus y Google Académico. Se mencionan como opciones de búsqueda y **no se afirma que se realizaron consultas verificadas en todas ellas**.

**Términos de búsqueda orientativos:** `piezoelectric transducers fruit firmness`, `strain gauge load cell Wheatstone bridge`, `HX711 calibration`, `force sensing resistor robotic gripper`, `non-destructive fruit vibration`, `FFT fruit ripeness`, `Passiflora ligularis peel acoustic properties`.

**Criterios de selección:** autores y fecha identificables; publicación o repositorio verificable; principio físico, método y resultados explícitos; cercanía con la tecnología estudiada; y separación entre datos obtenidos por otros investigadores y afirmaciones del proyecto. Una ficha técnica describe características nominales, pero **no sustituye una investigación experimental**.

---

## 4. Libros científicos

Los libros se emplean como **fuentes de fundamento general**. Se verificaron datos bibliográficos editoriales y temáticas relevantes; no se presentan como si todos sus capítulos hubieran sido objeto de lectura íntegra.

### Sensores y acondicionadores de señal — Ramón Pallás Areny

Pallás Areny explica cómo determinadas magnitudes físicas se convierten en señales eléctricas y por qué los sensores requieren circuitos de acondicionamiento e interfaces de adquisición [27]. Sirve para comprender las galgas extensométricas, la lectura resistiva del FSR y los transductores piezoeléctricos. La respuesta particular de cada modelo se complementa con su documentación técnica.

### Piezoelectric Sensorics — Gustav Gautschi

Gautschi presenta los principios de piezoelectricidad, los materiales de sensado y los circuitos de medición de carga eléctrica [28]. Este fundamento permite distinguir el efecto directo del inverso y comprender por qué el receptor piezoeléctrico puede requerir un circuito de acondicionamiento de alta impedancia.

### Handbook of Modern Sensors — Jacob Fraden

Fraden trata principios físicos y características generales de sensores, entre ellas **sensibilidad, linealidad y calibración** [29]. Su relación con LIGURA es el estudio de sensores resistivos y de fuerza y las precauciones necesarias para interpretar sus lecturas como medidas físicas.

### Mechanical Vibrations — Singiresu S. Rao

Rao desarrolla vibración forzada, frecuencias naturales, resonancia y amortiguamiento [30]. Estos conceptos explican por qué la respuesta depende de las propiedades del cuerpo y de las condiciones de montaje, aunque no suministran valores específicos medidos en las granadillas del equipo.

### Discrete-Time Signal Processing — Alan V. Oppenheim y Ronald W. Schafer

Oppenheim y Schafer presentan muestreo, representación de señales discretas, DFT, filtrado y métodos de análisis espectral [31]. Esta base permite estudiar la FFT y los riesgos de una adquisición insuficiente, como el **aliasing**. El algoritmo analiza una señal registrada; no interpreta directamente calidad interna sin evidencia experimental.

---

## 5. Tesis académicas

### Detección no destructiva de problemas de calidad interna en sandías apirenas mediante respuesta acústica a impactos de baja intensidad

**Belén Diezma Iglesias**, Universidad Politécnica de Madrid, **2003** [32]. Investigó la detección de alteraciones internas, incluidas cavidades y grietas, mediante impactos de baja intensidad y registro de respuestas acústicas. El interés para LIGURA radica en el análisis de características acústicas relacionadas con diferencias internas. **Diferencia de método:** LIGURA propone excitación periódica sin impacto como mecanismo principal.

### Diseño y construcción de un dispositivo de medición de firmeza de cerezas basado en ultrasonido

**Fabiola Vianney Soto Chávez**, Universidad de Concepción, **2020** [33]. Desarrolló un sistema ultrasónico de **40 kHz**, de tipo pulso-eco, para estudiar firmeza de cerezas. La combinación de señal, diámetro y masa explicó el **26,9 %** de la variación de firmeza observada en el cultivar Regina; el voltaje por sí solo no fue suficiente. El resultado ilustra la necesidad de interpretar las señales junto con otras variables, **sin extrapolar esa cifra a granadillas**.

### Desarrollo y aplicación de un sensor de impacto para la determinación de firmeza en líneas de manipulación de fruta

**Ian Homer**, Universidad Politécnica de Madrid, **2003** [34]. Evaluó un sensor de impacto con acelerómetro, que empleaba parámetros de la curva aceleración-tiempo para estudiar firmeza de frutas y clasificar niveles de firmeza. Es un antecedente de adquisición y procesamiento de señales mecánicas, pero su método de impacto difiere del que se propone investigar en LIGURA.

**Síntesis de las tesis:** documentan cómo estudiar señales acústicas y mecánicas en frutas con mediciones de referencia. Ninguna constituye una prueba del sistema de LIGURA ni demuestra por sí misma una clasificación fiable de la condición interna de granadilla.

---

## 6. Conclusiones

La revisión bibliográfica identificó principios científicos que respaldan el estudio de respuestas vibroacústicas en frutas. Las investigaciones de kiwis, peras y sandías documentan relaciones entre ciertas respuestas acústicas o vibratorias y propiedades físicas concretas; sus resultados no pueden extrapolarse automáticamente a *Passiflora ligularis* [2], [3], [8], [19].

Los **transductores piezoeléctricos** sustentan la conversión entre señales eléctricas y vibraciones mecánicas; la **celda de carga y el HX711** permiten estudiar el peso y estimar masa mediante deformación y digitalización; y el **FSR** permite detectar cambios de fuerza local de contacto en un brazo del gripper [1], [4], [5], [9], [10]. Cada principio presenta condiciones de medición y necesidades de calibración que deben distinguirse.

La **síntesis digital directa** fundamenta la generación de señales de frecuencia programable; los sistemas de **acondicionamiento y conversión analógico-digital** permiten adquirir respuestas eléctricas; y la **FFT** proporciona una representación de su contenido en frecuencia [13], [14], [16], [18]. Ninguna técnica determina automáticamente la calidad interna de una granadilla sin información experimental de referencia.

El estado del arte identificó estudios sobre cáscara de granadilla **procesada** y patentes de análisis vibratorio de frutas, pero estas fuentes no constituyen una validación de la propagación ni de la clasificación de la condición interna en **frutos intactos** bajo el sistema propuesto [25], [26].

En conjunto, la recopilación de artículos, antecedentes tecnológicos, libros y tesis constituye una **base documental coherente con los indicadores de TRL 1 de CONCYTEC**. El desarrollo de una prueba de concepto, la determinación experimental de umbrales de fuerza y la validación de una eventual clasificación corresponden a etapas posteriores. Este documento **no es una certificación oficial** del nivel tecnológico por CONCYTEC.

---

## Referencias bibliográficas

> La numeración **[1]–[34]** es única para todo el documento. Los artículos y libros sustentan fenómenos y antecedentes; las fichas técnicas respaldan características nominales de componentes; las patentes documentan anterioridad tecnológica. Los enlaces DOI y de repositorios permiten consultar los registros de las publicaciones.

[1] R. Lay, G. S. Deijs y J. Malmström, “The intrinsic piezoelectric properties of materials – a review with a focus on biological materials,” *RSC Advances*, vol. 11, pp. 30657–30673, 2021. https://doi.org/10.1039/D1RA03557F

[2] E. Macrelli, A. Romani, R. P. Paganelli, E. Sangiorgi y M. Tartagni, “Piezoelectric transducers for real-time evaluation of fruit firmness. Part I: Theory and development of acoustic techniques,” *Sensors and Actuators A: Physical*, vol. 201, pp. 487–496, 2013. https://doi.org/10.1016/j.sna.2013.07.033

[3] H. Zhang, J. Wu, Z. Zhao y Z. Wang, “Nondestructive firmness measurement of differently shaped pears with a dual-frequency index based on acoustic vibration,” *Postharvest Biology and Technology*, vol. 138, pp. 11–18, 2018. https://doi.org/10.1016/j.postharvbio.2017.12.002

[4] O. S. Al-Dahiree et al., “Design and Shape Optimization of Strain Gauge Load Cell for Axial Force Measurement for Test Benches,” *Sensors*, vol. 22, n.º 19, art. 7508, 2022. https://doi.org/10.3390/s22197508

[5] Avia Semiconductor, “HX711: 24-Bit Analog-to-Digital Converter (ADC) for Weigh Scales,” ficha técnica, rev. 2.0. https://www.mouser.com/datasheet/2/813/hx711_english-1022875.pdf

[6] G. Benkek, Z. Vrhovski y K. Husak, “Didactic Equipment for Mass Sensor Calibration with Computer,” *Polytechnic and Design*, vol. 10, n.º 3, pp. 198–204, 2022. https://doi.org/10.19279/TVZ.PD.2022-10-3-07

[7] C. L. Kok et al., “A Novel and Self-Calibrating Weighing Sensor with Intelligent Peristaltic Pump Control for Real-Time Closed-Loop Infusion Monitoring in IoT-Enabled Sustainable Medical Devices,” *Electronics*, vol. 13, n.º 9, art. 1724, 2024. https://doi.org/10.3390/electronics13091724

[8] Z. Oveisi, S. Minaei, S. Rafiee, A. Eyvani y A. Borghei, “Application of vibration response technique for the firmness evaluation of pear fruit during storage,” *Journal of Food Science and Technology*, vol. 51, n.º 11, pp. 3261–3268, 2014. https://doi.org/10.1007/s13197-012-0811-z

[9] Interlink Electronics, “Force Sensing Resistor (FSR) Sensor Series,” documentación técnica del fabricante. https://www.interlinkelectronics.com/force-sensing-resistor

[10] J. Jung, K. Lee y B. Kim, “Precision Calibration and Linearity Assessment of Thin Film Force-Sensing Resistors,” *Applied Sciences*, vol. 14, n.º 16, art. 6859, 2024. https://doi.org/10.3390/app14166859

[11] Q. Cong, W. Fan y D. Zhang, “TacFR-Gripper: A Reconfigurable Fin-Ray-Based Gripper with Tactile Skin for In-Hand Manipulation,” *Actuators*, vol. 13, n.º 12, art. 521, 2024. https://doi.org/10.3390/act13120521

[12] S. M. Kargar y G. Berselli, “A sensorized soft-pad-integrated compliant gripper for safe handling of agricultural produce,” *The International Journal of Advanced Manufacturing Technology*, vol. 143, pp. 3761–3772, 2026. https://doi.org/10.1007/s00170-026-17716-3

[13] I. N. Rifai, W. D. Astuti, J. Hendry, A. W. Santoso y A. P. Aji, “Design of Direct Digital Synthesizer (DDS) Based on Field Programmable Gate Array (FPGA) for Electrical Impedance Tomography (EIT),” *Jurnal Listrik, Instrumentasi, dan Elektronika Terapan*, vol. 6, n.º 1, pp. 48–54, 2025. https://doi.org/10.22146/juliet.v6i1.102579

[14] Analog Devices, “AD9833: Low Power, Programmable Waveform Generator,” ficha técnica del fabricante. https://www.analog.com/en/products/ad9833.html

[15] Diodes Incorporated, “PAM8403: 3W Stereo Class-D Audio Amplifier,” ficha técnica del fabricante. https://www.diodes.com/part/view/PAM8403/

[16] Analog Devices, “CN0350: 12-Bit, 1 MSPS, Single-Supply, Two-Chip Data Acquisition System for Piezoelectric Sensors,” *Circuit Note*, 2014. https://www.analog.com/en/resources/reference-designs/circuits-from-the-lab/cn0350.html

[17] Espressif Systems, “Analog-to-Digital Converter (ADC),” *ESP-IDF Programming Guide*. https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/adc/index.html

[18] J. W. Cooley y J. W. Tukey, “An Algorithm for the Machine Calculation of Complex Fourier Series,” *Mathematics of Computation*, vol. 19, n.º 90, pp. 297–301, 1965. https://doi.org/10.1090/S0025-5718-1965-0178586-1

[19] R. Abbaszadeh, A. Moosavian, A. Rajabipour y G. Najafi, “An intelligent procedure for watermelon ripeness detection based on vibration signals,” *Journal of Food Science and Technology*, vol. 52, n.º 2, pp. 1075–1081, 2015. https://doi.org/10.1007/s13197-013-1068-x

[20] Analog Devices, “Dynamic Testing of High-Speed ADCs, Part 2,” artículo técnico. https://www.analog.com/en/resources/technical-articles/dynamic-testing-of-highspeed-adcs-part-2.html

[21] Espressif Systems, “ESP32 Series Datasheet,” documentación técnica del fabricante. https://documentation.espressif.com/esp32_datasheet_en.html

[22] M. J. Espinosa-Gavira, A. Agüera-Pérez, J. C. Palomares-Salas, J. M. Sierra-Fernández, P. Remigio-Carmona y J. J. González-de-la-Rosa, “Characterization and Performance Evaluation of ESP32 for Real-time Synchronized Sensor Networks,” *Procedia Computer Science*, vol. 237, pp. 261–268, 2024. https://doi.org/10.1016/j.procs.2024.05.104

[23] P. Kolok, M. Hodoň, P. Ševčík, L. Hotz y N. Remy, “Low-Cost IoT-Based Predictive Maintenance Using Vibration,” *Sensors*, vol. 25, n.º 21, art. 6610, 2025. https://doi.org/10.3390/s25216610

[24] Espressif Systems, “ESP-DSP Library,” documentación oficial. https://docs.espressif.com/projects/esp-dsp/en/latest/esp32/

[25] V. Puyana-Romero, A. Debut, K. Vizuete y G. Ciaburro, “Exploring Passiflora ligularis Juss. Peel as a Natural Sound-Absorbing and Insulating Material,” *Scientific Reports*, vol. 16, art. 18208, 2026. https://doi.org/10.1038/s41598-026-48916-2

[26] S. Terasaki y N. Wada, “Method of Measuring Ripeness and Texture of Vegetable or Fruit and Measuring Instrument,” patente estadounidense **US6276536B1**, 2001. https://patents.google.com/patent/US6276536B1/en

[27] R. Pallás Areny, *Sensores y acondicionadores de señal*, 4.ª ed. Marcombo, 2003. https://www.marcombo.com/libro/libros-tecnicos-de-arte-y-cientificos/electronica-libros-tecnicos-y-cientificos/microcontroladores-electronica/sensores-y-acondicioadores-de-senal-4a/

[28] G. Gautschi, *Piezoelectric Sensorics: Force, Strain, Pressure, Acceleration and Acoustic Emission Sensors, Materials and Amplifiers*. Springer, 2002. https://doi.org/10.1007/978-3-662-04732-3

[29] J. Fraden, *Handbook of Modern Sensors: Physics, Designs, and Applications*, 5.ª ed. Springer, 2016. https://doi.org/10.1007/978-3-319-19303-8

[30] S. S. Rao, *Mechanical Vibrations*, 6.ª ed. Pearson, © 2017. ISBN 9780134361307. https://www.pearson.com/subject-catalog/p/mechanical-vibrations/P200000003425/9780137515288

[31] A. V. Oppenheim y R. W. Schafer, *Discrete-Time Signal Processing*, 3.ª ed. Pearson, 2010. ISBN 9780131988422. https://www.pearson.com/subject-catalog/p/discrete-time-signal-processing/P200000003226/9780137549771

[32] B. Diezma Iglesias, *Detección no destructiva de problemas de calidad interna en sandías apirenas mediante respuesta acústica a impactos de baja intensidad*, tesis doctoral, Universidad Politécnica de Madrid, 2003. https://dialnet.unirioja.es/servlet/tesis?codigo=185337

[33] F. V. Soto Chávez, *Diseño y construcción de un dispositivo de medición de firmeza de cerezas basado en ultrasonido*, tesis de magíster, Universidad de Concepción, 2020. https://repositorio.udec.cl/handle/11594/1012

[34] I. Homer, *Desarrollo y aplicación de un sensor de impacto para la determinación de firmeza en líneas de manipulación de fruta*, tesis doctoral, Universidad Politécnica de Madrid, 2003. https://dialnet.unirioja.es/servlet/tesis?codigo=185342

### Documento normativo utilizado

Consejo Nacional de Ciencia, Tecnología e Innovación Tecnológica (CONCYTEC), **Directiva N.° 001-2022-CONCYTEC-P — Uso de la Metodología Nivel de Madurez Tecnológica (TRL)**, aprobada mediante Resolución de Presidencia N.° 020-2022-CONCYTEC-P. Se consultaron especialmente los **anexos 1 y 2** del documento compartido en clase.

---

<div align="center">

*LIGURA · TRL 1 · Proyecto Integrador · 2026*

</div>
