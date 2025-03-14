---
draft: false
title: "Tutorial introductorio: Primeros pasos en OMNeT++"
---
# Tutorial Introductorio de OMNeT++

Este tutorial le ayudará con los primeros para trabajar con OMNeT++ , comprender los componentes principales y herramientas, y conocer el flujo de trabajo para ejecutar una simulación.
## Instrucciones

Siga esta guia paso a paso, y al final de la sesión presente los resultados del ejercicio.
## Parte 1:  Como empezar
### 1.1 El modelo

El modelo que vamos a simular consta de una **red** formada por dos nodos. Los nodos realizarán una tarea sencilla: **uno de ellos creará un paquete**, y ambos lo enviarán de un lado a otro de forma continua. Llamaremos a estos nodos **tic** y **toc**.

Más adelante, iremos mejorando este modelo, incorporando nuevas características de **OMNeT++** en cada paso.
### 1.2 Configuración del espacio de trabajo y el proyecto

1. **Iniciar el IDE de OMNeT++** ejecutando el comando `omnetpp` desde la terminal del sistema operativo. En Windows, debe usarse la terminal **MINGW64** incluida con OMNeT++, o alternativamente **WSL** si está configurado.

> [!NOTA]
> Se asume que OMNeT++ ya está instalado en su sistema operativo y que las variables de entorno fueron configuradas correctamente.

2. **Selecciónar el espacio de trabajo (workspace)**:
	- Si está utilizando OMNeT++ por primera vez, se recomienda crear una carpeta específica para este propósito. Puede ubicarla, por ejemplo, en su carpeta de usuario:
		- **Windows:** `C:/Users/miusuario/tutorial`
		- **Linux/macOS:**` /home/miusuario/tutorial`

	- Al abrir OMNeT++, probablemente se le solicitará seleccionar la carpeta para el espacio de trabajo. Elija la carpeta que creó en el paso anterior.
		![[Pasted image 20250312071129.png|600]]
3. Después de hacer clic en **Launch**, es probable que aparezca una ventana de introducción con accesos directos a documentación y tutoriales. Puede cerrarla haciendo clic en la **X** de la pestaña.

	![[Pasted image 20250312071931.png]]

4. En caso de mostrarse una ventana para confirmar la instalación del **INET Framework** y otros ejemplos de OMNeT++, **deselecciónelos** por ahora y haga clic en **OK**.

	![[Pasted image 20250312072147.png|600]]

5. Finalmente, debería visualizar la pantalla principal del IDE de OMNeT++, como se muestra a continuación:

	![[Pasted image 20250312072421.png|600]]

6. **Crear el proyecto:** Desde el menú principal, seleccione **File -> New -> OMNeT++ Project**.

	![[Pasted image 20250312072747.png|600]]

7. Se abrirá un asistente (wizard). Complete los siguientes campos:

	- **Project name:** `tictoc`
	
		![[Pasted image 20250312073207.png]]
	
	- Seleccione la opción **Empty Project**.
	
		![[Pasted image 20250312073409.png]]
	
	- Finalmente, haga clic en **Finish**.

8. El nuevo proyecto aparecerá en el **Explorador de Proyectos**. 

	- Aquí es donde se deberán guardar todos los archivos relacionados con la simulación.
		
		![[Pasted image 20250312073543.png]]

> [!NOTA] 
> 🔑 En simulaciones más complejas, es posible organizar los archivos en subcarpetas para mantener el proyecto ordenado.

### 1.3 Agregar el achivo NED

OMNeT++ utiliza ficheros NED para definir componentes y ensamblarlos en unidades mayores como redes. Comenzamos a implementar nuestro modelo añadiendo un **archivo NED.** 

Para añadir el archivo al proyecto, haga clic con el botón derecho del ratón en el directorio del proyecto en el panel del *Project Explorer* a la izquierda, y seleccione **New -> Network Description File (NED)** en el menú. 

![[Pasted image 20250313152434.png]]


Introduzca `tictoc1.ned` cuando se le pida el nombre del archivo.

