---
created: 2025-03-22T02:42:25-06:00
modified: 2025-03-22T09:48:20-06:00
title: tictoc13.msg
aliases:
  - tictoc13.msg
---
```cpp showLineNumbers{1}
//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

message TicTocMsg13
{
    int source;
    int destination;
    int hopCount = 0;
}

```