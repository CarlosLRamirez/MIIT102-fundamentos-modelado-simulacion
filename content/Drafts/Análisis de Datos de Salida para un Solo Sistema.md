---
modified: 2025-04-02T22:18:55-06:00
created: 2025-04-02T07:17:04-06:00
draft: false
title: Análisis de Datos de Salida para un Solo Sistema
---


## Introducción

En muchos estudios de simulación se invierte una gran cantidad de tiempo y dinero en el desarrollo y programación del modelo, pero muy poco esfuerzo en analizar los datos obtenidos de la simulación de forma apropiada.

Cuando se ejecuta una sola corrida en una simulación de tamaño arbitrario, se utilizan muestras aleatorias extraídas de una distribución de probabilidad. Estas muestras son simplemente observaciones particulares de variables aleatorias que pueden presentar una gran variabilidad. Como resultado, las estimaciones obtenidas en una corrida específica podrían diferir considerablemente de las características reales del modelo simulado.

Muchos estudios de simulación fallan en el análisis de resultados porque se enfocan solo en programar, no aplican estadística correctamente, enfrentan datos complejos (no IID), y además, el análisis puede ser costoso y difícil de aplicar.

---
## Independencia entre corridas (replicas)

**Ejemplo 9.1** Consideremos un banco con 5 cajeros y una cola, el cual abre a las 9:00 AM y cierra a las 5:00 PM, pero permanece abierto hasta que todos los clientes presentes en el banco a las 5:00 PM hayan sido atendidos. Supongamos que los clientes llegan según un proceso de Poisson con una tasa promedio de 1 cliente por minuto; es decir, los tiempos entre llegadas son independientes e idénticamente distribuidos (IID) con distribución exponencial y media de 1 minuto. Los tiempos de servicio son variables aleatorias exponenciales (IID) con media de 4 minutos. La siguiente tabla muestra estadísticas típicas obtenidas en 10 réplicas independientes de la simulación del banco, asumiendo que no hay clientes presentes al inicio. Note cómo los resultados de diferentes réplicas difieren entre sí, por lo que **una sola corrida no proporciona la respuesta real del sistema**.

![[Pasted image 20250402173145.png]]


De los datos en la tabla se puede afirmar que los resultados de cada corrida (filas) son independientes entre sí, debido a que en cada corrida se utiliza una secuencia diferente de números aleatorios, aunque el modelo y las condiciones iniciales sean idénticos.

Dentro de una misma corrida, los datos observados no son necesariamente independientes ni idénticamente distribuidos (por ejemplo, el tiempo de espera del primer cliente podría influir en el del segundo cliente).

Este concepto de **independencia entre corridas** es crucial porque permite aplicar técnicas estadísticas estándar, como intervalos de confianza y pruebas estadísticas, sobre cada columna para inferir características reales del sistema simulado.

---

## Comportamiento transitorio y de estado estable en los procesos estocásticos


El **comportamiento transitorio** de un proceso estocástico se refiere a la fase inicial de su evolución en el tiempo, influenciada significativamente por las **condiciones iniciales** del sistema. Durante este período, la **distribución de probabilidad** de las variables del proceso **cambia con el tiempo**. Por ejemplo, en un sistema de colas, si el sistema comienza vacío y desocupado, las primeras observaciones de la longitud de la cola o el tiempo de espera de los clientes reflejarán estas condiciones iniciales y su distribución será diferente de la que se observa después de que el sistema haya estado en funcionamiento durante un tiempo. Las densidades de probabilidad transitorias correspondientes a las variables aleatorias ($Y_i$) generalmente serán diferentes para cada valor de ($i$) y cada conjunto de condiciones iniciales ($I$).

El **comportamiento de estado estable** ocurre después de que el proceso ha operado durante un tiempo suficientemente largo y la influencia de las condiciones iniciales ha disminuido. En este punto, la **distribución de probabilidad** del proceso se vuelve **aproximadamente constante con el tiempo**. Se dice que un sistema de colas está en **equilibrio estadístico** o **estado estable** si la probabilidad de que el sistema esté en un estado dado no depende del tiempo. Es decir, ($P(L(t) = n) = P_n(t) = P_n$) es independiente del tiempo ($t$). Sin embargo, es importante notar que aunque la distribución sea estable, las variables aleatorias en sí mismas seguirán variando. En estado estable, las variables aleatorias constituirán aproximadamente un proceso estocástico **covariante-estacionario**. Esto significa que sus propiedades estadísticas como la media y la varianza se mantienen constantes a lo largo del tiempo.

