---
created: 2025-03-21T23:41:44-06:00
modified: 2025-03-22T09:23:34-06:00
title: "Tutorial TicToc: Introducción a OMNeT++  - Parte 4: Convirtiéndose en una red real"
aliases:
  - "Tutorial TicToc: Introducción a OMNeT++  - Parte 4: Convirtiéndose en una red real"
description: Convirtiéndose en una red real
date: 2025-03-21
---
## 4.1 Más de dos nodos

En este paso, vamos a dar un gran salto: **crear varios módulos `tic` y conectarlos en una red.**

Por ahora, vamos a mantener su funcionamiento simple:
- Uno de los nodos generará un mensaje.
- Los otros nodos continuarán pasando el mensaje alrededor en **direcciones aleatorias** hasta que llegue a un nodo de destino predefinido (`tic[3]`).

### 4.1.1 Cambios en el modelo

**Uso de múltiples módulos tic (seis en total)**:
- Los módulos están definidos como un **vector de módulos** (`tic[6]`).
- Esto significa que se crean automáticamente seis módulos con nombres `tic[0]`, `tic[1]`, `tic[2]`, etc.

**Uso de vectores de puertas (`in[]` y `out[]`)**:
- Las puertas (in y out) se definen como vectores para permitir múltiples conexiones por cada módulo.
- El tamaño del vector se determina automáticamente al conectar los módulos.

### 4.1.2 Definición de red (NED)

En el archivo **NED (`tictoc10.ned`)** se declaran las puertas como vectores con el uso de `[]`.

```ned showLineNumbers{13}
	simple Txc10
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];  // declare in[] and out[] to be vector gates
        output out[];
}
```

Luego, se define la red con varios nodos conectados entre sí:

```ned showLineNumbers{22}
network Tictoc10
{
    submodules:
        tic[6]: Txc10;
    connections:
        tic[0].out++ --> {  delay = 100ms; } --> tic[1].in++;
        tic[0].in++ <-- {  delay = 100ms; } <-- tic[1].out++;

        tic[1].out++ --> {  delay = 100ms; } --> tic[2].in++;
        tic[1].in++ <-- {  delay = 100ms; } <-- tic[2].out++;

        tic[1].out++ --> {  delay = 100ms; } --> tic[4].in++;
        tic[1].in++ <-- {  delay = 100ms; } <-- tic[4].out++;

        tic[3].out++ --> {  delay = 100ms; } --> tic[4].in++;
        tic[3].in++ <-- {  delay = 100ms; } <-- tic[4].out++;

        tic[4].out++ --> {  delay = 100ms; } --> tic[5].in++;
        tic[4].in++ <-- {  delay = 100ms; } <-- tic[5].out++;
}
```

La topología resultante queda de esta forma:

![[Pasted image 20250322001726.png|350]]
  
### 4.1.3 Explicación del Código

- Se crean **6 módulos tic** en un arreglo llamado `tic[]`.
- Cada módulo tiene múltiples entradas (`in[]`) y salidas (`out[]`).
- Los módulos están conectados con retardos (`delay = 100ms`).
- El mensaje se crea en `tic[0]` y se envía al siguiente nodo al azar.

#### 4.1.3.1 Generación de mensaje inicial en `tic[0]`

En este modelo, **solo el módulo `tic[0]` es el encargado de generar el mensaje inicial** que será enviado y retransmitido por los demás nodos.  

En la función `initialize()` del módulo se `TxC10`utiliza la función `getIndex()` para identificar si el módulo actual es `tic[0]`.

El proceso arranca mediante `tic[0]`programando el envío del mensaje a si mismo, en el tiempo `0.0`, por lo cual se activa el método `handleMessage()`

```c++ showLineNumbers{35}
void Txc10::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        snprintf(msgname, sizeof(msgname), "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}
```


#### 4.1.3.2 Reenvio de  mensajes al azar

El código principal que maneja este comportamiento está en la función `forwardMessage()`.

Se selecciona aleatoriamente una puerta de salida para reenviar el mensaje.

```c++ showLineNumbers{59}
void Txc10::forwardMessage(cMessage *msg)
{
    // Seleccionar aleatoriamente una puerta de salida del vector `out[]`
    int n = gateSize("out");
    int k = intuniform(0, n-1);  // Selección aleatoria de un índice de puerta

    EV << "Reenviando mensaje " << msg << " por la puerta out[" << k << "]\n";
    send(msg, "out", k);  // Enviar el mensaje por la puerta seleccionada
}
```

