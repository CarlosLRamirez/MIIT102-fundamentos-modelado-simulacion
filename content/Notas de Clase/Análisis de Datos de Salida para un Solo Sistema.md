---
modified: 2025-04-05T07:15:25-06:00
created: 2025-04-02T07:17:04-06:00
draft: false
title: Análisis de Datos de Salida para un Solo Sistema
---
#  Análisis de Datos de Salida de la Simulación

---
##  ¿Por qué es importante el análisis de resultados en simulación?

- 🎯 ¿Qué pasa si no analizamos correctamente?
	- Una sola corrida → puede dar resultados engañosos
	- Las salidas de simulación son **variables aleatorias**
	- Debemos **estimar parámetros** (como la media) usando estadística
	- Muchos estudios se enfocan en programar el modelo y **descuidan el análisis**-
 - 📊 La simulación NO da una respuesta exacta
	- Estimamos, no determinamos
	- Cada réplica puede dar un resultado distinto
	- El análisis permite cuantificar el **error de muestreo**
- **📌 Necesitamos:**
	- Múltiples réplicas independientes
	- Intervalos de confianza
	- Comparaciones estadísticas
---

## Principios clave del análisis de salida

1. Variabilidad y replicación
	- Cada corrida genera un resultado distinto → **¡hay que repetir!**
	- Simulamos con **distintas semillas aleatorias**
2. Estimaciones con error
	- Usamos medias muestrales, varianzas y proporciones
	- Aplicamos **intervalos de confianza** para cuantificar la incertidumbre
3. Tipos de simulación
	- **Terminante**: tiene un final natural (ej. banco que cierra)
	- **No terminante**: análisis en estado estable (ej. red de datos)

---

> [!Conclusion]
>Sin análisis estadístico, no hay simulación confiable.

---
## Independencia entre corridas (replicas)

[**Ejemplo 9.1**] Consideremos un banco con 5 cajeros y una cola, el cual abre a las 9:00 AM y cierra a las 5:00 PM, pero permanece abierto hasta que todos los clientes presentes en el banco a las 5:00 PM hayan sido atendidos. Supongamos que los clientes llegan según un proceso de Poisson con una tasa promedio de 1 cliente por minuto; es decir, los tiempos entre llegadas son independientes e idénticamente distribuidos (IID) con distribución exponencial y media de 1 minuto. Los tiempos de servicio son variables aleatorias exponenciales (IID) con media de 4 minutos. La siguiente tabla muestra estadísticas típicas obtenidas en 10 réplicas independientes de la simulación del banco, asumiendo que no hay clientes presentes al inicio. 

---

Note cómo los resultados de diferentes réplicas difieren entre sí, por lo que **una sola corrida no proporciona la respuesta real del sistema**.

![[Pasted image 20250402173145.png]]

---
De los datos en la tabla se puede afirmar que los resultados de cada corrida (filas) son independientes entre sí, debido a que en cada corrida se utiliza una secuencia diferente de números aleatorios, aunque el modelo y las condiciones iniciales sean idénticos.

Dentro de una misma corrida, los datos observados no son necesariamente independientes ni idénticamente distribuidos (por ejemplo, el tiempo de espera del primer cliente podría influir en el del segundo cliente).

Este concepto de **independencia entre corridas** es crucial porque permite aplicar técnicas estadísticas estándar, como intervalos de confianza y pruebas estadísticas, sobre cada columna para inferir características reales del sistema simulado.

---

## Comportamiento transitorio y de estado estable en los procesos estocásticos

1. Comportamiento transitorio
	- Corresponde a la fase **inicial** de operación del sistema.
	- Está **fuertemente influenciado por las condiciones iniciales**.
	- Durante esta fase, la **distribución de probabilidad de las variables aleatorias cambia con el tiempo**.
	- Ejemplo clásico: un sistema de colas que comienza vacío; las primeras observaciones no reflejan el comportamiento típico del sistema.

> **📌 Importancia:** Si se incluyen datos transitorios en el análisis sin considerar su efecto, se puede obtener un sesgo en la estimación de las métricas del sistema.

---

