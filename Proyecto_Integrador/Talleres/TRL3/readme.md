# TRL 3 — Pruebas de concepto de LIGURA

**Proyecto:** LIGURA — Sistema inteligente de evaluación de granadilla  
**Equipo:** Equipo 03  
**Curso:** Proyecto Integrador 2026-2  
**Institución:** Universidad Peruana Cayetano Heredia  
**Nivel documentado:** TRL 3 — Prueba de concepto analítica y experimental

---

## 1. Objetivo general

Documentar los ensayos de prueba de concepto de componentes críticos de LIGURA: transductores piezoeléctricos para excitación y adquisición de señales, celda de carga con convertidor HX711 para medición de carga y sensor resistivo FSR para detección de presión de contacto. La finalidad es comprobar la viabilidad preliminar de cada principio de funcionamiento mediante análisis, simulación y/o ensayos experimentales, con trazabilidad hacia sus evidencias.

Los resultados corresponden a **pruebas individuales de subsistemas**. No constituyen una validación del funcionamiento integrado del gripper ni de la clasificación de la condición interna de la granadilla.

## 2. Fundamento del TRL 3

Según la escala de madurez tecnológica de la NASA, **TRL 3** corresponde a una *prueba de concepto analítica y experimental de las funciones o características críticas*. En esta etapa se documentan análisis y resultados de ensayos que respaldan la factibilidad de un principio tecnológico. El **TRL 4** implica la validación de componentes o montajes experimentales en un entorno de laboratorio más representativo.

Por ello, para cada componente se identifican: objetivo, fundamento, configuración, metodología, registros, resultados cuantitativos, interpretación y limitaciones.