![[Pasted image 20250402182105.png]]

> [!NOTE] 
> No todos los procesos estocásticos alcanzan un estado estable. Algunos pueden mostrar un comportamiento transitorio indefinidamente o exhibir patrones cíclicos.

La distribución en estado estable $F(y)$ no depende de las condiciones iniciales $I$; sin embargo la taza de convergencia de la distribución $F_i(y|I)$ a $F(y)$ si lo es, como se puede ver en la siguiente graficas:

![[Pasted image 20250402191645.png|450]]

![[Pasted image 20250402193456.png|450]]

La convergencia hacia el estado estacionario en una simulación no se limita solo a la media o valor esperado de una variable de salida ($E(Y_i)$). La distribución de probabilidad completa de esa variable de salida ($Y_i$) también evoluciona y se acerca a una distribución límite, conocida como la **distribución de estado estacionario ($Y$)**, a medida que transcurre el tiempo (a medida que $i$ se hace grande) 

---
## Tipos de simulación en cuanto al análisis de salida (Output Analysis)

La forma en que se debe diseñar y analizar una simulación depende del tipo de simulación en cuestión. Existen **dos tipos principales**:

---
### 1. **Simulación Terminante (Terminating Simulation)**

- Se caracteriza por tener un **evento natural E** que indica el final de cada corrida o réplica.
- Este evento puede ser:
  - Cuando el sistema se “limpia” (ej. ya no hay clientes en cola).
  - Cuando ya no se obtiene información útil.
  - Por mandato de gestión.
- Las corridas usan condiciones iniciales iguales y números aleatorios independientes, generando variables aleatorias **IID** (independientes e idénticamente distribuidas).
- Las **condiciones iniciales** suelen influir en las métricas de rendimiento y deben representar bien el sistema real.
- Ejemplos:
  - Un banco que cierra a las 5 pm y se simula hasta que se atiende al último cliente.
  - Un conflicto militar que finaliza cuando una fuerza queda sin recursos.

---
### 2. **Simulación No Terminante (Nonterminating Simulation)**

- No hay un evento natural que indique cuándo terminar.
- Se busca analizar el **comportamiento en estado estable (steady-state)**.
- Requiere técnicas específicas para evitar que las **condiciones iniciales sesguen los resultados**.
- Hay tres subtipos de métricas:
  1. **Parámetros de estado estable**: valores promedio a largo plazo (ej. media del tiempo en sistema).
  2. **Parámetros de ciclo en estado estable**: métricas dentro de ciclos repetitivos en el sistema (por ejemplo, producción por turno).
  3. **Otros parámetros**: no encajan en las categorías anteriores (ej. tiempo hasta que ocurre cierto evento).

---
![[Pasted image 20250402205613.png|450]]

---

##  Análisis Estadístico para Simulaciones Terminantes

- En simulaciones terminantes, existe un evento natural E que marca el final de cada réplica.
- Se realizan $n$ réplicas independientes, todas iniciadas con las mismas condiciones iniciales pero con diferentes semillas de números aleatorios.
- Asumiendo que solo hay una métrica de interés, definimos $X_j$ como la variable aleatoria correspondiente a la réplica $j$, con $j = 1, 2, \dots, n$. Las $X_j$ son variables aleatorias independientes e idénticamente distribuidas (**IID**).
- Por ejemplo, $X_j$ puede representar el **tiempo de espera promedio diario** en la simulación de un banco, o la **tasa de pérdida de paquetes** durante la réplica $j$ en una simulación de red de datos.
 
---

### Estimación de la media 

Supongamos que queremos obtener una estimación puntual y un intervalo de confianza para la media $\mu=E(X)$, donde $X$ es una variable aleatoria definida en una réplica como se ha descrito anteriormente. Realice $n$ réplicas independientes de la simulación y deje que $X_1$,  $X_2$ , $...$, $X_n$ son las variables aleatorias IID resultantes. 

Entonces $\bar{X}(n)$ es un estimador puntual no sesgado para $\mu$, y un intervalo de confianza aproximado del $100(1- \alpha)$ por ciento $(0<\alpha<1)$ para $\mu$ y viene dado por:

$$\bar{X}(n) \pm t_{n-1,1-\alpha / 2} \sqrt{\frac{S^2(n)}{n}}$$

