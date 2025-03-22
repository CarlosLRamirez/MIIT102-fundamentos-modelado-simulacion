---
created: 2025-03-22T02:44:40-06:00
modified: 2025-03-22T10:22:48-06:00
title: "Tutorial TicToc - Introducción a OMNeT++ - Parte 5: Recolección de Estadísticas"
aliases:
  - "Tutorial TicToc - Introducción a OMNeT++ - Parte 5: Recolección de Estadísticas"
date: 2025-03-22
---
## 5.1 Mostrando el número de paquetes enviados/recibidos

Para obtener una visión general en tiempo de ejecución sobre cuántos mensajes envía o recibe cada nodo, se han añadido dos contadores a la clase del módulo: `numSent` y `numReceived`.

```cpp showLineNumbers{}
class Txc14 : public cSimpleModule
{
  private:
    long numSent;
    long numReceived;

  protected:
```

Estos contadores se inicializan en cero y se monitorean usando `WATCH()` en el método `initialize()`.  

Ahora, puedes usar la opción de **Find/Inspect objects** en el menú **Inspect** (también disponible en la barra de herramientas) para ver cuántos paquetes se han enviado o recibido por cada nodo.

![[Pasted image 20250322093006.png]]


![[Pasted image 20250322093050.png]]


Aunque en este modelo específico los números serán aproximadamente los mismos (lo cual demuestra que `intuniform()` funciona correctamente), en simulaciones reales puede ser muy útil para obtener rápidamente un resumen del estado de los diferentes nodos en el modelo.

También se puede hacer que esta información aparezca sobre los íconos de los módulos. El uso del tag `t=` en el `display string` especifica el texto; solo necesitamos modificar el `display string` durante la simulación con el siguiente código:

```cpp showLineNumbers{1}
void Txc14::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}
```

![[Pasted image 20250322093124.png]]


### 5.1.1 Código Fuente

- [[tictoc14_msg|tictoc14.msg]]
- [[tictoc14_ned|tictoc14.ned]]
- [[txc14_cc|txc14.cc]]
- [[omnetpp_ini|omnetpp.ini]]

---

## 5.2 Añadiendo recolección de estadísticas

El modelo de simulación actual hace algo suficientemente interesante como para que podamos recopilar algunas estadísticas. Por ejemplo, puedes estar interesado en el promedio de saltos (`hop count`) que un mensaje debe recorrer antes de llegar a su destino.

Para ello, agregamos dos nuevos objetos a la clase:
- `cHistogram`: Calcula estadísticas como media, desviación estándar, mínimo y máximo por nodo.
- `cOutVector`: Registra datos en un archivo de salida (`Tictoc15-#0.vec`), generando una serie de pares `(tiempo, valor)`.

```cpp showLineNumbers{1}
class Txc15 : public cSimpleModule
{
  private:
    long numSent;
    long numReceived;
    cHistogram hopCountStats;
    cOutVector hopCountVector;

  protected:
```

Cada vez que un mensaje llega a su nodo destino, actualizamos las estadísticas con:

```cpp showLineNumbers{1}
hopCountVector.record(hopcount);
hopCountStats.collect(hopcount);
```

La llamada a `hopCountVector.record()` escribe los datos en `Tictoc15-#0.vec`.  

Si el archivo crece demasiado debido a un modelo de simulación extenso, puedes desactivar o activar la recolección de vectores en `omnetpp.ini`.

### 5.2.1 Grabando estadísticas en `finish()`

Los datos escalares (`scalars`) recopilados por `cHistogram` deben ser grabados manualmente en el método `finish()`.  
Este método se llama al completar la simulación correctamente (no cuando se detiene por un error).

```cpp
void Txc15::finish()
{
    EV << "Sent:     " << numSent << endl;
    EV << "Received: " << numReceived << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", numSent);
    recordScalar("#received", numReceived);

    hopCountStats.recordAs("hop count");
}
```

Los archivos generados se almacenan en el subdirectorio `results/`.

### 5.2.3 Visualización de estadísticas durante la simulación

También puede ver los datos durante la simulación. Para ello, haga clic con el botón derecho del ratón en un módulo y seleccione *Open Details*. En la página Contenido del inspector de módulos encontrará los objetos `hopCountStats` y `hopCountVector`. Para abrir sus inspectores, haga clic con el botón derecho del ratón en `cHistogram hopCountStats` o `cOutVector HopCount`, y haga clic en `Open Graphical View`.

![[Pasted image 20250322095620.png]]


!![[Pasted image 20250322095738.png]]

Inicialmente estarán vacíos -- ejecute la simulación en modo **Rápido** (o incluso **Express**) para obtener suficientes datos para ser mostrados. Después de un rato obtendrás algo como esto:

![[Pasted image 20250322100015.png|450]]

![[Pasted image 20250322100027.png|450]]


