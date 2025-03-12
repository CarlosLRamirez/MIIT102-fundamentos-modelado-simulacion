---
modified: 2025-02-20T03:42:52-06:00
created: '"2025-02-04 19:11", "2tc/G2T+6"'
title: "Unidad 2: Simulación de Eventos Discretos (Conceptos Básicos)"
---
## La Simulación de Eventos Discretos

La Simulación de Eventos discretos (DES) es una técnica de modelado que representa el funcionamiento de un sistema como una secuencia de eventos distintos que ocurren en momentos **específicos** del tiempo. En la DES, el estado del sistema cambia unicamente cuando ocurre un **evento**, y entre los eventos el estado permanece constante.

Este método resulta especialmente útil para analizar sistemas sistemas en donde los cambios se producen en intervalos discretos - por ejemplo, la llegada de clientes, la finalización o la ocurrencia de fallas en maquinaria -permitiendo así estudiar de forma focalizada el impacto y la sincronización de estos eventos en lugar de analizar una evolución continua del sistema.
### Ejemplos: 
- Sistema de colas en un banco
- Línea de producción en una fábrica

### Eventos discretos vs Variables de estado discretas

Es importante diferenciar entre un **sistema que tiene eventos discretos en la realidad** y un **modelo que lo representamos con eventos discretos**, independientemente de si sus variables de estado son continuas o discretas.

Por ejemplo, en un banco, los clientes llegan en momentos específicos y son atendidos en intervalos de tiempo bien definidos. No existe el concepto de “medio cliente” o “0.75 clientes” en un instante dado. Esto hace que el sistema **naturalmente tenga eventos discretos**, pues su evolución ocurre en puntos específicos en el tiempo.

Sin embargo, un sistema no necesita ser inherentemente discreto para que lo modelemos con un **enfoque de simulación de eventos discretos (DES)**. Un ejemplo es el **nivel de agua en un embalse**, que en la realidad **cambia de forma continua** conforme entra y sale agua. Aun así, podríamos modelarlo con **eventos discretos**, registrando cambios en el nivel solo cuando ocurren eventos específicos, como lluvias, aperturas de compuertas o consumo de agua.
## Conceptos en la Simulación de Eventos Discretos (DES)

**Sistema**: Una colección de entidades (e.g. personas y maquinaria) que interactúan entre si a lo largo del tiempo para alcanzar uno más objetivos

**Modelo**: Una representación abstracta del sistema, que contiene relaciones estructurales, lógicas o matemáticas que describen el sistema en términos de su estado, entidades y atributos, conjuntos, procesos, eventos, actividades y retardos.

**Estado del Sistema:** Una colección de **variables** que contienen toda la información necesaria para describir el sistema en cualquier momento.

**Entidad**: Cualquier objeto o componente en el sistema que requiere una representación explícita en el modelo (e.g., un servidor, un cliente, una máquina).

**Atributo**: Las propiedades de una entidad dada (e.g., la prioridad de un cliente en espera, la velocidad actual de un vehículo).

**Lista**: Una colección de entidades, ya sean permanentes o temporales, que se asocian y organizan siguiendo un orden lógico. Esto significa que, más allá de simplemente agrupar elementos, la lista impone una secuencia basada en algún criterio.

**Cola**: Una cola es un tipo específico de lista en donde el orden sigue reglas particulares, generalmente basadas en el orden de llegada (**FIFO**) o algún otro criterio, como prioridad.

**Evento**: Algo que ocurre de forma instantánea y que podría cambiar el estado del sistema (por ejemplo, la llegada de un cliente).

Los eventos son el elemento clave en la simulación de eventos discretos (**DES**). En una simulación, **no se registra ni se computa** lo que sucede entre un evento y otro.

Un evento también puede usarse para programar la finalización de la simulación en un tiempo particular o para tomar una decisión sobre la operación del sistema en un instante dado. En este caso, el evento no necesariamente cambia el estado del sistema.

**Aviso de Evento (Event Notice):** Un **aviso de evento** es el descriptor o registro de un evento que ocurrirá en el momento actual o en algún momento futuro. Incluye cualquier dato asociado necesario para ejecutar el evento, así como otras instrucciones relevantes para la simulación.

Como mínimo, el aviso de evento contiene el **tipo de evento** y el **tiempo del evento**. Se puede decir que es la representación estructurada que permite al simulador saber **cuándo** y **cómo** debe procesar el evento.

