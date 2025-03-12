---
created: 2025-02-20T04:01:16
modified: 2025-02-27T21:33:08-06:00
aliases:
  - Introducción a Sistemas de Colas
title: "Unidad 3: Introducción a Sistemas de Colas"
---
# Unidad III: Introducción al Sistema de Colas
## El proceso de colas básico

La simulación es utilizada frecuentemente para el análisis de modelos de colas.

En un simple pero común modelo de colas como el de la figura, los clientes llegan cada cierto tiempo y se unen a una *cola* (linea de espera), eventualmente son servidos, y finalmente se van del sistema.

![[Pasted image 20250220041248.png]]

El termino cliente puede referirse a cualquier tipo de entidad que pueda ser vista como solicitante de un servicio, por lo tanto muchas instalaciones de servicios, sistemas de producción, instalaciones de reparación y mantenimiento, sistemas de comunicaciones e informáticos y sistemas de transporte y manipulación de materiales pueden considerarse sistemas de colas.

Las medidas típicas del rendimiento del sistema incluyen la utilización del servidor (porcentaje del tiempo que el servidor esta ocupado) la longitud de la linea de espera y el retraso de los clientes.

La teoría de colas y el análisis de simulación se utilizan para predecir estas medidas de rendimiento del sistema en función de los parámetros de entrada. Los parámetros de entrada incluyen la tasa de llegada de clientes, las demandas de servicio de los clientes, la tasa a la que trabaja un servidor y el número y disposición de los servidores. 

## Características de un sistema de colas

- Los elementos claves de un sistema de colas son los clientes y los servidores
- El termino **cliente** puede referirse a personas, maquinas, camiones, pacientes, pallets, aviones, correo electrónico, casos, ordenes o ropa sucia: cualquier entidad que llegue a una instalación y requiera un servicio.
- El término **servidor** puede referirse a recepcionistas, personal de reparación, mecánicos, personal médico, máquinas automáticas de almacenamiento y recuperación (por ejemplo, grúas), pistas de aterrizaje de un aeropuerto, empaquetadoras automáticas, preparadoras de pedidos, CPU de un ordenador o lavadoras: cualquier recurso (persona, máquina, etc.) que preste el servicio solicitado. 
- A veces el **servidor** es quien se mueve al cliente, sin embargo esto no invalida el modelo, por ejemplo un personal de reparación que se mueve a una maquina averiada.
- Un **sistema de autoservicio**, también puede considerarse un sistema de colas.

## Estructura básica de un modelo de colas:

### Fuente de entrada: 

Llamada también "población de llamadas - *calling population*", es la población potencial de clientes que generan solicitudes en un sistema de colas. Puede ser finita o infinita. 

Por ejemplo, en una pequeña empresa, las computadoras de los empleados representan una población de llamadas **finita**, ya que solo un número limitado de ellas puede requerir servicio del equipo de TI.

En sistemas con una gran cantidad de clientes potenciales, como un banco o restaurante, se asume que la población de llamadas es **infinita**. Aunque en realidad la cantidad de clientes es finita, cuando es lo suficientemente grande, este modelo simplifica el análisis sin afectar la precisión.

La principal diferencia radica en la forma en que se define la **tasa de llegada**:
- En un **modelo de población infinita**, la tasa de llegada es constante y no se ve afectada por el número de clientes en el sistema.
- En un **modelo de población finita**, la tasa de llegada depende de cuántos clientes están en servicio o esperando.

Por ejemplo, si cinco pacientes dependen de una sola enfermera, la tasa de llegada es máxima cuando todos los pacientes están descansando, ya que cualquiera podría llamarla. Sin embargo, si todos los pacientes han solicitado atención al mismo tiempo, la tasa de llegada es **cero**, pues nadie más puede entrar en la cola hasta que la enfermera atienda a un paciente y este regrese a la población de llamadas.
### El proceso de llegadas

