---
modified: 2025-03-08T09:54:49-06:00
created: '"2024-03-05 08:16", "2tc/G3T+6"'
aliases:
  - "Notas de Clase: Unidad V - Generación de Variables Aleatorias"
title: "Unidad 4: Generación de Variables Aleatorias"
---
# Unidad IV - Generación de Variables Aleatorias

## Los números "realmente" aleatorios

**Un número aleatorio** es aquel obtenido al azar, es decir, que todo número tenga la misma probabilidad de ser elegido y que la elección de uno no dependa de la elección del otro. El ejemplo clásico más utilizado para generarlos es el lanzamiento repetitivo de una moneda o dado ideal no trucado, o una moneda.

Por lo general, el método para obtener números ‘realmente’ aleatorios implica medir algún fenómeno físico que se espera sea aleatorio.Por ejemplo: el decaimiento radiactivo de átomos o algún tipo de "ruido". La medición de estos fenómenos debe realizase con cuidado para evitar sesgos.

La generación de números aleatorios es una parte fundamental en la simulación de sistemas de eventos discretos.
## Propiedades de los números aleatorios

Una secuencia de números aleatorios $R_{1},R_{2},...$, debe tener dos propiedades estadísticas importantes: 

1. **Uniformidad**, es decir, son igualmente probables en cualquier parte. 
2. **Independencia**, es decir, el valor actual de una variable aleatorio no tiene relación con el valor anterior.

Cada numero aleatorio $R_{i}$ es una muestra independiente extraída de una distribución uniforme continua entre cero y uno. Su función de densidad de probabilidad esta dada por:

$$f(x)=\begin{cases}
1, & 0 \leq x \leq 1  \\
0, & \text{ de lo contrario } 
\end{cases}$$

La función de densidad se muestra en la siguiente figura:

