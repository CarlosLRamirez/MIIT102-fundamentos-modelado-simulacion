---
draft: true
modified: 2025-03-29T05:00:28-06:00
---


## ¿Qué es un Intervalo de Confianza?
Un **intervalo de confianza** es un rango de valores que se utiliza para estimar un **parámetro poblacional desconocido**, calculado a partir de datos muestrales. El intervalo se construye de manera que existe una cierta probabilidad, denominada **nivel de confianza**, de que el verdadero valor del parámetro esté contenido dentro de ese rango.

---
## Conceptos Básicos
### Parámetro vs. Estadístico
- Un **parámetro poblacional** es un valor real que describe una característica de toda la población. Ejemplos: media verdadera (μ), proporción verdadera (p).
- Un **estadístico muestral** es un valor calculado a partir de una muestra que se usa para estimar un parámetro poblacional. Ejemplos: media muestral (̄X), proporción muestral (̂p).

### Error Estándar
El **error estándar** mide la variabilidad de un estadístico muestral con respecto al verdadero parámetro poblacional. Se calcula como:

\[
SE = \frac{S}{\sqrt{n}}
\]

Donde:
- \( S \) es la desviación estándar de la muestra.
- \( n \) es el tamaño de la muestra.

---

## Construcción de un Intervalo de Confianza
El intervalo de confianza para la media poblacional se calcula de la siguiente manera:

\[
IC = \bar{X} \pm Z \left( \frac{S}{\sqrt{n}} \right)
\]

Donde:
- \( \bar{X} \) es la media muestral.
- \( Z \) es el valor crítico correspondiente al nivel de confianza deseado (1.96 para un 95% de confianza, 1.645 para un 90%, 2.576 para un 99%).
- \( S \) es la desviación estándar de la muestra.
- \( n \) es el tamaño de la muestra.


---

## Interpretación del Intervalo de Confianza
Un intervalo de confianza del 95% significa que, si se repitiera el experimento un gran número de veces, aproximadamente el 95% de los intervalos calculados contendrían el verdadero parámetro poblacional.

---

## Aplicación Práctica en Simulaciones
En simulaciones realizadas en OMNeT++, generamos múltiples repeticiones de un experimento bajo las mismas condiciones. Las **estadísticas registradas** (por ejemplo, `Ping Loss Rate`) se utilizan para construir intervalos de confianza que permiten estimar el valor real con un cierto nivel de precisión.

### Ejemplo: Ping Loss Rate en OMNeT++
Imaginemos que se realizan 5 repeticiones de un experimento en OMNeT++ y obtenemos:

| Repetición | Ping Loss Rate (%) |
|------------|--------------------|
| 1          | 1.20               |
| 2          | 1.00               |
| 3          | 1.30               |
| 4          | 0.90               |
| 5          | 1.10               |

### Cálculo del Intervalo de Confianza
- \( \bar{X} = 1.10\%
- \( S = 0.158\) (calculado usando la fórmula de desviación estándar)
- Nivel de Confianza: 95% (\( Z = 1.96\))

\[
IC = 1.10 \pm 1.96 \left( \frac{0.158}{\sqrt{5}} \right) \approx 1.10 \pm 0.138
\]

\[
IC = [0.962, 1.238]
\]

Esto significa que tenemos un 95% de confianza de que el verdadero Ping Loss Rate se encuentra entre **0.96% y 1.24%**.

---

## Relación con la Simulación en OMNeT++
Al realizar múltiples corridas de una simulación en OMNeT++, OMNeT++ automáticamente calcula estadísticas agregadas y genera **intervalos de confianza** si está configurado para hacerlo.

El parámetro "Confidence Interval" (en la configuración de gráficas) permite ajustar el nivel de confianza y visualizar el rango estimado.

### Preguntas para Reflexión
1. ¿Por qué es importante realizar múltiples repeticiones en una simulación?
2. ¿Qué significa si dos intervalos de confianza de diferentes configuraciones se sobrelapan?
3. ¿Qué pasa con el intervalo de confianza si aumentamos el número de repeticiones?

---

¿Quieres que continúe con la creación del ejercicio práctico utilizando OMNeT++ relacionado con esta teoría? 📊✨