**Ejemplo de Aviso de Evento: Llegada de un Cliente**
- Tiempo del evento: 3.25 minutos
- Tipo de Evento: Llegada
- Descripción: un nuevo cliente (ID 101) llega al banco
- Impacto en el estado del sistema:
	- La longitud de la cola se incremente en 1
	- Si un cajero esta disponible, el cliente comenzará a ser servido inmediatamente, de lo contrario esperará en la cola
- Proximas acciones:
	- Programar un evento de **“Inicio de servicio”** si hay un cajero disponible.
	- Actualizar el calendario de eventos con el siguiente evento de llegada o finalización de servicio, según corresponda.

**Lista de Eventos:** Una lista de **avisos de eventos** para futuros eventos, ordenados según el tiempo de ocurrencia. También se conoce como **Lista de Eventos Futuros (FEL, Future Event List).**

**Actividad:** Una duración de tiempo de **longitud específica** (por ejemplo, un tiempo de servicio o un tiempo entre llegadas), que se conoce desde el momento en que inicia (aunque puede definirse en términos de una distribución estadística).

**Retardo (Delay):** Un período de tiempo durante el cual ocurre un proceso o actividad particular, y en el que el estado del sistema **permanece en espera** hasta que el proceso se complete.

El retardo se modela como el tiempo transcurrido entre el inicio de un proceso (o evento) y su finalización.

**Reloj**: Una variable representando el tiempo simulado, generalmente llamada CLOCK.

### Diferencia entre una Actividad y un Retardo

Una **actividad** generalmente representa un tiempo de servicio, un tiempo entre llegadas o cualquier otro tiempo de procesamiento cuya duración ha sido definida dentro del modelo.

Una actividad puede ser especificada de varias formas:
• **Determinista**: Su duración es fija. Ejemplo: siempre dura exactamente **5 minutos**.
• **Estadística**: Su duración se define a partir de una distribución de probabilidad. Ejemplo: un sorteo aleatorio del conjunto {2,5,7} con probabilidades iguales.
• **Funcional**: La duración depende de otras variables del sistema o atributos de la entidad.

Ejemplo: el tiempo de carga de un buque de mineral de hierro puede depender del **peso de carga permitido** y de la **tasa de carga en toneladas por hora**.

A diferencia de una **actividad**, la duración de un **retardo** no la especifica el modelador de antemano, sino que es determinada dinámicamente por las condiciones del sistema.

Frecuentemente, los retardos son valores medidos y constituyen **resultados de la simulación**.

## Algoritmo de Programación de Eventos / Avance de Tiempo

El **Algoritmo de Programación de Eventos/Avance del Tiempo** es el mecanismo central en la **Simulación de Eventos Discretos (DES, Discrete Event Simulation)** que determina cómo avanza el tiempo en la simulación. Funciona avanzando el **reloj de simulación** hasta el tiempo del próximo evento programado, actualizando el estado del sistema y programando futuros eventos según corresponda. Esto garantiza que la evolución del sistema ocurra en función de eventos discretos en lugar de incrementos de tiempo continuos.

### Lista de Eventos Futuros (FEL) en DES

El mecanismo que permite avanzar el tiempo en una simulación y garantizar que los eventos ocurran en el orden correcto se basa en la **Lista de Eventos Futuros (FEL, Future Event List)**. Esta lista contiene todos los eventos que están programados para ocurrir en el futuro.

Cuando se programa un evento futuro, significa que, en el momento en que comienza una actividad, se calcula o se genera su duración a partir de una **distribución estadística**. Luego, el evento que marca el final de esa actividad, junto con el tiempo en el que ocurrirá, se añade a la **Lista de Eventos Futuros**.

En el mundo real, la mayoría de los eventos no están programados, sino que simplemente ocurren de forma aleatoria, como **fallas inesperadas en una máquina** o **la llegada de clientes a una tienda**. En un modelo de simulación, estos eventos aleatorios se representan a través del final de una actividad, cuya duración se determina con una **distribución estadística**.

### Funcionamiento de la Lista de Eventos Futuros (FEL)

- En cualquier instante de tiempo $t$, la **Lista de Eventos Futuros (FEL)** contiene los eventos programados para ocurrir en el futuro, junto con sus tiempos asociados $t_1, t_2, \dots, t_n$.
- La FEL está ordenada cronológicamente según el tiempo de los eventos:
  $$t < t_1 \leq t_2 \leq t_3 \leq \dots \leq t_n$$