#### 4.1.3.3 Eliminación del mensaje en  `tic[3]`

Cuando un mensaje llega al módulo `tic[3]`, se elimina, lo cual simula que ha llegado a su destino.

```c++ showLineNumbers{48}
    if (getIndex() == 3) {
        // Message arrived.
        EV << "Message " << msg << " arrived.\n";
        delete msg;
    }
```

### 4.1.4 Resultados de la simulacíon

1. En la consola, verás mensajes indicando el envío de mensajes entre nodos:

![[Pasted image 20250322005413.png]]

2. En la gráfica de secuencia (Sequence Chart), podrás observar cómo el mensaje viaja entre los nodos.

![[Pasted image 20250322005556.png]]

3. Cuando un mensaje llega a `tic[3]`, se elimina y se muestra un mensaje indicando su eliminación.

![[Pasted image 20250322005440.png]]

### 4.1.5 Código Fuente

- [[tictoc10_ned|tictoc10.ned]]
- [[txc10_cc|txc10.cc]] 
- [[omnetpp_ini|omnetpp.ini]]


## 4.2 Canales y definiciones de tipo interno

Nuestra definición de red se está volviendo bastante compleja y larga, especialmente la sección de conexiones. Vamos a simplificarla.   Lo primero que notamos es que las conexiones siempre usan el mismo parámetro de retardo (`delay`).

Es posible crear tipos personalizados para las conexiones (llamados **canales**) de manera similar a como se crean los módulos simples (`simple modules`).  

Vamos a crear un tipo de canal que especifica el parámetro de retardo y usaremos ese tipo para todas las conexiones en la red.

### 4.2.1 Definición de red (`tictoc11.ned`)

```ned showLineNumbers{26}
network Tictoc11
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tic[6]: Txc11;
    connections:
        tic[0].out++ --> Channel --> tic[1].in++;
        tic[0].in++ <-- Channel <-- tic[1].out++;
 
        tic[1].out++ --> Channel --> tic[2].in++;
        tic[1].in++ <-- Channel <-- tic[2].out++;
 
        tic[1].out++ --> Channel --> tic[4].in++;
        tic[1].in++ <-- Channel <-- tic[4].out++;
 
        tic[3].out++ --> Channel --> tic[4].in++;
        tic[3].in++ <-- Channel <-- tic[4].out++;
 
        tic[4].out++ --> Channel --> tic[5].in++;
        tic[4].in++ <-- Channel <-- tic[5].out++;
}
```

### 4.2.2 Explicación:

- Hemos definido un nuevo tipo de canal llamado `Channel` dentro de la sección `types`.
- Este canal se basa en `ned.DelayChannel`, que es un tipo incorporado de OMNeT++.
- Este tipo personalizado (`Channel`) solo es visible dentro de la red `Tictoc11`.
- Simplifica las conexiones al permitirnos especificar solo `Channel` en lugar de definir el retardo (`delay`) en cada conexión.

### 4.2.3 Código Fuente

- [[tictoc11_ned|tictoc11.ned]]
- [[txc11_cc|txc11.cc]]
- [[omnetpp_ini|omnetpp.ini]]

---
## 4.3 Uso de conexiones bidireccionales

Si observamos la sección de conexiones, nos damos cuenta de que cada par de nodos está conectado con **dos conexiones**: una para cada dirección.  
OMNeT++ permite usar conexiones bidireccionales (`inout gates`), así que vamos a implementarlas.

### 4.3.2 Definición del módulo (`Txc12.ned`)

```ned showLineNumbers{}
simple Txc12
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];  // Declarar conexiones bidireccionales
}
```

### 4.3.3 Definición de red (`tictoc12.ned`)

```ned showLineNumbers{}
network Tictoc12
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        tic[6]: Txc12;
    connections:
        tic[0].gate++ <--> Channel <--> tic[1].gate++;
        tic[1].gate++ <--> Channel <--> tic[2].gate++;
        tic[1].gate++ <--> Channel <--> tic[4].gate++;
        tic[3].gate++ <--> Channel <--> tic[4].gate++;
        tic[4].gate++ <--> Channel <--> tic[5].gate++;
}
```

### 4.3.4 Modificación del código en C++ (`txc12.cc`)

```cpp showLineNumbers{}
void Txc12::forwardMessage(cMessage *msg)
{
    int n = gateSize("gate");
    int k = intuniform(0, n - 1);

    EV << "Forwarding message " << msg->getName() << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}
```

### 4.3.5 Explicación:

