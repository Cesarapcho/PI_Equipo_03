# Modelado y análisis estructural de la tapa de soporte

## Diseño de la pieza

La pieza denominada **"tapa_granadilla"** fue modelada en Onshape con una geometría ranurada y perfiles curvos, diseñada específicamente para cumplir funciones de sujeción, tope y guía dentro de la interfaz mecánica del banco de pruebas de la granadilla.

**Modelo CAD:**
https://cad.onshape.com/documents/9646bf9db203edd03243ce51/w/271f0e1e4154f239f0ceebcc/e/28c914a937d1f98a4f0c58fb

<img width="1600" height="758" alt="t3" src="https://github.com/user-attachments/assets/7d6ca09c-968a-4fae-985b-9de14b424783" />


---

## Resultados de la simulación

El análisis estático realizado en SimScale permite visualizar la distribución de los esfuerzos internos generados sobre la pieza ante la aplicación de las cargas operativas (`Force 1` y `Fixed support 2`).

**Vista superior de la simulación:**
<img width="1600" height="779" alt="t1" src="https://github.com/user-attachments/assets/56ecc8e7-085e-4312-8b0e-b807befb42be" />


**Vista lateral de la simulación:**
<img width="1600" height="771" alt="t2" src="https://github.com/user-attachments/assets/f0bfe57f-8828-44f7-a979-cee6878a42eb" />


De acuerdo con la escala de colores de la simulación, los niveles de esfuerzo se mantienen en rangos mínimos, registrando un valor pico que alcanza aproximadamente:

$$\sigma_{\text{VM,max}} \approx 18.54 \text{ Pascales}$$ 

| Parámetro técnico | Resultado de la simulación |
| :--- | :--- |
| **Material** | PLA |
| **Tipo de análisis** | Estructural estático |
| **Resultado evaluado** | Esfuerzo de Von Mises |
| **Esfuerzo máximo aprox.** | 18.54 Pa |
| **Condición de carga** | Force 1 |
| **Condición de fijación** | Fixed support 2 |

---

## Conclusión

Los resultados de la simulación estructural demuestran que el nivel de esfuerzo al que se somete la pieza es extremadamente bajo en comparación con el límite de fluencia del material PLA. Esto garantiza que la geometría propuesta cuenta con la resistencia mecánica adecuada para soportar las exigencias operativas del prototipo sin sufrir deformaciones ni fallas estructurales.

---

## Enlaces del proyecto

* **Modelo CAD:** https://cad.onshape.com/documents/9646bf9db203edd03243ce51/w/271f0e1e4154f239f0ceebcc/e/28c914a937d1f98a4f0c58fb
* **Simulación estructural:** https://www.simscale.com/workbench/?pid=6081502423614524530&mi=spec:cbf36295-95c4-4e0c-80cb-aaf1c32c3801%2Cservice:SIMULATION%2Cstrategy:4