- El tiempo $t$ representa el valor del **RELOJ**, es decir, el tiempo actual en la simulación.
- El evento asociado al tiempo $t_1$ se denomina **evento inminente**, ya que es el siguiente evento en ocurrir.
- Una vez que se actualiza el **estado del sistema** en el tiempo $t$, el **RELOJ** avanza hasta $t_1$, se elimina el aviso del evento inminente de la FEL y se ejecuta dicho evento.
- La ejecución del evento inminente implica la creación de un **nuevo estado del sistema en el tiempo** $t_1$, el cual se basa en el estado anterior (en $t$) y en la naturaleza del evento ejecutado.
- En el instante $t_1$, es posible que se generen nuevos eventos futuros. Si esto ocurre, se programan y se insertan en la FEL en la posición correspondiente según su tiempo de ocurrencia.
- Luego de actualizar el estado del sistema en $t_1$, el **RELOJ** avanza hasta el tiempo del nuevo **evento inminente**, y dicho evento es ejecutado.
- Este proceso se repite iterativamente hasta que la simulación alcanza su condición de finalización.
- La secuencia de acciones que un simulador (o un lenguaje de simulación) debe ejecutar para **avanzar el reloj y construir un nuevo estado del sistema** se conoce como el **Algoritmo de Programación de Eventos y Avance del Tiempo**.

## Mecanismo de Avance en el Tiempo en la Simulación de Eventos Discretos

En una **Simulación de Eventos Discretos (DES)**, el tiempo **no avanza de manera continua** como en la vida real, sino que **salta de un evento a otro**. Esto significa que el simulador **no procesa cada instante del tiempo**, sino solo los momentos en los que ocurre algo relevante en el sistema, como **la llegada de un cliente o la finalización de un servicio**.

### Tipos de Avance en el Tiempo

#### 1. Avance por Incrementos Fijos

- Se avanza el tiempo en intervalos regulares (por ejemplo, cada 1 segundo, cada 5 minutos, etc.).
- Se usa en simulaciones donde los cambios en el sistema ocurren de manera continua o cuando necesitamos conocer el estado en momentos específicos.
- **Ejemplo:** Un simulador de temperatura que mide los valores cada minuto.

#### 2. Avance por Eventos (o Avance de Tiempo por Próximo Evento)

- En lugar de avanzar en intervalos fijos, el tiempo **salta directamente al momento en que ocurre el siguiente evento**.
- Esto hace que la simulación sea **más eficiente**, ya que solo se procesan los momentos en los que realmente ocurre algo.
- **Ejemplo:** En la simulación de un banco, solo se avanza el tiempo cuando llega un cliente o cuando un cajero termina de atender.

### ¿Cómo Funciona el Avance de Tiempo en DES?

1. Se identifica el siguiente evento en la **Lista de Eventos Futuros (FEL, Future Event List).**
2. El reloj de simulación avanza hasta el tiempo del próximo evento.
3. Se ejecuta el evento y se actualiza el estado del sistema.
4. Si el evento genera nuevos eventos (por ejemplo, la salida de un cliente genera la entrada de otro en servicio), estos se agregan a la FEL.
5. El proceso se repite hasta que se cumpla la condición de finalización de la simulación.

Esto permite simular sistemas de manera eficiente sin procesar cada unidad de tiempo innecesaria.

### ¿Por qué es importante el mecanismo de avance en el tiempo?

- **Optimiza el uso de recursos**: No necesitamos evaluar cada instante del tiempo, solo los momentos clave.
- **Permite modelar sistemas complejos**: Nos ayuda a representar eventos como llegadas, servicios y cambios de estado en sistemas reales.
- **Facilita el análisis del comportamiento del sistema**: Al centrarnos en eventos importantes, podemos calcular métricas como tiempos de espera, utilización de recursos y rendimiento del sistema.

## Ejemplos de Simulación sin uso de Computadora

> [!NOTE]
> Si podemos pensar como una computadora, probablemente podemos programar una para ejecutar una tarea.

A continuación, exploraremos los detalles de un modelo de simulación de eventos discretos a través de ejemplos prácticos.
### Ejemplo 1: Simulación de demanda

Supongamos que sabemos que la demanda semanal de un producto sigue la siguiente distribución de probabilidad. 