![[Pasted image 20250307124443.png#center|450]]


El valor esperade para cada $R_{i}$ está dado por:


$$E(R)=\int_0^1 x d x=\left.\frac{x^2}{2}\right|_0 ^1=\frac{1}{2}$$

y la Varianza esta dada por

$$V(R)=\int_0^1 x^2 d x-[E(R)]^2=\left.\frac{x^3}{3}\right|_0 ^1-\left(\frac{1}{2}\right)^2=\frac{1}{3}-\frac{1}{4}=\frac{1}{12}$$

Algunas consecuencias de las propiedades de uniformidad e independencia:

1. Si el intervalo $[0,1]$ es dividido en $n$ clases o sub-intervalos de igual longitud, el numero esperado de observaciones de cada intervalo es $N/n$ donde $N$ es el número total de observaciones. Nótese que $N$ tiene que ser lo suficientemente largo para mostrar esta tendencia.
2. La probabilidad de observar un valor en un intervalo particular es independiente de los valores anteriormente extraídos.

## Generación de Números Pseudo-aleatorios

El mero acto de utilizar un *método conocido* para generar números aleatorios remueve el potencial de una aleatoriedad verdadera. Si el método es conocido, el conjunto de números aleatorios puede ser repetido, por lo que se puede decir que los números no son verdaderamente aleatorios.

Generar números [verdaderamente aleatorios](https://www.bbc.com/mundo/noticias-45515927) requiere acceso a un proceso físico aleatorio, lo que puede ser poco **práctico** para muchos usos computacionales.  Los algoritmos para generar números pseudo-aleatorios, por otro lado, pueden producir números a una velocidad mucho mayor.

Un generador de números pseudoaleatorios es un algoritmo para generar una secuencia de números cuyas propiedades se aproximen a las propiedades de secuencias de números  aleatorios. La secuencia no será verdaderamente aleatoria, pero es determinista, debido a que es completamente determinada por su valor iniciar, la **semilla** (la cual si podría incluir un valor verdaderamente aleatorio).

El objetivo de cualquier esquema de generación es, sin embargo, producir una secuencia de números entre 0 y 1 que simule o imite las propiedades ideales de **distribución uniforme** e **independencia** lo más cercano posible.

En una simulación por computadora, a menudo nos interesa tener números pseudo-aleatorios, porque nos permiten tener el control de los números aleatorios para poder **repetir** el experimento. En general, se utiliza una forma sistemática de generar números pseudo-aleatorios, estos números son completamente predecibles si se conoce el algoritmo y el valor inicial (semilla).

Durante la generación de números pseudoaleatorios pueden producirse ciertos problemas o errores. Estos errores, o desviaciones de la aleatoriedad ideal. Algunos ejemplos de estas desviaciones son los siguientes:

1. Los números generados pueden no estar uniformemente distribuidos.
2. Los números generados podrian ser de valor discreto en lugar de contínuo.
3. La media de los números generados puede ser demasiado alta o demasiado baja.
4. La varianza de los números generados puede ser demasiado alta o demasiado baja.
5. Podría haber dependencia medida, por ejemplo por autocorrelación

> [!NOTE]
> La **autocorrelación** en un generador de números pseudoaleatorios se refiere a la correlación existente entre los números de una secuencia y sus propias versiones retrasadas (anteriores) dentro de la misma secuencia
> 
> Esencialmente, mide cuánto se relaciona un número con otro a cierta distancia o retraso en la secuencia. 

Los métodos utilizados por una computadora para generar números pseudo-aleatorios, deben tener en cuenta las siguientes consideraciones:

1. El método debe ser rápido.
2. El método debe ser portable hacia diferentes computadoras (idealmente diferentes lenguajes de programación.)
3. El método debe tener una longitud de ciclo (período) suficientemente largo: 
4. Los números aleatorios deben poder replicarse.
5. Y lo que es más importante, los números aleatorios generados deben aproximarse mucho a las propiedades estadísticas ideales de **uniformidad** e **independencia**.

El **período o longitud de ciclo** representa la longitud de la secuencia de números aleatorios antes de que los números anteriores empiecen a repetirse en un orden anterior. 

Por ejemplo $4,9,5,6,9,3,8, 4,9,5,6,9,3,8, 4,9,5,6,9,3,8,...$ parece tener una longitud de ciclo de 7 (esto es sólo un ejemplo de ciclo, ¡un número aleatorio de ciclo 7 es completamente inaceptable!

Un caso especial de ciclo es la **degeneración**, en la que los mismos números aleatorios aparecen repetidamente.

Como utilizamos un algoritmo para generar números aleatorios, los ciclos no se pueden evitar. Pero los ciclos largos (por ejemplo, algunos millones o algunos miles de millones) sirven al propósito de las simulaciones generales.

Los números pseudoaleatorios también se utilizan en criptografía.
## Técnicas para generar números pseudo-aleatorios

### Ejemplo de un Generador simple de Números Pseudoaleatorios

El método del cuadrado medio, también conocido como *“middle-square method”*, es una técnica simple de generación de números pseudoaleatorios desarrollada por John von Neumann en 1946. Este método es relativamente sencillo de implementar y se basa en el siguiente proceso:
  
**Pasos del Método del Cuadrado Medio:**

1. **Seleccionar un número semilla**: Empiezas con un número inicial o “semilla”. Este número generalmente tiene un número $n$ fijo de dígitos, generalmente un número par. (por ejemplo, 4 dígitos).
2. **Elevar al cuadrado la semilla**: Calcula el cuadrado de este número.
3. **Agregar ceros a la izquierda**  Si el numero resultante tiene menos de $2n$ digitos, se añaden ceros a la izquierda  del en numero resultante. Por ejemplo, al  elevar al cuadrado "1111" se obtiene 1234321, el cual puede escribirse como 01234321.
4. **Extraer el número del medio**: Del resultado obtenido (con $2n$ digitos) se extrae el mismo número de dígitos del medio. Por ejemplo, si la semilla inicial tenía 4 dígitos y su cuadrado resulta en un número de 8 dígitos, extraes los 4 dígitos centrales. 
5. **Repetir el proceso**: Este número extraído se convierte en la nueva semilla para el siguiente ciclo del proceso.

Von Neumann utilizó 10 dígitos para este algoritmo en una computadora ENIAC.

**Ejemplo:**
- Supongamos que la semilla inicial es $1234$:
- Elevas al cuadrado la semilla: $1234^2 = 1522756$
- Agregas los ceros necesarios a la izquierda: $01522756$
- Extraes los cuatro dígitos del medio: $5227$
- Este número, 5227, se convierte en la nueva semilla para la próxima iteración.

**Consideraciones:**

• **Ciclos y repeticiones**: Una limitación importante del método del cuadrado medio es que puede caer en ciclos cortos o repetir números, especialmente si el número extraído tiende a cero. Esto reduce su eficacia y aleatoriedad en aplicaciones que requieren una secuencia larga y altamente aleatoria.

• **Uso práctico**: A pesar de su simplicidad, debido a las limitaciones en cuanto a la calidad de los números generados y su tendencia a caer en ciclos repetitivos, este método no es recomendado para aplicaciones serias de generación de números aleatorios, como en criptografía o simulaciones complejas.

El método del cuadrado medio es más una curiosidad histórica y un ejemplo educativo sobre cómo se pueden generar números pseudoaleatorios, pero hay métodos más robustos y eficientes disponibles para uso práctico en la actualidad.
### Método del Generador lineal congruencial (GLC)

#### Descripción

El generador lineal congruencial (GLC) produce una secuencia de enteros $X_{1},X_{2},X_{3},...$ entre $0$ y $m-1$ de acuerdo a la siguiente relación recursiva:

$$X_{i+1}=\left(a X_i+c\right) \bmod m,\quad i=0,1,2, \ldots$$
donde:
- Al valor inicial de $X_{0}$ se le llama semilla.
- $a$ es el multiplicador.
- $c$ es el incremento.
- $m$ es el módulo.

La selección de $a$, $c$, $m$ y $X_{0}$ afecta drásticamente las propiedades estadísticas como la media y la varianza, así como la longitud de ciclo. De acuerdo con el teorema de Hull-Dobell, para obtener el ciclo máximo se deben cumplir ciertas condiciones sobre estos parámetros.

Cuando $c\neq0$, entonces se le llama *generador congruencial mixto*, cuando $c=0$, se conoce como *generador congruencial multiplicativo*

Observe que la ecuación anterior genera números enteros pseudoaleatorios en el conjunto $\{0, 1, \ldots, m-1\}$ que, con una buena parametrización, **parecen** estar uniformemente distribuidos.

Para obtener números pseudoaleatorios de punto flotante en el intervalo $[0,1)$ se utiliza la transformación:

$$R_{i}=\frac{X_{i}}{m}\quad,i=1,2,...$$
De este modo, $R_i$ toma valores en el intervalo $[0, 1)$.

---
#### Ejemplo
Utilice el método congruencial lineal para generar una secuencia de números aleatorios con $X_{0}=27$ , $a=17$ , $c=43$ y $m=100$.

$$X_{0}=27$$

$$X_{1}=(17\cdot27+43)\bmod100=502\bmod100=2$$

$$R_{1}=\frac{2}{100}=0.02$$

$$X_{2}=(17\cdot2+43)\bmod100=77\bmod100=77$$

$$R_{2}=\frac{77}{100}=0.77$$

$$X_{3}=(17\cdot77+43)\bmod100=1352\bmod100=52$$

$$R_{3}=\frac{52}{100}=0.52$$

--- 

#### Aspectos a considerar en los GLC

Los números $R_1, R_2, \dots$ generados con este método solo pueden tomar valores en el conjunto $I = \left\{ 0, \frac{1}{m}, \frac{2}{m}, \dots, \frac{m-1}{m} \right\}$.

Es decir, cada $R_i$ es **discreto** en $I$ en lugar de ser un número continuo en el intervalo $[0,1]$. Sin embargo, si $m$ es muy grande (por ejemplo, $m = 2^{31}-1$ o m = $2^{48}$, que son valores comúnmente utilizados), esta discretización tiene poco impacto práctico.

 La *densidad máxima* se refiere a qué tan “densamente” los valores generados llenan el intervalo $[0,1]$. Por otro lado, el *período máximo* es la longitud de la secuencia antes de que los números comiencen a repetirse.

Para lograr una *buena densidad* y alcanzar el *período máximo* en un rango determinado, es crucial seleccionar apropiadamente los parámetros $a$, $c$, $m$ y la semilla $X_0$. Algunas **selecciones comprobadas** son las siguientes:

**Caso 1: $m$ es una potencia de 2 y $c \neq 0$ (generador congruencial mixto):**

Si $m = 2^b$, el período máximo es $P = m = 2^b$. Este período se alcanza cuando:
- $c$ es relativamente primo con $m$ (es decir, $\mathrm{MCD}(c, m) = 1$).
- $a$ se elige de forma que $a = 1 + 4k$, donde k es un entero (por ejemplo, $a = 5, 9, 13, \dots$).

**Caso 2: $m$  es una potencia de 2 y $c = 0$ (generador congruencial multiplicativo):**

En este caso, el período máximo posible es $P = \frac{m}{4} = 2^{b-2}$. Este máximo se alcanza si:
- La semilla $X_0$ es impar.
- El multiplicador a se elige de forma que $a = 3 + 8k$ o $a = 5 + 8k$ con $k$ entero (por ejemplo, $a = 11, 21, 29, \dots$).

**Caso 3: $m$ es un número primo y $c = 0$:**

En este caso, el período máximo posible es $P = m - 1$. Para lograr este período máximo, es necesario que el multiplicador $a$ tenga la propiedad que el entero mas pequeño $k$ para el cual $a^k-1$ sea divisible por $m$ es $k=m-1$ 

#### Valores de parámetros conocidos para GLC

Existen varios conjuntos de parámetros que se han vuelto famosos en la implementación de generadores congruenciales lineales en lenguajes de programación y bibliotecas numéricas. 
Algunos de los más conocidos son:

**El “Minimal Standard” de Park y Miller:**

Utiliza $a = 16807$, $m = 2^{31}-1$ y$ c = 0$. Este generador es apreciado por su simplicidad y buenas propiedades estadísticas, y ha sido ampliamente recomendado para aplicaciones generales.

**El generador del estándar ANSI C:**

Muchas implementaciones de C utilizan $a = 1103515245$, $c = 12345$ y $m = 2^{31}$ (o en algunos casos $2^{32}$). Aunque es muy utilizado, se ha criticado por ciertos patrones en secuencias específicas.

**Parámetros sugeridos en “Numerical Recipes”:**

Se propone el uso de $a = 1664525$, $c = 1013904223$ y $m = 2^{32}$, parámetros que han sido adoptados en varias aplicaciones debido a su eficiencia y un período suficientemente largo para muchas tareas prácticas.

### Otros métodos de Generación de Números Pseudoaleatorios

Además del Generador Lineal Congruencial (GLC), existen otros métodos para generar números pseudoaleatorios, cada uno con sus ventajas y aplicaciones específicas. Algunos de los más conocidos son:

**Mersenne Twister:**
Es uno de los generadores más utilizados en aplicaciones generales debido a su período extremadamente largo (por ejemplo, $2^{19937}-1$) y a su buena calidad estadística.

**Xorshift:**
Se basa en operaciones bit a bit (XOR y desplazamientos) y es muy eficiente computacionalmente. Es popular en aplicaciones donde se requiere rapidez.

**Generadores de Fibonacci con Retardo (Lagged Fibonacci):**
Utilizan una fórmula similar a la sucesión de Fibonacci, pero con términos anteriores de la secuencia, lo que permite períodos largos y una buena calidad si se eligen adecuadamente los parámetros.

**Generadores Combinados:**
Combinan dos o más generadores (por ejemplo, dos GLC o un GLC con otro método) para compensar las debilidades individuales y mejorar la calidad general de la secuencia.

**Generadores Criptográficamente Seguros:**
Diseñados para aplicaciones en seguridad, estos generadores (como el Blum Blum Shub o métodos basados en algoritmos de cifrado) cumplen con criterios de impredecibilidad y resistencia a ataques, aunque generalmente son más lentos que los métodos convencionales.

Cada uno de estos métodos se elige en función de los requerimientos de la aplicación, ya sea para simulaciones, modelado estadístico o aplicaciones criptográficas.

## Pruebas para Generadores de Números Aleatorios

Las pruebas para generadores de números aleatorios tienen como objetivo evaluar dos propiedades fundamentales:
1. **Uniformidad:** Los números generados deben estar distribuidos de forma uniforme a lo largo del intervalo esperado.
2. **Independencia:** No debe existir correlación o patrón predecible entre los números consecutivos.

Para ello, se aplican diferentes tests estadísticos, tales como:

- **Test de Frecuencia (Chi-cuadrado):** Verifica si la frecuencia de aparición de cada valor se ajusta a la distribución uniforme esperada.
- **Test de Corridas (Runs Test):** Evalúa la aleatoriedad de la secuencia midiendo la cantidad y longitud de “corridas” o secuencias de valores consecutivos por encima o por debajo de la media.
- **Test de Autocorrelación:** Detecta posibles dependencias entre valores a distintos lags, comprobando que no haya correlación entre ellos.

Además, existen suites más completas como la **Diehard** o los **tests NIST**, que incluyen múltiples pruebas para asegurar la calidad de los generadores en aplicaciones críticas, especialmente en criptografía.

## Generación de Variables Aleatorias

Ahora que hemos aprendido a generar una variable aleatoria uniformemente distribuida, estudiaremos cómo producir variables aleatorias de otra distribución utilizando la variable aleatoria uniformemente distribuida.

Todas estas técnicas asumen que se tiene una fuente de números aleatorios uniformes entre $[0,1]$, $R_1, R_2, ...$, en donde cada $R_i$  tiene las siguientes funciones de probabilidad:

Función de Densidad de Probabilidad

$$f_R(x)=\begin{cases}
1, & 0 \leq x \leq 1  \\
0, & \text{ de lo contrario } 
\end{cases}$$

Función de Probabilidad Acumulada

$$F_R(x)=\begin{cases}
0, & x < 0  \\
x, & 0 \leq x \leq 1  \\ 
1, & x > 1 
\end{cases}$$

## Técnica de la transformación inversa

- La técnica de la transformación inversa puede utilizarse para tomar muestras de las distribuciones **exponenciales**, **uniformes**, **Weibulll** y **triangulares**.
- El principio básico es encontrar la función inversa de $F$, $F^{-1}$, tal que $F(F^{-1}) = F^{-1}(F) = 1$.
- $F^{-1}$ denota la solución a la ecuación $r=F(x)$ en términos de $r$, no $1/F$. 
- Por ejemplo, la inversa de $y=x$ es $x=y$, la inversa de $y=2x+1$ es $x=(y-1)/2$, la inversa de $y=x^{2}-1$ es $x=\sqrt{y+1}$

## Generación de una Distribución Exponencial

Recordemos la distribución exponencial

- Función de densidad de probabilidad:

$$f(x)=\begin{cases}
\lambda e^{-\lambda x}, & x \geq 0  \\
0, & x < 0  \\ 
\end{cases}$$


- Función de probabilidad acumulada

$$F(x)=\int_{-\infty}^x f(t) d t=\begin{cases}
1-e^{-\lambda x}, & x \geq 0  \\
0, & x < 0  \\ 
\end{cases}$$

Este método puede ser utilizado para **cualquier** distribución en teoría. Pero es particularmente util para variables aleatorias cuyo función inversa puede ser resuelta con facilidad.

Los pasos son los siguientes:

**Paso 1:**
- Obtenga la función de probabilidad acumulada para la variable aleatoria $X$.
- Para la distribución exponencial, la función de probabilidad acumulada es $F(X)=1-e^{-\lambda x}$
**Paso 2**
- Definir $R=F(X)$ en el rango de $X$
- Para la distribución exponencial, $R=1-e^{-\lambda x}$ en el rango de $x \geqslant 0$.
**Paso 3**
- Resolver la ecuación $F(X) = R$ para $X$ en términos de $R$.
- Para la distribución exponencial, la solución es la siguiente:
$$\begin{align} 
1-e^{-\lambda X} & =R \\ 
e^{-\lambda X} & =1-R \\
-\lambda X & =\ln (1-R) \\
X & =-\frac{1}{\lambda} \ln (1-R)
\end{align}$$

  A la ultima ecuación se le llama generador de la variable aleatoria para la distribución exponencial. En general se escribe como $X=F^{-1}(R)$.
**Paso 4**
Generar (según sea necesario) los números aleatorios $R_1, R_2, ...$ y calcular las variables aleatorias deseadas mediante.
$$X_i=F^{-1}(R_i)$$
En el caso de la distribución exponencial

$$X_i=\frac{-1}{\lambda}\ln{(1-R_i)}$$
para $i=1,2,3...$ donde $R_i$ es un numero aleatorio uniformemente distribuido entre $(0,1)$.

En la práctica, dado que tanto $R_i$ como $1-R_i$, son números aleatorios uniformemente distribuidos, el calculo puede simplificarse según:

$$X_i=\frac{-1}{\lambda}\ln{(R_i)}$$

Una vez tenemos este procedimiento establecido, podemos proceder a resolver otras distribuciones similares para las cuales la función inversa es relativamente fácil de obtener y tiene una formula cerrada.

## Generación de una Distribución Uniforme

Si $X$ es una variable aleatoria uniformemente distribuida entre el intervalo $[a,b]$, la función para generar $X$ esta dada por $X = a + (b-a)R$. Veamos el paso a paso:

La función de densidad de probabilidad de X esta dada por:

$$f_(x)=\begin{cases}
\frac{1}{b-a} & a \leq x \leq b \\
0 & \text { de lo contrario }
\end{cases}$$

**Paso 1**: La función de densidad acumulada es:

$$F(x)=\begin{cases}
0 & x < a \\
\frac{x-a}{b-a} & a \leq x \leq b \\
1 & x>b
\end{cases}$$ 

**Paso 2**: Definimos $F(X)=(X-a)/(b-a)=R$

**Paso 3**: Resolvemos $X$ en términos de $R$ obtenemos

$$X=a+(b-a)R$$

**Paso 4**: Generamos $R_i$ según sea necesario, calculamos $X_i$ utilizando la función obtenida.

## Generación de una Distribución Weibull

La función de densidad de probabilidad es:

$$f(x)= \begin{cases}
\frac{\beta}{\alpha^\beta} x^{\beta-1} e^{-(x / \alpha)^\beta}, & x \geq 0 \\ 
0, & \text { de lo contrario }
\end{cases}$$

**Paso 1** 

Obtenemos la función de probabilidad acumulada:

$$F(X)=1-e^{-(X / \alpha)^\beta}, X \geqslant 0$$

**Paso 2**

Definimos $F(X)=1-e^{-(X / \alpha)^\beta} = R$

**Paso 3**

Resolvemos para $X$ en términos de $R$, obtenemos:

$$X=\alpha[-\ln (1-R)]^{1 / \beta}$$

**Paso 4**

Generar valores de $R_i$ uniformemente distribuidos entre $(0,1)$, para calcular valores de $X$, según la función del paso 3.

## Generación de una Distribución Triangular

Considere una variable aleatoria X con la siguiente función de densidad de probabilidad

$$f(x)=\begin{cases}
x & 0 \leq x \leq 1\\
2-x & 1 < x \leq 2 \\ 
0 & \text{de lo contrario}
\end{cases}$$

Esta distribución es llamada *distribución triangular* con mínimo 0, máximo 2, y moda 1


**Paso 1**

Función de probabilidad acumulada

$$F(x)= \begin{cases}
0 & x \leq 0 \\
\frac{x^2}{2} & 0 < x \leq 1 \\
1 - \frac{(2-x)^2}{2} & 1 < x \leq 2 \\
1 & x > 2
\end{cases}$$

**Paso 2**

Para $0 < X \leq 1$

$$R=\frac{X^2}{2}$$

y para $1< X \leq 2$

$$R=1-\frac{(2-X)^{2}}{2}$$

**Paso 3**

Resolver $X$ en términos de $R$

$$X= \begin{cases}
\sqrt{2R} & 0 < R \leq \frac{1}{2} \\
2 - \sqrt{2(1-R)} & \frac{1}{2} < R \leq 1
\end{cases}$$

**Paso 4**

Generar valores de $R_i$ uniformemente distribuidos entre $(0,1)$, para calcular valores de $X$, según la función del paso 3.

## Referencias
https://www.ugr.es/~batanero/pages/ARTICULOS/aleatoriedad.pdf

## Bibliografía
- Banks, J., Carson, J. S., Nelson, B. L., & Nicol, D. M. (2010). _Discrete-event system simulation_ (5th ed.). Pearson Education.  _(Capítulo 7, páginas 275-295)_.
- Banks, J., Carson, J. S., Nelson, B. L., & Nicol, D. M. (2010). _Discrete-event system simulation_ (5th ed.). Pearson Education.  _(Capítulo 8, páginas 297-304)_.

