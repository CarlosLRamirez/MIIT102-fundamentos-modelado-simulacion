//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


simple Txc4
{
    parameters:
        bool sendMsgOnInit = default(false); // whether the module should send out a message on initialization
        int limit = default(2);   // another parameter with a default value
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

//
// Adding module parameters.
//
network Tictoc4
{
    @display("bgb=468,269");
    submodules:
        tic: Txc4 {
            parameters:
                sendMsgOnInit = true;
                @display("i=,cyan;p=48,124");
        }
        toc: Txc4 {
            parameters:
                sendMsgOnInit = true;
                @display("i=,gold;p=357,61");
        }
    connections:
        tic.out --> {  delay = 150ms; } --> toc.in;
        tic.in <-- {  delay = 225ms; } <-- toc.out;
}

