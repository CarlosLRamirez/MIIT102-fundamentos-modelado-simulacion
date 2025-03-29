---
title: "INET Framework - Laboratorio 1: Modificación de Parámetros en PingApp"
aliases:
  - INET Framework - Laboratorio 1:  Modificación de Parámetros en PingApp
modified: 2025-03-29T07:24:50-06:00
---
## Introducción

En este laboratorio, aplicarás lo aprendido sobre búsqueda de documentación y modificación de parámetros en INET Framework. Además, analizarás cómo las modificaciones afectan las estadísticas generadas.

## Objetivo
Investigar cómo cambiar el tamaño de los paquetes transmitidos por `PingApp` y analizar su impacto en las estadísticas generadas (`rtt` y `numLost`), así como comparar los resultados con la configuración original y documentar tus conclusiones.

## Instrucciones

En esta actividad, deberás investigar y aplicar cambios en la configuración de `PingApp` para analizar cómo la modificación de ciertos parámetros afecta el desempeño de la red. La documentación relevante se encuentra en la **Referencia de INET**: [INET Reference](https://doc.omnetpp.org/inet/api-current/neddoc/index.html).

### Tareas
1. Investiga en la documentación de `PingApp` cómo modificar el tamaño de los paquetes transmitidos (`packetLength` o algún parámetro relacionado).
2. Modifica la configuración de `PingApp` para enviar paquetes de **300 Bytes**.
3. Dentro del proyecto anterior, crea una nueva configuración en el archivo `.ini` llamada `PingModified` para reflejar este cambio. Por ejemplo:

```ini
[Config PingModified]
network = Red2hosts_v2
sim-time-limit = 3600s

*.HostA.numApps = 1
*.HostA.app[0].typename = "PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].packetLength = 300B
*.HostA.app[0].printPing = true
```
   
4. Ejecuta la simulación con la nueva configuración y analiza cómo cambian las estadísticas generadas (`rtt`, `numLost`, etc.).
5. Exporta tus resultados a archivos `.csv` para facilitar el análisis en Excel o cualquier otra herramienta externa.
6. Genera gráficos que comparen el rendimiento con el tamaño de paquete original y el modificado (**300 Bytes**).
7. Prepara un informe que incluya:
	- Descripción del proceso que seguiste para modificar el parámetro `packetLength`.
	- Comparación de los resultados (`rtt`, `numLost`) entre ambas configuraciones.
	- Cálculo del `% rate loss` usando la fórmula:
   
     $$
     \text{Rate Loss} = \left( \frac{\text{numLost}}{\text{Total Packets Sent}} \right) \times 100
     $$
	- Reflexiones sobre las diferencias encontradas y cómo estos resultados pueden aplicarse a simulaciones más avanzadas.

## Reflexión Metacognitiva

Responde brevemente a las siguientes preguntas y agrégalas a tu informe:

1. ¿Cómo supiste que el parámetro `packetLength` era el que debías modificar? ¿Qué pasos seguiste para encontrarlo?
2. ¿Qué diferencias observaste en `rtt` y `numLost` después de modificar el tamaño del paquete?
3. ¿Qué crees que causa la diferencia en los resultados obtenidos? ¿Es lo que esperabas?
4. ¿Qué aprendiste al realizar este laboratorio que podrías aplicar a simulaciones más avanzadas?

---
