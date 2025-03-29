---
created: 2025-03-22T13:54:28-06:00
modified: 2025-03-29T07:06:16-06:00
title: "INET Framework: Primeros Pasos - Guía Inicial"
aliases:
  - "INET Framework: Primeros Pasos - Guía Inicial"
---
## Contenido

- [Introducción](#introducci%C3%B3n)
- [Objetivo](#objetivo)
- [Instalación del INET Framework](#instalaci%C3%B3n-del-inet-framework)
- [Creación y configuración del proyecto](#creaci%C3%B3n-y-configuraci%C3%B3n-del-proyecto)
- [Definición de la topología de red](#definici%C3%B3n-de-la-topolog%C3%ADa-de-red)
	- [Archivo NED](#archivo-ned)
	- [Adición de la Red](#adici%C3%B3n-de-la-red)
	- [Adición de los Hosts](#adici%C3%B3n-de-los-hosts)
	- [Adición del Configurador de Red](#adici%C3%B3n-del-configurador-de-red)
	- [Conexión de Hosts](#conexi%C3%B3n-de-hosts)
	- [Resultado Final en `lab1.ned`](#resultado-final-en-lab1ned)
- [Generación del archivo `omnetpp.ini`](#generaci%C3%B3n-del-archivo-omnetppini)
- [Ejecución de la simulación](#ejecuci%C3%B3n-de-la-simulaci%C3%B3n)
- [Visualización de estadísticas](#visualizaci%C3%B3n-de-estad%C3%ADsticas)
	- [Entendiendo las Estadísticas en OMNeT++](#entendiendo-las-estad%C3%ADsticas-en-omnet)
	- [Visualización de estadísticas en OMNeT++](#visualizaci%C3%B3n-de-estad%C3%ADsticas-en-omnet)
	- [Estadísticas de tipo escalar (`numLost`)](#estad%C3%ADsticas-de-tipo-escalar-numlost)
	- [Multiples estadisticas tipo escalar (`TxPk`)](#multiples-estadisticas-tipo-escalar-txpk)
	- [Estadísticas tipo vector (`pingTxSeq`)](#estad%C3%ADsticas-tipo-vector-pingtxseq)
	- [Estadísticas tipo histograma (`rtt`)](#estad%C3%ADsticas-tipo-histograma-rtt)
- [Exportación de Datos a CSV o Excel](#exportaci%C3%B3n-de-datos-a-csv-o-excel)
- [Búsqueda de Documentación en INET Framework](#b%C3%BAsqueda-de-documentaci%C3%B3n-en-inet-framework)
- [Módulos utilizados en esta simulación](#m%C3%B3dulos-utilizados-en-esta-simulaci%C3%B3n)
	- [StandardHost](#standardhost)
	- [PingApp](#pingapp)
	- [Eth100M](#eth100m)


---
## Introducción

El [INET Framework](https://inet.omnetpp.org/) es un conjunto de simulaciones de protocolos de red para OMNeT++. Proporciona una amplia gama de componentes para modelar distintos aspectos de las redes de comunicaciones, incluyendo protocolos de Internet, redes inalámbricas y móviles, protocolos de transporte como TCP y UDP, y aplicaciones de red como HTTP y otros. Se utiliza principalmente para la investigación y educación en el campo de las redes de comunicaciones.

La última versión del INET Framework (Marzo 2025) es la 4.5.4.

---
## Objetivo

En esta guía paso a paso aprenderás a configurar y ejecutar una simulación básica utilizando la aplicación `PingApp` del INET Framework en OMNeT++. También aprenderás a visualizar, analizar y exportar estadísticas generadas por la simulación, utilizando herramientas internas de OMNeT++.

---
## Instalación del INET Framework

Hay varias maneras de instalar el INET Framework:

- Deje que el IDE OMNeT++ lo descargue e instale por usted. Esta es la forma más fácil. Sólo tiene que aceptar la opción de instalar INET en el cuadro de diálogo que aparece cuando se inicia por primera vez el IDE, o elegir Ayuda ‣ Instalar modelos de simulación en cualquier momento posterior.
- Desde el sitio web del INET Framework, (http://inet.omnetpp.org). El IDE siempre instala la última versión estable compatible con su versión de OMNeT++. Si necesita alguna otra versión, están disponibles para su descarga desde el sitio web. Las instrucciones de instalación también se proporcionan allí.
- Desde GitHub. Si tienes experiencia con *git*, clone el proyecto INET Framework `(inet-framework/inet)`, revise la revisión de tu elección, y sigua el archivo INSTALL en la raíz del proyecto.
- [Video con instrucciónes para la instalación del INET Framework 4.5 en OMNeT++ 6.0.2](https://youtu.be/8l07dHbfu28?si=rH5P0SB8ZIIJgC0v)  

---
## Creación y configuración del proyecto

- Inicia OMNeT++ y crea un nuevo proyecto de OMNeT++ vacío nombrándolo `lab1Ping`.
- El proyecto debe estar en el mismo espacio de trabajo donde se encuentra el `inet4.5


![picture 6](content/Notas%20de%20Clase/attachments/fd692b26c943f41da45ad107c05dd555238492ad056c09a75faa769c0867bd1b.png)

- Haz clic derecho sobre el proyecto `lab1Ping` en el explorador de proyectos y selecciona *Properties*.

![](content/Notas%20de%20Clase/attachments/2024-03-12-22-46-11.png)

- En la sección *Project References*, marca la casilla correspondiente a `inet4.5`. Luego, selecciona *Apply and Close* para cerrar la ventana.  

![](content/Notas%20de%20Clase/attachments/2024-03-12-22-47-24.png)

---
## Definición de la topología de red

### Archivo NED

- Crea un archivo NED vacío dentro del proyecto y nómbralo `lab1.ned`.

![[Pasted image 20250326175611.png|600]]

---
### Adición de la Red

- Abre la pestaña *Design* en el editor del archivo NED `lab1.ned`.
- Agrega un elemento `Network` al lienzo.
- Renombra la red con este nombre por `Red2hosts`

![[Pasted image 20250328073059.png|400]]

---
### Adición de los Hosts

- Añade dos hosts al diseño de la red, utilizando el módulo `StandardHost`.

![](content/Notas%20de%20Clase/attachments/2024-03-12-23-05-44.png)

---
### Adición del Configurador de Red  

- Inserta un elemento `ipv4NetworkConfigurator` en la red.

![](content/Notas%20de%20Clase/attachments/2024-03-12-23-08-43.png)

- Renombra este módulo a `configurator` para simplificar su identificación.


![[Pasted image 20250328073305.png|400]]

---
### Conexión de Hosts

- Utilizando la herramienta `Connection`, selecciona `Eth100M`.  

![Eth100M](content/Notas%20de%20Clase/attachments/Eth100M.jpg)

- Conecta los dos host haciendo click en el primero y luego en el segundo, seleccionando la interfaz `ethg[0]`. 

![picture 9](content/Notas%20de%20Clase/attachments/d3ca65c835e79adf40e4071d434cdb0609de43ae535f8c82be974bedacb1c505.png)

- Renombra el nombre de los host por `HostA`y `HostB`respectivamente

![[Pasted image 20250326180409.png]]

---
###  Resultado Final en `lab1.ned`

- En la pestaña de *Source* del editor del archivo NED, modifica la sección de `connections` para que en lugar de aparecer como `ethg[0]`, este como `ethg++`. Esta modificación permite que OMNeT++ asigne automáticamente el número de interfaz cuando se establecen múltiples conexiones.

- Asegúrate de que tu archivo `lab1.ned` tenga el siguiente aspecto después de seguir los pasos anteriores:

```ned
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.StandardHost;

//
// TODO documentation
//
network Red2hosts
{
    @display("bgb=308,175");
    submodules:
        HostA: StandardHost {
            @display("p=51.9,117.2");
        }
        HostB: StandardHost {
            @display("p=236,105");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=258,27");
        }
    connections:
        HostA.ethg++ <--> Eth100M <--> HostB.ethg++;
}
```

---
## Generación del archivo `omnetpp.ini`

En este paso, aprenderás a configurar la aplicación `PingApp` para que se ejecute dentro de la simulación. Además, definirás parámetros como la frecuencia de envío de los mensajes `Ping` y cómo definir la duración total de la simulación.  

Vamos a simular el envío de mensajes tipo `Ping` desde `HostA` hacia `HostB`, iniciando `1s` después de que comience la simulación. Los mensajes se enviarán a intervalos distribuidos uniformemente entre `1s` y `3s`. También estableceremos un límite de tiempo de simulación de `3600s` (1 hora).  

- Crea un archivo de inicialización vacio (`omnetpp.ini`) y pega el siguiente código:

```ini
[PingSimple]
network = Red2hosts
sim-time-limit = 3600s

#Aplicación Ping
*.HostA.numApps = 1
*.HostA.app[0].typename="PingApp"
*.HostA.app[0].destAddr = "HostB"
*.HostA.app[0].startTime = 1s
*.HostA.app[0].sendInterval = uniform(1s,3s)
*.HostA.app[0].printPing = true


```

---
## Ejecución de la simulación

- Inicia la simulación en OMNeT++ y podrás ver los mensajes de `ICMPv4 ECHO-REQ` e `ICMPv4 ECHO-REPLY` entre los dos hosts.  

![[Mar-26-2025 18-31-33.gif]]

---
## Visualización de estadísticas
### Entendiendo las Estadísticas en OMNeT++

OMNeT++ genera tres tipos principales de estadísticas:

- **Escalares:** Son valores únicos que se registran al finalizar la simulación. Ejemplo: `numLost`.
- **Vectores:** Son series temporales que registran valores a lo largo de la simulación. Ejemplo: `pingTxSeq`.
- **Histogramas:** Representan distribuciones de valores a lo largo del tiempo. Ejemplo: `rtt`.

La comprensión de cada tipo de estadística es fundamental para analizar el desempeño de una simulación y compararla con escenarios alternativos.

---
### Visualización de estadísticas en OMNeT++

Después de correr la simulación, sigue estos pasos:

1. **Detener la simulación:**
   - Cuando la simulación se complete (o si deseas detenerla antes), haz clic en el botón de `Stop`.

1. **Abrir el `Run Analysis Tool`:**
   - En la ventana principal de OMNeT++, en el explorador del proyecto busca dentro de la carpeta `results`los archivos `.sca`y `.vec`con las estadísticas generadas por la simulación.
   
	![[Pasted image 20250326185333.png|250]]
   
   - Haz doble clic en cualquiera de estos archivos para abrir el `Analysis Tool`, paso previo debes confirmar el nombre de un archivo `.anf`el cual sirve para agrupar todas las Estadísticas que deseas analizar.
   
	![[Pasted image 20250326185304.png|400]]

- Esto abrira una ventana con tres pestañas:
	- La primera `Inputs`contiene los archivos de s (`.sca`y `.vec`) que se incluyen en este analisis
	- La segunda `Browse Data`es donde podemos explorar todas las s incluidas en el analisis (escalares, vectores e histogramas)
	- La tercera: `Charts`es donde podemos ir agrupando todas las gráficas que vayamos generando en el analisis.
	
		![[Pasted image 20250326185546.png]]


> [!TIP]
> Guarda tu archivo `.anf` frecuentemente para evitar perder tus configuraciones de análisis.

---
### Estadísticas de tipo escalar (`numLost`)

1. En la pestaña `Browse Data`,  selecciona la pestaña `Scalars`.
2. Navega por la estructura del árbol hasta encontrar el `app[0]` bajo `HostA`.
	- Puedes tambien utilizar el filtro del módulo  `Red2hosts.HostA.app[0]` según se muestra en la figura. Esto muestra todas las s tipo Escalar que la aplicación `PingApp`(en este caso `app[0]`) del `HostA` ha generado .

![[Pasted image 20250326190011.png]]

> [!NOTE]
> Por defecto OMNeT++ genera todas las  definidas por el modulo al momento de la simulación

3. Busca la  `numLost` y anota el valor que aparece en la parte derecha.
4. Observa que dice `numLost:last`, lo que significa que ese valor lo que representa el conteo final de pings **perdidos** al final de la simulación. En ese caso por ser una red muy simple y en condiciones ideales, es posible que este valor sea `0` o `nan`.

---
### Multiples estadisticas tipo escalar (`TxPk`)

1. Ahora busca la estadística llamada `TxPk:count`, esto representa el numero total de paquetes transmitidos hacia la capa física. A diferencia de la estadística anterior, esta es generada por el módulo  [EthernetMac](https://doc.omnetpp.org/inet/api-current/neddoc/inet.linklayer.ethernet.basic.EthernetMac.html)el cual este embebido dentro el módulo `StandardHost`utilizado en la simulación.
2. Selecciona el contador para ambos nodos (`HostA`y `HostB`), con ambos seleccionados haz click derecho y selecciona crear *Plot using Bar Chart*. 
	![[Pasted image 20250327051320.png|600]]
	
	![[Pasted image 20250327051608.png|600]]

3. Se genera dos gráficas tipo barra independientes para cada nodo, en este caso los valores son iguales, sin embargo esto te puede servir cuando quieras comparar diferentes estadísticas escalares, según la naturaleza de la simulación.

	![[Pasted image 20250327052525.png]]


4. Ahora prueba seleccionar todos las estadísticas que inician con`TxPk:*`y genera un nuevo gráfico de barras seleccionando las dos estadísticas de cada nodo.

	![[Pasted image 20250327052807.png]]   
5. El resultado es un gráfico de barras agrupadas donde cada barra representa una estadística y las barras estan agrupadas por módulo, en este caso por el nodo `HostA`y `HostB`
	 ![[Pasted image 20250327054928.png]]

6. Puedes guardar esta gráfica para su consulta posterior, esta quedará guardada en el archivo de análisis (`.anf`). 

	![[Pasted image 20250327055201.png]]


---
### Estadísticas tipo vector (`pingTxSeq`)

Ahora vamos a ver como visualizar estadísticas tipo vector, es decir arreglos bidimencionales donde uno representa el valor de registro y el otro el punto en el tiempo. Este tipo de estadísticas nos sirven para conocer como se comportó cierta estadística a lo largo del tiempo de simulación

Para este ejemplo vamos a utilizar la estadística `pingTxSeq:vector` del modulo tipo aplicación `PingApp`, la cual representa el numero de secuencia de los mensajes de ping transmitidos en el tiempo.

1. Cambia a la pestaña `Vectors` en la herramienta de análisis.
2. Busca `PingApp` (`app[0]`)  bajo `HostA` y selecciona el vector llamado `pingTxSeq`.

	![[Pasted image 20250327060201.png]]

3. Haciendo click derecho sobre la estadística y seleccionando *Show Output Vector View* puedes visualizar la serie temporal completa generada por `pingTxSeq`.

	![[Pasted image 20250327060316.png]]

4. También podrías exportar la serie temporal completa a un archivo de salida como CSV

	![[Pasted image 20250327060706.png]]

5. Podrias generar un gráfico de linea de la serie temporal, con click derecho y *Plot using Line Chart*
 
	![[Pasted image 20250327060822.png]]

6. Tambien puede crear graficos de varios vectores en la misma gráfica, ya sea en los mismos ejes o ejes separados:

	![[Pasted image 20250327062015.png]]

5. Para exportar los datos, haz clic derecho y selecciona `Export as CSV`.

---

> [!NOTE] Diferencias entre Plot using Line Chart vs Plot using Line Chart with Matplotlib
> - **Plot using Line Chart:**  
>   - Esta opción genera un gráfico de líneas básico utilizando el generador de gráficos interno de OMNeT++.  Es ideal para visualizaciones rápidas y sencillas de vectores o datos escalarizados. Es más liviano y rápido pero limitado en personalización avanzada de gráficos. No requiere que `Matplotlib` esté instalado.
> 
> - **Plot using Line Chart with Matplotlib:**  
>   - Genera gráficos de líneas utilizando la biblioteca `Matplotlib`, la cual es estándar en Python para visualización avanzada. Permite personalización detallada y estética más elaborada de gráficos. Requiere tener instalado `Matplotlib`.  
>  

---
### Estadísticas tipo histograma (`rtt`)

Tambien podemos visualizar las estadísticas tipo histograma, para este ejemplo utilizaremos la Estadística `rtt`, que represente el *round-trip time* , es decir el tiempo que tardaron los mensajes de ping en ir y regresar a lo largo del tiempo,

1. Cambia a la pestaña `Histograms`.
2. Busca `PingApp` bajo `HostA` y selecciona la estadística llamada `rtt`.
3. Este histograma muestra la distribución de los tiempos de ida y vuelta (`Round Trip Time`) para cada mensaje `Ping`.
4. También puedes exportar el histograma en formato CSV si lo deseas.

![[Pasted image 20250327062410.png]]

---
## Exportación de Datos a CSV o Excel

Para exportar estadísticas a archivos externos (CSV o Excel), sigue los siguientes pasos:

   - En la pestaña `Browse Data` dentro del `Analysis Tool`, selecciona la pestaña correspondiente al tipo de estadistica que desas exportar, ya sea `Scalars`, `Vectors`o `Histograms`.
   - Selecciona los elementos que deseas exportar (puedes seleccionar múltiples elementos manteniendo presionada la tecla `Ctrl` o `Shift`).
   - Haz clic derecho y selecciona `Export Data` , y luego `CSV for Spreadsheets`
   - OMNeT++ generará un archivo `CSV` con los datos exportados para poder ser procesados fuera de OMNeT++
   
	   ![[Pasted image 20250328165027.png]]


> [!TIP]
> Los archivos CSV generados pueden ser abiertos en Excel, Google Sheets o cualquier herramienta que soporte la importación de archivos de texto delimitados.

---

##  Búsqueda de Documentación en INET Framework

Con el INET Framework es importante poder investigar la documentación sobre los módulos y aplicaciones disponibles.

 INET Framework posee documentación oficial que puedes consultar en: [INET Framework Documentation](https://inet.omnetpp.org/) Aquí puedes buscar módulos específicos y leer la documentación relacionada con cada uno.

Otra fuente importante para buscar documentación sobre los modulos es el [INET Reference](https://doc.omnetpp.org/inet/api-current/neddoc/index.html) donde se pued encontrar información específica de cada módulo.

---
## Módulos utilizados en esta simulación

### StandardHost

StandardHost contiene los protocolos de Internet más comunes: UDP, TCP, IPv4, IPv6, Ethernet, IEEE 802.11. También soporta un modelo de movilidad opcional, modelos de energía opcionales, y cualquier número de aplicaciones que son totalmente configurables desde archivos INI.

- [StandardHost](https://doc.omnetpp.org/inet/api-current/neddoc/inet.node.inet.StandardHost.html)  

---
### PingApp

La aplicación PingApp genera solicitudes de ping y calcula la pérdida de paquetes y los parámetros de ida y vuelta de las respuestas.

El tiempo de inicio/parada, intervalo entre envíos etc. pueden ser especificados a través de parámetros. Una dirección puede ser dada en notación decimal punteada (o, para IPv6, en la notación usual con dos puntos), o con el nombre del módulo. (La clase `L3AddressResolver` se utiliza para resolver la dirección.) Para desactivar el envío, especifique `destAddr` vacío.

Cada solicitud de ping se envía con un número de secuencia, y se espera que las respuestas lleguen en el mismo orden. Siempre que haya un salto en el número de secuencia de las respuestas de ping recibidas (por ejemplo, 1, 2, 3, 5), entonces el ping que falta (el número 4 en este ejemplo) se cuenta como perdido. Entonces, si todavía llega más tarde (es decir, una respuesta con un número de secuencia menor que el mayor recibido hasta el momento) se contará como llegada fuera de secuencia, y al mismo tiempo se decrementa el número de pérdidas. (Se supone que el paquete llegado se contó antes como pérdida, lo que es cierto si no hay paquetes duplicados).

- [PingApp](https://doc.omnetpp.org/inet/api-current/neddoc/inet.applications.pingapp.PingApp.html)

---
### Eth100M
  
Conexión que representa un enlace Ethernet de 100Mb/s, en los enlaces tipo Ethernet es posible específicar el retardo de propagación mediante la longitud del cable.

- [Eth100M](https://doc.omnetpp.org/inet/api-current/neddoc/inet.node.ethernet.Eth100M.html)

---
## Referencias

- [Guía de Usuario de INET - Networks](https://inet.omnetpp.org/docs/users-guide/ch-networks.html)
- [Guía de Usuario de INET - Applications](https://inet.omnetpp.org/docs/users-guide/ch-apps.html)
- [Guía de Usuario de INET - The Ethernet Model](https://inet.omnetpp.org/docs/users-guide/ch-ethernet.html)
- [Guía de Usuario de INET - Transport Protocols](https://inet.omnetpp.org/docs/users-guide/ch-transport.html)


---

Ahora que te has familiarizado con la ejecución de simulaciones con el INET Framework y la visualización de estadísticas, intenta realizar este [[INET Framework - Laboratorio 1  Modificación de Parámetros en PingApp]]