![[Pasted image 20250313152524.png]]

A continuación seleccione la opción para crear un archivo NED vacio.

![[Pasted image 20250313152608.png]]


Una vez creado, el archivo puede editarse en el área de edición del IDE OMNeT++. 

El editor NED del IDE OMNeT++ tiene dos modos, **Diseño** *(Design)* y **Fuente** *(Source)*; se puede cambiar entre ellos utilizando las pestañas de la parte inferior del editor. 

![[Pasted image 20250313152807.png]]

En el modo **Diseño**, la topología puede editarse gráficamente, utilizando el ratón y la paleta de la derecha. En el modo **Fuente**, el código fuente NED puede editarse directamente como texto. Los cambios realizados en un modo se reflejarán inmediatamente en el otro, por lo que puede alternar libremente entre los modos durante la edición, y realizar cada cambio en el modo que le resulte más cómodo. (Dado que los archivos NED son archivos de texto sin formato, puede incluso utilizar un editor de texto externo para editarlos, aunque se perderá el resaltado de sintaxis, el asistente de contenido, las referencias cruzadas y otras características del IDE).

Cambie al modo Fuente e introduzca lo siguiente:

```ned
simple Txc1
{
    gates:
        input in;
        output out;
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Tictoc1
{
    submodules:
        tic: Txc1;
        toc: Txc1;
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}
```

![[Pasted image 20250313153202.png]]

Cuando haya terminado, vuelva al modo **Diseño**. Debería ver algo como esto:

![[Pasted image 20250313153334.png]]

El primer bloque del archivo declara `Txc1` como un tipo de módulo simple. Los módulos simples son atómicos en el nivel NED. También son componentes activos y su comportamiento se implementa en C++. La declaración también dice que `Txc1` tiene una puerta de entrada llamada `in`, y una puerta de salida llamada `out`.

El segundo bloque declara `Tictoc1` como una red. `Tictoc1` se ensambla a partir de dos sub-módulos, `tic` y `toc`, ambos instancias del módulo tipo `Txc1`. La puerta de salida de `tic` se conecta a la puerta de entrada de `toc`, y viceversa. 

Habrá un retardo de propagación de 100 ms en ambos sentidos.

### 1.4 Agregar los archivos de C++

Ahora necesitamos implementar la funcionalidad del módulo simple `Txc1` en C++. Cree un archivo llamado `txc1.cc` seleccionando **New -> Source File** en el menú contextual del proyecto (o **File -> New-> File** en el menú principal del IDE). 

![[Pasted image 20250313155104.png]]

Asegúrese que se encuentre en el folder padre `tictoc` y coloque `txc1.cc` como nombre del achivo

![[Pasted image 20250313171911.png]]

En el editor, pegue el siguiente contenido:

```c++
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Txc1 : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);

void Txc1::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");
    }
}

void Txc1::handleMessage(cMessage *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
    send(msg, "out"); // send out the message
}
```

![[Pasted image 20250313172133.png]]
  
El **módulo simple** llamado `Txc1` está representado por la **clase C++** `Txc1`.

Esta clase debe **heredar** (es decir, extender o basarse) en una clase especial de OMNeT++ llamada `cSimpleModule`.

Además, para que OMNeT++ pueda usar esta clase en la simulación, debemos **registrarla** usando la instrucción especial `Define_Module(Txc1`);.

Dentro de esta clase, hay **dos funciones importantes** que **redefinimos** (es decir, escribimos de nuevo para que hagan lo que queremos):

1. **`initialize()`**: Esta función se llama **una sola vez**, al **inicio de la simulación**.
	
	• Aquí, uno de los módulos (el que se llama **“`tic`”**) crea un **mensaje** (objeto `cMessage`) y lo envía por una **puerta de salida** llamada "`out`".
	• Esa puerta está conectada al otro módulo (llamado “`toc`”), así que el mensaje viajará hacia él.

