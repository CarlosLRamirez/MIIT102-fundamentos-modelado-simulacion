---
created: 2025-04-04T19:17:33-06:00
modified: 2025-04-05T07:15:56-06:00
draft: true
---


---

### Estimación de proporciones 

(**Ejemplo 9.16**) Este ejemplo extiende el análisis de desempeño más allá de la media, al estimar una **proporción**: la fracción de clientes que esperan **menos de 5 minutos** en ser atendidos.

Tomando los datos de las mismas 10 réplicas utilizadas en el ejemplo anterior (ver Tabla 9.1), se desea calcular la proporción promedio de clientes que cumplieron con ese criterio en cada réplica, y construir un intervalo de confianza del 90%.

En cada réplica, se calcula la proporción de clientes cuyo tiempo de espera $Y_i$ se encuentra en el intervalo $[0,\ 5)$ minutos, es decir:

$$
X_j = \frac{1}{N_j} \sum_{i=1}^{N_j} I_i(0,5)
$$

donde:
- \( N_j \) es el número de clientes atendidos en la réplica \( j \),
- \( I_i(0,5) \) es una variable indicadora que vale 1 si el tiempo de espera del cliente \( i \) está entre 0 y 5 minutos, y 0 si no.

A partir de los valores de \( X_j \) en las 10 réplicas, se obtiene:

- Media muestral:  
  $$\[
  \bar{X}(10) = 0.853
  \]$$
- 
- Varianza muestral:  
  \[
  S^2(10) = 0.004
  \]

Usando un valor \( t_{9, 0.95} = 1.833 \) (para un intervalo del 90% con 9 grados de libertad), el error estándar es:

\[
\sqrt{\frac{0.004}{10}} = 0.063
\]

y el margen de error:

\[
1.833 \cdot 0.063 \approx 0.12
\]
#### ✅ Intervalo de confianza del 90% para la proporción:

\[
0.853 \pm 0.12 = [0.733,\ 0.973]
\]

---

#### 📌 Interpretación

Con un 90% de confianza, se estima que **entre el 73.3% y el 97.3% de los clientes esperaron menos de 5 minutos** en ser atendidos. Este tipo de análisis permite evaluar el servicio desde una perspectiva más enfocada en la **experiencia del cliente**, y complementa el uso de la media al capturar la distribución del desempeño.

---


## Estimación de otras medidas de desempeño

(**Ejemplo 9.20**)  Considere nuevamente el **Ejemplo 9.1** :

- **Tasa de llegada:** $\lambda = 1$ cliente por minuto y
- **Tasa de servicio:** $\mu = 0.25$ clientes por minuto por servidor. 
- **Numero de cajeros:** $c = 5$

La **capacidad total del sistema** es de:

$$5 \cdot \mu = 5 \cdot 0.25 = 1.25 \text{ clientes por minuto}$$
Esto implica un **factor de utilización del sistema** de:

$$\rho = \frac{\lambda}{5 \cdot \mu} = \frac{1}{5 \cdot 0.25} = 0.8$$

Bajo este escenario se comparan dos políticas de atención a clientes:
- En la **Política A**, los clientes se forman en colas separadas, una por cada servidor.
- En la **Política B**, todos los clientes hacen una sola cola común y el primero en la fila es atendido por el siguiente servidor disponible.

Al realizar una simulación de ambas políticas, se observa que **el tiempo de espera promedio diario de los clientes (es decir, la media)** es muy similar en ambos casos. Sin embargo, al analizar con más detalle los resultados, se descubre que en la **Política A** hay una mayor proporción de clientes que experimentan **tiempos de espera excesivos**, lo cual no se refleja en la media.


![[Pasted image 20250403174936.png]]


![[Pasted image 20250403175839.png]]


---




Por ejemplo, bajo la política de múltiples colas, **una mayor proporción de clientes experimenta tiempos de espera elevados**, lo cual no se refleja en la media. En contraste, la política de una sola cola produce un sistema más balanceado, con menos variabilidad en la experiencia de los clientes.

Este ejemplo demuestra que **en muchas situaciones no basta con comparar únicamente las medias** de desempeño, ya que pueden ocultar información relevante sobre la distribución de los resultados. Para una evaluación más completa, es útil estimar otras métricas como:

- **Proporciones**, por ejemplo: clientes que esperaron más de 5 minutos,
- **Cuantiles**, como el percentil 90 del tiempo de espera,
- **Varianza o desviación estándar** de los resultados,
- O integrales como el número promedio de clientes en cola durante el día.

Estas métricas pueden estimarse mediante **variables indicadoras**. Por ejemplo, si queremos conocer la proporción de clientes cuyo tiempo de espera \( Y_i \) estuvo en un rango \( B \), definimos:

$$\[
Z_i = 
\begin{cases}
1 & \text{si } Y_i \in B \\
0 & \text{si no}
\end{cases}
\quad \Rightarrow \quad E(Z) = P(Y \in B)
\]$$

Luego, se aplica el mismo marco de análisis de salida (como en la estimación de medias), calculando promedios e intervalos de confianza para estas proporciones.

Así, el análisis de salida se vuelve más robusto y útil para tomar decisiones informadas, considerando no solo los promedios, sino también **la variabilidad y las experiencias extremas** dentro del sistema simulado.



---

## Bibliografia
Libro de Law, Capitulo 9