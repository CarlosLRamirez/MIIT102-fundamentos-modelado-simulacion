---
modified: 2025-03-29T07:33:57-06:00
title: "INET Framework - Laboratorio 2: Parámetros en el Canal de Comunicación"
aliases:
  - "INET Framework - Laboratorio 2: Parámetros en el Canal de Comunicación"
---
## Introducción

En este laboratorio, continuaremos con la simulación de un escenario básico utilizando `PingApp` en el INET Framework. Esta vez, introduciremos la manipulación de parámetros del canal de comunicación (`Eth100M`) como el retardo (`delay`) y la tasa de error de bits (`ber`). El objetivo es que comprendas cómo estas modificaciones afectan el desempeño de la red y cómo visualizarlas a través de las estadísticas generadas por OMNeT++.

---
## Objetivo
- Configurar un escenario de simulación en OMNeT++ con parámetros personalizados para el canal de comunicación.
- Comparar los resultados generados bajo diferentes condiciones del canal.
- Familiarizarse con la obtención y análisis de estadísticas de la simulación en OMNeT++.

---

## Reutilización del proyecto anterior

En lugar de crear un proyecto desde cero, haremos una copia del proyecto anterior (`lab1Ping`) y lo modificaremos. 

1. En el explorador de proyectos de OMNeT++, selecciona la carpeta del proyecto `lab1Ping`.
2. Copia y pega la carpeta en el mismo espacio de trabajo y renómbrala como `lab2Ping`.
3. Cambia el nombre de tu archivo `lab1.ned` a `lab2.ned`.

---

## Modificación de la topología de red

### Configuración del archivo `lab2.ned`

Abre el archivo `lab2.ned` y asegúrate que tiene la siguiente configuración:

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
            delay = 5ms; 
            ber = 0.00001;
        } <--> HostB.ethg++;
}
```

> [!NOTE]  
> Hemos agregado dos parámetros importantes al canal `Eth100M`:  
> - `delay = 5ms;` (Simula un enlace con un retardo fijo)  
> - `ber = 0.00001;` (Bit Error Rate, simula interferencias o ruido en el canal)  

---

## Modificación del archivo `omnetpp.ini`

Edita tu archivo `omnetpp.ini` para que coincida con la siguiente configuración:

```ini
[Config PingModified]
network = Red2hosts_v2
sim-time-limit = 3600s

#Aplicación Ping
*.HostA.numApps = 1
*.HostA.app[0].typename="PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].printPing = true
```

> [!TIP]  
> Puedes cambiar el nombre de la configuración a `PingModified` para diferenciarla de la simulación anterior.

---

## Ejecutar la Simulación

1. Ejecuta la simulación como lo hiciste en `Lab 1`.
2. Verifica que las estadísticas tipo `numLost` y `rtt` se generen adecuadamente.
3. Observa el comportamiento del sistema al introducir un retardo fijo (`delay`) y errores en la transmisión (`ber`).
4. Experimenta con diferentes valores de `delay`y `ber` modificando el archivo `.ned`y ejecutando la simulación varias veces, anota como impacta las estadísticas de `numLost`y `rtt`.


---

## Análisis de Estadísticas

Al finalizar la simulación, explora los archivos `.sca` y `.vec` para obtener estadísticas como:

- `numLost`: Paquetes perdidos por errores introducidos en el canal.
- `rtt`: Round-trip time (demora causada por el retardo del canal).
- `TxPk` y `RxPkOk`: Comparación del número de paquetes transmitidos y recibidos correctamente.

 > [!TIP]
 > Prueba con varios valores de `ber`y `delay` y observa como estos influyen en ambas estadísticas `numLost`, `rtt` y `RxPxOK`

---
## Cálculo del % Rate Loss

1. Calcula el porcentaje de paquetes perdidos (`% rate loss`) utilizando la siguiente fórmula:

  $$ 
   \text{Paquetes perdidos} = \left( \frac{\text{numLost}}{\text{Total Packets Sent}} \right) \times 100
   $$

2. Compara el resultado con el valor proporcionado por `PingApp` como parte de sus estadísticas.

---
## Preguntas para responder

1. ¿Qué efecto tiene aumentar el retardo (`delay`) en la estadística `rtt`?
2. ¿Qué efecto tiene aumentar el `ber` en la estadística `numLost`?
3. ¿Cómo afectan estos parámetros la cantidad de paquetes transmitidos y recibidos correctamente (`TxPk` y `RxPkOk`) así como el *Porcentaje de paquetes perdidos* que calculaste?
4. ¿El modulo `PingApp` genera una estadística sobre el porcentaje de perdida de paquetes? ¿Es este valor similar al que calculaste?