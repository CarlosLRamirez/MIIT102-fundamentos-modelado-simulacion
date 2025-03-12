---
modified: 2025-02-08T11:01:24-06:00
created: '"2025-02-01 05:57", "6tc/G2T+6"'
title: "Unidad 1: Introducción al modelado y simulación"
---
## ¿Qué es Simulación?

Una **simulación** es la **imitación** del funcionamiento de un proceso o un **sistema** del mundo real a lo largo del **tiempo**.

Una simulación puede realizarse de forma totalmente manual, o puede hacerse ayudado con una computadora, y conlleva la generación de una historia artificial de un sistema la cual observamos para inferir información de las características de operación de dicho sistema.

Al simular como funciona un sistema podemos entender e inferir como funcionaria ese sistema en la vida real bajo condiciones similares.

Para estudiar el comportamiento de un sistema a travez del tiempo necesitamos un **modelo** de simulación. Un modelo es una **aproximación** al sistema real, es decir una representación simplificada y abstracta que captura las características y comportamientos clave que se desean estudiar.

### ¿Qué es el Modelado?

Uniendo ambos conceptos,  el **modelado** es la es proceso de crear una representación simplificada de un sistema real, y la **simulación** es la ejecución de ese **modelo** para analizar su comportamiento  a lo largo del tiempo. 

> [!NOTE]
El **modelado** es un paso previo y necesario para la **simulación**. Sin un **módelo**, no se puede hacer una **simulación**.

### Importancia del modelado y simulación

El modelado y simulación son herramientas esenciales para el análisis y diseño de sistemas complejos, entre ellos los sistemas de comunicaciones.

### Aspectos Clave

- Por medio de la simulación podemos investigar una gran cantidad de preguntas de "¿Qué pasa si?" acerca del sistema real.
- Podemos simular cambios potenciales en el sistema y predecir el impacto en su rendimiento. 
- Tambien podemos utilizar la simulación de un sistema en su etapa de diseño, antes de construirlo en la vida real.

## Diferencia entre la Simulación y la Solución Analítica

A veces podemos representar un sistema mediante un modelo lo suficientemente simple para que pueda estudiarse de forma analítica, es decir, una fórmula matemática o algoritmo que, si introducimos la misma entrada, siempre obtendremos la misma salida. 

Esto se llama un **modelo determinista** o solución analítica. Por otro lado, un **modelo estocástico** incorpora elementos de aleatoriedad, lo que significa que la misma entrada puede producir diferentes salidas en diferentes ejecuciones debido a la incertidumbre inherente del sistema.

Muchos sistemas de la vida real son tan complejos que modelarlos es virtualmente imposible resolverlo a analizarlo matemáticamente, es aquí donde la **simulación** numérica basada en computadora puede ser utilizada mara imitar el comportamiento del sistema.

## Cuando usar la simulación como herramienta

La simulación puede utilizarse para los siguientes propósitos:

1. La simulación es útil para analizar cómo los componentes de un sistema interactúan entre sí, lo que puede ser difícil de entender solo con observación o análisis teórico.
	- **Ejemplo**: En una fábrica, se puede simular cómo interactúan las líneas de producción, los trabajadores y las máquinas para identificar cuellos de botella o ineficiencias.
2. La simulación permite probar cómo reacciona un sistema ante cambios sin necesidad de implementarlos en la realidad.
	- **Ejemplo**: En una cadena de suministro, se puede simular cómo afectaría un aumento en la demanda o un cambio en los proveedores para prepararse ante posibles escenarios.
3. Al construir un modelo de simulación, se obtiene una comprensión profunda del sistema, lo que puede llevar a identificar áreas de mejora.
	- **Ejemplo**: Al simular el flujo de pacientes en un hospital, se pueden identificar áreas donde se necesita más personal o recursos para mejorar la eficiencia.
4. La simulación permite probar diferentes escenarios para entender qué factores tienen mayor impacto en el sistema.
	- **Ejemplo**: En un sistema de transporte público, se puede simular cómo afecta el aumento de la frecuencia de los autobuses en la satisfacción del usuario y los costos operativos.
5. La simulación ayuda a visualizar y comprender conceptos teóricos, lo que facilita el aprendizaje.
	- **Ejemplo**: En un curso de ingeniería, se puede usar un simulador de circuitos eléctricos para que los estudiantes entiendan cómo funcionan las leyes de Kirchhoff en la práctica.