donde $S^2(n)$ es la varianza muestral. Llamaremos al intervalo de confianza basado en la ecuación anterior, el procedimiento de *tamaño de muestra fijo*. 

#### Ejemplo paso a paso

Supongamos que queremos estimar el valor esperado ($\mu$)   el **tiempo de espera promedio de un cliente durante el día**, usando los datos de la **Tabla 9.1**  con un intervalo de confianza del **90%**, basado en 10 réplicas de una simulación terminante.

![[Pasted image 20250402173145.png|600]]

Tiempos de espera promedio por réplica $(X_j)$ (en minutos):

```
1.53, 1.66, 1.24, 2.34, 2.00, 1.69, 2.69, 2.86, 1.70, 2.60
```

---
##### ✏️ Paso 1: Calcular la media muestral $\bar{X}(10)$

$$
\bar{X}(10) = \frac{1}{10} (1.53 + 1.66 + \ldots + 2.60) = 2.03 \, \text{minutos}
$$

---
##### ✏️ Paso 2: Calcular la varianza muestral $S^2(10)$


Formula para la varianza muestral:

$$S^2(n) = \frac{1}{n - 1} \sum_{j=1}^{n} \left(X_j - \bar{X}(n)\right)^2$$

Sustituyendo los valores en la formula:
$$S^2(10) = \frac{1}{10 - 1} \sum_{j=1}^{10} (X_j - 2.03)^2 = \frac{1}{9} \left[ \sum_{j=1}^{10} (X_j - 2.03)^2 \right]$$

Resultado de la varianza muestral:
$$
S^2(10) = 0.31
$$

---

##### ✏️ Paso 3: Determinar el valor $t_{9, 0.95}$

- Queremos un intervalo con **90% de confianza**, lo que implica:
  $$
  \alpha = 0.10 \Rightarrow 1 - \alpha/2 = 0.95
  $$

- Buscamos el valor de **t** en la **tabla de t de Student** con $n - 1 = 9$ grados de libertad:

![[Pasted image 20250402221121.png|600]]

  $$
  t_{9, 0.95} \approx 1.833
  $$

[Tabas de t-student](https://verso.mat.uam.es/~pablo.fernandez/Tablas-chi-t-F-IQ-14-15.pdf)


> [!TIP]
> ✅ Para un **90% de intervalo de confianza**, busca el valor de t en la **columna donde** $\alpha = 0.05$.

---

##### ✏️ Paso 4: Calcular el error estándar y el intervalo de confianza

$$
\text{Error estándar} = \sqrt{\frac{S^2(10)}{10}} = \sqrt{\frac{0.31}{10}} = \sqrt{0.031} \approx 0.176
$$

$$
\text{Margen de error} = t \cdot \text{Error estándar} = 1.833 \cdot 0.176 \approx 0.32
$$

---
##### ✅ Resultado final

$$
\mu \in \bar{X}(10) \pm 0.32 = 2.03 \pm 0.32
$$

**Intervalo de confianza del 90%:**

$$
[1.71,\ 2.35] \, \text{minutos}
$$

---

##### 📌 Interpretación

Podemos decir con un **90% de confianza** que el **tiempo de espera promedio diario** de un cliente en el banco está entre **1.71 y 2.35 minutos**, basado en las 10 réplicas simuladas 

---



$$129.35, 127.11 ,124.03, 122.13, 120.44, 118.39, 130.17, 129.77, 125.52, 133.75$$

lo cual resulta en:
$$\bar{X}(n)=126.07, S^2=23.55$$

y el intervalo de confianza del 95% viene dado por:

$$126.07 \pm t_{9,0.025} \sqrt{\frac{23.55}{10}}=126.07\pm3.47=[122.60,129.54]$$

---

### Ejercicio 2

Para los resultados obtenidos en el ejercicio 1, calcule el valor esperado de la media con un intervalo de confianza del 95% para las variables de interés del ejercicio.


---
## ¿Por qué es importante el análisis estadístico en una simulación?

El análisis estadístico es crucial en una simulación porque permite a los investigadores y profesionales extraer conclusiones significativas a partir de los datos de salida, evaluar la validez del modelo y comparar diferentes configuraciones del sistema. Al aplicar técnicas estadísticas, es posible estimar medidas de desempeño, determinar intervalos de confianza y tomar decisiones informadas basadas en los resultados de la simulación, asegurando que sean confiables y relevantes para los sistemas reales que se están modelando.

---

---

Libro de Law, Capitulo 9