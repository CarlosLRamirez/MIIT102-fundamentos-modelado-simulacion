//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <cstdio>
#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

// Include a generated file: the header file created from tictoc13.msg.
// It contains the definition of the TictocMsg10 class, derived from
// cMessage.
#include "tictoc13_m.h"

/**
 * In this step the destination address is no longer node 2 -- we draw a
 * random destination, and we'll add the destination address to the message.
 *
 * The best way is to subclass cMessage and add destination as a data member.
 * Hand-coding the message class is usually tiresome because it contains
 * a lot of boilerplate code, so we let OMNeT++ generate the class for us.
 * The message class specification is in tictoc13.msg -- tictoc13_m.h
 * and .cc will be generated from this file automatically.
 *
 * To make the model execute longer, after a message arrives to its destination
 * the destination node will generate another message with a random destination
 * address, and so forth.
 */
class Txc13a : public cSimpleModule
{
  private:
      cMessage *sendTimer;   // Temporizador para generación periódica de mensajes
      simtime_t sendInterval; // Intervalo entre mensajes
  protected:
    virtual TicTocMsg13 *generateMessage();
    virtual void forwardMessage(TicTocMsg13 *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual ~Txc13a(); // Destructor
};

Define_Module(Txc13a);

void Txc13a::initialize()
{
    // Crear el temporizador para generación periódica de mensajes
    sendTimer = new cMessage("sendTimer");
    sendInterval = par("sendInterval");

    // Solo el módulo 0 inicia la generación periódica de mensajes
    if (getIndex() == 0) {
        scheduleAt(simTime() + exponential(sendInterval.dbl()), sendTimer);
    }
}

void Txc13a::handleMessage(cMessage *msg)
{
    if (msg == sendTimer) {
        // Generar un nuevo mensaje periódico
        TicTocMsg13 *newmsg = generateMessage();
        EV << "Generando un nuevo mensaje periódico: " << newmsg->getName() << "\n";
        forwardMessage(newmsg);

        // Programar el siguiente evento periódico
        scheduleAt(simTime() + exponential(sendInterval.dbl()), sendTimer);
    }
    else {
        TicTocMsg13 *ttmsg = check_and_cast<TicTocMsg13 *>(msg);

        if (ttmsg->getDestination() == getIndex()) {
            // Mensaje llegó a su destino
            EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
            bubble("ARRIVED, starting new one!");
            delete ttmsg;
        } 
        else {
            // Reenviar el mensaje a otro nodo
            forwardMessage(ttmsg);
        }
    }
}

TicTocMsg13 *Txc13a::generateMessage()
{
    // Produce source and destination addresses.
    int src = getIndex();  // our module index
    int n = getVectorSize();  // module vector size
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;

    char msgname[20];
    snprintf(msgname, sizeof(msgname), "tic-%d-to-%d", src, dest);
    EV << "Generando mensaje nuevo desde " << src << " hacia " << dest << ".\n";
    
    // Create message object and set source and destination field.
    TicTocMsg13 *msg = new TicTocMsg13(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void Txc13a::forwardMessage(TicTocMsg13 *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

Txc13a::~Txc13a() {
    cancelAndDelete(sendTimer);
}
