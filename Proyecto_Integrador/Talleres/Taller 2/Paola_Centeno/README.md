#  Sistema de Sensado de Masa

### Taller de EasyEDA

Diseño de un sistema electrónico de sensado de masa utilizando una **celda de carga**, un **HX711** y un **ESP32 DevKitC**.

**Autora:** Paola Centeno  
**Revisado por:** Maria Rejas

---

## 📌 Descripción

El sistema permite adquirir la señal generada por una celda de carga para determinar la masa de un objeto.

La señal de la celda de carga es acondicionada y digitalizada mediante el **HX711** y posteriormente enviada al **ESP32** para su procesamiento.

### Flujo general

```text
Celda de carga
      │
      │ E+ / E- / A+ / A-
      ▼
    HX711
      │
      │ DATA / CLOCK
      ▼
    ESP32
      │
      ▼
Procesamiento
