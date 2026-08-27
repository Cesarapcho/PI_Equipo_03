# Modelado y análisis estructural del cuerpo

## Diseño de la pieza

El cuerpo fue diseñado en **Onshape** como una carcasa para alojar y proteger los componentes del prototipo. La geometría presenta una abertura superior y paredes curvas que forman la estructura exterior.

**Modelo CAD:**  
[Ver modelo en Onshape](https://cad.onshape.com/documents/78c2e73d7651f892ad752b49/w/dd60bbb31d5ebe465a9c0b28/e/fd7549c80ed0fa2590eccf70?renderMode=0&uiState=6a90afe95295ce2a6f08d134)

![Modelo 3D del cuerpo](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/ONSHAPE_ASMAT.png?raw=true)

---

## Análisis estructural

El modelo fue evaluado en **SimScale** mediante un análisis estructural estático. Para la simulación se utilizó **PLA** como material y se establecieron las condiciones de carga y fijación mediante **Force 1** y **Fixed support 2**.

**Simulación:**  
[Ver simulación en SimScale](https://www.simscale.com/workbench/?pid=5247788717663568371&rru=c7c2f2a7-9225-4022-b642-18e2a25e9b6f&ci=17ec0103-c219-4239-9951-8fe30e7bf6b3&mt=SIMULATION_RESULT&ct=SOLUTION_FIELD)

---

## Distribución del esfuerzo

### Vista frontal

![Vista frontal del esfuerzo](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/VF_ASMAT.png?raw=true)

En la vista frontal se observa la distribución del esfuerzo sobre la superficie de la pieza. Los valores más elevados se concentran principalmente en la zona superior.

### Vista lateral

![Vista lateral del esfuerzo](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/VL_ASMAT.png?raw=true)

La vista lateral permite observar la distribución del esfuerzo a lo largo de las paredes curvas de la carcasa. La mayor parte de la superficie presenta valores bajos.

### Vista superior

![Vista superior del esfuerzo](https://github.com/Cesarapcho/PI_Equipo_03/blob/main/Proyecto_Integrador/Talleres/Taller%201/imagenes/VC_ASMAT.png?raw=true)

En la vista superior se aprecia la distribución del esfuerzo alrededor de la abertura. Las mayores concentraciones se presentan cerca del borde de la pieza.

---

## Resultado de la simulación

De acuerdo con la escala mostrada en SimScale, el esfuerzo de Von Mises alcanza aproximadamente:

**σVM,max ≈ 0.1746 kPa**

Este valor corresponde al extremo superior de la escala mostrada en la simulación.

| Parámetro | Resultado |
|---|---:|
| Material | PLA |
| Tipo de análisis | Estructural estático |
| Resultado evaluado | Esfuerzo de Von Mises |
| Esfuerzo máximo aprox. | **0.1746 kPa** |
| Condición de carga | Force 1 |
| Condición de fijación | Fixed support 2 |

---

## Conclusión

El análisis estructural permitió observar la distribución del esfuerzo sobre el cuerpo diseñado. El valor máximo obtenido es aproximadamente **0.1746 kPa**, concentrándose principalmente en la zona superior de la pieza.

Los resultados permiten identificar las regiones de mayor exigencia mecánica y sirven como referencia para realizar futuras mejoras en la geometría del cuerpo.

---

## Enlaces del proyecto

### Modelo CAD

[**Abrir modelo en Onshape**](https://cad.onshape.com/documents/78c2e73d7651f892ad752b49/w/dd60bbb31d5ebe465a9c0b28/e/fd7549c80ed0fa2590eccf70?renderMode=0&uiState=6a90afe95295ce2a6f08d134)

### Simulación estructural

[**Abrir simulación en SimScale**](https://www.simscale.com/workbench/?pid=5247788717663568371&rru=c7c2f2a7-9225-4022-b642-18e2a25e9b6f&ci=17ec0103-c219-4239-9951-8fe30e7bf6b3&mt=SIMULATION_RESULT&ct=SOLUTION_FIELD)