2. **`handleMessage(cMessage *msg)`**:

	• Esta función se llama **cada vez que llega un mensaje** al módulo.
	• Lo que hace es muy simple: **volver a enviar el mensaje por la puerta “`out`”**, de regreso al otro módulo.
	• Así, los dos módulos se estarán enviando el mismo mensaje de un lado a otro, como un “ping-pong”.

**¿Qué más debemos saber?**

• En OMNeT++, **todos los mensajes**, ya sean paquetes, tramas, trabajos o eventos (como temporizadores o “timeouts”), son objetos de tipo `cMessage` o derivados de esta clase.

• Cuando enviamos un mensaje, **el núcleo de la simulación** (simulation kernel) se encarga de **guardar** ese mensaje y **entregarlo** al otro módulo **después de un tiempo**.

Ese tiempo se define, por ejemplo, en el archivo NED (en este caso, el enlace tiene un retraso de **100 ms**).

• Como ambos módulos hacen lo mismo (recibir y reenviar), el mensaje **nunca se detiene**. Se seguirá enviando una y otra vez, hasta que nosotros **paremos la simulación desde la interfaz gráfica (GUI)**.

• **Nota importante**: Esta simulación **no tiene una condición de parada automática**. Solo se detendrá si:
	• La paramos manualmente desde la GUI.
	• O si especificamos un **límite de tiempo de simulación** en un archivo de configuración (aunque en este tutorial no lo hacemos).

### 1.5 Agregar el omnetpp.ini
  
.Para poder **ejecutar la simulación**, necesitamos crear un archivo llamado `omnetpp.ini`.

Este archivo **le dice al programa de simulación** cuál red queremos simular (*porque los archivos NED pueden contener varias redes*).

Además, en este archivo podemos:

• Enviar **parámetros al modelo**.
• Especificar **semillas** para los generadores de números aleatorios.
• Y configurar otras opciones de la simulación.

**¿Cómo crear el archivo omnetpp.ini?**

1. En el menú principal, selecciona:

**File -> New -> Initialization File (INI)**

![[Pasted image 20250314061249.png]]

2. Asigne el nombre `omnetpp.ini` a este archivo y haga click en **Siguiente**
. 
![[Pasted image 20250314061440.png]]

3. Luego seleccione la opción para crear un **archivo vacío** y haga click en **Finalizar**

![[Pasted image 20250314061524.png]]


4. Se abrirá el **Inifile Editor**, que es un editor especial para este tipo de archivos.

Este editor tiene **dos modos de trabajo**:
- **Form (Formulario):** Más adecuado para configurar opciones generales de la simulación, usando una interfaz gráfica.
- **Source (Código):** Para escribir directamente el contenido del archivo de configuración.

![[Pasted image 20250314061822.png]]


3. Por ahora, cambia al modo **Source** (Código) y escribe el siguiente contenido:

```omnet
[General]
network = Tictoc1
```

![[Pasted image 20250314062014.png]]

Puede confirmar los resultados en el modo **Formulario (Form)**

![[Pasted image 20250314062144.png]]

El ejemplo con `tictoc2`y los pasos siguientes van a compartir el mismo archivo `omnetpp.ini`

Ha finalizado con la creación del primer modelo, y ahora si esta listo para compilarlo y ejecutarlo.

## Parte 2:  Ejecución de la Simulación

### 2.1 Iniciar la simulación

Una vez completados los pasos anteriores, ya puede **ejecutar la simulación**.

Para hacerlo, simplemente selecciona el archivo `omnetpp.ini` (ya sea desde el área del editor o desde el **Project Explorer**) y haga clic en el botón **Run** (ícono de “play”) como se muestra en la imagen:

![[Pasted image 20250314064345.png|500]]

Aparecerá el siguiente cuadro de dialogo indicando la creación de un archivo de configuración, hacer click en **OK**.

![[Pasted image 20250314065448.png]]

Antes de compilar y ejecutar la simulación debemos guardar los cambios en los archivos: `tictoc.ned`, `txc1.cc`y `omnetpp.ini`, si aparece los siguientes cuadros de dialogo, haga click en  **Save**  y **Save 2 of 2** respectivamente 

  ![[Pasted image 20250314065627.png]]

