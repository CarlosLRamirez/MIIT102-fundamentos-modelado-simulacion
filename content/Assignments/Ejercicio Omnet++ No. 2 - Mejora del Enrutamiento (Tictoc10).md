---
created: 2025-03-22T01:07:23-06:00
modified: 2025-03-22T07:22:34-06:00
title: "Ejercicio Omnet++ No. 2: Mejora del Enrutamiento (Tictoc10)"
---
## **📖 Contexto**

En la versión actual del modelo *Tictoc10*, un mensaje es generado por tic[0] y luego es pasado de un nodo a otro **de manera aleatoria**.

El problema con este enfoque es que un mensaje puede rebotar entre dos nodos indefinidamente antes de ser enviado a otro módulo diferente.

## 🎯 Objetivo del Ejercicio

Modificar el modelo Tictoc10 para que un nodo **no envíe el mensaje de regreso al mismo nodo del cual lo recibió**.

Esto debe hacerse modificando la función forwardMessage() para que considere el puerto de llegada del mensaje.

## 🔑 Conceptos que debes aplicar

1. `cMessage::getArrivalGate()`:

- Permite identificar **por cuál puerta llegó el mensaje** al módulo.

- Devuelve un puntero a un objeto cGate o NULL si es un mensaje auto-enviado (self-message).

2. `cGate::getIndex()`:

- Permite identificar el **índice de la puerta en un vector de puertas (in[] o out[])**.

- Útil para determinar qué puerta evitar al reenviar un mensaje.


## 🔨 Instrucciones

1. Abre el archivo txc10.cc y ubica la función `forwardMessage()`.

2. Modifica la función para que el mensaje **no se envíe de regreso por la misma puerta por la que llegó**.

3. Asegúrate de que el código verifique si el mensaje es un self-message antes de intentar identificar su puerto de llegada.

## ✅ Criterios de éxito

1. El mensaje **nunca debe regresar al nodo por la misma puerta por la que llegó**.
2. El mensaje debe poder llegar correctamente a `tic[3]` en la simulación.
3. El EV debe imprimir mensajes que indiquen qué puerta fue utilizada para reenviar cada mensaje.

## **💡 Preguntas para Reflexión**
- ¿Qué sucede si todos los módulos (tic[]) están interconectados en un ciclo cerrado?
- ¿Es posible mejorar aún más la eficiencia del enrutamiento al agregar métricas o prioridades a cada puerta de salida?
