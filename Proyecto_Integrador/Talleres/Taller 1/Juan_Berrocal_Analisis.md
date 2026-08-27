# Modelado y simulación del cuerpo

## Herramientas utilizadas

Para el desarrollo del cuerpo del prototipo se utilizaron herramientas de modelado tridimensional y simulación mediante el método de elementos finitos.

El modelado de la pieza se realizó en **Onshape**, donde se construyó la geometría del cuerpo considerando sus dimensiones, abertura central y puntos de fijación.

**Modelo 3D en Onshape:**  
[Modelo del cuerpo en Onshape](https://cad.onshape.com/documents/8faf323b3ad277acf5680e67/w/7f5d397c40762628c5e2da28/e/1d246344b054494bdf4784c7?renderMode=0&uiState=6a90ae6b04acdaf3b43cb3cc)

Posteriormente, el modelo fue analizado mediante una simulación estructural estática en **SimScale**, con el objetivo de evaluar la distribución de esfuerzos y el desplazamiento producido por la carga aplicada.

**Simulación en SimScale:**  
[Simulación estructural en SimScale](https://www.simscale.com/workbench/?pid=9096215687583154772)

---

# Modelo del cuerpo

![Modelo 3D del cuerpo](imagenes/juan_modelado.png)

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
- **Componente de fuerza:** **Fz = -20 N**.
- **Condiciones de fijación:** cuatro puntos de montaje.
- **Resultados analizados:** esfuerzo de Von Mises y desplazamiento.

## Cálculo de la carga equivalente

La relación entre la fuerza, la masa y la aceleración gravitacional se expresa mediante:

**F = m × g**

Despejando la masa:

**m = F / g**

Considerando:

- **F = 20 N**
- **g = 9.81 m/s²**

se obtiene:

**m = 20 N / 9.81 m/s²**

**m ≈ 2.04 kg**

Por lo tanto, una fuerza de **20 N** equivale aproximadamente al peso de una masa de **2.04 kg** bajo una aceleración gravitacional de **9.81 m/s²**.

> **Nota:** Esta equivalencia se utiliza únicamente para interpretar la magnitud de la fuerza aplicada en la simulación. No significa que el cuerpo deba soportar físicamente una masa de 2.04 kg durante su funcionamiento normal.

---

# Esfuerzo de Von Mises

## Vista frontal

![Esfuerzo de Von Mises - Vista frontal](imagenes/Juan_VMS_P1_Cuerpo_Frontal.png)

El **esfuerzo de Von Mises** permite identificar las regiones de la pieza que presentan una mayor exigencia mecánica ante la carga aplicada.

En la vista frontal se observa que los mayores valores de esfuerzo se concentran principalmente en la **zona superior del cuerpo**, mientras que gran parte de la estructura presenta valores considerablemente menores.

El valor máximo mostrado en la escala de la simulación es aproximadamente:

**σVM,max ≈ 99.49 kPa**

Para expresar este resultado en megapascales se utiliza la equivalencia:

**1 MPa = 1000 kPa**

Por lo tanto:

**99.49 kPa / 1000 = 0.09949 MPa**

Así, el esfuerzo máximo de Von Mises obtenido es aproximadamente:

**σVM,max ≈ 0.09949 MPa**

Las regiones representadas mediante colores **amarillos, naranjas y rojos** corresponden a las zonas donde se concentran los mayores esfuerzos, mientras que las regiones **azules** presentan niveles de esfuerzo menores.

---

## Vista superior

![Esfuerzo de Von Mises - Vista superior](imagenes/Juan_VMS_P1_Cuerpo_Superior.png)

La vista superior permite observar la distribución tridimensional del esfuerzo sobre el cuerpo.

Se aprecia que los mayores niveles de esfuerzo continúan concentrándose principalmente en la región superior de la pieza. Por otro lado, las zonas alejadas de la aplicación de la carga presentan valores inferiores.

Esta distribución se relaciona con la forma en que la carga vertical se transmite a través de la estructura hacia los puntos de fijación.

La representación mediante colores permite localizar visualmente las zonas que presentan una mayor exigencia mecánica y que podrían ser consideradas en futuras modificaciones de la geometría.

---

# Desplazamiento

El **desplazamiento** representa cuánto se deforma la pieza respecto a su posición original como consecuencia de la carga aplicada.

Para este análisis se considera una fuerza de:

**Fz = -20 N**

aplicada en la dirección negativa del eje Z.

El desplazamiento máximo obtenido en la simulación es aproximadamente:

**Dz,max ≈ 0.00767 mm**

Este valor representa una deformación muy pequeña en comparación con las dimensiones generales de la pieza.

El análisis del desplazamiento permite determinar si la deformación producida por la carga puede afectar la estabilidad dimensional de la pieza o interferir con el ensamblaje de los demás componentes.

En este caso, el valor reducido del desplazamiento indica que, bajo las condiciones de carga simuladas, la deformación del cuerpo es pequeña.

---

# Interpretación de los resultados

La simulación permitió evaluar el comportamiento estructural del cuerpo frente a una carga vertical de:

**Fz = -20 N**

El signo negativo indica que la fuerza se aplica en la dirección negativa del eje Z.

Los resultados de **Von Mises** muestran que las mayores concentraciones de esfuerzo se encuentran principalmente en la **zona superior del cuerpo**. Esto permite identificar dicha región como una de las zonas de mayor exigencia mecánica de la geometría.

El esfuerzo máximo observado en la simulación es aproximadamente:

**σVM,max ≈ 99.49 kPa**

equivalente a:

**σVM,max ≈ 0.09949 MPa**

Por otra parte, el desplazamiento máximo obtenido es aproximadamente:

**Dz,max ≈ 0.00767 mm**

Este desplazamiento es reducido, por lo que la deformación producida por la carga aplicada es pequeña respecto a las dimensiones generales del cuerpo.

En conjunto, los resultados de esfuerzo y desplazamiento permiten identificar las zonas de mayor exigencia y evaluar el comportamiento estructural de la pieza bajo las condiciones establecidas.

---

# Conclusión

La simulación estructural realizada sobre el cuerpo permitió evaluar su comportamiento mecánico frente a una carga vertical de **20 N aplicada en la dirección negativa del eje Z**, considerando **PLA** como material de referencia.

El análisis de Von Mises mostró un esfuerzo máximo aproximado de:

**99.49 kPa = 0.09949 MPa**

La mayor concentración de esfuerzos se localizó principalmente en la **zona superior del cuerpo**, mientras que gran parte de la estructura presentó valores menores.

El desplazamiento máximo obtenido fue aproximadamente:

**0.00767 mm**

Este valor indica una deformación pequeña bajo las condiciones de carga analizadas.

En conjunto, los resultados proporcionan una primera evaluación del comportamiento estructural de la pieza antes de su fabricación. Además, permiten identificar las regiones que podrían ser consideradas en futuras iteraciones del diseño, especialmente si se modifican el espesor, la geometría o las condiciones de carga.

---

# Enlaces del proyecto

## Modelo CAD

[**Abrir modelo del cuerpo en Onshape**](https://cad.onshape.com/documents/8faf323b3ad277acf5680e67/w/7f5d397c40762628c5e2da28/e/1d246344b054494bdf4784c7?renderMode=0&uiState=6a90ae6b04acdaf3b43cb3cc)

## Simulación estructural

[**Abrir simulación en SimScale**](https://www.simscale.com/workbench/?pid=9096215687583154772)