![[Pasted image 20250314071713.png]]

En el siguiente cuadro de diálogo, haga click en **Save**

![[Pasted image 20250314072041.png]]


El IDE de OMNeT++ **compilará automáticamente tu proyecto** antes de iniciar la simulación.

Si hay **errores de compilación**, deberás corregirlos hasta que la compilación y el enlace (linking) se completen sin errores.

Usted puedes forzar la compilación manualmente seleccionando **Project -> Build All** en el menú, o presionando **Ctrl + B**.
 
> [!NOTA]
> 💡 **Opción avanzada:** Si prefiereE compilar desde la terminal (línea de comandos), puedes crear un **Makefile** usando el comando `opp_makemake`, y luego ejecutar `make` para compilar. Esto generará un archivo ejecutable que se puede correr con `./tictoc`.

### 2.2 Ejecutar la simulación

Después de compilar y ejecutar la simulación, se abrirá una **nueva ventana gráfica (GUI)** como la que se muestra en la siguiente imagen.

Esta ventana pertenece a *Qtenv*, que es la interfaz gráfica principal para las simulaciones en OMNeT++.

En esa ventana, podrás ver la **red** que contiene los nodos **tic** y **toc**, representada de manera gráfica.

![[Pasted image 20250314072652.png]]
Para comenzar la simulación, haz clic en el botón **Run** de la barra de herramientas.

![[Pasted image 20250314073040.png]]

Verás cómo **tic y toc empiezan a enviarse mensajes** uno al otro, como un “ping-pong”.

![[Mar-14-2025 08-51-07.gif]]

  
En la barra de herramientas de la ventana principal verás el **tiempo actual de simulación** (tiempo virtual, no real).

![[Pasted image 20250314085345.png]]

- Este tiempo **no es el tiempo real** que tarda tu computadora en ejecutar la simulación.
- Cuánto tiempo de simulación puedes avanzar en un segundo real depende de la **potencia de tu computadora** y de la **complejidad del modelo**.
  
Note que el tiempo de simulación **solo avanza debido al retardo de propagación** (*propagation delay*) de los enlaces. El procesamiento del mensaje por parte de los módulos **no consume tiempo de simulación**.

#### Controles útiles durante la simulación:

- Puede **acelerar o ralentizar** la animación con el **slider** (barra deslizante) en la parte superior de la ventana gráfica.

![[Pasted image 20250314085658.png]]

- Para **detener la simulación:** presione **F8** (o el botón **STOP** en la barra de herramientas).
- 
![[Pasted image 20250314085854.png]]

- **Paso a paso:** presiona **F4**.
- 
![[Pasted image 20250314102210.png]]

- **Ejecutar con animación:** **F5**.

![[Pasted image 20250314102256.png]]

 - **Ejecutar sin animación:** **F6**.

![[Pasted image 20250314102359.png]]

-  **Modo rápido (sin trazas):** **F7** (para máxima velocidad).

![[Pasted image 20250314102457.png]]4
  

En la barra de estado de la ventana principal podrás ver indicadores como **eventos por segundo** y **segundos de simulación por segundo real**, útiles al correr en modo rápido.

![[Pasted image 20250314102717.png]]


>[!TODO] **Ejercicio sugerido**
> - Ejecuta la simulación varias veces.
> - Prueba las funciones: **Run**, **Run Until**, **Rebuild Network**, y otras opciones disponibles en la GUI.


• Para salir del simulador, cierra la ventana o selecciona **File -> Exit**.

---

**2.3 Depuración (Debugging)**

  

Recuerda: la simulación es simplemente un **programa en C++**, por lo que puede contener errores. Por eso, aprender a **depurar (debuggear)** es muy importante.

  

**¿Cómo ejecutar la simulación en modo Debug?**

  

Haz clic en el botón **Debug** (ícono de insecto) en la barra principal del IDE.

  

Esto iniciará la simulación bajo un **depurador** (normalmente **gdb**) y el IDE cambiará a la vista **Debug Perspective**, un entorno especializado para depuración.

  