6. Permite probar ideas sin riesgos ni costos asociados a la implementación real.
	- **Ejemplo**: Antes de construir un nuevo aeropuerto, se puede simular el flujo de pasajeros y aviones para optimizar el diseño de las terminales y pistas.
7. La simulación sirve para validar los resultados obtenidos mediante métodos teóricos o matemáticos.
	- **Ejemplo**: En ingeniería, se puede simular el comportamiento de un puente bajo diferentes cargas para verificar los cálculos estructurales.
8. La simulación permite probar cómo se comportaría una máquina bajo diferentes condiciones para definir sus especificaciones técnicas.
	- **Ejemplo**: En la fabricación de un vehículo autónomo, se puede simular su capacidad de procesamiento, sensores, batería y software necesarios para operar de manera segura y eficiente..
9. La simulación permite capacitar a las personas en un entorno controlado y sin riesgos.
	- **Ejemplo**: Los pilotos de avión usan simuladores de vuelo para practicar maniobras sin poner en riesgo vidas o equipos.
10. Las animaciones ayudan a entender cómo funcionará un sistema antes de construirlo o implementarlo.
	- **Ejemplo**: En la planificación urbana, se puede usar una animación para mostrar cómo se vería una nueva autopista y su impacto en el tráfico.
11. La complejidad de los sistemas modernos hace que la simulación sea esencial para entender y optimizar su funcionamiento.
	- **Ejemplo**: En una planta de fabricación de chips, se simula el flujo de materiales y procesos para maximizar la eficiencia y minimizar los defectos.

## Cuando NO es apropiada la simulación

De acuerdo con Banks and Gibson [1997], la simulación no es la herramienta más apropiada cuando:

1. Cuando el problema puede resolverse usando el sentido común.
	- **Ejemplo:** Determinar si un solo servidor puede manejar una pequeña carga de trabajo predecible. Un cálculo simple podría ser suficiente en lugar de una simulación completa.
2. Si el problema puede ser resuelto analíticamente.
	- - **Ejemplo:** Calcular el tiempo promedio de espera en una cola simple M/M/1 se puede hacer directamente usando la fórmula de Erlang-C, sin la necesidad de simulación.
3. Si es mas fácil o menos costoso realizar experimentos directos.
	- **Ejemplo:** Probar el rendimiento de una red Wi-Fi en una oficina pequeña podría ser más práctico mediante la realización de mediciones directas en lugar de simular toda la red.
4. Si los costos exceden los ahorros.
	-  **Ejemplo:** Simular un proceso de fabricación complejo con un alto nivel de detalle puede ser muy costoso. Si las posibles mejoras de la simulación son mínimas, la inversión podría no estar justificada.
5. Cuando no se dispone del tiempo o los recursos.
	- **Ejemplo:** Si un proyecto tiene una fecha límite ajustada y un presupuesto limitado, puede 00que no haya suficiente tiempo o recursos para desarrollar y validar un modelo de simulación.
6. Cuando no existe disponibilidad de los datos.
	- **Ejemplo:** Si una empresa quiere simular el impacto de una nueva política de ventas, pero no tiene datos históricos sobre el comportamiento de los clientes, la simulación no será confiable.
7. Cuando no exista el tiempo o  disponibilidad para validar y verificar el modelo.
	- **Ejemplo:** Si un equipo de desarrollo tiene que entregar un modelo de simulación en una semana, es probable que no haya tiempo para validarlo adecuadamente, lo que podría llevar a conclusiones erróneas.
8. Expectativas poco realistas, si esperan grandes resultados en poco tiempo.
	-  **Ejemplo:** Si un gerente espera que una simulación resuelva todos los problemas de producción en una semana, es mejor explicarle que la simulación requiere tiempo para ser desarrollada, validada y ejecutada.
9. Si el comportamiento del sistema es demasiado complejo o no puede ser definido
	- **Ejemplo:** Simular el comportamiento de una red social a gran escala con millones de usuarios e interacciones complejas puede ser extremadamente difícil debido a la complejidad y el comportamiento emergente del sistema.

## Ventajas y Desventajas de la Simulación

### Ventajas

De acuerdo con y Pegden, Shannon, y Sadowski [1995], algunas ventajas de la simulación son:

