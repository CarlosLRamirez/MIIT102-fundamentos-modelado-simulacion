---
aliases:
  - tictoc16.msg
title: tictoc16.msg
modified: 2025-03-22T09:48:50-06:00
---

```ned showLineNumbers{1}
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
message TicTocMsg16
{
    int source;
    int destination;
    int hopCount = 0;
}
```