Puedes terminar la depuración con el botón **Terminate** (cuadro rojo).

---

**🔍 Errores en tiempo de ejecución (Runtime Errors)**

  

A veces es necesario depurar para encontrar errores en tiempo de ejecución.

¡Vamos a probarlo!

  

**Ejemplo de error:**

  

En el archivo txc1.cc, dentro de la función handleMessage(), **duplica la línea send(msg, "out");**, así:

```
void Txc1::handleMessage(cMessage *msg)
{
    send(msg, "out"); // enviar mensaje
    send(msg, "out"); // ESTO DEBE CAUSAR UN ERROR
}
```

Cuando corras la simulación de manera normal (con **Run**), verás un mensaje de error.

  

Ahora, **corre la simulación en modo Debug**.

Gracias a una opción activa por defecto, la simulación se detendrá automáticamente cuando ocurra el error, y podrás ver el problema en la **vista de Debug**, incluyendo:

• El **stack trace** (lista de funciones llamadas antes del error).

• El código donde ocurrió el error.

• El valor de las variables en ese momento.

  

Esto te ayudará a **entender y corregir el error**.

---

**💥 Errores de crash (fallos/segmentation fault)**

  

Para practicar esto, puedes provocar un crash de la siguiente forma:

1. Quita la línea duplicada anterior (corrige el error).

2. Ahora, **modifica la función initialize() para no crear el mensaje**:

```
cMessage *msg; // sin inicializar
send(msg, "out"); // esto causará un crash
```

Cuando corras la simulación, verás un error como **“exit code: 139”** (segmentation fault).

Si corres en modo Debug, se detendrá al fallar, y podrás ver el error para corregirlo.

---

**⛔ Breakpoints (Puntos de ruptura)**

  

Puedes poner “puntos de ruptura” en el código para detener la ejecución en lugares específicos.

Esto te permite:

• Revisar el estado de las variables.

• Ejecutar línea por línea.

• Reanudar la ejecución hasta el siguiente breakpoint.

  

**¿Cómo poner un breakpoint?**

• Haz doble clic en la parte izquierda del editor, al lado del número de línea.

• O haz clic derecho y selecciona **Toggle Breakpoint**.

---

**🏋️‍♂️ Ejercicio:**

• Coloca un breakpoint al inicio de la función handleMessage().

• Corre la simulación y observa cómo se detiene en ese punto.

• Usa las opciones del depurador para avanzar, pausar, o continuar.

---

**2.4 El diálogo de Run/Debug**

  

Cada vez que corres o debuggeas, OMNeT++ crea una **configuración de lanzamiento** (Launch Configuration).

Estas configuraciones pueden verse y editarse en **Run/Debug Configurations** (clic en la flechita junto al botón Run/Debug -> “Run Configurations…”).

  

Allí puedes ajustar parámetros y opciones para futuras ejecuciones.

---

**2.5 Visualización con Sequence Chart (Gráfica de Secuencia)**

  

OMNeT++ puede guardar un registro (event log) de todos los mensajes intercambiados durante la simulación.

Para activar este registro:

• Marca la opción **Record eventlog** en la configuración de lanzamiento.

• O agrega esta línea al omnetpp.ini:

```
record-eventlog = true
```

También puedes activar el registro desde la GUI de Qtenv.

  

⚠️ **Nota:** Los archivos de log pueden volverse muy grandes, así que solo actívalo si es necesario.

  

📊 **¿Cómo verlo?**

• Abre el archivo .elog desde el directorio de resultados del proyecto.

• Se abrirá la herramienta **Sequence Chart**, que permite ver cómo se enviaron los mensajes.

  

Este gráfico es muy útil para **entender, depurar y documentar** modelos complejos.

---

Si quieres, puedo armar un resumen o tabla final de atajos y funciones, o continuar con ejemplos de omnetpp.ini y NED. ¿Cómo quieres seguir? 🚀💻

## Fuente
[Tic Toc Tutorial](https://docs.omnetpp.org/tutorials/tictoc/part1/)

