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