Cuando crea que se han recogido suficientes datos, puede detener la simulación y entonces analizaremos los archivos de resultados (`Tictoc15-#0.vec` y `Tictoc15-#0.sca`) fuera de línea. Tendrá que elegir *Simulate -> Call finish()* en el menú (o hacer clic en el botón correspondiente de la barra de herramientas) antes de salir -- esto hará que se ejecuten las funciones `finish()` y que se escriban los datos en `Tictoc15-#0.sca`.

![[Pasted image 20250322100110.png|350]]


![[Pasted image 20250322100154.png]]

![[Pasted image 20250322100341.png]]
### 5.2.4 Código Fuente

- [[tictoc15_msg|tictoc15.msg]]
- [[tictoc15_ned|tictoc15.ned]]
- [[txc15_cc|txc15.cc]]
- [[omnetpp_ini|omnetpp.ini]]

## 5.3 Recolección de estadísticas sin modificar tu modelo

OMNeT++ ofrece un mecanismo adicional para recolectar datos usando **señales (`signals`)**.  

Cualquier modelo puede emitir señales que llevan un valor o un objeto. Los usuarios pueden **adjuntar 'listeners' (escuchas)** a estas señales para procesar o registrar los datos, sin necesidad de modificar el código fuente del modelo.

#### 5.3.1 Definiendo un `signal`

Primero definimos nuestra señal (`arrivalSignal`) en la clase del módulo:

```cpp
class Txc16 : public cSimpleModule
{
  private:
    simsignal_t arrivalSignal;

  protected:
```

El registro de la señal se realiza en el método `initialize()`:

```cpp
void Txc16::initialize()
{
    arrivalSignal = registerSignal("arrival");
    if (getIndex() == 0) {
        // El módulo 0 envía el primer mensaje
    }
}
```

#### 5.3.2 Emitiendo una señal

Cada vez que un mensaje llega a su destino, se emite la señal (`emit()`) con el conteo de saltos (`hopCount`).

```cpp
void Txc16::handleMessage(cMessage *msg)
{
    TicTocMsg16 *ttmsg = check_and_cast<TicTocMsg16 *>(msg);

    if (ttmsg->getDestination() == getIndex()) {
        int hopcount = ttmsg->getHopCount();
        emit(arrivalSignal, hopcount);

        EV << "Message " << ttmsg << " arrived after " << hopcount << " hops.\n";
    }
}
```

#### 5.3.3 Declarando señales en el archivo `.ned`

En el archivo `.ned`, debes declarar la señal y la estadística que deseas recolectar:

```ned
simple Txc16
{
    parameters:
        @signal[arrival](type="long");
        @statistic[hopCount](title="hop count"; source="arrival"; record=vector,stats; interpolationmode=none);
}
```

#### 5.3.4 Configuración en `omnetpp.ini`

Si deseas visualizar un histograma en el nodo `tic[1]` y desactivar la grabación de vectores para ciertos nodos:

```ini
[Tictoc16]
network = Tictoc16
**.tic[1].hopCount.result-recording-modes = +histogram
**.tic[0..2].hopCount.result-recording-modes = -vector
```

Los resultados de la simulación se guardan en estos archivos en `/results`, tanto los escalares como los vectores, en la proxima sección verá como visualizarlos

![[Pasted image 20250322101712.png]]

### 5.3.5 Código Fuente

- [[tictoc16_msg|tictoc16.msg]]
- [[tictoc16_ned|tictoc16.ned]]
- [[txc16_cc|txc16.cc]]
- [[omnetpp_ini]]

---

## 5.4 Añadiendo figuras al Canvas

OMNeT++ permite mostrar figuras estáticas o dinámicas en el Canvas (pantalla principal de la simulación).  
Por ejemplo, se puede mostrar un texto que indique el último conteo de saltos (`hopCount`) registrado.

---

#### 5.4.1 Definiendo figuras en el archivo `.ned`

```ned 
network Tictoc17
{
    parameters:
        @figure[description](type=text; pos=5,20; font=,,bold; text="Random routing example - displaying last hop count");
        @figure[lasthopcount](type=text; pos=5,35; text="last hopCount: N/A");
}
```

---

#### 5.4.2 Actualizando las figuras dinámicamente (`txc17.cc`)

```cpp
if (hasGUI()) {
    char label[50];
    sprintf(label, "last hopCount = %d", hopcount);
    cCanvas *canvas = getParentModule()->getCanvas();
    cTextFigure *textFigure = check_and_cast<cTextFigure*>(canvas->getFigure("lasthopcount"));
    textFigure->setText(label);
}
```

![[Pasted image 20250322102238.png]]

### 5.4.3 Código Fuente

- [[tictoc17_msg|tictoc17.msg]]
- [[tictoc17_ned|tictoc17.ned]]
- [[txc17_cc|txc17.cc]]
- [[omnetpp_ini|omnetpp.ini]]