El proceso de llegadas para modelos de población infinita suele ser caracterizado en términos del tiempo entre llegadas de clientes consecutivos. Las llegadas pueden ocurrir de forma programada o de forma aleatoria. Cuando se producen en momentos aleatorios, los tiempos entre llegadas suelen caracterizarse por una distribución de probabilidad.

Ademas, los clientes pueden llegar  de uno en uno o por lotes. El lote puede tener un tamaño constante o aleatorio.
#### Proceso de Poisson

El modelo más importante para llegadas aleatorias es el proceso de llegadas de Poisson.

En un proceso de Poisson, el tiempo entre la llegada ($A_n$) de un cliente ($n$) con el cliente anterior ($n-1$) esta distribuido **exponencialmente** con una media de ($\frac{1}{\lambda}$) unidades de tiempo. 

La **tasa de llegada** es  $\lambda$  clientes por unidad de tiempo. El número de llegadas en un intervalo de tiempo de duración  $t$ , denotado como  $N(t)$ , sigue una **distribución de Poisson** con media  $\lambda t$  clientes.

**Ejemplo:**
Supongamos que en una central de llamadas de soporte técnico, los clientes llegan en promedio a una tasa de **5 clientes por hora** ($\lambda = 5$).

1. El **tiempo entre llegadas** (IAT = inter-arrival time) de los clientes sigue una distribución exponencial con media $60/5$ minutos = $12$ minutos.

![[Distribución Exponencial del Tiempo entre Llegadas.png]]

1. La cantidad de llamadas que llegan en **2 horas** sigue una distribución de Poisson con media  $5 \times 2 = 10$  llamadas.

![[Distribución de Poisson para la Cantidad de Llamadas en 2 Horas.png]]

Esto significa que, en promedio, en un intervalo de **2 horas**, se pueden recibir **10 llamadas**, aunque la cantidad exacta variará debido a la naturaleza aleatoria del proceso.

El proceso de llegada de Poisson a sido empleado de forma exitosa como un modelo de llegadas de personas a restaurantes, auto bancos, y otros servicios; la llegada de llamadas telefónicas a un centro de llamadas; el arribo de demandas, o ordenes de servicio o producto, la llegada de componentes o maquinas a una instalación de reparación.

Típicamente el proceso de llegadas de Poisson es utilizado para describir una población potencial grande en la cual cada cliente toma decisiones independientes acerca de cuando llegar. 

### Capacidad del Sistema

En muchos sistemas de colas, existe un **límite en la cantidad de clientes** que pueden estar en la fila de espera o dentro del sistema.

Cuando un sistema tiene **capacidad limitada**, se distingue entre la **tasa de llegada** (número total de clientes que intentan ingresar por unidad de tiempo) y la **tasa de llegada efectiva** (clientes que realmente logran entrar en el sistema).

### Comportamiento y Disciplina de la Cola

#### Comportamiento en la Cola
  
El **comportamiento en la cola** se refiere a las acciones de los clientes mientras esperan su turno para ser atendidos. Algunos comportamientos comunes incluyen:

- **Balk:** El cliente decide no entrar a la cola al ver que es demasiado larga.
- **Renege:** El cliente abandona la cola después de haber esperado un tiempo si percibe que el servicio es demasiado lento.
- **Jockey:** El cliente cambia de una fila a otra si cree que la nueva línea avanzará más rápido
#### Disciplina de la Cola

La **disciplina de la cola** determina el orden en que los clientes son atendidos cuando un servidor queda disponible. Algunos tipos comunes incluyen:

- **FIFO (First-In-First-Out):** El primer cliente en llegar es el primero en ser atendido.
- **LIFO (Last-In-First-Out):** El último cliente en llegar es el primero en recibir servicio.
- **SIRO (Service In Random Order):** El servicio se asigna de manera aleatoria.
- **SPT (Shortest Processing Time First):** Se atiende primero al cliente cuyo servicio toma menos tiempo.
- **PR (Priority Service):** Se atiende según un criterio de prioridad. 

### Tiempos de Servicio y Mecanismo de Servicio

