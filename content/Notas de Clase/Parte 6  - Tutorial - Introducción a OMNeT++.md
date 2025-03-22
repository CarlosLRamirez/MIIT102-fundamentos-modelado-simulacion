---
created: 2025-03-22T10:23:29-06:00
modified: 2025-03-22T11:49:10-06:00
title: "Tutorial TicToc - Introducción a OMNeT++ - Parte 6: Visualización de resultados"
aliases:
  - "Tutorial TicToc - Introducción a OMNeT++ - Parte 6: Visualización de resultados"
---
## 6.1 Visualización de escalares y vectores de salida

El IDE de OMNeT++ puede ayudarle a analizar sus resultados. Soporta el filtrado, procesamiento y visualización de datos **escalares**, **vectoriales** e **histogramas**. Los siguientes diagramas se han creado con la herramienta Análisis de resultados (*Result Analysis tool*) del IDE.

El directorio `/results` de la carpeta del proyecto contiene archivos `.vec` y `.sca`, que son los archivos que almacenan los resultados en forma vectorial y escalar, respectivamente. 

Los vectores registran los valores de los datos en función del tiempo, mientras que los escalares suelen registrar los valores agregados al final de la simulación. 

> [!NOTA]
> Para estos ejemplos , asegurarse de colectar todas las estadisticas durante la simulación agregando esta linea al archivo *omnetpp.ini* 
> 
> `**.tic[*].hopCount.result-recording-modes = +histogram, +vector, +stats`


Para abrir la **herramienta de Análisis de Resultados**, haga doble clic en los archivos `.vec` o `.sca` en el IDE de OMNeT++. Ambos archivos serán cargados por la **herramienta de Análisis de Resultados**. 

![[Pasted image 20250322102635.png|600]]


Encontrará la pestaña Examinar datos (*Browse Data*) en la parte inferior del panel de la herramienta Análisis de resultados. Aquí puede examinar los resultados por tipo cambiando las distintas pestañas de la parte superior del panel de herramientas, es decir, Escalares, Vectores, Estadísticas o Histogramas. 

![[Pasted image 20250322102927.png]]

Por defecto, se muestran todos los resultados de un tipo de resultado. Puede filtrarlos por el filtro de módulo para ver todos o algunos de los módulos individuales, o el filtro de nombre de estadística para mostrar diferentes tipos de estadísticas, es decir, **media**, **máx**, **mín**, **desviación** estándar, etc. 

Puede seleccionar algunos o todos los resultados individuales resaltándolos. Si selecciona varios resultados, se representarán en un mismo gráfico. 

Haga clic con el botón derecho del ratón y seleccione una de las opciones del menú *Plot using...*  para visualizar las diferentes opciones.

![[Pasted image 20250322104835.png]]

## 6.1.1 Grafico de Vectores

Nuestro último modelo registra el `hopCount` de un mensaje cada vez que el mensaje llega a su destino. Para representar gráficamente estos vectores para todos los nodos, seleccione las 6 líneas en la pestaña *Browse Data* y, a continuación, haga clic con el botón derecho del ratón y seleccione Representar con gráfico de líneas. (*Line Chat with Matplotlib*)

![[Pasted image 20250322105747.png]]

Podemos cambiar varias opciones sobre cómo se muestran los datos en el gráfico. Haga clic con el botón derecho en el fondo del gráfico y seleccione Configurar gráfico. En el cuadro de diálogo que aparece, en la pestaña Líneas, establezca Estilo de línea como Ninguno y Marcador como . (punto).

![[Pasted image 20250322105912.png]]

El gráfico tiene el siguiente aspecto:

![[Pasted image 20250322105938.png]]


Si aplicamos una operación de media podemos ver como los hopCount en los diferentes nodos convergen a una media. Haga clic con el botón derecho en el gráfico y seleccione *Apply... -> Mean*. De nuevo, haga clic con el botón derecho del ratón sobre el fondo del gráfico y seleccione Configurar gráfico. En la pestaña Líneas, establezca Estilo de línea como **Sólido** y Marcador como **Ninguno**. La media se muestra en el siguiente gráfico. Las líneas son más fáciles de ver de esta manera porque son más finas.


![[Pasted image 20250322110203.png]]


![[Pasted image 20250322110324.png]]


## 6.1.2 Grafico de escalares

Los datos escalares pueden representarse en gráficos de barras. El siguiente gráfico muestra la **media** y el **máximo** del `hopCount` de los mensajes para cada nodo de destino, basándose en los datos escalares registrados al final de la simulación. En la pestaña Examinar datos, seleccione Escalares y **asegúrese de que el botón Mostrar estadísticas/campos vectoriales como escalares** (*Show Statistics/Vector Fields as Scalars*) está activado en la barra de herramientas superior derecha. Seleccione ahora `hop count:max` y `hop count:mean` para los 6 nodos. Puede utilizar el filtrado y la ordenación para encontrar los escalares más fácilmente, como se muestra a continuación.

![[Pasted image 20250322110617.png]]

![[Pasted image 20250322113618.png]]

Este es el aspecto inicial del gráfico:

![[Pasted image 20250322113548.png]]

Ahora realiza estas configuración en las opciones del gráfico, en la pestaña **Input**:

![[Pasted image 20250322113839.png]]

Y en la pestaña **Legend**:

![[Pasted image 20250322113905.png]]

Y este es el resultado final del grafico de barras agrupadas por modulo para las tres estadísticas de `hop count`:

![[Pasted image 20250322114012.png]]


## 6.1.3 Grafico de histograma

Para crear un histograma que muestre la distribución de hopCount, seleccione Histogramas en la pestaña Examinar Datos. Seleccione todas las filas, luego haga clic con el botón derecho y elija Graficar usando Gráfico de Histograma.

![[Pasted image 20250322114721.png]]