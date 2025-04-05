---
created: 2025-04-03T17:03:48-06:00
modified: 2025-04-03T17:10:04-06:00
draft: true
---
Perfecto, Carlos. A continuación te presento un **plan de clase completo para 3 horas** que cubre:

1. Los **fundamentos del análisis de salida de simulación** (output analysis), y  
2. Una **introducción a la prueba de chi-cuadrado** como parte del análisis de entrada (input modeling).  

Además, incluyo para cada sección la **referencia directa al libro de Averill Law** (*Simulation Modeling and Analysis*, 5ª edición).

---

## 🧑‍🏫 **Plan de clase: Análisis de Entrada y Salida en Simulación**
**Duración total:** 3 horas (180 minutos)

---

### 🔹 **Objetivos generales:**
- Comprender los fundamentos del análisis de salida en simulaciones.
- Distinguir entre simulaciones terminantes y no terminantes.
- Aplicar el cálculo de intervalos de confianza.
- Introducir la validación de datos de entrada con la prueba de chi-cuadrado.

---

## 🕐 **Estructura de la clase**

---

### 🟦 1. Introducción al análisis de resultados de simulación (15 min)

- ¿Por qué no basta con una sola corrida?
- Variabilidad, incertidumbre y toma de decisiones.

📖 **Referencia:** Capítulo 9.1 y 9.2 (pág. 490–493)

---

### 🟩 2. Tipos de simulación según el análisis de salida (20 min)

- Simulación **terminante** vs. **no terminante**
- Ejemplos prácticos: banco, red de datos, sistema de manufactura.
- Diagrama de clasificación (Fig. 9.4)

📖 **Referencia:** Sección 9.3 (pág. 493–497)

---

### 🟨 3. Estimación en simulaciones terminantes (50 min)

- Media muestral, varianza e intervalo de confianza:
  $$\[
  \bar{X}(n) \pm t_{n-1, 1 - \alpha/2} \cdot \sqrt{\frac{S^2(n)}{n}}
  \]$$
- Uso de tablas t de Student
- Ejemplo completo usando los datos de la Tabla 9.1 (pág. 498)
- Interpretación del intervalo

📖 **Referencia:** Sección 9.4.1 y 9.4.2 (pág. 497–504)

---

### ☕️ **Break / pausa corta (10 min)**

---

### 🟥 4. Elección de condiciones iniciales y cierre de análisis de salida (15 min)

- Problema del sesgo por condiciones iniciales.
- Métodos: calentamiento o inicialización aleatoria.
- Buenas prácticas y errores comunes.

📖 **Referencia:** Sección 9.4.3 (pág. 504–511)

---

### 🟪 5. Introducción a análisis de entrada y bondad de ajuste (15 min)

- ¿Qué son datos de entrada? ¿Por qué ajustamos distribuciones?
- Modelar datos con funciones teóricas (exponencial, normal, etc.)
- Introducción a pruebas de bondad de ajuste

📖 **Referencia:** Capítulo 6.6.1 y 6.6.2 (pág. 344–349)

---

### 🧪 6. Prueba de chi-cuadrado paso a paso (30 min)

- Supuestos: datos agrupados, \( np_j \geq 5 \), clases con probabilidades esperadas
- Fórmula del estadístico:
  \[
  \chi^2 = \sum_{j=1}^{k} \frac{(N_j - np_j)^2}{np_j}
  \]
- Ejemplo práctico guiado: probar si tiempos entre llegadas siguen una distribución exponencial.
- Interpretación con tabla \( \chi^2 \)

📖 **Referencia:** Sección 6.6.2 (pág. 346–349)

---

### 🧠 7. Actividad práctica y cierre (25–30 min)

- Análisis de salida con réplica de datos (puedes usar la tabla 9.1 o un dataset que prepares)
- Análisis de entrada con chi-cuadrado
- Discusión de resultados y reflexiones
- Revisión final de conceptos clave

---

## 📚 Materiales que puedes usar o preparar

| Recurso | Propósito |
|--------|-----------|
| Tabla t de Student | Para cálculo de intervalos de confianza |
| Tabla \( \chi^2 \) | Para prueba de bondad de ajuste |
| Hoja de Excel (o Google Sheets) | Para cálculos guiados (media, varianza, IC, chi-cuadrado) |
| Python/Colab (opcional) | Automatización de análisis |
| Diapositivas (10–15) | Para guiar visualmente cada bloque |
| Mini guía resumen | Para que los estudiantes la usen como referencia rápida |

---

¿Te gustaría que te ayude a armar alguno de estos materiales (diapositivas, hoja de Excel, guía resumen)? Puedo comenzar por el que más necesites para tu clase.