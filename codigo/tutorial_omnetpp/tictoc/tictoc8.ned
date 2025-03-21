//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


simple Tic8
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Toc8
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
        output out;
}

network Tictoc8
{
    @display("bgb=312,220");
    submodules:
        tic: Tic8 {
            parameters:
                @display("i=,cyan;p=57,162");
        }
        toc: Toc8 {
            parameters:
                @display("i=,gold;p=239,45");
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}

