# Sistema de Sensado de Masa

## Taller 2 - EasyEDA

Diseño de un sistema electrónico para el **sensado de masa** utilizando una **celda de carga**, el convertidor analógico-digital **HX711** y un **ESP32 DevKitC**.

**Autora:** Paola Centeno  
**Curso:** Proyecto Integrador  
**Fecha:** 03/09/2026  

---

## 1. Descripción

El sistema utiliza una **celda de carga** para detectar la fuerza producida por el peso de un objeto.

La señal generada por la celda es de baja amplitud, por lo que se utiliza el **HX711** para amplificarla y convertirla a formato digital. Posteriormente, los datos son enviados al **ESP32** para su procesamiento.

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
