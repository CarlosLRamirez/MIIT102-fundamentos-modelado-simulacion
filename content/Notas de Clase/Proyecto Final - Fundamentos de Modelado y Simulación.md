---
created: 2025-03-29T07:44:59-06:00
modified: 2025-04-12T11:16:21-06:00
title: Proyecto Final - Fundamentos de Modelado y Simulación
---
\begin{center}
Escuela de Estudios de Postgrado

Facultad de Ingeniería

Universidad de San Carlos de Guatemala

Maestría en Ingeniería para la Industria con Especialidad en Telecomunicaciones

Curso: Fundamentos de Modelado y Simulación

Catedrático: Ing MSc. Carlos Leonel Ramírez
\end{center}


# Proyecto Final de Curso


## Objetivo

El propósito de este proyecto es que los estudiantes apliquen los conceptos aprendidos a lo largo del curso para resolver un problema de simulación utilizando herramientas informáticas. Esto incluye la construcción de un modelo de eventos discretos, la ejecución de múltiples simulaciones, el análisis estadístico de resultados, la estimación de parámetros, y la comparación de diferentes políticas o configuraciones mediante técnicas estadísticas.


## Instrucciones Generales

Cada grupo de estudiantes deberá seleccionar un problema que será abordado mediante simulación por computadora. Los pasos a seguir son los siguientes:
  
### 1. Descripción del Problema

- Definir claramente el problema que se desea resolver mediante simulación.
- Describir el objetivo del ejercicio de simulación.
- Justificar por qué una solución analítica no es aplicable o por qué es preferible utilizar simulación.
### 2. Identificación de Componentes del Sistema

- Identificar y describir claramente las **entidades**, **eventos**, **actividades**, **variables de estado**, y cualquier otro componente relevante del sistema a simular.
- Establecer las relaciones entre estos componentes.

### 3. Generación de Números Aleatorios

- Investigar y describir el método de generación de números pseudoaleatorios que utiliza la herramienta de simulación seleccionada (por ejemplo, SimPy, CloudDES, OMNeT++ u otra de su preferencia).
- Identificar sus características principales, incluyendo período y método de generación.

### 4. Implementación del Modelo

- Crear los scripts o archivos de configuración necesarios para ejecutar la simulación.
- Explicar detalladamente cómo se implementa el modelo de simulación en la herramienta elegida.

### 5. Ejecución de Simulaciones

-  Realizar múltiples corridas de la simulación (mínimo 5 repeticiones por configuración).
- Registrar los resultados de las simulaciones en archivos `.sca` o `.vec` (para OMNeT++), o su equivalente en otras herramientas para la colección de estadísticas.
### 6. Análisis Estadístico

- Calcular intervalos de confianza para las medidas de desempeño clave del sistema simulado (por ejemplo, tiempo promedio en cola, tasa de pérdida de paquetes, utilización de recursos, etc.).
- Realizar una estimación comparativa de proporciones o medias para evaluar el desempeño de dos o más políticas dentro del mismo escenario de simulación.
- Incluir gráficos estadísticos, gráficos comparativos u otro tipo de visualizaciones de resultados que consideren pertinentes para mejorar la comprensión y presentación del análisis realizado.

### 7. Reporte de Resultados y Conclusiones

Elaborar un informe escrito que incluya:

- Descripción clara del problema y justificación.
- Identificación detallada de los componentes del sistema.
- Explicación del modelo implementado y sus configuraciones.
- Resultados detallados de las simulaciones, incluyendo visualizaciones gráficas relevantes.
- Análisis estadístico con intervalos de confianza y comparación entre políticas.
- Conclusiones fundamentadas y recomendaciones prácticas.

## Formato de Entrega

- El proyecto se trabajará en los grupos definidos en clase.
- El informe debe ser entregado en formato PDF o presentación con diapositivas.
- Adjuntar los archivos generados durante la simulación (.sca, .vec, .ini, .ned, .py, etc.).
- Cada grupo hará una presentación breve del proyecto en un tiempo máximo de 20 minutos.


## Criterios de Evaluación

| Criterio de evaluación                         | Puntaje |
| ---------------------------------------------- | ------- |
| Descripción clara del problema y justificación | 20      |
| Identificación detallada de componentes        | 15      |
| Implementación correcta del modelo             | 20      |
| Ejecución adecuada de simulaciones             | 10      |
| Calidad del análisis estadístico y comparativo | 20      |
| Claridad, organización y calidad del informe   | 10      |
| Calidad y claridad de la presentación oral     | 5       |
| **Total**                                      | **100** |

---
Guatemala, Abril de 2025