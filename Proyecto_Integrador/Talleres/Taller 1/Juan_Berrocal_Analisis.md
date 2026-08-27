# Modelado y simulación del cuerpo

## Herramientas utilizadas

Para el desarrollo del cuerpo del prototipo se utilizaron herramientas de modelado tridimensional y simulación mediante el método de elementos finitos.

El modelado de la pieza se realizó en **Onshape**, donde se construyó la geometría del cuerpo considerando sus dimensiones, abertura central y puntos de fijación.

🔗 **Modelo 3D en Onshape:**  
https://cad.onshape.com/documents/8faf323b3ad277acf5680e67/w/7f5d397c40762628c5e2da28/e/1d246344b054494bdf4784c7?renderMode=0&uiState=6a90ae6b04acdaf3b43cb3cc

Posteriormente, el modelo fue analizado mediante una simulación estructural estática en **SimScale**, con el objetivo de evaluar la distribución de esfuerzos y el desplazamiento producido por la carga aplicada.

🔗 **Simulación en SimScale:**  
https://www.simscale.com/workbench/?pid=9096215687583154772

---

# Modelo del cuerpo

![Modelo 3D del cuerpo](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/juan_modelado.png?raw=true)

El cuerpo constituye una de las piezas principales de la estructura del prototipo. Su geometría fue diseñada para proporcionar soporte a los componentes internos y mantener una estructura compacta.

La pieza presenta una abertura central destinada a proporcionar el espacio necesario para los componentes internos del sistema. Asimismo, cuenta con cuatro puntos de fijación que permiten realizar su unión con las demás partes del dispositivo.

El modelo fue desarrollado considerando una fabricación mediante **impresión 3D en PLA**.

---

# Simulación estructural

Para evaluar el comportamiento mecánico del cuerpo se realizó una **simulación estructural estática** mediante el método de elementos finitos.

La simulación se configuró con las siguientes condiciones:

- **Material:** PLA.
- **Tipo de análisis:** estático.
- **Carga aplicada:** 20 N.
- **Dirección de la carga:** eje Z.
- **Sentido de la carga:** negativo.
- **Componente de fuerza:** \(F_z = -20\,\text{N}\).
- **Condiciones de fijación:** cuatro puntos de montaje.
- **Resultados analizados:** esfuerzo de Von Mises y desplazamiento.

### Cálculo de la carga equivalente

La fuerza aplicada de 20 N puede expresarse como una masa equivalente utilizando la segunda ley de Newton:

\[
F = m \cdot g
\]

Despejando la masa:

\[
m = \frac{F}{g}
\]

Considerando:

\[
F = 20\,\text{N}
\]

\[
g = 9.81\,\text{m/s}^2
\]

se obtiene:

\[
m = \frac{20\,\text{N}}{9.81\,\text{m/s}^2}
\]

\[
\boxed{m \approx 2.04\,\text{kg}}
\]

Por lo tanto, una carga de **20 N** equivale aproximadamente a la fuerza gravitacional ejercida por una masa de **2.04 kg**.

> **Nota:** esta equivalencia se utiliza únicamente para interpretar la magnitud de la fuerza aplicada en la simulación. No significa que el cuerpo del prototipo tenga que soportar físicamente una masa de 2.04 kg durante su funcionamiento normal.

---

# Esfuerzo de Von Mises

## Vista frontal

![Esfuerzo de Von Mises - Vista frontal](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/Juan_VMS_P1_Cuerpo_Frontal.png?raw=true)

El **esfuerzo de Von Mises** permite identificar las regiones de la pieza que presentan una mayor exigencia mecánica ante la carga aplicada.

En la vista frontal se observa que los mayores valores de esfuerzo se concentran principalmente en la **zona superior del cuerpo**, mientras que gran parte de la estructura presenta valores considerablemente menores.

El valor máximo mostrado en la escala de la simulación es aproximadamente:

\[
\sigma_{\mathrm{VM,max}} = 99.49\,\text{kPa}
\]

Realizando la conversión a megapascales:

\[
99.49\,\text{kPa}
\times
\frac{1\,\text{MPa}}{1000\,\text{kPa}}
=
0.09949\,\text{MPa}
\]

Por lo tanto:

\[
\boxed{\sigma_{\mathrm{VM,max}} \approx 0.09949\,\text{MPa}}
\]

