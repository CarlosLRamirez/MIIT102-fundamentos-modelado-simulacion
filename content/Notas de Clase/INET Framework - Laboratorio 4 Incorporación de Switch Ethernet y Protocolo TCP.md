---
modified: 2025-03-29T07:19:03-06:00
draft: false
title: "INET Framework - Laboratorio 4: Incorporación de Switch Ethernet y Protocolo TCP"
aliases:
  - "INET Framework - Laboratorio 4: Incorporación de Switch Ethernet y Protocolo TCP"
---
## Tabla de Contenidos

- [Introducción](#introducción)
- [Objetivos](#objetivos)
- [1. Creación del Proyecto](#1-creación-del-proyecto)
- [2. Configuración de la Red](#2-configuración-de-la-red)
- [3. Configuración del Canal Personalizado](#3-configuración-del-canal-personalizado)
- [4. Generación del Archivo .ini](#4-generación-del-archivo-ini)
- [5. Ejecución de la Simulación](#5-ejecución-de-la-simulación)
- [6. Módulos Utilizados en Este Laboratorio](#6-módulos-utilizados-en-este-laboratorio)
	- [DatarateChannel](#dataratechannel)
	- [EthernetSwitch](#ethernetswitch)
	- [TcpBasicClientApp](#tcpbasicclientapp)
	- [TcpGenericServerApp](#tcpgenericserverapp)
- [7. Preguntas y Actividades Adicionales](#7-preguntas-y-actividades-adicionales)
- [8. Implementación de Aplicación UDP](#8-implementación-de-aplicación-udp)
	- [Instrucciones](#instrucciones)
- [9. Referencias](#9-referencias)
- [10. Ejecución de Múltiples Simulaciones](#10-ejecución-de-múltiples-simulaciones)

## Introducción

En este laboratorio, los estudiantes aprenderán a incorporar un Switch Ethernet a una red existente y a implementar el protocolo TCP entre un cliente y un servidor utilizando las aplicaciones `TcpBasicClientApp` y `TcpGenericServerApp`. Al finalizar, los participantes comprenderán cómo configurar redes en OMNeT++ y cómo simular el tráfico TCP.

## Objetivos

- Incorporar un Switch Ethernet a la red existente.
- Utilizar un canal personalizado basado en `DataRateChannel`.
- Implementar el protocolo TCP entre un cliente y un servidor mediante las aplicaciones `TcpBasicClientApp` y `TcpGenericServerApp`.

## 1. Creación del Proyecto

- Crear un nuevo proyecto vacío en OMNeT++ llamado `lab2EthSwitch`.
- Establecer la referencia al proyecto `inet4.5`.

## 2. Configuración de la Red

- Crear un archivo NED vacío y nombrarlo `lab4.ned`.
- Agregar un elemento `Network`, un `ipv4NetworkConfigurator` y dos `StandardHost` en la red.
- Renombrar el `ipv4NetworkConfigurator` a `configurator` y los dos hosts a `client` y `server` respectivamente.
- Insertar un elemento `ethernetSwitch` entre los dos hosts.

![picture 12](2%20Areas/204%20Trabajo/206.01%20USAC%20Fundamentos%20de%20MyS/published/Notas%20de%20Clase/_attachments/be28ce0a41758649faf751601bf61130bd157077fbbbba4627b3eef92c0c105f.png)

## 3. Configuración del Canal Personalizado

- Agregar un canal personalizado seleccionando `Channel` y luego haciendo clic en cualquier parte del lienzo.

![picture 13](2%20Areas/204%20Trabajo/206.01%20USAC%20Fundamentos%20de%20MyS/published/Notas%20de%20Clase/_attachments/24f89dacb491e5cdb959f279db8b4522ca100c9b0dea25dc6dd6ba6be02c0528.png)

- Renombrar el canal como `GigabitEthernet`.
- Utilizar la conexión recién creada para conectar los dos hosts al Switch Ethernet.

![picture 14](02%20Areas/02.05%20Teaching/Curso-Fundamentos-de-Modelado-y-simulacion/images/5ccfa08bd8998e86a15a532221f383aa76ee12d1d0db499a599502479d841b47.png)

- Modificar el canal `GigabitEthernet` en el código del archivo NED para que esté basado en `DataRateChannel`, con los siguientes parámetros: 

```ned
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;

network TwoHostSwitch
{
    @display("bgb=422,228");

    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=223,31");
        }

        client: StandardHost {
            @display("p=93,161");
        }

        server: StandardHost {
            @display("p=307,161");
        }

        ethernetSwitch: EthernetSwitch {
            @display("p=200,104");
        }

    connections:
        client.ethg++ <--> GigabitEthernet <--> ethernetSwitch.ethg++;
        ethernetSwitch.ethg++ <--> GigabitEthernet <--> server.ethg++;
}

channel GigabitEthernet extends ned.DatarateChannel
{
    datarate = 1Gbps;
    delay = 1us;
    ber = 1e-10;
}
```

## 4. Generación del Archivo .ini

- Para este laboratorio, se utilizarán las aplicaciones `TcpBasicClientApp` en el cliente y `TcpGenericServerApp` en el servidor.
- Limitar el tiempo de simulación a 600 segundos (10 minutos).
- Crear un archivo de inicialización vacío (`omnetpp.ini`) y añadir el siguiente código:

```ini
[Config AppTCP]
network = TwoHostSwitch
sim-time-limit = 600s

*.client.numApps = 1
*.client.app[0].typename = "TcpBasicClientApp"
*.client.app[0].connectAddress = "server"
*.client.app[0].connectPort = 10021
*.client.app[0].requestLength = 100B
*.client.app[0].replyLength = 100B
*.client.app[0].numRequestsPerSession = 2
*.client.app[0].thinkTime = 1s
*.client.app[0].idleInterval = 20s

*.server.numApps = 1
*.server.app[0].typename = "TcpGenericServerApp"
*.server.app[0].localAddress = "server"
*.server.app[0].localPort = 10021
*.server.app[0].replyDelay = 1s
```

## 5. Ejecución de la Simulación

- Correr la simulación en OMNeT++. Podrás ver los mensajes de las sesiones TCP que se establecen entre el cliente y el servidor.

![picture 15](02%20Areas/24%20Teaching/Curso-Fundamentos-de-Modelado-y-simulacion/images/437edae506bee23b084348d1be6444422043af9827664addd78c17999a23f33c.png)

## 6. Módulos Utilizados en Este Laboratorio

### DatarateChannel

Las conexiones de red cableadas, por ejemplo, los cables Ethernet, se representan con conexiones OMNeT++ estándar utilizando el tipo `DatarateChannel` NED. Los parámetros `datarate` y `delay` del canal deben proporcionarse para todas las conexiones cableadas.

[Documentación de DatarateChannel](https://doc.omnetpp.org/inet/api-current/neddoc/ned.DatarateChannel.html)

### EthernetSwitch

`EthernetSwitch` modela un conmutador Ethernet. Los conmutadores Ethernet desempeñan un papel importante en las LAN Ethernet modernas.

[Documentación de EthernetSwitch](https://doc.omnetpp.org/inet/api-current/neddoc/inet.node.ethernet.EthernetSwitch.html)

### TcpBasicClientApp

Cliente para un protocolo genérico de tipo petición-respuesta sobre TCP. Puede utilizarse como modelo aproximado de usuarios HTTP o FTP.

[Documentación de TcpBasicClientApp](https://doc.omnetpp.org/inet/api-current/neddoc/inet.applications.tcpapp.TcpBasicClientApp.html)

### TcpGenericServerApp

Aplicación de servidor genérico para modelar protocolos o aplicaciones del estilo petición-respuesta basadas en TCP.

[Documentación de TcpGenericServerApp](https://doc.omnetpp.org/inet/api-current/neddoc/inet.applications.tcpapp.TcpGenericServerApp.html)

## 7. Preguntas y Actividades Adicionales

- ¿Cuál es la secuencia de mensajes para el inicio y finalización de las sesiones TCP?
- ¿Qué host inicia y termina las sesiones en esta simulación?
- ¿Cuántos segmentos TCP se envían entre el cliente y el servidor en cada sesión?
- Aumente el valor del `requestLength` a 1024 bytes. Con esta nueva configuración, ¿cuántos segmentos TCP se enviarán entre el cliente y el servidor en cada sesión? Explique su respuesta.
- Agregue un cliente y modele la generación de tráfico FTP hacia el servidor.
- Agregue un cliente y modele la generación de tráfico HTTP 1.1 hacia el servidor.
- ¿Cuál es el throughput del tráfico recibido por el cliente para cada aplicación? Sugerencia: utilice la estadística `packetReceived`.

## 8. Implementación de Aplicación UDP

### Instrucciones

- Utilizando de referencia los laboratorios anteriores y la [documentación del INET Framework](https://inet.omnetpp.org/docs/users-guide/ch-networks.html), genere una simulación de tráfico UDP entre el cliente y el servidor.
- Utilice la aplicación `UdpBasicApp` en el cliente y `UdpEchoApp` en el servidor.

## 9. Referencias

- [Guía de Usuario de INET - Networks](https://inet.omnetpp.org/docs/users-guide/ch-networks.html)
- [Guía de Usuario de INET - Applications](https://inet.omnetpp.org/docs/users-guide/ch-apps.html)
- [Guía de Usuario de INET - The Ethernet Model](https://inet.omnetpp.org/docs/users-guide/ch-ethernet.html)
- [Guía de Usuario de INET - Transport Protocols](https://inet.omnetpp.org/docs/users-guide/ch-transport.html)

## 10. Ejecución de Múltiples Simulaciones

Si deseas correr varias simulaciones con diferentes parámetros, agrega las siguientes líneas al archivo `omnetpp.ini`:

```ini
repeat = 10  # Ejecuta la simulación 10 veces
```

Esto generará resultados múltiples que puedes analizar para obtener promedios, intervalos de confianza y otras métricas estadísticas.
