---
draft: false
title: "Parte 4: Mejorando el Tic Toc de 2 nodos"
---
## 4.1 Modelando el retardo en el proceso

En el modelo anterior tanto `tic`como `toc`reenviaban el mensaje de vuelta **inmediatamente** después de recibirlo.

En este paso, vamos a **agregar un temporizador** para simular un tiempo de procesamiento:
- Tanto `tic` como `toc` van a **retener el mensaje durante 1 segundo** antes de enviarlo de regreso.

**📌**  **¿Cómo funciona este modelo?**

En OMNeT++, implementar un temporizador se logra mediante el uso de **mensajes auto-enviados** (_self-messages_).

Estos mensajes se envían por un módulo a sí mismo para que regresen después de cierto tiempo.

📖 Aunque se llaman _self-messages_ por su uso, en realidad son objetos de mensaje ordinarios (cMessage) que simplemente se programan para ser recibidos por el mismo módulo que los envía.

**🔍 Variables agregadas a la clase**

Añadimos dos variables de tipo `cMessage*` a la definición de la clase para diferenciar entre:
1. `event`: El mensaje que representa el temporizador o retardo.
2. `tictocMsg`: El mensaje que se transmite entre los nodos y que estamos simulando que tiene un tiempo de procesamiento.

```c++ showLineNumbers{29}
class Txc6 : public cSimpleModule
{
  private:
    // Set the pointers to nullptr, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    cMessage *event = nullptr;  // pointer to the event object which we'll use for timing
    cMessage *tictocMsg = nullptr;  // variable to remember the message until we send it back

  public:
```

**⏳ ¿Cómo se programa un auto-mensaje?**

Para programar un mensaje a sí mismo (auto-mensaje) se utiliza la función `scheduleAt()`.

Esta función necesita:
- El tiempo en que queremos recibir el mensaje (`simTime() + 1.0`).
- El mensaje que queremos recibir (`event`).

Ejemplo del uso de scheduleAt() en el código:

```c++ showLineNumbers{94}
		scheduleAt(simTime()+1.0, event);
```

**📥 ¿Cómo diferenciamos los mensajes recibidos?**

En el método `handleMessage()`, necesitamos distinguir si el mensaje que recibimos es un **auto-mensaje (`event`)** o un mensaje enviado desde otro módulo (`tictocMsg`).

Esto se hace comparando si el mensaje recibido (`msg`) es el mismo que el evento programado (`event`):

```c++ showLineNumbers{80}
		if (msg == event) {
```

Alternativamente, se puede hacer así:

```c++
		if (msg->isSelfMessage())
```

Ambas maneras funcionan, pero la comparación directa (`msg == event`) es más rápida y sencilla para este caso.

En este ejemplo no se dejó por fuera el contador de mensajes para mantener el código pequeño:

**📌 ¿Qué se debe observar al correr la simulación?**

1. En la consola de OMNeT++, deberías ver mensajes como:

![[Pasted image 20250320171850.png]]

2. En la **gráfica de Secuencia de Eventos (Sequence Chart)**, verás cómo el mensaje tictocMsg viaja entre los módulos con un retraso de 1 segundo en cada rebote.

![[Pasted image 20250320171801.png]]


Código fuente del ejemplo:  [[tictoc6.ned]], [[txc6.cc]], [[omnetpp.ini]]

## 4.2 Números aleatorios y parámetros

En este ejemplo vamos a introducir el uso de **números aleatorios** en la simulación.

Vamos a cambiar el retardo fijo de 1 segundo por un **valor aleatorio** que puede configurarse desde el archivo **NED** o desde `omnetpp.in`.

**🔍 ¿Cómo se especifica un retardo aleatorio?**

En OMNeT++, los **parámetros del módulo** pueden devolver **valores aleatorios**.

Sin embargo, para utilizar correctamente esta característica, debemos leer el parámetro cada vez que lo necesitemos en `handleMessage()`.

Ejemplo de cómo se lee el parámetro aleatorio:

```c++ showLineNumbers{70}
            // The "delayTime" module parameter can be set to values like
            // "exponential(5)" (tictoc7.ned, omnetpp.ini), and then here
            // we'll get a different delay every time.
            simtime_t delay = par("delayTime");
 
            EV << "Message arrived, starting to wait " << delay << " secs...\n";
            tictocMsg = msg;
```
  
**🔢 ¿Cómo se configuran estos parámetros?**

Puedes definir el parámetro `delayTime` en el archivo `omnetpp.ini` para cada módulo.

Ejemplo:
```ini showLineNumbers{31}
Tictoc7.tic.delayTime = exponential(3s)
Tictoc7.toc.delayTime = truncnormal(3s,1s)
```

**❌ ¿Cómo se simula la pérdida de mensajes?**

En este modelo, se agrega la posibilidad de que un mensaje sea **perdido (eliminado)** con una probabilidad fija.

Esto se realiza utilizando la función uniform(0, 1) que genera un número aleatorio entre 0 y 1.

Si ese número es menor que 0.1 (10%), el mensaje se considera perdido y se elimina.

Ejemplo en código:
``` c++ showLineNumbers{65}
		if (uniform(0, 1) < 0.1) {
			EV << "\"Losing\" message\n";
			delete msg;
		}
```

**🔑 ¿Cómo funciona la generación de números aleatorios en OMNeT++?**
 
OMNeT++ utiliza un algoritmo determinista (por defecto, el **Mersenne Twister RNG**) para generar números aleatorios.
La ventaja de esto es que, si no cambias la semilla (*seed*), obtendrás siempre los mismos resultados al ejecutar la simulación varias veces.
Esto es importante para garantizar que los experimentos sean **reproducibles**.