- Ahora usamos puertas `inout` en lugar de `input` y `output`.
- El sufijo `$o` se usa para identificar la parte de salida de una puerta bidireccional.
- El sufijo `$i` se usa para identificar la parte de entrada de una puerta bidireccional (no utilizado en este ejemplo).
- OMNeT++ permite definir conexiones bidireccionales con `<-->`, simplificando la topología.

### 4.3.6 Código Fuente

- [[tictoc12_ned|tictoc12.ned]]
- [[txc12_cc|txc12.cc]]
- [[omnetpp_ini|omnetpp.ini]]

## 4.4 Definición de nuestra propia clase de mensaje

En este paso, vamos a eliminar la dependencia de que el mensaje siempre llegue a `tic[3]` y permitiremos que **el destino se seleccione al azar**.  

Agregaremos la dirección de destino como un campo dentro del mensaje.

La mejor manera de hacerlo es crear una **subclase de cMessage** y agregar la dirección de destino (`destination`) como un miembro de datos (variable) dentro de esa clase.

Escribir manualmente la clase de mensaje sería un proceso tedioso porque normalmente requiere mucho código repetitivo y estructural (**boilerplate code**).

En lugar de hacerlo a mano, vamos a permitir que OMNeT++ genere la clase por nosotros.

La especificación de la clase de mensaje se escribe en un archivo llamado `tictoc13.msg`.

### 4.4.1 Definición del mensaje (`tictoc13.msg`)

```cpp showLineNumbers{}
message TicTocMsg13
{
    int source;
    int destination;
    int hopCount = 0;
}
```
### 4.4.2 Generación del código para la clase **mensaje**

OMNeT++ genera automáticamente las clases necesarias (`tictoc13_m.h` y `tictoc13_m.cc`) al compilar el proyecto con el comando `opp_msgc`.

### 4.4.3 Modificación del código en C++ (`txc13.cc`)

Primero, incluye el archivo generado:

```cpp showLineNumbers{}
#include "tictoc13_m.h"
```

Luego, modificamos la función `generateMessage()` para crear el mensaje y configurar sus campos.

```cpp showLineNumbers{}
TicTocMsg13 *generateMessage(int src)
{
    int dest = intuniform(0, 5);  // Generar un destino aleatorio
    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    TicTocMsg13 *msg = new TicTocMsg13(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
```

Y actualizamos `handleMessage()` para verificar el destino del mensaje.

```cpp showLineNumbers{}
void Txc13::handleMessage(cMessage *msg)
{
    TicTocMsg13 *ttmsg = check_and_cast<TicTocMsg13 *>(msg);

    if (ttmsg->getDestination() == getIndex()) {
        EV << "Message " << ttmsg->getName() << " arrived at its destination.\n";
        delete ttmsg;

        // Generar un nuevo mensaje con destino aleatorio
        TicTocMsg13 *newMsg = generateMessage(getIndex());
        forwardMessage(newMsg);
    }
    else {
        forwardMessage(ttmsg);  // Reenviar el mensaje si no ha llegado al destino
    }
}
```

### 4.4.4 Explicación:
- Creamos un nuevo tipo de mensaje `TicTocMsg13` con campos `source`, `destination` y `hopCount`.
- Usamos la función `generateMessage()` para crear un nuevo mensaje con un destino aleatorio cada vez que llega uno a su destino.
- La función `check_and_cast<>()` asegura que el mensaje recibido es del tipo correcto (`TicTocMsg13`).

### 4.4.5 Resultado de la Simulación

Al ejecutar la simulación podemos ver que cuando un mensaje llega a su destino, el nodo destino genera otro mensaje con un destino aleatorio.

![[Pasted image 20250322021850.png]]

Al hacer click en el mensaje es posible ver el contenido en la ventana de inspección.  Al hacer doble click se abre una nueva ventana, la cual muestra información valiosa; los campos del mensaje se pueden ver en la pagina de contenido:

![[Pasted image 20250322022147.png]]

### 4.4.6 Código Fuente
- [[tictoc13_msg|tictoc13.msg]]
- [[tictoc13_ned|tictoc13.ned]]
- [[txc13_cc|txc13.cc]]
- [[omnetpp_ini|omnetpp.ini]]

### 4.5 Ejercicio sugerido

- Actualmente, solo hay un mensaje en circulación en cada momento: los nodos solo generan un nuevo mensaje cuando reciben otro.  
- Modifica la clase para que genere mensajes periódicamente.  
- El intervalo entre mensajes debe ser un parámetro del módulo, retornando valores distribuidos exponencialmente.  