1. Explorar de nuevas políticas y procedimientos sin interrumpir el sistema.
	- **Ejemplo:** Un hospital puede simular un nuevo protocolo de atención al paciente para reducir tiempos de espera, sin necesidad de implementarlo primero y arriesgarse a afectar la calidad del servicio.
2. Probar nuevos diseños de hardware, distribuciones físicas, sistemas de transporte, sin invertir recursos.
	- **Ejemplo:** Un operador de red móvil puede simular el rendimiento de una nueva configuración de antenas para mejorar la cobertura, sin necesidad de instalarlas físicamente y realizar pruebas en el campo.
3. Prueba de viabilidad de hipótesis.
4. Compresión o expansión del tiempo.
	- **Ejemplo:** Un equipo de ingenieros puede simular el desgaste de un motor durante 10 años en solo unas horas, o ralentizar una reacción química para estudiar sus etapas intermedias.
	- **Ejemplo:** Se puede simular la propagación de un virus informático en una red en cuestión de minutos, o simular el crecimiento de una red de telecomunicaciones a lo largo de varios años.
5. Obtener información sobre la interacción entre las variables de un sistema.
	- **Ejemplo:** En un sistema de riego agrícola, se puede simular cómo interactúan factores como la humedad del suelo, la temperatura y la frecuencia de riego para optimizar el crecimiento de los cultivos.
6. Entender qué variables tienen mayor impacto en el desempeño de un sistema.
	 - **Ejemplo:** Simular un centro de atención telefónica para identificar si el número de agentes, el tiempo de atención promedio o la tasa de llegada de llamadas tienen un mayor impacto en el tiempo de espera de los clientes.
7. Análisis de cuellos de botella.
	- **Ejemplo:** Simular una línea de producción para identificar dónde se acumulan los productos en proceso y optimizar el flujo de trabajo.
8. Comprender cómo funciona un sistema en lugar de cómo los individuos piensan que funciona.
	- **Ejemplo:** En una aerolínea, se puede simular el flujo de pasajeros en el aeropuerto para entender realmente cómo se mueven (en lugar de basarse en suposiciones), y así optimizar los tiempos de embarque.
9. Responder a preguntas tipo “Qué Pasaría Si”.
	- **Ejemplo:** Simular el rendimiento de una red 5G con diferentes densidades de usuarios y aplicaciones para evaluar su capacidad y planificar su despliegue.

### Desventajas

1. La construcción de modelos requiere capacitación especializada.
	- **Ejemplo:** Dos ingenieros de telecomunicaciones podrían construir modelos diferentes de una red de datos, incluso si tienen los mismos datos y objetivos. Uno podría enfocarse en el rendimiento de los protocolos de enrutamiento, mientras que el otro podría enfocarse en la capacidad de los enlaces.
	- **Ejemplo:** Una simulación de la propagación de una enfermedad podría predecir un aumento de casos. Interpretar si este aumento se debe a un cambio real en la dinámica de la enfermedad o a la variabilidad del modelo requiere un análisis cuidadoso
2. Los resultados de la simulación pueden ser difíciles de interpretar.
	- **Ejemplo:** Si una simulación de una red de telecomunicaciones muestra un aumento en la latencia, puede ser difícil determinar si esto se debe a un problema en la red o simplemente a la variabilidad aleatoria en el tráfico simulado.
3. El modelado y análisis de una simulación puede consumir tiempo y ser costoso.
	- **Ejemplo:** Simular una red de telecomunicaciones a gran escala con un alto nivel de detalle puede ser muy costoso y llevar meses de trabajo. Si no se asignan suficientes recursos, el modelo podría ser demasiado simple o los resultados podrían no ser confiables.
	- **Ejemplo:** Simular la evolución de una galaxia a lo largo de millones de años requiere una enorme capacidad de procesamiento y puede llevar mucho tiempo, incluso con supercomputadoras.
4. Podríamos llegar a  sobre utilizar la simulación cuando existe una solución analítica.
	- **Ejemplo:** Algunos problemas de colas tienen soluciones analíticas que pueden proporcionar resultados más rápidos y precisos que la simulación.
	- **Ejemplo:** Determinar el punto de equilibrio en un mercado con oferta y demanda lineales puede resolverse analíticamente, sin recurrir a la simulación

## Areas de aplicación

