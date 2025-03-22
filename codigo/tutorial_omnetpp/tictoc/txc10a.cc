#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc10a : public cSimpleModule
{
  protected:
    virtual void forwardMessage(cMessage *msg, int arrivalGateIndex);
    virtual void justforwardMessage(cMessage *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc10a);

void Txc10a::initialize()
{
    if (getIndex() == 0) {  // Solo el módulo tic[0] genera el mensaje inicial
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());  // Generar nombre del mensaje
        cMessage *msg = new cMessage(msgname);
        EV << "Enviando mensaje " << msg->getName() << " al inicio.\n";
        scheduleAt(0.0, msg);  // Enviar mensaje como self-message para iniciar la simulación
    }
}

void Txc10a::handleMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();  // Verificar por dónde llegó el mensaje

    if (arrivalGate != nullptr) {  // Si el mensaje NO es un self-message
        int gateIndex = arrivalGate->getIndex();  // Obtener el índice de la puerta de llegada

        if (getIndex() == 3) {  // Si llegó al módulo tic[3], eliminar el mensaje
            EV << "El mensaje " << msg->getName() << " ha llegado finalmente al nodo tic[3].\n";
            delete msg;
        } 
        else {  // Si llegó a cualquier otro módulo
            EV << "El mensaje " << msg->getName() << " llegó por la puerta " << gateIndex << ".\n";
            forwardMessage(msg, gateIndex);  // Reenviar el mensaje evitando la puerta de llegada
        }
    }
    else {  // Si es un self-message
        EV << "El mensaje " << msg->getName() << " es un self-message, reenviando sin restricciones.\n";
        justforwardMessage(msg);  // Enviar el mensaje sin restricciones
    }
}

void Txc10a::forwardMessage(cMessage *msg, int arrivalGateIndex)
{
    int n = gateSize("out");

    // Si solo hay una puerta, reenviar por esa puerta
    if (n == 1) {
        EV << "Enviando mensaje " << msg->getName() << " por la única puerta disponible.\n";
        send(msg, "out", 0);
        return;
    }

    // Generar un índice aleatorio diferente al de llegada
    int k = intuniform(0, n - 1);
    if (k == arrivalGateIndex && n > 1) {
        k = (k + 1) % n;  // Seleccionar la siguiente puerta disponible si hay conflicto
    }

    EV << "Reenviando mensaje " << msg->getName() << " por la puerta out[" << k << "]\n";
    send(msg, "out", k);
}

void Txc10a::justforwardMessage(cMessage *msg)
{
    int n = gateSize("out");
    int k = intuniform(0, n - 1);

    EV << "Reenviando self-message " << msg->getName() << " por la puerta out[" << k << "]\n";
    send(msg, "out", k);
}