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