**Referencia:** [NASA Earth Science Technology Office — Technology Readiness Levels](https://esto.nasa.gov/trl/).

## 3. Resumen de las pruebas de concepto

| Subsistema | Función evaluada | Actividades y evidencia | Resultado documentado | Documento del experimento |
|---|---|---|---|---|
| **Celda de carga + HX711** | Conversión de la carga aplicada a una lectura digital calibrada en unidades de masa | Tara, calibración con masas conocidas, regresión lineal y verificación con masa no usada en el ajuste | Calibración con 0, 5, 10, 20 y 50 g; **R² = 0.999410**. Para 65 g se obtuvo **65.459 g**, con **0.459 g** de error absoluto (**0.706 %**) | [Celda de Carga - HZ711](./Celda%20de%20Carga%20-%20HZ711/readme.md) |
| **Sensor FSR RFP-602** | Detección de variaciones de presión aplicadas al sensor | Fundamento matemático, ensayo sintético en Python, prueba con ESP32, simulación en Tinkercad y diseño de procedimiento de calibración | En la prueba física se registraron **valores ADC de 0 a 149** al aplicar y retirar presión; las simulaciones evidenciaron una respuesta no lineal | [Sensor FSR](./Sensor%20FSR/README.md) |
| **Transductores piezoeléctricos** | Evaluación de una respuesta eléctrica en el receptor asociada a la excitación nominal de 2000 Hz | Piezos acoplados con plástico aislante; adquisición ESP32; análisis Goertzel; 69 registros, código, fotografías y gráficas | Magnitud media a 2000 Hz de **1.99** con emisor apagado y **4.99** encendido; incremento aproximado del **151.2 %** | [Piezoeléctricos - AD9833](./Piezoel%C3%A9ctricos%20-%20AD9833/README.md) |

Las cifras corresponden a las evidencias de cada ensayo y **no son comparables directamente entre sensores**, ya que expresan variables y escalas diferentes.

## 4. Experimento 1 — Celda de carga con HX711

### 4.1 Objetivo y método

Se evaluó una **celda de carga de capacidad nominal de 1 kg**, conectada a un **HX711** y un **ESP32**, para comprobar si sus lecturas podían relacionarse con masas de referencia. El procedimiento incluyó tara, adquisición de **30 muestras por punto** y calibración lineal con masas de **0, 5, 10, 20 y 50 g**. Se realizaron cálculos de pendiente, intercepto, errores y coeficiente de determinación.

La calibración utilizó **una serie experimental**: 30 muestras por masa no equivalen a 30 repeticiones independientes. Posteriormente se verificó el modelo mediante una carga de **65 g** que no participó en el ajuste.

### 4.2 Resultados

| Indicador | Resultado |
|---|---:|
| Coeficiente de determinación de la recta de calibración | **0.999410** |
| Masa de referencia en verificación | **65.000 g** |
| Masa estimada en verificación | **65.459 g** |
| Error absoluto en verificación | **0.459 g** |
| Error relativo absoluto en verificación | **0.706 %** |

La respuesta fue consistente con la posibilidad de medir pequeñas cargas en el montaje ensayado. Sin embargo, no se evaluaron de forma suficiente la repetibilidad, la deriva del cero ni la transferencia de esfuerzos en el gripper. El montaje empleó una fijación provisional de la celda.

**Evidencias y procedimiento completos:** [documentación de calibración de celda de carga](./Celda%20de%20Carga%20-%20HZ711/readme.md).

## 5. Experimento 2 — Sensor resistivo FSR

### 5.1 Objetivo y método

Se estudió el **FSR RFP-602** como candidato para detectar cambios de presión en una mordaza del gripper. El trabajo documentado en el repositorio se desarrolló en cinco actividades:

1. Fundamento matemático de la resistencia del sensor, divisor de tensión y conversión a ADC.
2. Prueba sintética de la respuesta eléctrica mediante Python.
3. Prueba física con **ESP32**, aplicando y liberando presión manualmente.
4. Simulación del comportamiento del sensor en **Tinkercad**.
5. Planteamiento de una calibración con masas conocidas y diseño de soporte en **Onshape**.

### 5.2 Resultados

El ensayo físico registró **valores ADC comprendidos entre 0 y 149**, que variaron durante las acciones de aplicación y liberación de presión. Las pruebas y simulaciones documentaron un comportamiento **no lineal** del sensor.

La actividad de calibración describe un procedimiento y un análisis ilustrativo; **no debe interpretarse como una calibración física completa ya validada**. Tampoco se ha demostrado un umbral de fuerza seguro para una granadilla ni se ha probado el cierre automático del gripper utilizando ese umbral.

**Evidencias y actividades completas:** [documentación del sensor FSR](./Sensor%20FSR/README.md).

## 6. Experimento 3 — Transductores piezoeléctricos

### 6.1 Objetivo y método

Se realizó una prueba experimental con dos transductores piezoeléctricos dispuestos cara a cara y separados por una **lámina de plástico no conductor** para evitar el contacto eléctrico directo. El **AD9833**, controlado mediante un **ESP32**, configuró una excitación nominal de **2000 Hz**. El ESP32 adquirió la señal del receptor y aplicó el **algoritmo Goertzel** para obtener magnitudes de componentes espectrales.

Se compararon el estado **emisor apagado** (control RESET del AD9833) y el estado **emisor encendido**, sin cambiar intencionalmente el acoplamiento entre los transductores.

### 6.2 Resultados

| Indicador | Emisor apagado | Emisor encendido |
|---|---:|---:|
| Registros | 33 | 36 |
| Magnitud media Goertzel a 2000 Hz | **1.99** | **4.99** |
| Desviación estándar de la magnitud | 1.06 | 1.29 |

El incremento medio de la componente a 2000 Hz fue de aproximadamente **151.2 %**. Esto constituye evidencia de una respuesta medida asociada al estado del generador. **No prueba por sí solo que la transmisión haya sido exclusivamente mecánica o acústica**, pues el aislamiento entre las superficies metálicas no elimina todas las posibles interferencias eléctricas.

Se conservan **69 registros originales, código Arduino, cinco fotografías del ensayo y tres gráficas** en la carpeta específica.

**Evidencias y procedimiento completos:** [documentación de piezoeléctricos](./Piezoel%C3%A9ctricos%20-%20AD9833/README.md).

## 7. Interpretación conjunta y alcance de TRL 3

Las tres experiencias muestran avances verificables en funciones individuales de LIGURA:

- La **celda de carga** convierte variaciones mecánicas en lecturas digitales que admiten un ajuste con masas conocidas, con una verificación puntual fuera de los puntos usados para calibrar.
- El **FSR** registra cambios de presión mediante variaciones de su señal eléctrica; la fuerza exacta de contacto y el umbral de protección del fruto aún requieren calibración y ensayos de validación.
- Los **piezoeléctricos** producen una respuesta espectral asociada a la excitación nominal de 2000 Hz, aunque todavía deben descartarse otras rutas de acoplamiento.

Los resultados sustentan **pruebas de concepto a nivel de componente**. No acreditan aún una integración validada, la sujeción sin daño de granadillas ni la detección de defectos internos. La asignación formal del nivel de madurez al sistema completo depende del alcance y de los criterios de evaluación aplicados.

## 8. Actividades de validación posteriores

- **Celda de carga:** montar rígidamente el sensor, evaluar repetibilidad, retorno al cero y respuesta en la disposición mecánica final.
- **FSR:** realizar calibración física con condiciones de carga controladas y determinar límites seguros mediante ensayos sobre fruta.
- **Piezoeléctricos:** controlar interferencias, asegurar el acondicionamiento seguro de la entrada ADC y repetir las pruebas con una referencia mecánica y, posteriormente, con granadillas.
- **Integración:** evaluar de manera conjunta el gripper, las lecturas de fuerza, la excitación y la recepción de señales en condiciones reproducibles de laboratorio, como parte de etapas de madurez posteriores.

## 9. Organización y trazabilidad

Este README es el índice general de las pruebas de concepto. Cada carpeta conserva su documentación técnica particular:

- [**Celda de Carga - HZ711**](./Celda%20de%20Carga%20-%20HZ711/readme.md): calibración, código, registros gráficos y evidencia fotográfica.
- [**Sensor FSR**](./Sensor%20FSR/README.md): fundamentos, pruebas sintéticas y experimentales, simulación y propuesta de calibración.
- [**Piezoeléctricos - AD9833**](./Piezoel%C3%A9ctricos%20-%20AD9833/README.md): ensayo comparativo a 2000 Hz, código, registros originales, fotografías y gráficas.
- [**TRL3_LIGURA.md**](./TRL3_LIGURA.md): documentación complementaria de simulaciones estructurales de componentes mecánicos, existente en el repositorio.


## 10. Fuentes

1. [NASA — Technology Readiness Levels](https://esto.nasa.gov/trl/).
2. [TRL 3 — Celda de carga con HX711, repositorio LIGURA](https://github.com/Cesarapcho/PI_Equipo_03/tree/main/Proyecto_Integrador/Talleres/TRL3/Celda%20de%20Carga%20-%20HZ711).
3. [TRL 3 — Sensor FSR, repositorio LIGURA](https://github.com/Cesarapcho/PI_Equipo_03/tree/main/Proyecto_Integrador/Talleres/TRL3/Sensor%20FSR).
4. [TRL 3 — Documentación estructural, repositorio LIGURA](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/TRL3/TRL3_LIGURA.md).