| **Demanda <br>(unidades por semana)** | **Probabilidad** |
| ------------------------------------- | ---------------- |
| 0                                     | .20              |
| 1                                     | .30              |
| 2                                     | .40              |
| 3                                     | .10              |
|                                       | Total = 1.00     |
Para **simular** la demanda semanal, podemos generar números aleatorios entre 0 y 9 y asignarlos a valores de demanda semanal de la siguiente manera:

| **Demanda <br>(unidades por semana)** | **Probabilidad** | **Digito(s) asignados** |
| ------------------------------------- | ---------------- | ----------------------- |
| 0                                     | .20              | 0,1                     |
| 1                                     | .30              | 2,3,4                   |
| 2                                     | .40              | 5,6,7,8                 |
| 3                                     | .10              | 9                       |
|                                       | Total = 1.00     |                         |
Esto significa que, si generamos un número aleatorio y obtenemos 0 o 1, la demanda semanal será 0. Si el número es 2, 3 o 4, la demanda será 1. Si es 5, 6, 7 u 8, la demanda será 2, y si es 9, la demanda será 3.

Para **correr** la simulación, generamos 10 valores aleatorios entre 0 y 9 y registramos la demanda simulada correspondiente.

https://numbergenerator.org/randomnumbergenerator#!numbers=10&low=0&high=9&unique=true&csv=&oddeven=&oddqty=0&sorted=false&addfilters=

**Ejemplo de simulación con 10 semanas**

| Semana | Dígito aleatorio <br>muestreado | Demanda<br>simulada |
| ------ | ------------------------------- | ------------------- |
| 1      | 5                               | 2                   |
| 2      | 8                               | 2                   |
| 3      | 9                               | 3                   |
| 4      | 2                               | 1                   |
| 5      | 8                               | 2                   |
| 6      | 6                               | 2                   |
| 7      | 5                               | 2                   |
| 8      | 2                               | 1                   |
| 9      | 5                               | 2                   |
| 10     | 2                               | 1                   |
|        | Suma                            | 18                  |
|        | $\bar{X}=18/10$                 | 1.8                 |
|        | $s$                             | 0.97                |
Este proceso nos permite estimar un parámetro del sistema, en este caso, la **media muestral** de la demanda semanal.

Si repetimos el experimento con otro conjunto de 10 valores aleatorios, obtendremos una **estimación diferente** de la media poblacional.

| Semana | Dígito aleatorio <br>muestreado | Demanda<br>simulada |
| ------ | ------------------------------- | ------------------- |
| 1      | 1                               | 0                   |
| 2      | 7                               | 2                   |
| 3      | 8                               | 2                   |
| 4      | 2                               | 1                   |
| 5      | 2                               | 1                   |
| 6      | 7                               | 2                   |
| 7      | 0                               | 0                   |
| 8      | 9                               | 1                   |
| 9      | 5                               | 2                   |
| 10     | 0                               | 0                   |
|        | Suma                            | 11                  |
|        | $\bar{X}=11/10$                 | 1.1                 |
|        | $s$                             | 0.88                |

En este caso ambos valores de $\bar{X}$ serán **estimadores** del verdadero promedio: $\mu$, la **media poblacional** ; la cual por tratarse de una simple distribución de probabilidad totalmente conocida sabemos que es igual que el valor esperado de X.

> [!NOTE]
> Sabemos que $\bar{x}$ es un estimador de $\mu=E(X)$

>[!QUESTION]
> ¿Cuál es el valor de  $\mu$ ?

#### Cálculo Analítico del Valor Esperado  $\mu$

Dado que conocemos la distribución de probabilidad de la demanda, podemos calcular su valor esperado:
$$\mu=E(C)=\Sigma X \cdot P(X)$$

| 0 x 0.2 = | 0           |
| --------- | ----------- |
| 1 x 0.3 = | 0.3         |
| 2 x 0.4 = | 0.8         |
| 3 x 0.1 = | 0.3         |
|           | 1.4 = $\mu$ |
Esto confirma que la **demanda promedio real** para esta distribución es **1.4 unidades por semana**.

Como se puede ver, la simulación es muy similar a lo que haríamos en un ejercicio estadísticos, con la diferencia que en lugar de obtener los datos del mundo real, utilizamos en este caso un algoritmo para simular los datos.
#### Reflexión: ¿Cuándo es útil la simulación?

En este caso particular, como ya conocemos la distribución de demanda, la mejor opción es calcular directamente su valor esperado. Sin embargo, en la mayoría de los problemas del mundo real, **no conocemos la distribución exacta** o es demasiado compleja para resolverla analíticamente.