#### Tiempos de Servicio

Los **tiempos de servicio** de los clientes que llegan sucesivamente se denotan como $S_1, S_2, S_3, ….$ Estos pueden ser **constantes** o **aleatorios**. En el caso aleatorio, los tiempos de servicio suelen modelarse como **variables aleatorias independientes e idénticamente distribuidas (iid)**.

Para modelar los tiempos de servicio, se utilizan diferentes distribuciones de probabilidad, como la **exponencial, Weibull, gamma, lognormal y normal truncada**, dependiendo del contexto. En algunos sistemas, todos los clientes de una misma categoría tienen tiempos de servicio idénticos, mientras que diferentes tipos de clientes pueden tener distribuciones de servicio completamente distintas.

Además, en ciertos sistemas, los tiempos de servicio pueden depender de **factores externos**, como la **hora del día** o la **longitud de la cola**. Por ejemplo, si la fila de espera es muy larga, los servidores pueden acelerar su trabajo para reducir el tiempo de servicio.  
#### Mecanismo de Servicio  

Un **sistema de colas** está compuesto por **centros de servicio** y las colas que los interconectan. Cada **centro de servicio** tiene un número determinado de servidores ($c$) trabajando en paralelo. Cuando un cliente llega al frente de la fila, toma el primer servidor disponible.

Los mecanismos de servicio pueden clasificarse en:

- **Servidor único (** $c = 1$ **)** → Un solo servidor atiende a los clientes uno por uno.
- **Servidores múltiples (** $1 < c < \infty$ **)** → Varios servidores atienden en paralelo.
- **Servidores ilimitados (** $c = \infty$ **)** → Característico de sistemas de autoservicio, donde siempre hay un servidor disponible.

Este modelo permite analizar la eficiencia y el desempeño de los sistemas de atención en diversas aplicaciones.

## Notación en Teoría de Colas
  
Para representar de manera estandarizada los sistemas de colas, **Kendall (1953)** propuso un sistema de notación ampliamente adoptado. Este se basa en el formato:  

$$A/B/c/N/K$$

Donde:

- **A** representa la distribución del **tiempo entre llegadas**.
- **B** representa la distribución del **tiempo de servicio**.
- **c** es el **número de servidores en paralelo**.
- **N** es la **capacidad del sistema** (máximo número de clientes permitidos en el sistema).
- **K** es el **tamaño de la población de llamadas** (número total de clientes potenciales).

**Símbolos Comunes para A y B**
- **M** → Distribución exponencial (Markoviana).
- **D** → Tiempo constante o determinístico.
- **Eₖ** → Distribución Erlang de orden  k .
- **PH** → Distribución por fases.
- **H** → Distribución hiperexponencial.
- **G** → Distribución general arbitraria.
- **GI** → Distribución general independiente.

### Ejemplos de Notación

- $M/M/1/∞/∞$ → Un sistema con **un solo servidor**, capacidad de cola **ilimitada** y una población de clientes **infinita**. Tanto los **tiempos entre llegadas como los tiempos de servicio** siguen una **distribución exponencial**. Cuando  N  y  K  son infinitos, pueden omitirse, por lo que $M/M/1/∞/∞$ se suele escribir simplemente como $M/M/1$.
- $M/M/1/5/5$ → Representa una **enfermera atendiendo a 5 pacientes**, con una capacidad máxima de 5 en el sistema.

En este sistema de notación, los sistemas de colas suelen asumir una **disciplina FIFO** (First-In-First-Out), aunque en algunos casos pueden tener otras reglas de prioridad.

## Terminología utilizada en el estudio de colas

**Estado del Sistema** $\equiv$ el número de clientes en el sistema de cola

**Longitud de la cola** $\equiv$ el número de clientes esperando a ser servidos = El Estado del Sistema menos el numero de clientes que están siendo servidos.

