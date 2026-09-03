# Sistema de Sensado de Masa

## Taller 2 - EasyEDA

Diseño de un sistema electrónico para el **sensado de masa** utilizando una **celda de carga**, el convertidor analógico-digital **HX711** y un microcontrolador.

**Autora:** Paola Centeno  
**Curso:** Proyecto Integrador  
**Taller:** Taller 2 - EasyEDA  
**Fecha:** 03/09/2026  

---

## 1. Descripción

En este taller se desarrolló el diseño electrónico de un sistema de **sensado de masa** utilizando el software **EasyEDA**.

El sistema emplea una **celda de carga** para detectar la fuerza generada por el peso de un objeto. Debido a que la señal eléctrica producida por la celda de carga es de muy baja amplitud, se utiliza el módulo **HX711**, encargado de amplificar y convertir dicha señal a formato digital.

Posteriormente, la información obtenida puede ser enviada a un microcontrolador para realizar el procesamiento y determinar la masa del objeto.

### Flujo general del sistema

```text
┌──────────────────┐
│  Celda de carga  │
└────────┬─────────┘
         │
         │ E+ / E- / A+ / A-
         ▼
┌──────────────────┐
│      HX711       │
│ Amplificación y  │
│ digitalización   │
└────────┬─────────┘
         │
         │ DATA / CLOCK
         ▼
┌──────────────────┐
│ Microcontrolador │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│ Procesamiento de │
│       masa       │
└──────────────────┘
```

---

## 2. Objetivo

Diseñar en **EasyEDA** el esquemático y la placa PCB de un sistema capaz de adquirir la señal proveniente de una celda de carga mediante el convertidor **HX711**.

Durante el desarrollo del taller se buscó:

- Diseñar el esquemático electrónico del sistema.
- Realizar correctamente las conexiones entre los componentes.
- Asignar los footprints correspondientes.
- Distribuir los componentes sobre la PCB.
- Realizar el enrutamiento de las pistas.
- Incorporar un plano de tierra conectado a **GND**.
- Verificar el diseño mediante **DRC (Design Rule Check)**.
- Visualizar el resultado final en 2D y 3D.
- Generar los archivos **Gerber** para una futura fabricación.

---

## 3. Componentes principales

| Componente | Función |
|---|---|
| **Celda de carga** | Detecta la fuerza producida por el peso del objeto |
| **HX711** | Amplifica y digitaliza la señal de la celda de carga |
| **Microcontrolador** | Recibe y procesa los datos obtenidos |
| **Capacitores** | Ayudan al filtrado y estabilización de la alimentación |
| **Conectores** | Permiten conectar los dispositivos externos al circuito |
| **PCB** | Integra físicamente los componentes y conexiones del sistema |

---

## 4. Esquemático electrónico

El esquemático representa las conexiones eléctricas necesarias para realizar la adquisición de la señal proveniente de la celda de carga.

La celda de carga se conecta al **HX711** mediante las terminales:

- **E+**: excitación positiva.
- **E-**: excitación negativa.
- **A+**: entrada diferencial positiva.
- **A-**: entrada diferencial negativa.

El HX711 se encarga de amplificar la señal proveniente de la celda y convertirla en información digital.

La comunicación con el microcontrolador se realiza mediante dos señales principales:

- **DATA**: transmisión de los datos obtenidos.
- **CLOCK**: señal de reloj para controlar la comunicación.

<p align="center">
  <img src="./SCH_Sensado%20de%20Masa%20HX711_1-P1_2026-09-03.png" alt="Esquemático del sistema de sensado de masa" width="950">
</p>

<p align="center">
  <strong>Figura 1. Esquemático electrónico del sistema de sensado de masa.</strong>
</p>

---

## 5. Diseño de la PCB

A partir del esquemático electrónico se desarrolló el diseño físico de la placa PCB.

Durante esta etapa se realizó la distribución de los componentes y el trazado de las pistas considerando aspectos como:

- Organización de los componentes.
- Reducción de la longitud de las pistas.
- Separación adecuada entre conexiones.
- Accesibilidad de los conectores.
- Distribución de las líneas de alimentación.
- Conexión adecuada a tierra.
- Reducción de cruces innecesarios entre pistas.

---

## 5.1 Vista 2D de la PCB

La vista 2D permite observar la distribución de los componentes, pads, pistas y áreas de cobre utilizadas en la placa.

<p align="center">
  <img src="./2D_PCB1_2026-09-03.png" alt="Diseño 2D de la PCB" width="850">
</p>

<p align="center">
  <strong>Figura 2. Diseño 2D de la PCB desarrollado en EasyEDA.</strong>
</p>

---

## 5.2 Vista 3D de la PCB

EasyEDA permite generar una representación tridimensional de la placa para visualizar de forma más clara la distribución y orientación de los componentes.

Esta vista resulta útil para comprobar cómo se verá físicamente la PCB antes de realizar su fabricación.