2. Comportamiento en estado estable
	- Se alcanza después de un “tiempo suficientemente largo” de operación.
	- Las distribuciones de las variables se **estabilizan** y se vuelven **aproximadamente independientes del tiempo**.
	- El sistema entra en **equilibrio estadístico**: la probabilidad de estar en un cierto estado ya **no depende del instante** en que se observe.

🧠 En términos probabilísticos:

Si $L(t)$ es la longitud de la cola en el tiempo $t$, entonces: $P(L(t) = n) \to P_n \quad \text{para } t \to \infty$

---

![[Pasted image 20250405052110.png|400]]

La figura 9.1 ilustra **cómo evoluciona la distribución de probabilidad** de una variable aleatoria de salida $Y_i$ en una simulación a medida que avanza el tiempo o el número de observaciones $i$.
- Cada curva $Y_i$ representa la **densidad de probabilidad** de la variable de salida en la observación $i$, o después de $i$ unidades de tiempo.
- Las primeras curvas (como $Y_1$, $Y_2$) reflejan el **comportamiento transitorio**, influenciado por las condiciones iniciales.
- Las curvas posteriores se van **acercando a una forma estable**, que corresponde a la densidad de probabilidad **en estado estacionario**

---

3. Procesos covariante-estacionarios
	- En estado estable, el proceso puede tratarse como **covariante-estacionario**, lo cual significa que sus propiedades estadísticas como la media y la varianza se mantienen constantes a lo largo del tiempo.

---

4. No todos los sistemas alcanzan estado estable., algunos procesos estocásticos:
	- Nunca alcanzan equilibrio (se quedan en fase transitoria indefinidamente),
		- Ejemplo: un sistema de colas con sobrecarga (ρ > 1)
	- O tienen comportamientos cíclicos o periódicos.
		- Ejemplo: Fábrica con turnos de producción cíclicos

---

5. Distribución límite
	- A medida que el tiempo avanza, la **distribución de las variables aleatorias de salida** se aproxima a una **distribución límite** o de **estado estable** F(y), independientemente de las condiciones iniciales I.
	- Sin embargo, **la velocidad de convergencia** a esta distribución **sí depende** de las condiciones iniciales.

---

![[Pasted image 20250402191645.png|350]]

La figura 9.2 muestra cómo cambia el valor esperado del tiempo total en el sistema $E(D_i)$ para el **cliente** $i-ésimo$ en una cola **M/M/1** a medida que el número de clientes observados $i$ aumenta.

**La velocidad de convergencia depende de las condiciones iniciales**:
- Si el sistema empieza vacío (s = 0), el tiempo en sistema inicia bajo y sube.
- Si empieza muy cargado (s = 20), los primeros clientes esperan mucho, pero el valor desciende con el tiempo

---

**📌 Implicaciones para simulación**

- Es fundamental **identificar y remover el período transitorio** antes de analizar datos en simulaciones no terminantes.
- Para eso se utilizan métodos como:
	- Descartar las observaciones iniciales (“warm-up period”),
	- O iniciar el sistema desde una condición representativa del estado estable.

---
## Tipos de simulación en cuanto al análisis de salida 

La forma en que se debe diseñar y analizar una simulación depende del tipo de simulación en cuestión. Existen **dos tipos principales**:

1. **Simulación Terminante (Terminating Simulation)**
2. **Simulación No Terminante (Nonterminating Simulation)**

---
###  Simulación Terminante (Terminating Simulation)

- **📌 Características:**
	- Tiene un **evento natural** que determina el fin de la simulación (ej. el banco cierra, termina una campaña, se alcanza un objetivo).
	- Se usa cuando el **período simulado es finito y relevante** para el estudio.
	- Las condiciones iniciales suelen ser representativas de la realidad (ej. sin clientes al inicio del día).
- **📊 Ejemplos:**
	- Un banco que abre a las 9:00 y cierra a las 17:00.
	- Una línea de ensamblaje que se reinicia cada jornada.
- **🧠 Implicación para el análisis:**
	- Se realizan múltiples réplicas independientes.
	- Las medidas de salida (como el tiempo de espera promedio) son variables aleatorias IID.
	- Se pueden aplicar directamente técnicas de estimación e intervalos de confianza sobre estas réplicas.