$s\equiv$ numero de servidores
$\lambda\equiv$ tasa promedio de llegada
$\mu\equiv$ tasa promedio de servicio
$\frac{1}{\lambda}\equiv$ tiempo esperado entre llegadas
$\frac{1}{\mu}\equiv$ tiempo esperado entre llegadas
$\rho=\frac{\lambda}{s\mu}\equiv$ factor de utilización, la fracción de tiempo que se espera que el servidor esté ocupado.

## Condición de estado estable  de un sistema de colas Markoviano

Un sistema de colas se considera **Markoviano** cuando cumple con las siguientes características y supuestos:

- La **población potencial es infinita**.
- Las **llegadas siguen un proceso de Poisson** con una tasa de  $\lambda$  llegadas por unidad de tiempo (e.g., 12 clientes por hora).
- Esto implica que el **tiempo entre llegadas sigue una distribución exponencial** con una media de  $1/\lambda$  (e.g.,  1/12  horas).
- Los **tiempos de servicio** pueden seguir una **distribución exponencial** ( M ) o una **distribución arbitraria** ( G ).
- La **disciplina de la cola** es **FIFO** (First-In, First-Out).

Un sistema de colas se dice que está en *equilibrio estadístico* o en *estado estable* si la **probabilidad de que el sistema esté en un cierto estado no depende del tiempo.** Es decir, la probabilidad de tener  $n$  clientes en el sistema **es constante a lo largo del tiempo**, independientemente del tiempo que haya transcurrido en la simulación.
## Medidas de Desempeño en Estado Estable

La principales medidas de desempeño que nos interesan en un sistema de colas Markoviano en estado estable son:

$L$ = número esperado de clientes en el sistema 
$L_q$ = número esperado de clientes en la cola
$W$ = tiempo esperado de espera en el sistema (incluyendo el tiempo de servicio)
$W_q$ = tiempo esperado de espera en la cola

### Relación entre las medidas de desempeño

$$L=\lambda W$$
$$L_q=\lambda W_q$$
$$W=W_q+\frac{1}{\mu}$$


## Modelo Básico de Cola M/M/1

En un modelo básico de cola con un solo servidor asumimos:
- Población infinita ($p=\infty$)
- Llegadas Poissonianas
- Tiempos de Servicio exponenciales
- 1 servidor ($s=1$)
- Espacio en cola infinito ($q=\infty$)

![picture 0](8479ae13630f1a3716b26eacdd3f6505d6aa6d316059818a1fe816044a670d49.png)  
### Medidas de desempeño para una cola M/M/1

$$\rho=\frac{\lambda}{\mu}$$
$$L=\frac{\rho}{1-\rho}=\frac{\lambda}{\mu-\lambda}$$
$$L_q=\frac{\lambda^2}{\mu(\mu-\lambda)}$$
$$W_q=\frac{\lambda}{\mu(\mu-\lambda)}$$
$$W=\frac{1}{\mu-\lambda}$$


## Medidas de Desempeño en Estado Estable para colas M/M/s

![[Pasted image 20250221171349.png]]

$P_n\equiv$ Probabilidad que $n$ clientes estén en el sistema
$P_0\equiv$ Probabilidad que no existan clientes en el sistema


$$\mathrm{P}_0=\frac{1}{\sum_{n=0}^{s-1} \frac{\rho^n}{n!}+\frac{\rho^S}{(s-1)!(s-\rho)}}$$

$$\mathrm{L}_q=\frac{\rho^{s+1}}{(s-1)!(s-\rho)^2} P_0$$

$$\mathrm{W}_{\mathrm{q}}=\frac{L_q}{\lambda}$$

$$L=L_q+\rho$$

$$\mathrm{W}=\mathrm{W}_{\mathrm{q}}+\frac{1}{\mu}$$

$$\text{Si}\space\mathrm{n} \leq \mathrm{s}, \mathrm{P}_{\mathrm{n}}=\frac{\rho^n}{n!} P_0$$

$$\text{Si}\space \mathrm{n}>\mathrm{s}, \mathrm{P}_{\mathrm{n}}=\frac{\rho^n}{s!s^{n-s}} P_0$$