En estos casos, la **simulación** es una herramienta clave para estimar valores y analizar el comportamiento del sistema bajo diferentes condiciones.

### Ejemplo 2: Ejemplo de una Caja Registradora

Queremos modelar el proceso de pago en una tienda pequeña. **Hay un solo cajero y una única fila de clientes.**

**Objetivos del análisis**
1. **Determinar el tiempo promedio que un cliente pasa en el sistema** (espera + servicio).
2. **Calcular el porcentaje de tiempo que el cajero permanece inactivo**.

Supongamos que:
• El **tiempo entre llegadas** de los clientes sigue una distribución **uniforme** entre **1 y 10 minutos**.
• El **tiempo de servicio** de cada cliente sigue una distribución **uniforme** entre **1 y 6 minutos**

Para simular este sistema, necesitamos generar una secuencia de eventos artificiales que sean representativos del comportamiento real. En otras palabras, requerimos una manera artificial de generar los **tiempos entre llegadas** y los **tiempos de servicio**, de acuerdo con las distribuciones establecidas.

Una manera de hacer esto es utilizar **diez fichas de póker** y **un dado**:
• Extraemos una ficha numerada del **1 al 10** para determinar el **tiempo entre llegadas**.
• Lanzamos un dado **(1 a 6)** para obtener el **tiempo de servicio** del cliente.

Repitiendo este proceso, podemos generar una secuencia de llegadas de clientes y tiempos de servicio.

Una vez que generamos estos tiempos, nuestro problema se reduce a **un ejercicio de registro y seguimiento de eventos en el sistema**.

#### Resultados de una simulación manual con 20 clientes

A continuación, se muestra un **ejemplo de simulación** con 20 clientes. (Se asume que la simulación comienza en el momento en que llega el primer cliente al sistema).


![[Pasted image 20250215045530.png]]

#### Métricas del sistema

Los resultados de esta corrida de la simulación son los siguientes:

- Tiempo promedio de los clientes en el sistema:  $\frac{68}{20}=3.4$ minutos
- Porcentaje del tiempo que el cajero esta desocupado = $\frac{55}{118}\times100\%=47\%$

Para obtener resultados estadísticamente significativos, sería necesario utilizar una muestra mucho más grande. Además, hemos pasado por alto algunos aspectos importantes en la simulación de sistemas, como las **condiciones iniciales** (por ejemplo, cuántos clientes ya están esperando cuando la tienda abre por la mañana).

Lo más importante aquí es que estamos utilizando **dos métodos para generar números aleatorios** (fichas numeradas y un dado) con el fin de **crear una experiencia simulada** del sistema. Esto nos permite analizar y comprender mejor algunas de sus características de desempeño.

#### Consideraciones

Que podemos aprender de esta simulación:
1.  Es un modelo de simulación de eventos discretos (DES), el sistema únicamente cambia cuando ocurre uno de dos posibles eventos: un cliente entra al sistema o el cajero termina el servicio (y el cliente se va).
2. Este simple ejemplo iustra tres elementos críticos que están presentes en todo modelo de Simulación de Eventos Discretos (DES):
	- **Aleatoriedad**: Modelamos la incertidumbre con distribuciones de probabilidad.
	- **Avance de tiempo**: La simulación **salta de un evento a otro** en lugar de avanzar en intervalos fijos.
	- **Estadísticas de resultados**: Calculamos métricas como **tiempo en cola, tiempo en servicio y porcentaje de inactividad del cajero**.

## ¿Por qué es necesario repetir una simulación varias veces?

- Cuando realizamos una simulación, los resultados dependen de valores aleatorios generados durante el experimento. Esto significa que cada vez que corremos la simulación, obtenemos una muestra diferente del comportamiento del sistema.
- En la vida real, cuando tomamos una decisión basada en simulaciones, no podemos basarnos en una sola ejecución porque esta podría ser atípica o no representar adecuadamente el comportamiento real del sistema.
- Para aproximarnos mejor al valor poblacional, debemos repetir la simulación muchas veces y analizar:
	- La media de las métricas obtenidas en varias simulaciones. 
	- La variabilidad entre simulaciones (desviación estándar, intervalos de confianza).

## Bibliografia

Banks, J., Carson, J. S., Nelson, B. L., & Nicol, D. M. (2010). _Discrete-event system simulation_ (5th ed.). Pearson Education.  _(Capítulo 3, páginas 90-97)_.