La simulación tiene aplicaciones en una gran vasta cantidad de áreas, como por ejemplo:
1. Manufactura
2. Procesos de Negocio
3. Economía y Finanzas
4. Ingeniería Civil
5. Gestión de Proyectos
6. Logística, Transporte y Distribución
7. Seguridad ciudadana y sector militar
8. Cuidados de la Salud
9. Telecomunicaciones
10. Ciberseguridad
11. Y muchas otras mas…

[Ejemplos de casos de estudio de simulación de diversas áreas de aplicación - WSC 2024](https://informs-sim.org/wsc24papers/by_area.html)

### Ejemplos de Proyectos de Simulación
**Area**: Ingeniería Civil/Transporte
**Ejemplo**: Simulación del tráfico de una ciudad o una avenida 

**Area**: Biología
**Ejemplo:** Simulación de la propagación de una enfermedad infecciosa.

**Área:** Telecomunicaciones
**Ejemplo:** Simulación de una red de comunicaciones inalámbricas (por ejemplo, una red celular 5G).

**Área:** Ciberseguridad / Seguridad Informática
**Ejemplo:** Simulación de un ataque de denegación de servicio distribuido (DDoS) en una red corporativa.


## Sistema y Entorno del Sistema

### Definición de Sistema
Un sistema se puede definir como un **conjunto** de **elementos** que interactúan o tienen alguna  interdependencia entre sí  para lograr un **propósito común.**

### Entorno del sistema
Un sistema es comúnmente afectado por cambios que ocurren fuera del sistema mismo, a esto se le conoce como el **entorno o ambiente del sistema**

### Limite del Sistema
- Cuando modelamos un sistema es importante definir las **fronteras** del sistema, es decir la donde separar el **sistema** de su **ambiente**, esta decisión depende del propósito del estudio.
- Es posible que para un estudio en particular, cierta variable o factor lo consideremos como algo fuera del sistema, sin embargo para otro estudio con un proposito diferente, la misma variable la consideremos como parte del sistema.

## Ejemplos de Sistemas

1. **Sistema de Transporte Público**
	- **Elementos:** Autobuses, conductores, rutas, pasajeros, estaciones.
	- **Interacción:** Los autobuses siguen rutas específicas, los conductores manejan los autobuses, los pasajeros suben y bajan en las estaciones.
	- **Propósito:** Transportar personas de un lugar a otro de manera eficiente.
	- **Entorno:** Tráfico vehicular, condiciones climáticas, políticas gubernamentales.
    
2. **Sistema Digestivo**
	- **Elementos:** Estómago, intestinos, hígado, páncreas, etc.
	- **Interacción:** Cada órgano realiza una función específica en el proceso de digestión.
	- **Propósito:** Procesar los alimentos para extraer nutrientes y eliminar desechos.
	- **Entorno:** Dieta, estado de salud general, medicamentos.

3. **Sistema Nacional Interconectado (SNI)**
	- **Elementos:** Centrales generadoras, redes de transmisión, subestaciones, redes de distribución.
	- **Interacción:** Las centrales generan electricidad, las redes de transmisión la transportan, las subestaciones y redes de distribución la llevan a los usuarios finales.
	- **Propósito:** Suministrar energía eléctrica de manera confiable y eficiente.
	- **Entorno:** Demanda de energía, condiciones climáticas (que afectan la generación renovable), políticas energéticas.
    
## Componentes de Un Sistema

### Entidad
Una **entidad** se define como un objeto o componente de interés en el sistema, debido a su interés requiere una representación explícita en el modelo.  **Por ejemplo**, los clientes de un banco.

### Atributo
Un **atributo** es una propiedad de una entidad. **Por ejemplo**, el saldo de la cuenta bancaria de un cliente, o la calificación crediticia de un cliente.

### Actividad
Una **actividad** representa un periodo de **tiempo** de una duración determinada. **Por ejemplo**, hacer un deposito en la cuenta monetaria.

### Estado 
El **estado** de un sistema se define como el conjunto de variables necesarias para describir el sistema en cualquier **momento**, relativo a los objetivos del estudio. **Por ejemplo**, número de cajeros ocupados, número de clientes esperando en la cola.

En el estado del sistema de deben considerar todas las variables que entreguen información relevante, la cual dependerá de los objetivos deseados y de las medidas de salida que serán evaluadas.
### Evento
Un **evento** se define como un suceso instantáneo que puede cambiar el estado del sistema. **Por ejemplo**, la llegada de un cliente, la incorporación de un nuevo cajero o la salida de un cliente.
### Endógeno:
A las actividades o eventos  que ocurren dentro del sistema. se les llama endógenos. **Por ejemplo:** La completación del servicio de un cajero
### Exógeno
A las actividades y eventos en el entorno que afectan el sistema, se les llama exógenos. **Por ejemplo:** La llegada de un nuevo cliente.

## Sistemas Discretos y Continuos

Los sistemas se pueden categorizar en **discretos** o **continuos**.

> [!NOTE]
> En la práctica, pocos sistemas son totalmente discretos o totalmente continuos, aunque generalmente podemos clasificarlos según ell tipo de cambio que predomina.
### Sistema Discreto
Un sistema **discreto** es aquel en el que las variables de estado cambian solo en momentos específicos en el tiempo.

- **Ejemplo del banco:** El número de clientes en un banco (variable de estado) cambia solo cuando un cliente llega o cuando se completa el servicio a un cliente. Entre estos eventos, el número de clientes permanece constante.
- **Ejemplo en una Red de computadoras:** El número de paquetes en un router cambia cuando llega un nuevo paquete o cuando se envía un paquete.

### Sistema Continuo

Un sistema **continuo** es aquel en el que las variables de estado cambian continuamente a lo largo del tiempo.

- **Ejemplo del nivel de agua en una presa:** El nivel de agua detrás de una presa cambia continuamente debido a la lluvia, la evaporación, la descarga para control de inundaciones y la generación de electricidad.
- **Temperatura de una habitación:** La temperatura cambia gradualmente a lo largo del tiempo en respuesta a la calefacción, la refrigeración y las condiciones externas.

![[Pasted image 20250201093210.png]]





## Modelo de un Sistema

Muchas veces no se puede experimentar con un sistema real, como un banco o una autopista. Hay que experimentar con un **modelo** del sistema real.

Un **modelo** se define como una representación de un sistema con el fin de estudiarlo. 

Un modelo es una **aproximación** al sistema real, es decir una representación **simplificada** y abstracta que captura las características y comportamientos clave que se desean estudiar. Por otro lado, el **modelo** debe ser lo suficientemente detallado para permitir obtener conclusiones validas del sistema real que se esta estudiando.

Dicha representación puede estar dada mediante herramientas analíticas, algoritmos u otras técnicas.

Así como un sistema se compone de entidades, atributos y actividades, estos tambien se deben representar en el modelo, sin embargo el modelo únicamente contendrá aquellos componentes que son relevantes para el estudio.
## Tipos de Modelos

Los modelos pueden clasificarse en **matemáticos** o **físicos**. Un modelo matemático usa ecuaciones y notación simbólica para representar un sistema, y un **modelo de simulación** es un tipo específico de modelo matemático. Un modelo físico es una versión a escala (más grande o más pequeña) de un objeto, como un átomo ampliado o un sistema solar en miniatura.

Los modelos de simulación se clasifican además en:
1. **Estáticos o dinámicos:**  
2. **Deterministas o estocástico:**  

Un modelo **estático** (a veces llamado simulación de Monte Carlo) representa un sistema en un momento específico.  

Un modelo **dinámico** muestra cómo cambia un sistema con el tiempo, como simular un banco de 9:00 a.m. a 4:00 p.m.

Un modelo **determinista** no tiene variables aleatorias; las entradas siempre producen las mismas salidas. **Por ejemplo**, pacientes que llegan a una consulta dental exactamente a su hora programada.  
 
Un modelo **estocástico** incluye variables aleatorias, lo que genera salidas aleatorias. **Por ejemplo**, en un banco, los tiempos de llegada y servicio son aleatorios, y las salidas (como el tiempo de espera promedio) son estimaciones estadísticas.
### Modelos Continuos vs Discretos

Así como los sistemas se clasifican en **continuos** y **discretos**, los modelos se pueden clasificar de la misma manera

Sin embargo, no siempre se utiliza un modelo de simulación discreto para un sistema discreto, así como un modelo de simulación continuo para un sistema continuo.  Además, los modelos de simulación pueden ser mixtos, tanto discretos como continuos.

La elección de utilizar un modelo de simulación discreto o continuo (o ambos) depende de las características del sistema y del objetivo del estudio.

**Por ejemplo**, un canal de comunicación podría modelarse **discretamente** si las características y el movimiento de cada mensaje se consideran importantes.  Sin embargo, si el flujo de mensajes en conjunto sobre el canal es lo importante, modelar el sistema mediante simulación **continua** podría ser más apropiado.

En este curso nos enfocaremos en los modelos que son **dinámicos** , **estocásticos** y **discretos**.

## Formas de Representar un Modelo de Simulación

Cuando diseñamos un modelo de simulación, es fundamental contar con herramientas para representar su comportamiento y estructura. A continuación, se presentan tres métodos comunes para representar modelos de simulación:
### 1. Diagrama de Flujo

Un **diagrama de flujo** es una representación gráfica de los procesos y decisiones dentro del sistema. Utiliza símbolos estándar para mostrar la lógica del sistema y la secuencia de eventos.

**Elementos principales:**

- **Óvalos:** Indican el inicio y el fin del proceso.
- **Rectángulos:** Representan actividades o procesos dentro del sistema.
- **Rombos:** Indican decisiones o bifurcaciones en el flujo.

**Ejemplo:** Un diagrama de flujo para la atención de clientes en un banco podría incluir:

1. Cliente llega a la fila.
2. Decide si hay un cajero disponible.
3. Si hay un cajero, el cliente es atendido.
4. Si no hay un cajero, el cliente espera en la fila.
5. Cliente completa la transacción y sale del sistema.

### 2. Lista de Eventos Ordenados

Una **lista de eventos ordenados** representa una ejecución específica de la simulación, mostrando la secuencia de eventos en el tiempo.

**Elementos principales:**

- **Tiempo:** Momento en que ocurre el evento.
- **Evento:** Acción que ocurre en ese momento.
- **Estado del sistema:** Condiciones del sistema después del evento.

**Ejemplo:** Una lista de eventos para un sistema de transporte público podría verse así:

|Tiempo (min)|Evento|Estado del Sistema|
|---|---|---|
|00:00|Pasajero 1 llega|1 en espera|
|00:03|Pasajero 2 llega|2 en espera|
|00:10|Autobús llega|2 suben, 0 en espera|

Este método es útil en simulaciones basadas en eventos discretos, donde se necesita un seguimiento detallado de los cambios en el tiempo.

### 3. Storyboard (Narración Paso a Paso)

Un **storyboard** representa la evolución del sistema en una serie de imágenes o descripciones secuenciales.

**Elementos principales:**

- **Escenarios:** Diferentes estados del sistema en momentos clave.
- **Descripción:** Explicación de lo que ocurre en cada escena.
- **Representación visual (opcional):** Imágenes o diagramas que ilustran el proceso.

**Ejemplo:** Un storyboard para un sistema de autobuses podría incluir:

6. Un pasajero llega a la parada de autobús y revisa el horario.
7. Más pasajeros llegan y esperan en la parada.
8. Llega un autobús y los pasajeros suben.
9. El autobús parte y los pasajeros llegan a su destino.

### Comparación de Métodos

| Método                         | Ventajas                                            | Uso Principal                          |
| ------------------------------ | --------------------------------------------------- | -------------------------------------- |
| **Diagrama de Flujo**          | Fácil de entender, visualiza procesos y lógica      | Definir la estructura del modelo       |
| **Lista de Eventos Ordenados** | Muestra ejecución específica con tiempos reales     | Simulación basada en eventos discretos |
| **Storyboard**                 | Explicación visual sencilla, útil en presentaciones | Explicar sistemas de forma didáctica   |

## Simulación de Sistemas Eventos Discretos

La simulación de sistemas de eventos discretos, es el modelado de sistemas en los que el **estado** de las **variables** del sistema cambia **instantáneamente** en puntos separados del tiempo. 

La simulación de eventos discretos se realiza utilizando métodos numéricos, en lugar de analíticos.

Los métodos analíticos emplean el razonamiento deductivo de las matemáticas para "resolver" el modelo. **Por ejemplo,** el cálculo diferencial puede utilizarse para calcular la política de coste mínimo de algunos modelos de inventario.

Los métodos numéricos emplean procedimientos computacionales para "resolver" modelos matemáticos. En el caso de los modelos de simulación, que emplean métodos numéricos, los modelos se "**corren o ejecutan**" en lugar de resolverse.
## Etapas de un estudio de simulación

Banks, Carson, Nelson y Nicol describen 12 etapas en un estudio de simulación:

1. **Formulación del Problema:**  
   - Definir claramente el problema a resolver. Asegurarse de que los responsables y el analista estén alineados en la comprensión del problema.  
   - **Ejemplo**: Identificar cuellos de botella en una línea de producción.

2. **Establecimiento de Objetivos y Plan del Proyecto:**  
   - Definir las preguntas que la simulación debe responder. Decidir si la simulación es la metodología adecuada.  
   - Planificar los recursos, costos y tiempo necesarios.  
   - **Ejemplo**: Determinar si aumentar el número de cajeros en un banco reduce los tiempos de espera.

3. **Conceptualización del Modelo:**  
   - Crear un modelo abstracto del sistema, comenzando con una versión simple y aumentando la complejidad según sea necesario.  
   - Involucrar a los usuarios del modelo para mejorar su calidad y aceptación.  
   - **Ejemplo**: Modelar el flujo de clientes en un banco, incluyendo llegadas y tiempos de servicio.

4. **Recopilación de Datos:**  
   - Recolectar los datos necesarios para alimentar el modelo. Esto puede incluir distribuciones de tiempos de llegada, servicio, etc.  
   - **Ejemplo**: Registrar los tiempos de llegada de clientes y los tiempos de servicio en un banco.

5. **Traducción del Modelo:**  
   - Convertir el modelo en un formato computacional utilizando software de simulación (como Arena, AnyLogic, Omnet++, etc.) o lenguajes de programación.  
   - **Ejemplo**: Programar el modelo de simulación del banco en un software especializado.

6. **Verificación:**  
   - Asegurarse de que el programa informático funcione correctamente y represente fielmente el modelo conceptual.  
   - **Ejemplo**: Depurar el código para garantizar que no haya errores en la lógica del modelo.

7. **Validación:**  
   - Comparar los resultados del modelo con el comportamiento del sistema real para asegurar su precisión.  
   - **Ejemplo**: Verificar que el modelo del banco reproduzca correctamente las colas y tiempos de espera observados en la realidad.

8. **Diseño Experimental:**  
   - Definir los escenarios a simular, la duración de las corridas y el número de repeticiones.  
   - **Ejemplo**: Simular el banco con 3, 4 y 5 cajeros para comparar resultados.

9. **Corridas de Producción y Análisis:**  
	   - Ejecutar las simulaciones y analizar los resultados para evaluar el desempeño del sistema.  
   - **Ejemplo**: Calcular el tiempo promedio de espera de los clientes en cada escenario.

10. **¿Se necesitan más Corridas?**  
    - Decidir si se necesitan más simulaciones basándose en los resultados obtenidos.  
    - **Ejemplo**: Si los resultados no son concluyentes, simular con más cajeros o bajo diferentes condiciones.

11. **Documentación y Reporte:**  
    - Documentar el modelo, los resultados y el proceso seguido. Presentar un informe final claro y conciso.  
    - **Ejemplo**: Incluir gráficos, tablas y recomendaciones basadas en los resultados de la simulación.

12. **Implementación:**  
    - Aplicar las recomendaciones derivadas de la simulación en el sistema real.  
    - **Ejemplo**: Aumentar el número de cajeros en el banco para reducir los tiempos de espera.

### Fases del Proceso de Simulación

Los 12 pasos anteriorse se pueden agrupar en 4 fases:

1. **Descubrimiento y Orientación (Pasos 1 y 2):**  
   - Definir el problema, objetivos y plan del proyecto.

2. **Construcción del Modelo y Recopilación de Datos (Pasos 3-7):**  
   - Crear el modelo, recolectar datos, traducirlo a un formato computacional, verificarlo y validarlo.

3. **Ejecución del Modelo (Pasos 8-10):**  
   - Diseñar experimentos, ejecutar simulaciones y analizar resultados.

4. **Implementación (Pasos 11 y 12):**  
   - Documentar, reportar y aplicar las soluciones en el sistema real.


## Bibliografia

Banks, J., Carson, J. S., Nelson, B. L., & Nicol, D. M. (2010). _Discrete-event system simulation_ (5th ed.). Pearson Education.  _(Capítulo 1, páginas 1-19)_.