**🔧 ¿Cómo se cambia la semilla (seed)?**

Si deseas cambiar la semilla para obtener resultados diferentes, debes especificar un nuevo valor en `omnetpp.ini` así:

``` ini
[General]
seed-0-mt=532569  # or any other 32-bit value
```

💡 **Nota:** OMNeT++ admite múltiples generadores de números aleatorios (RNGs), aunque en este tutorial se usa únicamente el RNG 0.

**📌 ¿Qué debes observar al correr la simulación?**
1. Verás que cada vez que se genera un retardo (delayTime), el valor será diferente.
2. Los mensajes pueden ser eliminados con una probabilidad del 10%, al momento de perder un evento, se termina la simulación.
3. Puedes experimentar utilizando diferentes distribuciones aleatorias en `omnetpp.ini`.


![[Pasted image 20250320181209.png]]

Código Fuente del ejemplo: [[tictoc7.ned]], [[txc7.cc]], [[omnetpp.ini]]

## 4.3 Simulación Stop-and-Wait 

Timeout y Cancelación de temporizadores

En este paso, vamos a implementar un mecanismo básico de **Stop-and-Wait** que es común en **protocolos de comunicación confiables**.

El objetivo es garantizar que un mensaje llegue correctamente al receptor, incluso si se pierde en el camino.

**🔍 ¿Qué cambia en este modelo?**

1. **Implementación de timeout (tiempo de espera):**
	- Si el receptor (`toc`) pierde un mensaje, el emisor (`tic`) debe **retransmitirlo después de un tiempo límite (`timeout`)**.

2. **Cancelación de temporizadores:**
	- Si `tic` recibe una respuesta de `toc` antes de que expire el tiempo límite, se cancela el temporizador.
	- Si el temporizador expira antes de recibir respuesta, se retransmite el mensaje.

**💡 ¿Cómo se simula la pérdida de mensajes? (Código de `toc`)**

El receptor (`toc`) tiene una probabilidad fija del 10% de perder cualquier mensaje que recibe.. Esto se implementa utilizando un número aleatorio generado con `uniform(0, 1)`.

``` c++ showLineNumbers{94}
void Toc8::handleMessage(cMessage *msg)
{
    if (uniform(0, 1) < 0.1) { // Probabilidad del 10% de perder el mensaje
        EV << "\"Losing\" message.\n";
        bubble("message lost");  /// Muestra una burbuja de notificación en la GUI
        delete msg;
    }
    else {
	    // Procesa el mensaje normalmente si no se pierde
        EV << "Sending back same message as acknowledgement.\n";
        send(msg, "out");
    }
}
```

**🔑 ¿Qué hace la llamada a `bubble()`?**

- La función `bubble("message lost")` muestra un **mensaje visual temporal** en la GUI cada vez que se pierde un mensaje.
- Esto es útil para **visualizar eventos importantes o fallos en la simulación**.

**⏳ ¿Cómo se maneja el temporizador en `tic`?**

Cada vez que `tic` envía un mensaje, programa un temporizador usando `scheduleAt()` para determinar cuándo debe retransmitir el mensaje si no recibe respuesta.

``` c++ showLineNumbers{67}
		scheduleAt(simTime() + timeout, timeoutEvent);
```

**❌ ¿Cómo se cancela el temporizador si toc responde?**

Si `tic` recibe una respuesta válida antes de que el temporizador expire, el temporizador se cancela usando:

``` c++ showLineNumbers{73}
		cancelEvent(timeoutEvent);
```

**🔑 Reutilización de mensajes de timeout**

Al cancelar un evento con `cancelEvent()`, el mensaje de timeout (`timeoutEvent`) **no se destruye**.

Esto permite que el mismo mensaje sea reutilizado múltiples veces sin tener que crear uno nuevo cada vez.

Esto es especialmente útil en simulaciones complejas donde hay que manejar múltiples eventos de **timeout**.

---

**📌 ¿Qué debes observar al correr la simulación?**

1. **Mensajes perdidos:**

• Se visualizarán burbujas con la etiqueta "message lost" cuando toc pierda un mensaje.

• Puedes ajustar la probabilidad de pérdida cambiando la condición (uniform(0, 1) < 0.1) a otro valor.

2. **Mecanismo de retransmisión:**

• tic continuará retransmitiendo un mensaje si no recibe una respuesta de toc debido a un mensaje perdido.

• Si tic recibe la respuesta a tiempo, el temporizador se cancela y se envía el siguiente mensaje.

---

**📊 ¿Por qué es importante este modelo?**

  

Este modelo introduce un concepto esencial en redes de comunicación:

• **Timeouts y retransmisión de mensajes.**

• El uso de cancelEvent() muestra cómo **cancelar y reutilizar temporizadores de manera eficiente**.

• Este mismo principio se utiliza en **protocolo TCP para manejo de retransmisiones (Stop-and-Wait, Go-Back-N, Selective Repeat, etc.)**.

---

**💡 Ejercicio adicional:**

1. Cambia la probabilidad de pérdida de mensajes a diferentes valores (0.2, 0.5, etc.) y observa el comportamiento.

2. ¿Qué sucede si agregas un retardo variable al mensaje que toc envía de regreso a tic?

3. Intenta hacer que tic muestre en pantalla cuántos intentos realiza antes de recibir una respuesta de toc.


Código Fuente del ejemplo: [[tictoc8.ned]] , [[txc8.cc]] , [[omnetpp.ini]]

---
**Fuente**:  [Tic Toc Tutorial](https://docs.omnetpp.org/tutorials/tictoc/part1/)




