# Actividad 01 — Fundamento matemático del sensor FSR

**Proyecto:** Ligura — Sistema de evaluación no destructiva de granadillas mediante excitación vibratoria y análisis vibroacústico  
**Etapa:** TRL 3 — Prueba de concepto  
**Componente evaluado:** Sensor resistivo de fuerza (FSR)  
**Tipo de prueba:** Análisis teórico y cálculos matemáticos  
**Estado:** Modelo teórico desarrollado; pendiente de contrastar con calibración experimental.

## 1. Objetivo

Analizar el principio de funcionamiento del sensor FSR y modelar la relación entre su resistencia eléctrica y el voltaje que leerá el ESP32, con miras a detectar la presión ejercida por el gripper sobre la granadilla.

## 2. Aplicación del FSR en Ligura

El FSR estará ubicado en uno de los brazos del gripper. Al entrar en contacto con la granadilla, la fuerza normal sobre la superficie sensible modificará su resistencia. Esta respuesta se convertirá en una señal eléctrica que el ESP32 podrá leer para monitorear la sujeción.

**Alcance:** el FSR no proporciona directamente una medida de fuerza en newtons. La relación fuerza–señal depende del sensor, la superficie de contacto y el montaje, por lo que requiere calibración. Tampoco debe asumirse que la fuerza medida en un punto equivale a toda la fuerza de agarre.

## 3. Principio de funcionamiento

En general, la resistencia del FSR **disminuye cuando aumenta la fuerza normal aplicada**. Esta relación es no lineal y puede presentar dispersión e histéresis. Para obtener una tensión de lectura se utiliza un divisor de voltaje compuesto por el FSR y una resistencia fija.

### 3.1. Circuito propuesto

```text
   3V3 (ESP32)
       |
      FSR
       |
       +---------- GPIO 34 (ADC)
       |
     10 kΩ
       |
      GND
```

Parámetros del modelo:

| Símbolo | Descripción | Valor o unidad |
|---|---|---|
| $V_{cc}$ | Alimentación | 3.3 V |
| $R_{FSR}$ | Resistencia del sensor | Variable (Ω) |
| $R_{fija}$ | Resistencia del divisor | 10 000 Ω |
| $V_{out}$ | Tensión en el punto intermedio | V |

## 4. Desarrollo matemático

Por la ley de Ohm, la corriente en el divisor ideal es:

$$
I=\frac{V_{cc}}{R_{FSR}+R_{fija}}
$$

El voltaje medido sobre la resistencia fija es:

$$
V_{out}=I\,R_{fija}
$$

Por tanto:

$$
\boxed{V_{out}=V_{cc}\frac{R_{fija}}{R_{FSR}+R_{fija}}}
$$

Sustituyendo los parámetros propuestos:

$$
\boxed{V_{out}=3.3\frac{10000}{R_{FSR}+10000}}
$$

Si se desea despejar la resistencia a partir de una tensión ideal positiva:

$$
R_{FSR}=R_{fija}\left(\frac{V_{cc}}{V_{out}}-1\right)
$$

Este despeje es una relación eléctrica teórica; no representa por sí mismo una calibración de fuerza.

### 4.1. Lectura ADC ideal

Para una conversión lineal ideal de 12 bits y una escala hipotética de 0 a 3.3 V, se obtiene una lectura aproximada que se redondea al entero más cercano:

$$
ADC_{ideal}\approx 4095\frac{V_{out}}{3.3}
$$

**Advertencia:** la respuesta real del ADC del ESP32 no es perfectamente lineal ni coincide necesariamente con esta aproximación, incluso configurando la atenuación. La conversión real deberá comprobarse experimentalmente.

## 5. Ejercicio matemático

Para una resistencia hipotética del FSR de **20 kΩ**:

$$
V_{out}=3.3\frac{10000}{20000+10000}=1.1\,V
$$

Y la lectura ADC ideal aproximada sería:

$$
ADC_{ideal}=4095\frac{1.1}{3.3}=1365
$$

## 6. Tabla de resultados teóricos

| Resistencia hipotética del FSR | Voltaje calculado | ADC ideal aproximado |
|---:|---:|---:|
| 100 kΩ | 0.300 V | 372 |
| 50 kΩ | 0.550 V | 683 |
| 20 kΩ | 1.100 V | 1365 |
| 10 kΩ | 1.650 V | 2048 |
| 5 kΩ | 2.200 V | 2730 |
| 1 kΩ | 3.000 V | 3723 |

Los valores son **supuestos eléctricos para análisis matemático**, no resistencias medidas ni equivalencias de fuerza aplicada.

## 7. Interpretación

Con este montaje, una menor resistencia del FSR provoca un mayor voltaje de salida. Por ello, la señal del ADC puede emplearse como indicador preliminar de cambios de presión durante la sujeción. Sin embargo, la magnitud exacta de la fuerza y el umbral seguro del gripper no pueden deducirse de esta tabla.

## 8. Conclusión

Se estableció un modelo matemático para transformar cambios de resistencia del FSR en cambios de voltaje medibles por el ESP32. El análisis fundamenta la adquisición de una señal de contacto, pero **no valida aún una medida de fuerza ni un umbral de sujeción seguro**. Esas afirmaciones requerirán calibración y ensayos físicos posteriores.

## 9. Evidencia y relación con las siguientes actividades

- **Actividad 02:** implementación numérica del modelo con resistencias sintéticas y visualización de resultados.
- **Actividad 03:** prueba física individual del FSR y lectura ADC mediante ESP32.
- **Actividad 04:** simulación del sensor FSR en Tinkercad.
- **Actividad 05:** procedimiento de calibración con masas de referencia.
- **Actividad 06:** análisis general de resultados y limitaciones.
