---
title: "Tutorial TicToc: Introducción a OMNeT++  - Parte 2: Ejecución de la Simulación"
modified: 2025-03-22T07:45:42-06:00
aliases:
  - "Tutorial TicToc: Introducción a OMNeT++  - Parte 2: Ejecución de la Simulación"
---
## 2.1 Lanzar el programa de simulación

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

## 2.2 Ejecutar la simulación

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

### 2.2.1 Controles útiles durante la simulación:

- Puede **acelerar o ralentizar** la animación con el **slider** (barra deslizante) en la parte superior de la ventana gráfica.

![[Pasted image 20250314085658.png]]

- Para **detener la simulación:** presione **F8** (o el botón **STOP** en la barra de herramientas).

![[Pasted image 20250314085854.png]]

- **Paso a paso:** presiona **F4**.

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

Para salir del simulador, cierra la ventana o selecciona **File -> Exit**.

## 2.3 Visualización con Sequence Chart (Gráfica de Secuencia)

OMNeT++ puede guardar un registro (*event log*) de todos los mensajes intercambiados durante la simulación.

### 2.3.1 Activación del Log de Eventos

Para activar este registro:

Marca la opción **Record eventlog** en la configuración de lanzamiento.

![[Pasted image 20250314165747.png]]

![[Pasted image 20250314170020.png]]


O agrega esta línea al `omnetpp.ini`:

```ini
record-eventlog = true
```

![[Pasted image 20250314165901.png]]

También puedes activar el registro desde la GUI de **Qtenv** al inicio de la simulación

![[Pasted image 20250314170136.png]]


> [!NOTA] 
> Los archivos de log pueden volverse muy grandes, así que solo actívalo si es necesario.
  
### 2.3.2  Visualización del log de eventos

Abre el archivo .elog desde el directorio de resultados del proyecto.

![[Pasted image 20250314170436.png]]

• Se abrirá la herramienta **Sequence Chart**, que permite ver cómo se enviaron los mensajes.

  ![[Pasted image 20250314170517.png]]

Este gráfico es muy útil para **entender, depurar y documentar** modelos complejos.

Continúe con  [[Parte 3 - Tutorial - Introducción a OMNeT++|Tutorial TicToc: Introducción a OMNeT++  - Parte 3: Mejorando el TicToc de 2 nodos]]

---
**Fuente**:  [Tic Toc Tutorial](https://docs.omnetpp.org/tutorials/tictoc/part1/)