<p align="center">
  <img src="./3D_PCB1_2026-09-03.png" alt="Vista 3D de la PCB" width="850">
</p>

<p align="center">
  <strong>Figura 3. Visualización 3D de la PCB.</strong>
</p>

---

## 6. Plano de tierra

Para el diseño de la PCB se incorporó un **Copper Area** conectado a la red **GND**, formando un plano de tierra sobre la placa.

El plano de tierra permite:

- Facilitar el retorno de corriente.
- Reducir la longitud de las conexiones hacia GND.
- Mejorar la distribución eléctrica de la placa.
- Reducir posibles interferencias y ruido eléctrico.
- Aprovechar de mejor manera las áreas libres de cobre de la PCB.

Después de definir el área de cobre se realizó la reconstrucción del plano para comprobar su correcta conexión con los pads asociados a **GND**.

---

## 7. Enrutamiento de pistas

Las conexiones definidas en el esquemático fueron trasladadas al diseño de PCB mediante pistas de cobre.

Durante el proceso de enrutamiento se procuró:

- Evitar cruces entre pistas.
- Mantener recorridos cortos.
- Facilitar la conexión entre los diferentes componentes.
- Utilizar un ancho adecuado para las pistas de alimentación.
- Mantener una distribución ordenada de la placa.

Las pistas correspondientes a alimentación fueron consideradas con un mayor ancho para proporcionar una conexión eléctrica adecuada.

---

## 8. Verificación del diseño

Antes de generar los archivos para fabricación se realizó una comprobación utilizando la herramienta:

### DRC - Design Rule Check

Esta herramienta permite detectar posibles problemas en el diseño, como:

- Pistas demasiado cercanas.
- Pads sin conectar.
- Conexiones incompletas.
- Separaciones inferiores a las reglas establecidas.
- Conflictos entre elementos de cobre.
- Violaciones de las reglas de diseño de la PCB.

Luego de realizar las correcciones necesarias, el diseño final fue verificado hasta obtener una placa **sin errores de DRC**.

---

## 9. Archivos Gerber

Como última etapa del diseño se generaron los archivos **Gerber**.

Estos archivos contienen la información necesaria para que un fabricante pueda producir físicamente la PCB.

El archivo generado se encuentra disponible dentro de este repositorio:

### [Descargar archivos Gerber](./Gerber_PCB1_2026-09-03.zip)

Los archivos Gerber incluyen información relacionada con:

- Capas de cobre.
- Máscara de soldadura.
- Serigrafía.
- Pads.
- Perforaciones.
- Contorno de la PCB.
- Dimensiones de fabricación.

---

## 10. Proceso realizado

El desarrollo de la PCB siguió el siguiente flujo de trabajo:

```text
Diseño del esquemático
        │
        ▼
Asignación de footprints
        │
        ▼
Conversión del esquemático a PCB
        │
        ▼
Distribución de componentes
        │
        ▼
Enrutamiento de pistas
        │
        ▼
Creación del plano GND
        │
        ▼
Verificación mediante DRC
        │
        ▼
Visualización 2D y 3D
        │
        ▼
Generación de archivos Gerber
```

---

## 11. Resultado final

Como resultado del taller se obtuvo el diseño completo de una PCB destinada a la adquisición de señales de una **celda de carga utilizando el HX711**.

El trabajo permitió desarrollar las principales etapas necesarias para pasar desde un esquema electrónico hasta un diseño de PCB preparado para fabricación.

Se completaron las siguientes actividades:

- Diseño del esquemático.
- Selección y asignación de footprints.
- Distribución de componentes.
- Diseño de pistas.
- Creación del plano de tierra.
- Comprobación mediante DRC.
- Visualización 2D.
- Visualización 3D.
- Generación de archivos Gerber.

De esta manera, el diseño queda preparado para una futura etapa de **fabricación, ensamblaje y pruebas experimentales**.

---

## 12. Archivos del repositorio

| Archivo | Descripción |
|---|---|
| `README.md` | Documentación del taller |
| `SCH_Sensado de Masa HX711_1-P1_2026-09-03.png` | Imagen del esquemático electrónico |
| `2D_PCB1_2026-09-03.png` | Vista 2D de la PCB |
| `3D_PCB1_2026-09-03.png` | Vista 3D de la PCB |
| `Gerber_PCB1_2026-09-03.zip` | Archivos Gerber para fabricación |

---

## 13. Herramienta utilizada

El diseño electrónico fue desarrollado utilizando:

**EasyEDA**

EasyEDA permite realizar de manera integrada:

- Diseño de esquemáticos electrónicos.
- Diseño de PCB.
- Enrutamiento de pistas.
- Verificación mediante DRC.
- Visualización 3D.
- Generación de archivos Gerber.

---

<p align="center">
  <strong>Universidad Peruana Cayetano Heredia</strong>
  <br>
  Proyecto Integrador
  <br>
  Taller 2 - EasyEDA
  <br><br>
  <strong>Paola Centeno</strong>
</p>
