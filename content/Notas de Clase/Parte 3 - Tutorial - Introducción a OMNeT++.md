---
draft: false
---
## Parte 3: Mejorando el Tic Toc de 2 nodos

### 3.1 Agregar íconos a los módulos
  
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

[[tictoc2.ned]]

### 3.2 Agregar mensajes de registro (logging)

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

Guarde estos cambios en nuevo archivo C++ llamado `txc2.cc`, el archivo debería quedar de esta manera: [[txc2.cc]] 

Como proximo paso, vamos a agregar en el archivo `omnetpp.ini`la nueva red que definimos en el archivo `tictoc2.ned`, agregamos una nueva configuración llamada `[Tictoc2]` y bajo esta configuración agregamos la nueva red con  `network = Tictoc2`.

```ini showLineNumbers{1}
[General]
# nothing here

[Tictoc1]
network = Tictoc1

[Tictoc2]
network = Tictoc2
```

Ejecutamos nuevamente la simulación, guardando previamente los cambios. Al inicio de la simulación nos saldrá un cuadro de diálogo para especificar el nombre de la *configuración* que vamos a simular, seleccionamos `Tictoc2`y damos click en OK.

![[Pasted image 20250314183124.png]]

Cuando ejecute la simulación en el entorno de ejecución OMNeT++, aparecerá la siguiente salida en la ventana de *log*:

![[Pasted image 20250314183502.png]]

También puede abrir ventanas de salida separadas para `tic` y `toc` haciendo clic con el botón derecho en sus iconos y seleccionando `Component log` en el menú. Esta función le resultará útil cuando tenga un modelo grande y sólo le interesen los mensajes de registro de un módulo específico.

Puede abrir ventanas de log por separado para `tic` y `toc` con **clic** **derecho** → **Component log**.

![[Pasted image 20250314230606.png]]

![[Pasted image 20250314230639.png]]


Código fuente: [[txc2.cc]], [[tictoc2.ned]], [[omnetpp.ini]]
### 3.3 Agregar variables de estado 

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

Ejecute la simulación, si hace click en el icono de `tic`, ventana del inspector en la parte inferior izquierda de la ventana principal mostrara detalles sobre `tic`. Asegúrese que el modo `Children`esté seleccionado en la barra de herramientas en la parte superior. El inspector deberia mostrar la variable del **contador**.

![[Pasted image 20250315000440.png]]

Al continuar la simulación puede ver que al llegar a cero esta se detendrá.

Código Fuente:  [[txc3.cc]] , [[tictoc2.ned]], [[omnetpp.ini]]

### 3.4 Agregar parámetros al módulo

En este pasó aprenderá a añadir parámetros a la simulación: convertirá el valor de inicio del contador = 10 en un parámetro, y agregará un parámetro booleano para decidir si el módulo debe enviar el primer mensaje al inicializar (dependiendo si es un módulo `tic`o `toc`).

Los parámetros del módulo deben **declararse** en el archivo NED. El tipo de datos puede ser numérico, cadena, booleano o xml (este último para facilitar el acceso a los archivos de configuración XML), entre otros.

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

En el entorno gráfico de ejecución, puede inspeccionar los parámetros de los módulos en el árbol de objetos situado a la izquierda de la ventana principal o en la página Parámetros del inspector de módulos (la información se muestra en la esquina inferior izquierda de la ventana principal tras hacer clic en un módulo).

El módulo con el límite más pequeño borrará el mensaje y, por tanto, concluirá la simulación.

![[Pasted image 20250315071948.png]]

Código Fuente: [[txc4.cc]], [[tictoc4.ned]], [[omnetpp.ini]]

---

### 3.5 Uso de herencia en del archivo NED

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

Código fuente:  [[txc5.cc]], [[tictoc5.ned]], [[omnetpp.ini]]

### 3.6 Ejercicio de Comprobación

Continue con el siguiente ejercicio: [[Ejercicio de Comprobación - Extensión del modelo Tic-Toc con Triángulo de 3 Nodos|Ejercicio: Tic Toc Triangulo]]


---
**Fuente**:  [Tic Toc Tutorial](https://docs.omnetpp.org/tutorials/tictoc/part1/)




