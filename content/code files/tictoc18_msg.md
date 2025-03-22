---
aliases:
  - tictoc18.msg
title: tictoc18.msg
modified: 2025-03-22T09:50:48-06:00
---

```c++ showLineNumbers{1}
//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// Same as TictocMsg11
//
message TicTocMsg18
{
    int source;
    int destination;
    int hopCount = 0;
}
```
