# 🏛️ Capítulo 1: Anatomía de un Programa Genesis
### *El Cimiento de la Voluntad en Genesis OS*

Todo programa en **NeuroCOBOL** es una declaración de voluntad. Para que esta voluntad sea interpretada por el motor **NWC**, debe seguir una anatomía estricta y soberana.

---

## 🟦 1. Teoría y Conceptos: Los Tres Pilares
Un programa genesis no es solo código; es un **Ciudadano de Genesis OS**. La estructura tripartite asegura que la memoria (Datos) y la acción (Lógica) estén separadas por un muro de integridad.
- **Identidad**: Declarada en el bloque inicial.
- **Estructura**: Asegura que el silicio sepa cuándo actuar y cuándo almacenar.

---

## 🟩 2. Manual de Referencia de Comandos (Anatomía)

### **A. Identidad del Programa**
- **Sintaxis**: `PROGRAMA [Nombre]`
- **Modo de Uso**: Es la primera línea de cada archivo `.nc`. El nombre debe ser único para el **NeuroBUS**.
- **Impacto**: Genera el opcode de registro `0xF0 (bus_init)` en el GXP.

### **B. Bloque de Memoria (DATOS)**
- **Sintaxis**: `DATOS ... (Variables) ... LOGICA`
- **Modo de Uso**: Define el almacén de información. No admite instrucciones ejecutables.
- **Tipos Base**: `TEXTO`, `NUMERO`, `LOGICO`.

### **C. Bloque de Ejecución (LOGICA)**
- **Sintaxis**: `LOGICA ... (Instrucciones) ... FIN`
- **Modo de Uso**: Contiene la potencia del programa: comandos de BUS, UI, y procesamiento.

---

## ⚠️ 3. Diccionario de Errores Comunes
Aprender a programar es aprender a leer los signos de error del sistema.

### 🟥 Error A: "Fuga de Voluntad" (Missing FIN)
- **Signo**: El compilador no termina la fase de análisis.
- **Causa**: Falta el comando `FIN` al final del programa.
- **Solución**: Asegúrate de que cada `PROGRAMA` termine con su respectivo `FIN`.

### 🟥 Error B: "Invasión de Lógica" (Variable en Bloque Incorrecto)
- **Signo**: `[ERROR] Sintaxis: se esperaba LOGICA, se recibió TEXTO`.
- **Causa**: Intentar declarar una variable dentro del bloque `LOGICA`.
- **Solución**: Mueve las declaraciones de variables al bloque `DATOS`.

---

## 📖 4. Glosario Específico: Capítulo 1
- **CIUDADANO**: Un programa que ha declarado su identidad correctamente en el bus.
- **VOLUNTAD**: Conjunto de instrucciones que el arquitecto inyecta en el sistema.
- **INTEGRIDAD DE BLOQUE**: Estado donde las secciones del código respetan el orden sagrado.

---

## 🏅 Examen de Ciudadanía I (Desafío de Anatomía)
**Misión**: El siguiente código está "corrupto" y no respeta la anatomía soberana. Debes identificar los **3 errores** y corregirlos para demostrar que eres digno de ser llamado **Arquitecto Ciudadano**.

### Código Corrupto:
```neurocobol
DATOS
    TEXTO mensaje = "Genesis OS Activado"
    NUMERO version = 2.7
    MOSTRAR mensaje
LOGICA
    MOSTRAR version
PROGRAMA Reparador
```

> [!TIP]
> **Pista**: El orden de los bloques es sagrado y las instrucciones de salida pertenecen a la Lógica, no a los Datos.

---
*Felicidades, Arquitecto. Dominar la anatomía es dominar el sistema.*
