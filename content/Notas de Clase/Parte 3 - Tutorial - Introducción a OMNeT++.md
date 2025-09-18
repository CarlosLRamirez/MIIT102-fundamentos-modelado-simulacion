---
draft: false
title: "Tutorial TicToc: Introducción a OMNeT++  - Parte 3: Mejorando el TicToc de 2 nodos"
aliases:
  - "Tutorial TicToc: Introducción a OMNeT++  - Parte 3: Mejorando el TicToc de 2 nodos"
modified: 2025-03-22T09:14:02-06:00
---
## 3.1 Agregar iconos a los módulos
  
Vamos a hacer que el modelo se vea **más atractivo** en la GUI.

Asignaremos un ícono (`block/routing`) a los módulos (archivo de imagen `images/block/routing.png`) y les daremos color cyan para `tic` y amarillo para `toc`'. Para esto agregamos **display string** en el archivo NED. La etiqueta `i=`significa que el **display string** específica el ícono.

Cree un archivo NED nuevo con el nombre `tictoc2.ned` y pegue el siguiente código

```ned showLineNumbers{1}
simple Txc2
{
    parameters:
        @display("i=block/routing"); // add a default icon
    gates:
        input in;
        output out;
}

//
// Make the two module look a bit different with colorization effect.
// Use cyan for `tic', and yellow for `toc'.
//
network Tictoc2
{
    submodules:
        tic: Txc2 {
            parameters:
                @display("i=,cyan"); // do not change the icon (first arg of i=) just colorize it
        }
        toc: Txc2 {
            parameters:
                @display("i=,gold"); // here too
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}
```

  El resultado de forma gráfica se ve en la pestaña **Design**:
  
![[Pasted image 20250314173250.png]]

## 3.2 Agregar mensajes de registro (logging)

Ahora vamos a modificar el código de C++ para agregar mensajes de **log**, de esta manera podamos ver que es lo que esta ocurriendo dentro del módulo.

OMNeT++ proporciona funcionalidades mas avanzadas para *logging*, los cuales son útiles para modelos grandes y complejos, sin embargo para este tutorial vamos a utilizar su forma más simple con la instrucción: `EV`

Agregamos la siguiente linea para que el nodo `tic`envíe un mensaje al momento de inicializar y justo antes de enviar el primer mensaje:

``` c++ showLineNumbers{27}
EV << "Sending initial message\n";
```

Adicionalmente con esta línea de código generamos un mensaje cada vez que un nodo recibe un mensaje y lo vuelve a reenviar:

``` c++ showLineNumbers{46}
EV << "Received message `" << msg->getName() << "', sending it out again\n";
```

Guarde estos cambios en nuevo archivo C++ llamado `txc2.cc`.

Como proximo paso, vamos a agregar en el archivo `omnetpp.ini`la nueva red que definimos en el archivo `tictoc2.ned`, agregamos una nueva configuración llamada `[Tictoc2]` y bajo esta configuración agregamos la nueva red con  `network = Tictoc2`.

```ini showLineNumbers{1}
[General]
# nothing here

[Tictoc1]
network = Tictoc1

[Tictoc2]
network = Tictoc2
```

### 3.2.1 Archivos con Código Fuente

Los nuevos archivos con código fuente que debería tener en este punto son:
- [tictoc2.ned](tictoc2_ned.md)
- [txc2.cc](txc2_cc.md)
- [omnetpp.ini](omnetpp_ini.md)
### 3.2.2 Ejecución de la simulación

Ejecutamos nuevamente la simulación, guardando previamente los cambios. Al inicio de la simulación nos saldrá un cuadro de diálogo para especificar el nombre de la *configuración* que vamos a simular, seleccionamos `Tictoc2`y damos click en OK.

![[Pasted image 20250314183124.png]]

Cuando ejecute la simulación en el entorno de ejecución OMNeT++, aparecerá la siguiente salida en la ventana de *log*:

![[Pasted image 20250314183502.png]]

También puede abrir ventanas de salida separadas para `tic` y `toc` haciendo clic con el botón derecho en sus iconos y seleccionando `Component log` en el menú. Esta función le resultará útil cuando tenga un modelo grande y sólo le interesen los mensajes de registro de un módulo específico.

Puede abrir ventanas de log por separado para `tic` y `toc` con **clic** **derecho** → **Component log**.

![[Pasted image 20250314230606.png]]

![[Pasted image 20250314230639.png]]

## 3.3 Agregar variables de estado 

En este paso agregamos un **contador** al modulo, y borraremos el mensaje luego de 10 intercambios.

 Cree una copia del archivo C++ y nombrelo `txc3.cc` y agregué lo siguiente:
 
Agregamos un contador como un miembro de la clase

```c++ showLineNumbers{18}
class Txc3 : public cSimpleModule
{
  private:
    int counter;
    
```

En `initialize()` establecemos la variable con un valor 10, ademas agregamos la instrucción `WATCH()`, lo cual nos permite poder ver el valor del contador en el entorno gráfico de la simulación.

```c++ showLineNumbers{34}
counter = 10;
```

```c++ showLineNumbers{40}
WATCH(counter);
```

En `handleMessage()` decrementamos el contador cada vez que llega un mensaje y al llegar a `0`borramos el mensaje,  Esto ocasionará que la simulación se quede sin eventos y se termine.

```c++ showLineNumbers{51}
    // Decrement counter and check value.
    counter--;
    if (counter == 0) {
        // If counter is zero, delete message. If you run the model, you'll
        // find that the simulation will stop at this point with the message
        // "no more events".
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
```

Genere un nuevo archivo `tictoc3.ned` para que sea consistente con el módulo `txc3.cc`, y actualice el `omnetpp.ini` para incluir esta nueva simulación.

### 3.3.1 Código Fuente

Los archivos con código fuente que debería tener en este punto son:
- [tictoc3.ned](tictoc3_ned.md)
- [txc3.cc](txc3_cc.md)
- [omnetpp.ini](omnetpp_ini.md)

### 3.3.2 Ejecución de la simulación

Ejecute la simulación, si hace click en el icono de `tic`, ventana del inspector en la parte inferior izquierda de la ventana principal mostrara detalles sobre `tic`. Asegúrese que el modo `Children`esté seleccionado en la barra de herramientas en la parte superior. El inspector deberia mostrar la variable del **contador**.

![[Pasted image 20250315000440.png]]

Al continuar la simulación puede ver que al llegar a cero esta se detendrá.


## 3.4 Agregar parámetros al módulo

En este pasó aprenderá a añadir parámetros a la simulación: convertirá el valor de inicio del **contador = 10** en un parámetro, y agregará un parámetro *booleano* para decidir si el módulo debe enviar el primer mensaje al inicializar (dependiendo si es un módulo `tic`o `toc`).

Los parámetros del módulo deben **declararse** en el archivo **NED**. El tipo de datos puede ser numérico, cadena, booleano o xml (este último para facilitar el acceso a los archivos de configuración XML), entre otros.

```ned showLineNumbers{12}
simple Txc4
{
    parameters:
        bool sendMsgOnInit = default(false); // whether the module should send out a message on initialization
        int limit = default(2);   // another parameter with a default value
        @display("i=block/routing");
    gates:
```

Para leer los parámetros dentro del código de C++ utilizamos la instrucción `par()`. Por ejemplo para leer el valor de `limit`y asignarlo a la variable `counter`utilizamos la instrucción dentro del método`initialize()`. Es importante asegurarse que el nombre del parámetro sea igual al definido en el archivo NED.

```c++ showLineNumbers{35}
counter = par("limit");
```

Adicionalmente utilizamos el parámetro `sendMsgOnInit`para decidir si el nodo envía o nó el mensaje inicial.

```c++ showLineNumbers{39}
if (par("sendMsgOnInit").boolValue())
    send(new cMessage("tictocMsg"), "out");
```

La asignación de valores a los parámetros lo podemos hacer desde el archivo NED o desde el `omnetpp.ini`. La asignación en el archivo NED toma precedencia.  Usted puede definir valores por defecto para los parámetros si utiliza la sintaxis `default(...)` en el archivo NED. En este caso usted puede  ya sea que establezca el valor del parámetro en el `omnetpp.ini`o utilize el valor por defecto provisto en el archivo NED.

Aquí, asignamos `true`al parametro  `sendMsgOnInit` para el notod `tic`y `false`para el nodo `toc`:

```ned showLineNumbers{26}
network Tictoc4
{
    submodules:
        tic: Txc4 {
            parameters:
                sendMsgOnInit = true;
                @display("i=,cyan");
        }
        toc: Txc4 {
            parameters:
                sendMsgOnInit = false;
                @display("i=,gold");
        }
    connections:
```

Y en el archivo `omnetpp.ini` asignamos un valor de `5`al limite de mensajes en `toc`

```ini showLineNumbers{17}
Tictoc4.toc.limit = 5
```

Dado que `omnetpp.ini` soporta **wildcards**, y los parámetros asignados en el archivo NED toma precedencia sobre los de `omnetpp.ini`, pudemos utilizar por ejemplo:

```ini
Tictoc4.t*c.limit = 5
```

o

```ini
Tictoc4.*.limit = 5
```

  o incluso 
  
```ini
**.limit = 5
```

Lo cual tendría el mismo efecto. (La diferencia entre `*` y `**`es que `*` **no** hace coincidencia con un punto, mientras `**`**si** lo hace)

Genere nuevos archivos `txc4.cc`y `tictoc4.ned`con los cambios indicados. Actualize el archivo`omnetpp.ini`con la configuración para este ejercicio, y corra esta configuración en la simulación.

### 3.4.1 Código Fuente

Los archivos con código fuente para este paso son los siguientes:
- [txc4.cc](txc4_cc.md)
- [tictoc4.ned](tictoc4_ned.md)
- [omnetpp.ini](omnetpp_ini.md)
### 3.4.2 Ejecución de la Simulación

En el entorno gráfico de ejecución, puede inspeccionar los parámetros de los módulos en el árbol de objetos situado a la izquierda de la ventana principal o en la página Parámetros del inspector de módulos (la información se muestra en la esquina inferior izquierda de la ventana principal tras hacer clic en un módulo).

El módulo con el límite más pequeño borrará el mensaje y, por tanto, concluirá la simulación.

![[Pasted image 20250315071948.png]]


---

## 3.5 Uso de herencia en del archivo NED

Si vemos mas de cerca al archivo NED nos daremos cuenta de que `tic` y `toc` sólo se diferencian en los valores de sus parámetros y en su cadena de visualización (icono). 

Podemos crear un nuevo tipo de módulo simple heredando de otro y especificando o sobreescribiendo algunos de sus parámetros. En nuestro caso derivaremos dos tipos de módulo simples (`Tic` y `Toc`). Más adelante podremos utilizar estos tipos al definir los submódulos de la red.

Derivar de un módulo simple existente es fácil. Este sería el **módulo base**:

``` ned showLineNumbers{14}
simple Txc5
{
    parameters:
        bool sendMsgOnInit = default(false);
        int limit = default(2);
        @display("i=block/routing");
    gates:
        input in;
        output out;
}
```

Y este sería un **modulo derivado**. Simplemente especificamos los valores de los parámetros y algunas propiedades de visualización.

```ned showLineNumbers{30}
simple Tic5 extends Txc5
{
    parameters:
        @display("i=,cyan");
        sendMsgOnInit = true;   // Tic modules should send a message on init
}
```

El módulo `Toc`sería muy similar, solo que valores diferentes de parámetros

```ned showLineNumbers{42}
simple Toc5 extends Txc5
{
    parameters:
        @display("i=,gold");
        sendMsgOnInit = false;  // Toc modules should NOT send a message on init
}
```

>[!NOTA]
La implementación en C++ se hereda del módulo base simple (`Txc5`).
  
Una vez creados los nuevos módulos simples, podemos utilizarlos como tipos de submódulos en nuestra red:

```ned showLineNumbers{52}
network Tictoc5
{
    submodules:
        tic: Tic5;  // the limit parameter is still unbound here. We will get it from the ini file
        toc: Toc5;
    connections:
```

Como puede ver, la definición de red es ahora mucho más corta y sencilla. La herencia te permite utilizar tipos comunes en tu grafo y evitar definiciones y parametrizaciones redundantes.

Genere nuevos archivos `txc5.cc`y `tictoc5.ned`con los cambios indicados. Actualize el archivo`omnetpp.ini`con la configuración para este ejercicio, y corra esta configuración en la simulación.

### 3.5.1 Código Fuente

Los archivos con código fuente que debería tener en este punto son:
- [tictoc5.ned](tictoc5_ned.md)
- [txc5.cc](txc5_cc.md)
- [omnetpp.ini](omnetpp_ini.md)

## 3.6 Ejercicio de Comprobación 1

Realice el siguiente ejercicio: [Ejercicio Omnet++ No. 1: Extensión del modelo Tic-Toc con Triángulo de 3 Nodos](Ejercicio%20Omnet++%20No.%201%20Extensión%20del%20modelo%20Tic-Toc%20con%20Triángulo%20de%203%20Nodos.md)

## 3.7 Modelando el retardo en el proceso

En el modelo anterior tanto `tic`como `toc`reenviaban el mensaje de vuelta **inmediatamente** después de recibirlo.

En este paso, vamos a **agregar un temporizador** para simular un tiempo de procesamiento:
- Tanto `tic` como `toc` van a **retener el mensaje durante 1 segundo** antes de enviarlo de regreso.

### 3.7.1 Funcionamiento del modelo

En OMNeT++, implementar un temporizador se logra mediante el uso de **mensajes auto-enviados** (_self-messages_).

Estos mensajes se envían por un módulo a sí mismo para que regresen después de cierto tiempo.

📖 Aunque se llaman _self-messages_ por su uso, en realidad son objetos de mensaje ordinarios (cMessage) que simplemente se programan para ser recibidos por el mismo módulo que los envía.

### 3.7.2 Variables adicionales 

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

### 3.7.3 Programación del auto-mensaje

Para programar un mensaje a sí mismo (auto-mensaje) se utiliza la función `scheduleAt()`.

Esta función necesita:
- El tiempo en que queremos recibir el mensaje (`simTime() + 1.0`).
- El mensaje que queremos recibir (`event`).

Ejemplo del uso de scheduleAt() en el código:

```c++ showLineNumbers{94}
		scheduleAt(simTime()+1.0, event);
```

### 3.7.4 ¿Cómo diferenciamos los mensajes recibidos?

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
### 3.7.5 Ejecución de la simulación

1. En la consola de OMNeT++, deberías ver mensajes como:

![[Pasted image 20250320171850.png]]

2. En la **gráfica de Secuencia de Eventos (Sequence Chart)**, verás cómo el mensaje tictocMsg viaja entre los módulos con un retraso de 1 segundo en cada rebote.

![[Pasted image 20250320171801.png]]


### 3.7.6 Código Fuente

- [tictoc6.ned](tictoc6_ned.md)
- [txc6.cc](txc6_cc.md)
- [omnetpp.ini](omnetpp_ini.md)

## 3.8 Números aleatorios y parámetros

En este ejemplo vamos a introducir el uso de **números aleatorios** en la simulación.

Vamos a cambiar el retardo fijo de 1 segundo por un **valor aleatorio** que puede configurarse desde el archivo **NED** o desde `omnetpp.in`.

### 3.8.1 Especificación del retardo aleatorio

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

### 3.8.2 Configuración de parámetros

Puedes definir el parámetro `delayTime` en el archivo `omnetpp.ini` para cada módulo.

Ejemplo:
```ini showLineNumbers{31}
Tictoc7.tic.delayTime = exponential(3s)
Tictoc7.toc.delayTime = truncnormal(3s,1s)
```

### 3.8.3 Simulando la pérdida del mensaje

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


### 3.8.4 Generación de números aleatorios en OMNeT++
 
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

### 3.8.5 Ejecución de la simulación

1. Verás que cada vez que se genera un retardo (delayTime), el valor será diferente.
2. Los mensajes pueden ser eliminados con una probabilidad del 10%, al momento de perder un evento, se termina la simulación.
3. Puedes experimentar utilizando diferentes distribuciones aleatorias en `omnetpp.ini`.


![[Pasted image 20250320181209.png]]

### 3.8.6 Código Fuente

- [tictoc7.ned](tictoc7_ned.md)
- [txc7.cc](txc7_cc.md)
- [omnetpp.ini](omnetpp_ini.md)


## 3.9 Simulación Stop-and-Wait  (Timeout y Cancelación de temporizadores)

En este paso, vamos a implementar un mecanismo básico de **Stop-and-Wait** que es común en **protocolos de comunicación confiables**.

El objetivo es garantizar que un mensaje llegue correctamente al receptor, incluso si se pierde en el camino.

### 3.9.1 Cambios en el modelo

1. **Implementación de timeout (tiempo de espera):**
	- Si el receptor (`toc`) pierde un mensaje, el emisor (`tic`) debe **retransmitirlo después de un tiempo límite (`timeout`)**.

2. **Cancelación de temporizadores:**
	- Si `tic` recibe una respuesta de `toc` antes de que expire el tiempo límite, se cancela el temporizador.
	- Si el temporizador expira antes de recibir respuesta, se retransmite el mensaje.

### 3.9.2 Simulación de la pérdida de mensajes (Código de `toc`)

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

### 3.9.3 Función  'bubble()'

- La función `bubble("message lost")` muestra un **mensaje visual temporal** en la GUI cada vez que se pierde un mensaje.
- Esto es útil para **visualizar eventos importantes o fallos en la simulación**.

### 3.9.4 Manejo de  temporizador en `tic`?

Cada vez que `tic` envía un mensaje, programa un temporizador usando `scheduleAt()` para determinar cuándo debe retransmitir el mensaje si no recibe respuesta.

``` c++ showLineNumbers{67}
		scheduleAt(simTime() + timeout, timeoutEvent);
```


### 3.9.5 Cancelación del temporizador si `toc` responde

Si `tic` recibe una respuesta válida antes de que el temporizador expire, el temporizador se cancela usando:

``` c++ showLineNumbers{73}
		cancelEvent(timeoutEvent);
```

### 3.9.6  Reutilización de mensajes de timeout

Al cancelar un evento con `cancelEvent()`, el mensaje de timeout (`timeoutEvent`) **no se destruye**.

Esto permite que el mismo mensaje sea reutilizado múltiples veces sin tener que crear uno nuevo cada vez.

Esto es especialmente útil en simulaciones complejas donde hay que manejar múltiples eventos de **timeout**.

### 3.9.7 Ejecución de la simulación

1. **Mensajes perdidos:**
	- Se visualizarán burbujas con la etiqueta "message lost" cuando toc pierda un mensaje
	- Puedes ajustar la probabilidad de pérdida cambiando la condición (`uniform(0, 1) < 0.1`) a otro valor.

2. **Mecanismo de retransmisión:**
	- `tic` continuará retransmitiendo un mensaje si no recibe una respuesta de `toc` debido a un mensaje perdido.
	- Si `tic` recibe la respuesta a tiempo, el temporizador se cancela y se envía el siguiente mensaje.

![[message lost.gif|400]]

![[Pasted image 20250321151003.png]]


### 3.9.8 Código Fuente

- [tictoc8.ned](tictoc8_ned.md)
- [txc8.cc](txc8_cc.md)
- [omnetpp.ini](omnetpp_ini.md)

## 3.10 Retransmisión del mismo mensaje

En este paso, vamos a mejorar el modelo anterior (*Stop-and-Wait*), en el cual cada vez que se necesitaba retransmitir un mensaje, simplemente se creaba uno nuevo.

Aunque eso funcionaba, no es una práctica eficiente en sistemas reales, porque:

1. Los mensajes pueden contener información compleja o grande (no es eficiente recrearlos cada vez).
2. Perderíamos información útil almacenada en el mensaje original.

### 3.10.1 Cambios en el módulo

En lugar de crear un mensaje nuevo cada vez que ocurre un timeout, vamos a:

1. Mantener una copia del mensaje original que se debe retransmitir.
2. Enviar copias del mensaje original cuando sea necesario retransmitirlo.
3. Eliminar el mensaje original solo cuando se recibe una confirmación (ACK) de `toc`.

**🔑 ¿Por qué hacer esto?**

1. **Evita recrear mensajes innecesariamente:**
	- En lugar de crear un nuevo mensaje cada vez que ocurre un timeout, se envía una copia del mensaje original.

2. **Facilita el seguimiento de mensajes:**
	- Al mantener el mensaje original, se puede incluir un **número de secuencia (`sequence number`)** para identificarlo.
	- Esto ayuda a visualizar mejor el comportamiento de la simulación y a depurar el código.

### 3.10.2 Funciones nuevas implementadas

Se crean dos funciones nuevas para simplificar `handleMessage()` y manejar la creación y retransmisión de mensajes.
#### 3.10.2.1 📌 Generar un nuevo mensaje: `generateNewMessage()`

Esta función crea un nuevo mensaje con un nombre único que incluye un número de secuencia (`seq`).

``` c++ showLineNumbers{89}
cMessage *Tic9::generateNewMessage()
{
    // Generate a message with a different name every time.
    char msgname[20];
    sprintf(msgname, "tic-%d", ++seq);
    cMessage *msg = new cMessage(msgname);
    return msg;
}turn msg;
}
```

#### 3.10.2.2 📌 Enviar una copia del mensaje: `sendCopyOf()`

Esta función duplica el mensaje original y envía la copia.

``` c++ showLineNumbers{98}
void Tic9::sendCopyOf(cMessage *msg)
{
    // Duplicate message and send the copy.
    cMessage *copy = (cMessage *)msg->dup();
    send(copy, "out");
}
```

**📌 ¿Por qué separar estas funciones?**

- Al separar el código en funciones, `handleMessage()` se mantiene limpio y fácil de entender.
- También facilita la reutilización de código y permite que cada función tenga una responsabilidad clara.

### 3.10.3 Ejecución de la simulación

1. En la consola, verás mensajes con nombres únicos (*tic-1*, *tic-2*, etc.) indicando la secuencia de mensajes enviados.
2. En la gráfica de secuencia (*Sequence Chart*), será fácil identificar cada mensaje por su número de secuencia.
3. Los mensajes se siguen retransmitiendo en caso de pérdida, pero ahora se envían **copias del mensaje original**.

![[Pasted image 20250321191818.png]]

![[Pasted image 20250321192118.png]]

### 3.10.4 Código Fuente

- [tictoc9.ned](tictoc9_ned.md)
- [txc9.cc](txc9_cc.md)
- [omnetpp.ini](omnetpp_ini.md)

---
**Fuente**:  [Tic Toc Tutorial](https://docs.omnetpp.org/tutorials/tictoc/part1/)