---
###  Simulación no terminante (Nonterminating Simulation)

- **📌 Características:**
	- No tiene un final natural evidente.
	- El interés está en estudiar el comportamiento **a largo plazo** o en **estado estable**.
	- Es importante eliminar el **efecto de las condiciones iniciales** (fase transitoria).

- **🧠 Consideraciones especiales:**
	- Puede requerirse un **período de calentamiento (warm-up)**.
	- Se deben aplicar técnicas estadísticas que consideren la **correlación entre datos** (ya que no son IID)

---
#### 🧩 Subtipos de métricas en simulaciones no terminantes:

 1. **Parámetros en estado estable**
	 - Ej. tiempo promedio en cola después de estabilización.
2. **Parámetros de ciclo en estado estable**
	- Ej. producción por turno, rendimiento por día en sistemas cíclicos.
3. **Otros parámetros**
	- Ej. tiempo esperado hasta que ocurra un evento poco frecuente.

---
Tipo de simulación con respecto al análisis de salida

![[Pasted image 20250402205613.png|500]]

---
**🧠 Conclusión clave:**

> La forma en que se deben recolectar y analizar los datos de salida depende de **si el sistema tiene un punto natural de terminación** o si requiere estudiar su comportamiento a largo plazo.

> La clasificación terminante vs. no terminante es fundamental para aplicar correctamente los métodos estadísticos y evitar errores en la interpretación de resultados.

---
##  Análisis Estadístico para Simulaciones Terminantes

- ¿Qué caracteriza una simulación terminante?**
	- Existe un **evento natural** E que define el final de cada réplica (por ejemplo, cierre del banco, fin de una campaña).
	- Todas las réplicas se inician bajo las **mismas condiciones iniciales**, pero con diferentes secuencias de números aleatorios.
	- Cada réplica produce una **medida de desempeño** $X_j$ (por ejemplo, tiempo de espera promedio diario), que se modela como una **variable aleatoria**.

---

- Supuestos clave:
	- Las salidas $X_1, X_2, …, X_n$ de las $n$ réplicas son **independientes e idénticamente distribuidas (IID)**.
	- Este supuesto permite usar técnicas estadísticas clásicas como:
		- Estimaciones puntuales,
		- Varianza muestral,
		- Intervalos de confianza.

- 📊 Ejemplos de variables de salida $X_j$:
	- Tiempo promedio de espera en el día $j$ en un banco.
	- Tasa de pérdida de paquetes en una red simulada durante la réplica $j$.


---

**Análisis Estadístico para Simulaciones Terminantes**

> [!NOTE]
> El análisis para simulaciones terminantes se basa en realizar **múltiples réplicas independientes**, tratar las métricas de salida como variables aleatorias IID, y aplicar **estadística inferencial** para estimar valores poblacionales como la media o proporciones.
 
---
### Estimación de la media 

- Se realizan $n$ **réplicas independientes** de la simulación, todas iniciadas con las mismas condiciones, pero con diferentes semillas aleatorias.
- Cada réplica produce un valor $X_j$, representando una métrica de salida (por ejemplo, *el tiempo de espera promedio diario*).
- Estas $X_j$ se consideran **variables aleatorias IID** (*independientes e idénticamente distribuidas*).

 **📊 Estimador puntual de la media:**
 
La **media muestral** se define como:
  
$$\bar{X}(n) = \frac{1}{n} \sum_{j=1}^{n} X_j$$


Este valor es un **estimador insesgado** del valor esperado $\mu = E(X)$.

---
**📐 Intervalo de confianza para** $\mu$ **:**

Como el verdadero valor de \mu es desconocido, se construye un **intervalo de confianza del** $100(1-\alpha)$ %:

$$\bar{X}(n) \pm t_{n-1,1-\alpha / 2} \sqrt{\frac{S^2(n)}{n}}$$

Donde 
- $S^2(n)$ es la **varianza muestral**, calculada sobre los $X_j$,
- $t_{n-1, 1 - \alpha/2}$ es el valor de la **distribución t de Student** con $n-1$ grados de libertad. 

