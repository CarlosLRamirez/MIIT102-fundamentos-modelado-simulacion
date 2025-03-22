---
modified: 2025-03-22T08:56:24-06:00
title: "Ejercicio Omnet++ No. 1: Extensión del modelo Tic-Toc con Triángulo de 3 Nodos"
aliases:
  - "Ejercicio Omnet++ No. 1: Extensión del modelo Tic-Toc con Triángulo de 3 Nodos"
---
 ## 🎯 Objetivo

Modificar y extender el modelo Tic-Toc para:

- Agregar un **tercer nodo** y conectarlos formando un **triángulo** (nodo1 → nodo2 → nodo3 → nodo1).
- Hacer que **nodo1** sea quien **genera los mensajes**.
- Limitar la cantidad de mensajes que enviará **nodo1** mediante un **parámetro configurable**.
- Usar **íconos diferentes** para cada nodo.
- Heredar todos los nodos de un **módulo genérico (Txc)**.
- Utilizar `WATCH()` para **monitorear** el número de mensajes enviados.
- Mostrar la **gráfica de secuencia de eventos (Sequence Chart)**.

---

## Instrucciones:
- Cree un nuevo modelo de simulación que cumpla con los objetivos indicados
- Nombre el archivo NED: `TictocTriangulo.ned`
- Nombre el archivo C++ con el código del módulo: `txcTriangulo.cc`
- Actualize el archivo `omnetpp.ini` para incluir esta simulación
- Ejecute la simulación y observe:
	- La circulación de mensajes entre los tres nodos.
	- La disminución del contador de mensajes en la GUI.
	- Detener la simulación al finalizar el intercambio.
- Genere la gráfica de secuencia de eventos.
- Responda a las preguntas de reflexión

---

## 🧩 Preguntas de Reflexión

- ¿Qué pasaría si todos los nodos tuvieran `sendMsgOnInit = true`?
- ¿Cómo ajustarías este modelo para que varios nodos generen mensajes?
- ¿Cómo se modificaría el comportamiento si cambiamos los parámetros `limit` de cada nodo?
- ¿Cómo se modificaría el comportamiento si el retardo de las conexiones es diferente entre cada nodo?

## Solución Propuesta
[[Solucion - Ejercicio Omnet++  No. 1 ]]