Las regiones representadas con colores amarillos, naranjas y rojos corresponden a las zonas donde se concentran los mayores esfuerzos, mientras que las regiones azules presentan niveles de esfuerzo menores.

---

## Vista superior

![Esfuerzo de Von Mises - Vista superior](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/Juan_VMS_P1_Cuerpo_Superior.png?raw=true)

La vista superior permite observar la distribución tridimensional del esfuerzo sobre el cuerpo.

Se aprecia que los mayores niveles de esfuerzo permanecen concentrados principalmente en la región superior de la pieza. Por otro lado, las zonas alejadas de la aplicación de la carga presentan valores inferiores.

Esta distribución se relaciona con la forma en que la carga vertical se transmite a través de la estructura hacia los puntos de fijación.

La representación mediante colores permite localizar visualmente las zonas que requieren mayor atención durante una posible optimización de la geometría.

---

# Desplazamiento

El **desplazamiento** representa cuánto se deforma la pieza respecto a su posición original como consecuencia de la carga aplicada.

Para este análisis se considera una fuerza de:

\[
\boxed{F_z=-20\,\text{N}}
\]

aplicada en la dirección negativa del eje Z.

El análisis del desplazamiento permite determinar si la deformación producida por la carga puede afectar la estabilidad dimensional de la pieza o interferir con el ensamblaje de los demás componentes.

La interpretación debe realizarse tomando como referencia el valor máximo indicado por la escala de desplazamiento obtenida en la simulación.

Un desplazamiento pequeño respecto a las dimensiones generales de la pieza indica que la deformación producida bajo las condiciones analizadas es reducida.

---

# Interpretación de los resultados

La simulación permitió evaluar el comportamiento estructural del cuerpo frente a una carga vertical de:

\[
\boxed{F_z=-20\,\text{N}}
\]

Los resultados de **Von Mises** muestran que las mayores concentraciones de esfuerzo se encuentran principalmente en la zona superior del cuerpo. Esto permite identificar dicha región como una de las zonas de mayor exigencia mecánica de la geometría.

El esfuerzo máximo observado en la simulación es:

\[
\boxed{\sigma_{\mathrm{VM,max}}\approx99.49\,\text{kPa}}
\]

o, expresado en megapascales:

\[
\boxed{\sigma_{\mathrm{VM,max}}\approx0.09949\,\text{MPa}}
\]

Por otra parte, el análisis de desplazamiento permite evaluar la deformación de la pieza bajo la misma condición de carga. Este resultado es importante debido a que una pieza puede presentar esfuerzos aceptables, pero una deformación excesiva podría afectar el ensamblaje o el funcionamiento del dispositivo.

En conjunto, ambos resultados permiten identificar las zonas críticas del cuerpo y sirven como referencia para futuras modificaciones de la geometría.

---

# Conclusión

La simulación estructural realizada sobre el cuerpo permitió evaluar su comportamiento mecánico frente a una carga vertical de **20 N aplicada en la dirección negativa del eje Z**, considerando **PLA** como material de referencia.

El análisis de Von Mises mostró un esfuerzo máximo aproximado de:

\[
\boxed{99.49\,\text{kPa}=0.09949\,\text{MPa}}
\]

La mayor concentración de esfuerzos se localizó principalmente en la zona superior del cuerpo, mientras que el resto de la estructura presentó valores menores.

El análisis de desplazamiento complementa estos resultados al permitir determinar la deformación producida por la carga aplicada. De esta manera, la simulación proporciona una primera evaluación del comportamiento estructural de la pieza antes de su fabricación.

Los resultados obtenidos también permiten identificar las regiones que podrían ser consideradas en futuras iteraciones del diseño, especialmente en caso de modificar el espesor, la geometría o las condiciones de carga.

---

# Enlaces del proyecto

## Modelo CAD

🔗 **[Abrir modelo del cuerpo en Onshape](https://cad.onshape.com/documents/8faf323b3ad277acf5680e67/w/7f5d397c40762628c5e2da28/e/1d246344b054494bdf4784c7?renderMode=0&uiState=6a90ae6b04acdaf3b43cb3cc)**

## Simulación estructural

🔗 **[Abrir simulación en SimScale](https://www.simscale.com/workbench/?pid=9096215687583154772)**
