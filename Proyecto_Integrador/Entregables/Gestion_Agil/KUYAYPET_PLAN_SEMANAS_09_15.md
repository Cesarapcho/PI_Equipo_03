# KuyayPet — Tablero de actividades (Semanas 9–15)

> Periodo de trabajo: semana 9 a semana 15.  
> Hitos de Sprint: semanas 9, 12 y 15.  
> Fuente funcional: Lista de Historias de Usuario de KuyayPet (HU-01 a HU-26).  
> Estados del tablero: **Pendiente**, **En proceso** y **Hecho**.

## Estado inicial

### Hecho
- [x] Se cuenta con la lista de historias de usuario HU-01 a HU-26.
- [x] Se cuenta con enunciados, criterios de aceptación y prototipos para las historias documentadas en el archivo de historias de usuario.

> Esto registra únicamente el trabajo documental visible en el material proporcionado; no afirma que funcionalidades de software ya estén implementadas.

### En proceso
- [ ] **Semana 9 — Sprint 1:** planificación del sprint, selección de historias, división en tareas y definición de criterios de aceptación verificables.
- [ ] Acordar responsables y estimaciones de cada tarea con el equipo.

### Pendiente
- [ ] Implementación, integración y pruebas de las funcionalidades asignadas a cada semana.
- [ ] Registrar evidencias (capturas, video, commits y resultados de pruebas) al terminar cada tarea.

---

## Plan semanal

| Semana | Hito / enfoque | Actividades | Historias relacionadas | Estado inicial |
|---|---|---|---|---|
| **9** | **Sprint 1 — planificación e inicio** | Revisar Product Backlog; priorizar historias; estimar y asignar tareas; revisar prototipos y criterios; acordar objetivo del sprint. Preparar base del flujo de autenticación y estructura inicial. | HU-01, HU-21; preparación técnica transversal | **En proceso** |
| **10** | Autenticación y catálogo base | Implementar registro e inicio de sesión/cierre de sesión; validaciones; mostrar listado de mascotas disponibles con información básica. | HU-01, HU-02, HU-21 | Pendiente |
| **11** | Perfiles y publicación de mascotas | Implementar vista de detalle de mascota y formulario para que el responsable registre una mascota; validar campos obligatorios. | HU-03, HU-11 | Pendiente |
| **12** | **Sprint 2 — revisión, planificación y entrega incremental** | Revisar incremento del Sprint 1; demostrar funcionalidades; recoger feedback; retrospectiva; priorizar el siguiente sprint. Implementar filtros de búsqueda y registrar preferencias Like/Dislike como siguiente incremento. | HU-04, HU-06; revisión de HU-01, HU-02, HU-03, HU-11, HU-21 | Pendiente |
| **13** | Preferencias y favoritos | Completar filtros y limpieza de filtros; guardar y retirar favoritos; conservar la selección de cada adoptante. | HU-04, HU-17, HU-18 | Pendiente |
| **14** | Compatibilidad y coordinación inicial | Implementar registro/visualización de Matches y preparar flujo de solicitud de adopción; probar casos sin resultados y estados de disponibilidad. | HU-07, HU-20, HU-10, HU-19 | Pendiente |
| **15** | **Sprint 3 — revisión final e integración** | Revisar el incremento; demo; recopilar feedback; retrospectiva; integrar funcionalidades priorizadas; ejecutar pruebas de aceptación; corregir errores críticos y preparar evidencias y documentación de entrega. | HU-08, HU-10 y funcionalidades terminadas de los sprints anteriores | Pendiente |

## Backlog sugerido por prioridad

| Prioridad | Historias | Motivo |
|---|---|---|
| Alta | HU-01, HU-02, HU-03, HU-04, HU-08, HU-10, HU-12, HU-21, HU-22, HU-23, HU-24 | Funcionalidades centrales, navegación, contacto y control de la plataforma. |
| Media | HU-05, HU-06, HU-07, HU-11, HU-13, HU-15, HU-16, HU-17, HU-19, HU-20, HU-25, HU-26 | Mejoran búsqueda, interacción, gestión de mascotas y administración. |
| Baja | HU-09, HU-14, HU-18 | Funciones complementarias que pueden priorizarse según la capacidad del equipo. |

## Plantilla para actualizar cada tarjeta

Para cada actividad, registrar:
- **Historia de usuario:** HU-XX.
- **Responsable:** nombre del integrante.
- **Criterios de aceptación:** condiciones verificables tomadas de la historia.
- **Estado:** Pendiente / En proceso / Hecho.
- **Evidencia:** enlace al commit, Pull Request, captura o video de prueba.
- **Observaciones / bloqueos:** dependencias o problemas encontrados.

## Definition of Done (criterio propuesto)

Una actividad se marca como **Hecho** cuando:
1. Cumple los criterios de aceptación de su historia.
2. Se ha probado el flujo principal y los casos de error relevantes.
3. El código está integrado en el repositorio y revisado por el equipo.
4. No quedan errores críticos conocidos.
5. Se adjunta evidencia verificable y se actualiza la documentación correspondiente.

## Ceremonias de los sprints

- **Semana 9 — Sprint 1:** Sprint Planning, asignación de tareas y definición del objetivo.
- **Semana 12 — Sprint 2:** Sprint Review, Sprint Retrospective y planificación del siguiente incremento.
- **Semana 15 — Sprint 3:** Sprint Review, Sprint Retrospective, integración final y evidencias de entrega.

> **Importante:** la distribución semanal es una propuesta inicial basada en las historias de usuario suministradas. El equipo debe confirmar las tareas realmente terminadas, responsables, estimaciones y alcance de cada sprint. No se marcan como implementadas funcionalidades sin evidencia.
