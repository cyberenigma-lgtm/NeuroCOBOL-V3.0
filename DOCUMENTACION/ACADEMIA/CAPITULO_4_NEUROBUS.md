# 🏛️ Capítulo 4: El NeuroBUS (Control Cognitivo)
### *La Orquestación de la IA en Genesis OS*

El **NeuroBUS** es el sistema nervioso central de Genesis OS. A través de NeuroCOBOL, el arquitecto puede enviar señales a los 35 módulos de IA, coordinar hemisferios y activar potencias de procesamiento masivo mediante opcodes de bajo nivel (`0xF0`).

---

## 🟦 1. Teoría y Conceptos: El Sistema Nervioso Digital
En Genesis OS, un programa no es una isla; es una neurona conectada al bus cognitivo.
- **Hemisferio Izquierdo (Lógica)**: Procesamiento de datos, archivos y matemáticas industriales.
- **Hemisferio Derecho (Creatividad)**: Renderizado NXG, interfaces y diseño.
- **Modo Nitro (Overdrive)**: Un estado de aceleración neural donde el bus elimina los protocolos de espera inter-procesos para el arquitecto.

---

## 🟩 2. Manual de Referencia de Comandos (NeuroBUS)

### **A. Identidad de Módulo**
- **Sintaxis**: `MODULO [Tipo] [Hemisferio]` (ej: `MODULO LENGUAJE IZQUIERDO`)
- **Modo de Uso**: Registra el programa como un agente del bus. Sin esto, el acceso a las señales es limitado.
- **Impacto**: Genera el opcode `0xF1 (bus_reg)` en el GXP.

### **B. Propagación de Señal (ENVIAR BUS)**
- **Sintaxis**: `ENVIAR BUS [Variable/Literal]`
- **Modo de Uso**: Inyecta una voluntad o dato en el flujo del bus cognitivo.

### **C. Captura de Señal (RECIBIR BUS)**
- **Sintaxis**: `RECIBIR BUS [Variable]`
- **Modo de Uso**: Escucha las respuestas del sistema o de otros módulos ciudadanos.

### **D. Aceleración Neural (ACTIVAR NITRO)**
- **Sintaxis**: `ACTIVAR NITRO`
- **Modo de Uso**: Úsalo para tareas de alta prioridad que requieran la atención total de los hemisferios.

---

## ⚠️ 3. Diccionario de Errores Cognitivos
El NeuroBUS es un entorno bilingüe y sensible a la coherencia de la señal.

### 🟥 Error A: "Ruido Cognitivo" (Mensaje Vacío)
- **Signo**: `[ERROR] Integridad: Mensaje de BUS vacío detectado. Bloqueando ruido cognitivo.`
- **Causa**: Intentar `ENVIAR BUS ""` o una variable sin contenido definido.
- **Solución**: Asegúrate de que cada señal enviada tiene una voluntad clara.

### 🟥 Error B: "Conflicto Hemisférico" (Falta de Registro)
- **Signo**: `[WARNING] Sistema: El programa no está registrado como MODULO. Acceso al bus limitado.`
- **Causa**: Usar comandos de BUS sin haber declarado previamente un `MODULO`.
- **Solución**: Declara la identidad del programa con `MODULO` antes de iniciar la lógica.

---

## 📖 4. Glosario Específico: Capítulo 4
- **NEUROBUS**: El bus de datos e intención que unifica todos los módulos de Genesis OS.
- **HEMISFERIO**: División lógica del sistema de inteligencia de Genesis (Lógica vs. Interfaz).
- **SEÑAL**: La unidad fundamental de información que viaja por el bus.
- **NITRO_STATE**: Estado de máximo rendimiento del motor NWC.

---

## 🏅 Examen de Ciudadanía IV (Desafío Cognitivo)
**Misión**: El siguiente programa está generando ruido en Genesis OS y no recibe respuesta del bus. Tu tarea es certificar su integridad.

### Código Corrupto:
```neurocobol
PROGRAMA AgenteSordo
LOGICA
    ENVIAR BUS ""
    RECIBIR BUS respuesta
    MOSTRAR respuesta
FIN
```

> [!TIP]
> **Pista**: Falta el registro de identidad del módulo y el mensaje está vacío, lo que dispara las defensas del sistema contra el ruido cognitivo.

---
*Felicidades, Arquitecto. El sistema nervioso de Genesis OS ahora obedece vuestra voluntad.*