---

> [! INTEPRETACION]
> Con un nivel de confianza del $100(1-\alpha)$ %, podemos decir que el verdadero valor esperado $\mu$ se encuentra dentro del intervalo calculado. 
> Este análisis nos permite tomar decisiones informadas a partir de los resultados de simulación, considerando la **incertidumbre estadística** asociada a los datos aleatorios.

---
### Ejemplo de Estimación de la Media paso a paso

Supongamos que queremos estimar el valor esperado ($\mu$)  del **tiempo de espera promedio de un cliente durante el día**, usando los datos de la **Tabla 9.1**  con un intervalo de confianza del **90%**, basado en 10 réplicas de una simulación terminante.

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

---

![[Pasted image 20250402221121.png|600]]

  $$
  t_{9, 0.95} \approx 1.833
  $$

[Tabas de t-student](https://verso.mat.uam.es/~pablo.fernandez/Tablas-chi-t-F-IQ-14-15.pdf)

---

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

### 📘 Ejercicio: Estimación del tiempo promedio de espera en una sala de tren

#### 🎯 Objetivo:

Aplicar el método de estimación de la media e intervalo de confianza usando datos de una simulación terminante.
#### 🚉 Contexto del problema:

Una estación de tren regional abre sus puertas todos los días a las **6:00 a.m.** y atiende pasajeros hasta las **10:00 a.m.**. Durante ese período, los pasajeros llegan a la sala de espera **según un proceso de Poisson** con una **tasa promedio de 1 pasajero cada 2 minutos**.

El tren llega cada 30 minutos y **se lleva a todos los pasajeros que estén esperando**. El tiempo de espera de cada pasajero se mide desde su llegada hasta el momento en que aborda un tren.

Se desea **estimar el tiempo promedio de espera de un pasajero durante una jornada**.

---
#### 🧪 **Simulación:**

Un estudiante simula este sistema usando un modelo computacional, realizando **10 réplicas independientes**, cada una representando una jornada (de 6:00 a 10:00 a.m.).

Al final de cada réplica, obtiene el **tiempo de espera promedio diario** de los pasajeros atendidos ese día.

Los resultados en minutos son:

```
4.2, 3.9, 4.8, 5.1, 4.3, 4.0, 4.7, 5.3, 4.4, 4.6
```

---

#### 📋 **Instrucciones:**

1. **Calcular la media muestral** $\bar{X}(n)$ de los tiempos de espera promedio.
2. **Calcular la varianza muestral** $S^2(n)$.
3. Determinar el valor $t_{n-1, 1 - \alpha/2}$ correspondiente a un **90% de intervalo de confianza**.
4. **Calcular el error estándar** y construir el intervalo de confianza.
5. Interpretar el resultado: ¿Qué significa ese intervalo en el contexto del problema?

---
#### 📌 Pregunta de reflexión:

- Comparar con un escenario donde el tren llega cada 15 minutos. ¿Cómo cambiaría el tiempo de espera esperado?

---


###  Precisión relativa y número de réplicas necesarias 

En simulaciones terminantes, queremos **estimar la media $\mu$** de una métrica de interés (por ejemplo, tiempo promedio de espera) con una **precisión deseada** y un **nivel de confianza específico**.

Pero… ¿**cuántas réplicas** necesitamos para lograr esa precisión?
#### Precisión relativa

La **precisión relativa** $g$ representa el **margen de error permitido en proporción a la media estimada**:

$$g = \frac{\text{margen de error}}{\bar{X}(n)}$$

🧠 Por ejemplo, si quieres que tu estimación esté dentro de un **10% del valor real**, entonces $g = 0.10$.

---
####  ¿Cómo calcular el número de réplicas necesarias?

Se usa la fórmula:


$$
n_r^*(g) = \left( \frac{t_{n-1, 1 - \alpha/2} \cdot \sqrt{S^2(n)}}{g \cdot \bar{X}(n)} \right)^2
$$

Donde:
- $\bar{X}(n)$: media muestral,
- $S^2(n)$: varianza muestral,
- $g$: precisión relativa deseada,
- $t$: valor de $t$ de Student con $n-1$ grados de libertad.

---

#### ✅ Ejemplo 1: Cuando el número de réplicas realizadas es suficiente

Simulamos 10 réplicas y obtenemos:
- $\bar{X}(10) = 4.5$
- $S^2(10) = 0.36$
- $g = 0.10$, $\alpha = 0.10 \Rightarrow t_{9, 0.95} \approx 1.833$

$$
n^*_r(0.10) = \left( \frac{1.833 \cdot \sqrt{0.36}}{0.10 \cdot 4.5} \right)^2
= \left( \frac{1.0998}{0.45} \right)^2
= 5.97
$$

🔍 Como hicimos 10 réplicas y necesitamos aproximadamente 6, **ya cumplimos con la precisión deseada**. ¡No se requieren más réplicas!

---

#### ⚠️ Ejemplo 2: Cuando se necesitan más réplicas

Mismos datos pero mayor varianza:

- $S^2(10) = 1.00$

$$
n^*_r = \left( \frac{1.833 \cdot \sqrt{1.00}}{0.10 \cdot 4.5} \right)^2
= \left( \frac{1.833}{0.45} \right)^2 = 16.6
$$

➡️ Necesitamos **17 réplicas**, pero solo hicimos 10.  

**Conclusión:** La varianza fue alta y **necesitamos seguir simulando**.

---

### Método secuencial

Si no sabemos cuántas réplicas se necesitan desde el inicio, podemos usar un **procedimiento secuencial**:

1. Comenzamos con al menos 10 réplicas.
2. Tras cada réplica nueva, **recalculamos**:
   - Media $\bar{X}(n)$,
   - Varianza $S^2(n)$,
   - Valor de $n^*_r$.
1. Parar cuando $n \geq n_r^*$


✔️ Ventaja: Evita hacer más réplicas de las necesarias.  

📉 Desventaja: Puede requerir muchas réplicas si la varianza es alta.

---

### 🎓 Ejercicio práctico: Simulación de una sala de espera con CloudES

#### 📘 Objetivo:
Simular un sistema sencillo con CloudES y aplicar sobre los resultados:
- Estimación de la media,
- Cálculo de un intervalo de confianza,
- Evaluación de la precisión relativa,
- Estimación del número de réplicas necesarias.

---

#### 🏢 Sistema a simular: “Sala de espera del tren”

##### 🔧 Parámetros:

- Llegadas: Distribución **exponencial**, media = 2 minutos (tasa \( \lambda = 0.5 \))
- Servidor: representa la llegada de un **tren cada 30 minutos**, que **atiende en batch** a todos los pasajeros en espera.
- Tiempo de simulación por réplica: **4 horas** (240 minutos).
- Condición de terminación: la simulación termina a las 10:00 a.m. (terminante).
- Métrica de interés: **tiempo promedio de espera por pasajero en cada jornada**.

---

##### 🧪 **Tareas para el estudiante:**

1. Simular el sistema en CloudES con **al menos 10 réplicas independientes**.
2. Para cada réplica, registrar el **tiempo promedio de espera por pasajero**.
3. Calcular:
	- La **media muestral $\bar{X}(n)$**,
	- La **varianza muestral $S^2(n)$**,
	- Un **intervalo de confianza del 90%** para $\mu$,
	- La **precisión relativa** lograda.
4. Determinar el número de réplicas necesarias $n^*_r$ para alcanzar una precisión relativa del 10%.
5. Concluir si el número de réplicas realizadas fue suficiente o si deben continuar simulando.

---

##### ✏️ **Preguntas guía para entrega:**

1. ¿Cuál fue el valor de $\bar{X}(n)$ y el intervalo de confianza obtenido?
2. ¿Cuál fue el valor calculado de $n^*_r$? ¿Hiciste suficientes réplicas?
3. ¿Qué representa la precisión relativa obtenida?
4. ¿Cómo afecta la varianza observada el número de réplicas necesarias?

---
##### 💡 **Opcional: Extensión del experimento**
- Repetir la simulación con el tren llegando cada **15 minutos**.
- Comparar resultados: ¿qué pasa con el tiempo de espera promedio? ¿y con la varianza?

---


