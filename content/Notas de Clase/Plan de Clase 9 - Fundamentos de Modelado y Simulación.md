---
created: 2025-03-28T06:54:55-06:00
modified: 2025-03-29T07:42:50-06:00
draft: false
title: Plan de Clase 9 - Fundamentos de Modelado y Simulación
aliases:
  - Plan de Clase 9 - Fundamentos de Modelado y Simulación
---

**Duración:** 3 horas

---
## Objetivos Generales:
1. Familiarizar a los estudiantes con la creación de simulaciones de redes utilizando el INET Framework en OMNeT++.
2. Enseñar cómo obtener, visualizar y exportar estadísticas de simulaciones (escalares, vectores, histogramas) y comprender qué representan.
3. Explorar cómo agregar parámetros adicionales (BER y delay) a las conexiones y evaluar su impacto en el rendimiento.
4. Introducir la ejecución de simulaciones con variaciones de parámetros y múltiples repeticiones para análisis estadístico.
5. Proveer ejemplos básicos con protocolos TCP para contextualizar conceptos aprendidos (Opcional para estudiantes avanzados).

---

## Agenda:

### Parte 1: Introducción a Simulaciones con INET Framework (Guía No. 1) (1 hora)
- **Breve introducción teórica:** ¿Qué es el INET Framework y qué se puede simular con él? (5 minutos)
- **Simulación básica:** Creación de una simulación de Ping entre dos nodos siguiendo la Guía No. 1. (20 minutos).
- **Estadísticas:** Obtención y visualización de estadísticas (escalares, vectores e histogramas) (20 minutos).
- **Exportación de datos:** Cómo exportar estadísticas a Excel o CSV para análisis externo (10 minutos).
- **Documentación:** Cómo buscar documentación de módulos en INET Framework (5 minutos).
- **Laboratorio No. 1:** Explorar y modificar parámetros de `PingApp` (PacketSize) para analizar su impacto en las estadísticas generadas. Preparar un informe con sus resultados y reflexiones.

> **Break y Discusión:** 5 minutos para aclarar dudas y responder preguntas.

---

### Parte 2: Experimentación con Parámetros y Repeticiones (Guía No. 2) (1 hora)
- **Introducción a parámetros adicionales:** Configuración de BER y delay en conexiones utilizando el archivo `.ini`. (15 minutos).
- **Evaluación de impacto:** Comparar resultados al modificar parámetros y cómo se reflejan en estadísticas generadas (`numLost`, `rtt`). (15 minutos).
- **Simulaciones con variaciones de parámetros:** 
  - Variar un solo parámetro (`delay`) y observar resultados. (10 minutos).
  - Variar un solo parámetro (`ber`) y observar resultados. (10 minutos).
- **Actividad Asíncrona (Laboratorio No. 2):** Modificación manual de parámetros `ber` y `delay` en múltiples corridas, cálculo de `% Rate Loss` y comparación con estadísticas generadas por `PingApp`. Elaborar un informe con gráficos y conclusiones.
- **Revisión y Discusión:** Breve revisión de resultados y conclusiones preliminares. (10 minutos).

> **Break y Discusión:** 5 minutos para retroalimentación y aclaración de conceptos.

---

### Parte 3: Simulaciones Parametrizadas y Repeticiones (Guía No. 3) 

- **Simulaciones parametrizadas:** Cómo definir parámetros variables (`ber` y `delay`) usando el archivo `.ini`. (10 minutos).
- **Ejecución de múltiples repeticiones:** Cómo configurar y ejecutar simulaciones con `repeat`. (10 minutos).
- **Análisis de resultados:** Generar gráficos con intervalos de confianza y comparar diferentes combinaciones de parámetros. (10 minutos).
- **Actividad Asíncrona (Laboratorio No. 3):** Crear configuraciones parametrizadas, ejecutar múltiples repeticiones y presentar un informe con resultados detallados.

---

### Parte 4: Protocolos TCP - Ejemplos Básicos (Laboratorio No. 4) (Opcional)
- **Introducción a tráfico TCP:** Utilización de `TcpBasicClientApp` y `TcpGenericServerApp`. (5 minutos).
- **Simulación de tráfico TCP:** Modificación del `.ini` para incluir tráfico TCP sobre Ethernet. (20 minutos).
- **Actividad Opcional (Laboratorio No. 4):** Experimentar con tráfico TCP, analizar throughput, latencia, y calcular `Rate Loss` en diferentes configuraciones.

---

## Cierre y Conclusiones (10 minutos)
- Revisión de lo aprendido durante la clase.
- Preguntas finales y preparación para la próxima clase (teoría de intervalos de confianza).
- Explicación sobre el material adicional disponible para profundizar por cuenta propia (Laboratorios opcionales).



---
