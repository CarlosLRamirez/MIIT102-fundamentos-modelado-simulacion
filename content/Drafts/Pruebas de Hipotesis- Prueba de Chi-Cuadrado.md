---
modified: 2025-04-02T17:30:44-06:00
draft: true
---


# Pruebas de Hipotesis- Prueba de Chi-Cuadrado

https://www.simplilearn.com/tutorials/statistics-tutorial/chi-square-test#what_are_categorical_variables

## Prueba de Chi-Cuadrado ($χ^2$ )

La prueba Chi-cuadrado es un procedimiento estadístico para determinar la diferencia entre los datos observados y los esperados [.](https://www.simplilearn.com/what-is-data-article) Esta prueba también puede utilizarse para determinar si existe una correlación con las variables categóricas de nuestros datos. Ayuda a averiguar si una diferencia entre dos variables categóricas se debe al azar o a una relación entre ellas.

## Definición de la prueba de Chi-Cuadrado

Una prueba chi-cuadrado es una prueba estadística que se utiliza para comparar los resultados observados y los previstos. El objetivo de esta prueba es identificar si una disparidad entre los datos reales y los previstos se debe al azar o a una relación entre las variables consideradas. En consecuencia, la prueba de chi-cuadrado es una opción ideal para ayudarnos a comprender e interpretar la conexión entre nuestras dos variables categóricas.  

Para probar una hipótesis relativa a la distribución de una variable categórica se requiere una prueba de ji-cuadrado o una prueba no paramétrica comparable. Las variables categóricas, que indican categorías como animales o países, pueden ser nominales u ordinales. No pueden tener una distribución normal, ya que sólo pueden tener unos pocos valores concretos.  

Por ejemplo, una empresa de reparto de comidas quiere investigar la relación entre el sexo, la geografía y las preferencias alimentarias de la gente.  

Se utiliza para calcular la diferencia entre dos variables categóricas, que son:  
- Como resultado del azar o   
- Debido a la relación

## Formula para la prueba de Chi-Cuadrado

$${X_c}^2=\sum{\frac{(O_i-E_i)^2}{E_i}}$$
Donde

$c$ = Grados de libertad
$O$ = Valor Observado
$E$ = Valor Esperado

Los grados de libertad en un cálculo estadístico representan el número de variables que pueden variar en un cálculo. Los grados de libertad pueden calcularse para garantizar que las pruebas de chi-cuadrado son estadísticamente válidas. Estas pruebas se utilizan con frecuencia para comparar los datos observados con los datos que se esperaría obtener si una determinada hipótesis fuera cierta.  

- Los valores observados son los que ustedes mismos recogen.  
- Los valores esperados son las frecuencias esperadas, basándose en la hipótesis nula

## ¿Por qué se utiliza la prueba Chi-cuadrado?  

Chi-cuadrado es una prueba estadística que examina las diferencias entre variables categóricas de una muestra aleatoria para determinar si los resultados esperados y observados se ajustan bien.  

Estos son algunos de los usos de la prueba Chi-cuadrado:  
- La prueba de Chi-cuadrado puede utilizarse para ver si sus datos siguen una distribución de probabilidad teórica bien conocida, como la distribución Normal o Poisson.   
- La prueba de Chi-cuadrado le permite evaluar la bondad de ajuste de su modelo de regresión entrenado en los conjuntos de datos de entrenamiento, validación y prueba.

## ¿Qué le dice una prueba estadística Chi-cuadrado?  

Una prueba Chi-cuadrado (representada simbólicamente como $χ^2$ ) es fundamentalmente un análisis de datos basado en las observaciones de un conjunto aleatorio de variables. Calcula cómo se equipara un modelo a los datos observados reales. Una prueba estadística Chi-cuadrado se calcula a partir de los datos, que deben ser brutos, aleatorios, extraídos de variables independientes, extraídos de una muestra amplia y mutuamente excluyentes. 

En términos sencillos, se comparan dos conjuntos de datos estadísticos, por ejemplo, los resultados de lanzar una moneda al aire. Karl Pearson introdujo esta prueba en 1900 para el análisis y la distribución de datos categóricos. Esta prueba también se conoce como "prueba Chi-cuadrado de Pearson".  

Las pruebas Chi-cuadrado se utilizan sobre todo en la comprobación de hipótesis. Una hipótesis es una suposición de que una determinada condición puede ser cierta, que puede comprobarse posteriormente. La prueba Chi-cuadrado estima el tamaño de la incoherencia entre los resultados esperados y los resultados reales cuando se menciona el tamaño de la muestra y el número de variables de la relación.  

Estas pruebas utilizan grados de libertad para determinar si se puede rechazar una hipótesis nula concreta basándose en el número total de observaciones realizadas en los experimentos. Cuanto mayor sea el tamaño de la muestra, más fiable será el resultado.  

Existen dos tipos principales de pruebas Chi-Cuadrado, llamados:  
1. de Independencia  
2. de bondad de ajuste  

## Prueba Chi-Cuadrado de independencia

La prueba Chi-cuadrado de independencia es una prueba estadística derivable ( también conocida como inferencial) que examina si es probable que dos conjuntos de variables estén relacionados entre sí o no. Esta prueba se utiliza cuando tenemos recuentos de valores para dos variables nominales o categóricas y se considera una prueba no paramétrica. Los criterios necesarios para realizar esta prueba son un tamaño de muestra relativamente grande y la independencia de las observaciones.  
### Ejemplo  

Supongamos que en una sala de cine elaboramos una lista de géneros cinematográficos. Considerémosla como la primera variable. La segunda variable es si las personas que han venido a ver esos géneros de películas han comprado o no bocadillos en el cine. En este caso, la hipótesis nula es que el género de la película y si la gente compró o no aperitivos no son correlacionables. Si esto es cierto, los géneros de las películas no influyen en la venta de aperitivos.
## Prueba de Chi-Cuadrado de bondad de ajuste  

En la comprobación estadística de hipótesis, la prueba de bondad de ajuste Chi-cuadrado determina si es probable que una variable proceda de una distribución determinada o no. Debemos tener un conjunto de valores de datos y la idea de la distribución de estos datos. Podemos utilizar esta prueba cuando tenemos recuentos de valores para variables categóricas. Esta prueba demuestra una forma de decidir si los valores de los datos tienen un ajuste "suficientemente bueno" para nuestra idea o si se trata de una muestra de datos representativa de toda la población.  

### Ejemplo  

Supongamos que tenemos bolsas de pelotas con cinco colores diferentes en cada bolsa. La condición es que la bolsa contenga el mismo número de bolas de cada color. La idea que queremos probar aquí es que las proporciones de los cinco colores de pelotas en cada bolsa deben ser exactas.

## Ejemplo de Calculo de una prueba de Chi-Cuadrado

Supongamos que quieres saber si el sexo tiene algo que ver con la preferencia por un partido político. Encuestas a 440 votantes en una muestra aleatoria simple para averiguar qué partido político prefieren. Los resultados de la encuesta se muestran en la tabla siguiente:

|         | Republicano | Demócrata | Independiente | Total |
| ------- | ----------- | --------- | ------------- | ----- |
| Hombres | 100         | 70        | 30            | 200   |
| Mujeres | 140         | 60        | 20            | 220   |
| Total   | 240         | 130       | 50            | 420   |

Para ver si el género está relacionado con la preferencia de partido político, realice una prueba de independencia de Chi-cuadrado siguiendo los pasos a continuación.

### Paso 1: Defina la Hipótesis

- H0: No existe relación entre el género y la preferencia por un partido político.
- H1: Existe una relación entre el género y la preferencia por un partido político.

### Paso 2: Calcule los Valores Esperados

Ahora calculamos la frecuencia esperada

$$\text{Valor Esperado}=\frac{(\text{Total Fila})*(\text{Total Columna})}{\text{Total de Observaciones}}$$

Por ejemplo, el valor esperado para los Hombres del P. Republicanos es:

$$=\frac{(200)*(240)}{420}=114.28$$

De forma similar, calculamos los demás valores esperados:

|         | Republicano | Demócrata | Independiente | Total |
| ------- | ----------- | --------- | ------------- | ----- |
| Hombres | 114.2857    | 61.9048   | 23.8095       | 200   |
| Mujeres | 125.7143    | 68.0952   | 26.1905       | 220   |
| Total   | 240         | 130       | 50            | 420   |
### Paso 3: Calculamos $\frac{(O-E)^2}{E}$ para cada celda en la tabla

Ahora calculamos el $\frac{(O-E)^2}{E}$ para cada celda de la tabla.
Donde
$O$ = Valor observado
$E$ = Valor esperado


| $\frac{(O-E)^2}{E}$ |             |           |               |       |
| ------------------- | ----------- | --------- | ------------- | ----- |
|                     | Republicano | Demócrata | Independiente | Total |
| Hombres             | 1.7857      | 1.0586    | 1.6095        | 200   |
| Mujeres             | 1.6234      | 0.9624    | 1.4632        | 220   |
| Total               | 240         | 130       | 50            | 420   |

## Paso 4: Paso 4: Calcular la estadística de prueba $χ^2$ 

$χ^2$ es la suma de todos los valores de la tabla anterior

$${X}^2=1.7857+1.0586+1.6095+1.6234+0.9624+1.4632=8.5028$$

Antes de poder llegar a una conclusión, primero hay que determinar el estadístico crítico, lo que requiere determinar nuestros **grados de libertad**. 

Los grados de libertad en este caso, que se traba de una [tabla de contingencia](https://statisticsbyjim.com/basics/contingency-table/#:~:text=For%20example%2C%20at%20our%20computer,a%202%20X%203%20table.),  viene dado por 
el número de columnas de la tabla menos uno multiplicado por el número de filas de la tabla menos uno, o $(r-1)*(c-1)$. Tenemos $(3-1)(2-1) = 2$.

Por último, comparamos el estadístico obtenido con el estadístico crítico que se encuentra en la [tabla chi-cuadrado](https://estdg.blogs.upv.es/files/2018/04/Tabla-Chi2_cola-derecha.pdf).  Como puede ver, para un nivel *alfa* de 0.05 y 2 grados de libertad, el estadístico crítico es 5.991, que es menor que nuestro estadístico obtenido de 8.50. 

![](2%20Areas/204%20Trabajo/206.01%20USAC%20Fundamentos%20de%20MyS/published/Drafts/_attachments/Pasted%20image%2020240413103909%201.png)

Puede rechazar nuestra hipótesis nula porque el estadístico crítico es mayor que el estadístico obtenido.

Esto significa que tenemos pruebas suficientes para afirmar que existe una asociación entre el sexo y la preferencia por un partido político.


## Ejercicio

Tenemos bolsas de caramelos con cinco sabores distintos cada una. Las bolsas deben tener el mismo número de caramelos de cada sabor. Queremos comprobar es que la proporción de sabores por bolsa es la misma.

Reunimos una muestra aleatoria de diez bolsas. Cada bolsa tiene 100 caramelos de cinco sabores. Nuestra hipótesis es que la proporción de los cinco sabores en cada bolsa es la misma.

| Sabor   | Numero de Caramelos (10 bolsas) |
| ------- | ------------------------------- |
| Manzana | 180                             |
| Lima    | 250                             |
| Cereza  | 120                             |
| Fresa   | 225                             |
| Uva     | 225                             |

Aplique la prueba de Chi-Cuadrado para comprobar si la hipotesis es Verdadera o Falsa. Utilize un valor de Alpha de 0.05


## Fundamentos de la comprobación de hipótesis  

La comprobación de [hipótesis](https://www.simplilearn.com/tutorials/statistics-tutorial/hypothesis-testing-in-statistics) es una técnica para interpretar y extraer conclusiones sobre una población a partir de datos de muestra. Ayuda a determinar qué datos de la muestra apoyan mejor las afirmaciones mutuamente excluyentes de la población.  

Hipótesis nula (H0) - La hipótesis nula es la suposición de que el suceso no ocurrirá. Una hipótesis nula no influye en el resultado del estudio a menos que se rechace.  

H0 es su símbolo y se pronuncia H-naught.  

Hipótesis alternativa (H1 o Ha) - La hipótesis alternativa es el opuesto lógico de la hipótesis nula. La aceptación de la hipótesis alternativa sigue al rechazo de la hipótesis nula. H1 es su símbolo.




---------


# PRUEBAS DE HIPÓTESIS  
https://latrobe.libguides.com/maths/hypothesis-testing#:~:text=Hypothesis%20testing%20is%20a%20systematic,a%20hypothesis%20about%20a%20population.

## Comprobación de hipótesis  

A la hora de interpretar los resultados de una investigación, los investigadores deben evaluar si éstos pueden haberse producido por casualidad. La comprobación de hipótesis es un procedimiento sistemático para decidir si los resultados de un estudio de investigación apoyan una teoría concreta que se aplica a una población.  

Las pruebas de hipótesis utilizan datos de muestra para **evaluar una hipótesis sobre una población**_._ Una prueba de hipótesis evalúa lo inusual del resultado, si se trata de una variación razonable por azar o si el resultado es demasiado extremo para ser considerado una variación por azar.

## Hipótesis nula y de investigación

Para realizar pruebas estadísticas de hipótesis, se emplean hipótesis de investigación e hipótesis nulas:  

- **Hipótesis** de investigación: es la hipótesis que se propone, también conocida como hipótesis alternativa HA. Por ejemplo: 
	- HA: Existe relación entre la inteligencia y los resultados académicos.  
	- HA: Los estudiantes universitarios de primer curso obtienen mejores notas tras un curso intensivo de Estadística.  
	- HA: Hombres y mujeres difieren en sus niveles de estrés.  

- La **hipótesis nula** (Ho) es la opuesta a la hipótesis de investigación y expresa que no hay relación entre variables, o no hay diferencias entre grupos; por ejemplo: 
	- Ho: No existe relación entre la inteligencia y los resultados académicos.  
	- Ho: Los estudiantes universitarios de primer curso no obtienen mejores notas tras un curso intensivo de Estadística.  
	- Ho: Los hombres y las mujeres no difieren en sus niveles de estrés.

El propósito de la prueba de hipótesis es comprobar si la hipótesis nula (no hay diferencia, no hay efecto) puede rechazarse o aprobarse. Si se rechaza la hipótesis nula, puede aceptarse la hipótesis de investigación. Si se acepta la hipótesis nula, se rechaza la hipótesis de investigación.  

En la prueba de hipótesis, se establece un valor para evaluar si se acepta o rechaza la hipótesis nula y si el resultado es estadísticamente significativo:  
- Un valor **crítico** es la puntuación que necesitaría la muestra para decidir en contra de la hipótesis nula.  
- Se utiliza un valor de **probabilidad** para evaluar la significación de la prueba estadística. Si se rechaza la hipótesis nula, se acepta la alternativa a la hipótesis nula.

## Valor de probabilidad y tipos de errores  

El valor de probabilidad, **o valor p**, es la probabilidad de una salida o resultado de investigación dada la hipótesis. Normalmente, el valor de probabilidad se fija en 0.05: la hipótesis nula se rechazará si el valor de probabilidad de la prueba estadística es inferior a 0.05. 

Hay dos tipos de errores asociados a las pruebas de hipótesis:  
- ¿Qué ocurre si observamos una diferencia, pero no existe ninguna en la población?  
- ¿Y si no encontramos ninguna diferencia, pero sí existe en la población?  

 Estas situaciones se conocen como errores de **tipo I y de tipo II** :  
- Error de tipo I: es el tipo de error que implica el rechazo de una hipótesis nula que en realidad es cierta (es decir, un falso positivo).    
- Error de tipo II: es el tipo de error que se produce cuando no rechazamos una hipótesis nula que es falsa (es decir, un falso negativo).  
- 
![](Pasted%20image%2020240413093209%201.png)


Estos errores no pueden eliminarse; pueden minimizarse, pero minimizar un tipo de error aumentará la probabilidad de cometer el otro.  

La probabilidad de cometer un error de tipo I depende del criterio que se utilice para aceptar o rechazar la hipótesis nula: el **valor p o nivel** alfa. El alfa lo fija el investigador, normalmente en 0.05, y es la probabilidad que el investigador está dispuesto a correr y seguir afirmando la significación de la prueba estadística). Elegir un nivel alfa más pequeño disminuirá la probabilidad de cometer un error de tipo I.  

Por ejemplo, p<0,05 indica que hay 5 posibilidades entre 100 de que la diferencia observada se deba realmente a un error de muestreo, es decir, que el 5% de las veces se producirá un error de tipo I o que hay un 5% de posibilidades de que lo contrario de la hipótesis nula sea realmente cierto.  

Con un p<0,01, habrá 1 posibilidad entre 100 de que la diferencia observada se deba realmente a un error de muestreo: el 1% de las veces se producirá un error de tipo I.  

El nivel p se especifica antes de analizar los datos. Si el análisis de los datos da como resultado un valor de probabilidad inferior al nivel α (alfa), se rechaza la hipótesis nula; si no es así, no se rechaza la hipótesis nula.

## Tamaño del efecto y significación estadística  

Cuando se rechaza la hipótesis nula, se dice que el efecto es estadísticamente significativo. Sin embargo, la significación **estadística no significa que el efecto sea importante.**  

Un resultado puede ser estadísticamente significativo, pero el tamaño del efecto puede ser pequeño. La conclusión de que un efecto es significativo no proporciona información sobre su magnitud o importancia. De hecho, un efecto pequeño puede ser estadísticamente significativo si el tamaño de la muestra es lo suficientemente grande.  

La información sobre el tamaño del efecto, o magnitud del resultado, la proporciona la prueba estadística. Por ejemplo, la fuerza de la correlación entre dos variables viene dada por el coeficiente de correlación, que varía de 0 a 1.

## Hipótesis Direccionales y No-Direccionales

- Una hipótesis direccional **especifica la dirección de la relación entre las variables independiente y dependiente**.  
	- Una hipótesis que afirma que los estudiantes que asisten a un curso intensivo de Estadística obtendrán notas más altas que los estudiantes que no asisten sería direccional. 
- Una hipótesis no direccional afirma **que habrá una diferencia, pero no sabemos en qué dirección será**.   
	- Una hipótesis no direccional afirma que habrá diferencias entre los estudiantes que asistan o no a un curso intensivo de Estadística, pero no sabemos qué grupo obtendrá notas más altas que el otro. La hipótesis sólo afirma que obtendrán notas diferentes.

