---
created: 2025-03-29T05:01:21-06:00
modified: 2025-03-29T06:59:29-06:00
title: Configuración de Simulaciones Parametrizadas en INET Framework
aliases:
  - "INET Framework - Laboratorio 3: Simulaciones Parametrizadas y Repeticiones"
---

## Introducción a las Simulaciones Parametrizadas

En este laboratorio, aprenderás a configurar simulaciones parametrizadas en OMNeT++. Evaluarás cómo ciertos parámetros, como `ber` y `delay`, afectan el desempeño de la red. También aprenderás a configurar repeticiones para analizar estadísticamente los resultados de múltiples corridas de simulación.

---

## Objetivos del Laboratorio

- Ejecutar simulaciones parametrizadas variando un solo parámetro (`ber`) y luego `delay`.
- Realizar simulaciones parametrizadas con combinaciones de múltiples parámetros (`ber` y `delay`).
- Configurar y ejecutar repeticiones de simulaciones en OMNeT++ para un análisis estadístico más robusto.

---

## Modificación del Archivo `.ned`

Para este ejercicio, dejaremos el canal con sus parámetros por defecto en el archivo `.ned`, ya que definiremos dichos parámetros en el archivo `.ini`.

Modifica el archivo `lab2.ned` para que quede de la siguiente forma:

```ned
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.StandardHost;

network Red2hosts_v2
{
    @display("bgb=308,175");
    submodules:
        HostA: StandardHost {
            @display("p=51.9,117.2");
        }
        HostB: StandardHost {
            @display("p=236,105");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=258,27");
        }
    connections:
        HostA.ethg++ <--> Eth100M {
        } <--> HostB.ethg++;
}
```

---

## Modificación del Archivo `omnetpp.ini`

### Configuración del Parámetro Individual (`ber`)

Agrega las siguientes líneas en tu archivo `omnetpp.ini` para configurar la variación del parámetro `ber`:

```ini
[Config PingWithBer]
network = Red2hosts_v2
sim-time-limit = 3600s

# Aplicación Ping
*.HostA.numApps = 1
*.HostA.app[0].typename = "PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].printPing = true

# Parámetro de Canal (ber)
**.ber = ${ber=0.000001, 0.00001, 0.0001, 0.001}
```

Ejecuta la simulación y observa cómo el cambio en el `ber` afecta las estadísticas generadas, como `numLost` y `rtt`.

---

### Ejecución de Simulaciones con Múltiples Corridas

En cada ejecución utilizando la configuración por defecto (*Qtenv*), debes seleccionar el valor de `BER` que deseas utilizar:

![[Pasted image 20250329051618.png]]

Para ejecutar la simulación con todos los valores de `BER`, necesitarás correr la simulación 3 veces, seleccionando diferentes parámetros en cada ocasión.

En OMNeT++, puedes configurar la simulación para que se ejecute sin un entorno gráfico, utilizando únicamente la línea de comandos. Esto permite ejecutar todas las combinaciones de parámetros automáticamente, sin necesidad de realizar múltiples ejecuciones manualmente.

Para hacer esto, haz clic en la flecha negra junto al ícono verde de ejecución normal y selecciona `Run Configurations`.

![[Pasted image 20250329051858.png]]

También puedes acceder al menú principal y seleccionar `Run -> Run Configurations`.

![[Pasted image 20250329052016.png]]

Esto abrirá una ventana con las diferentes configuraciones disponibles para la ejecución de la simulación. Dado que no deseas mostrar la interfaz gráfica, asegúrate de seleccionar en `Config name` la configuración correcta definida en el archivo `omnetpp.ini` y en `User interface` selecciona `Cmdenv`.

Luego, haz clic en **Apply** y **Run** para ejecutar la simulación.

![[Pasted image 20250329052409.png]]

Al finalizar la simulación, obtendrás archivos con estadísticas (`.sca` y `.vec`) diferentes para cada corrida, de acuerdo a cada combinación de parámetros definidos en el archivo `.ini`.

![[Pasted image 20250329053238.png]]

---

### Configuración del Parámetro Individual (`delay`)

Modifica el archivo `omnetpp.ini` para incluir diferentes valores de `delay`:

```ini
[Config PingWithDelay]
network = Red2hosts_v2
sim-time-limit = 3600s
repeat = 1

# Aplicación Ping
*.HostA.numApps = 1
*.HostA.app[0].typename = "PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].printPing = true

# Parámetro de Canal (delay)
**.delay = ${delay=1ms, 50ms, 150ms}
```

Ejecuta la simulación y analiza cómo diferentes valores de `delay` afectan el rendimiento de la red, especialmente en términos de `rtt`.

---

## Combinación de Parámetros (`ber` y `delay`)

Ahora, combinaremos ambos parámetros en una sola simulación:

```ini
[Config PingCombined]
network = Red2hosts_v2
sim-time-limit = 3600s
repeat = 1

# Aplicación Ping
*.HostA.numApps = 1
*.HostA.app[0].typename = "PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].printPing = true

# Parámetros combinados
**.ber = ${ber=0.000001, 0.00001}
**.delay = ${delay=1ms, 5ms}
```

OMNeT++ generará simulaciones para todas las combinaciones posibles de `ber` y `delay`.

---

## Repeticiones de Simulación

OMNeT++ permite realizar múltiples corridas de la misma simulación para obtener resultados estadísticamente más confiables.

### Instrucciones para la Configuración de Repeticiones

1. Modifica cualquier configuración agregando la línea:

```ini
repeat = 5
```

2. OMNeT++ ejecutará cada combinación de parámetros 5 veces. Esto significa que si tu configuración itera sobre 5 diferentes valores de un parámetro y configuras 5 repeticiones, se ejecutarán 25 corridas (5 x 5). Si tu configuración itera sobre 2 parámetros con 5 valores cada uno y configuras 5 repeticiones, tu simulación se ejecutará 125 veces (5 x 5 x 5).

---

## Exploración de Resultados

1. Para cada resultado, explora la generación de gráficos de tipo barra, línea e histogramas. Esto te permitirá comparar cómo la variación de parámetros impacta en las estadísticas de *Número de pings perdidos*, *Round-trip time* y *% de pérdida de paquetes*.

2. También puedes exportar los resultados a formatos como `CSV` para su posterior procesamiento.

---

## Preguntas para Reflexionar

1. ¿Qué diferencias observaste al variar los parámetros `ber` y `delay` de manera individual?
2. ¿Cómo afecta la combinación de los parámetros `ber` y `delay` al desempeño de la red?
3. ¿Qué ocurre al ejecutar múltiples repeticiones? ¿Qué patrones o tendencias has identificado?
4. ¿Cómo podrías aplicar estas técnicas para analizar protocolos o topologías más complejas?

---
