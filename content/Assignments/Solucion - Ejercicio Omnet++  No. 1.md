---
created: 2025-03-22T07:15:41-06:00
modified: 2025-03-22T07:25:39-06:00
title: Solucion - Ejercicio Omnet++  No. 1
---
## NED (`tictoc_ejercicio1.ned`)

```ned showLineNumbers{1}
// Archivo: tictoc_ejercicio1.ned
// Ejercicio 1: Modelo Tic-Toc para ejercicio en forma de triángulo.

simple nodox
{
    parameters:
        bool sendMsgOnInit = default(false); // whether the module should send out a message on initialization
        int limit = default(5);  // Número máximo de mensajes a enviar por nodo1
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

network TictocTriangulo
{
    @display("bgb=354,287");
    submodules:
        nodo1: nodox {
            parameters:
                sendMsgOnInit = true;
                @display("i=block/control,#FF2F92;p=162,211");
        }
        nodo2: nodox {
            parameters:
                @display("i=,gold;p=266,58");
                sendMsgOnInit = true;
        }
        nodo3: nodox {
            parameters:
                @display("i=block/user,#00FCFF;p=58,58");
                sendMsgOnInit = true;
        }
    connections:
        nodo1.out --> {  delay = 200ms; } --> nodo2.in;
        nodo2.out --> {  delay = 100ms; } --> nodo3.in;
        nodo3.out --> {  delay = 300ms; } --> nodo1.in;
}

```

## C++ (`nodox.cc`)

```cpp showLineNumbers{1}
// Archivo: nodox.cc
// Ejercicio 1: Modelo Tic-Toc para ejercicio en forma de triángulo.

#include <cstdio>
#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Modelo Tic-Toc para ejercicio en forma de triángulo.
 */
class nodox : public cSimpleModule
{
  private:
    int numMensajes;         // Contador de mensajes enviados

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(nodox);

void nodox::initialize()
{
    numMensajes = par("limit"); // Leer el parámetro 'limit' del archivo NED
    WATCH(numMensajes);         

    // Enviar el mensaje iniciar solo si tiene habilitado el parametro 'sendMsgOnInit'
    if (par("sendMsgOnInit").boolValue() == true) {
        EV << "Enviando mensaje inicial\n";
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void nodox::handleMessage(cMessage *msg)
{
    // Decrementar el contador de mensajes
    numMensajes--;
    // Verificar si el contador llegó a cero
    if (numMensajes == 0) {
        // Si el contador es cero, eliminar el mensaje
        // Esto detendra la simulación
        EV << "El contador de mensajes de " << getName() << " llegó a cero, eliminando mensaje\n";
        delete msg;
    }
    else {
        EV <<"El contador de mensajes de " << getName() << " esta en " << numMensajes << ", enviando de vuelta el mensaje\n";
        send(msg, "out");
    }
}
```

## INI (`omnetpp.ini`)

```ìni showLineNumbers{1}
[Ejercicio_Triangulo]
network = TictocTriangulo
record-eventlog = true
TictocTriangulo.nodo1.limit = 8
TictocTriangulo.nodo2.limit = 3
TictocTriangulo.nodo3.limit = 7
```
