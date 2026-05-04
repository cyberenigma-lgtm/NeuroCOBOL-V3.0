# 🏛️ Capítulo 2: Interfaz de Cristal (NXG V2)
### *La Orquestación Visual de Genesis OS*

La **Interfaz de Cristal** no es solo estética; es una ventana a la voluntad del sistema. En NeuroCOBOL, los elementos visuales son ciudadanos de primera clase con su propia lógica interna y opcodes dedicados (`0xD0`).

---

## 🟦 1. Teoría y Conceptos: El Lenguaje Visual de Genesis
Genesis OS utiliza el motor **NXG V2** (*Next Experience Genesis*). A diferencia de las interfaces gráficas convencionales, el cristal de Genesis es:
- **Declarativo**: El arquitecto declara qué quiere ver, no cómo dibujarlo.
- **Transparente**: Respeta los niveles de transparencia cognitiva del sistema.
- **Genesis**: Integrado directamente en el bus hemisférico.

---

## 🟩 2. Manual de Referencia de Comandos (Interfaz)

### **A. Contenedor de Ventana**
- **Sintaxis**: `VENTANA [Nombre] ... (Elementos) ... FIN VENTANA`
- **Modo de Uso**: Es el marco de renderizado genesis. Cada ventana es un proceso visual en Genesis.
- **Impacto**: Genera el opcode `0xD0 (ui_window)` en el GXP.

### **B. Capturador de Voluntad (BOTON)**
- **Sintaxis**: `BOTON "[Texto]" ... (Evento) ... FIN BOTON`
- **Modo de Uso**: Elemento de interacción industrial. Se usa para iniciar acciones de la Lógica.

### **C. Capturador de Evento (ON CLICK)**
- **Sintaxis**: `ON CLICK ... (Instrucciones) ... (FIN)` 
- **Modo de Uso**: Es el bloque que "escucha" la voluntad del usuario y la traduce a la Lógica del programa.

---

## ⚠️ 3. Diccionario de Errores Visuales
La interfaz de cristal es sensible a la estructura jerárquica y el sellado de bloques.

### 🟥 Error A: "Fuga de Cristal" (Missing FIN VENTANA)
- **Signo**: El programa compila, pero no aparece ninguna ventana en Genesis OS.
- **Causa**: Falta el comando `FIN` para la ventana.
- **Solución**: Asegúrate de que cada `VENTANA` y `BOTON` esté cerrado.

### 🟥 Error B: "Evento Huérfano" (ON CLICK sin Lógica)
- **Signo**: `[ERROR] Sintaxis: se esperaba LOGICA, se recibió FIN`.
- **Causa**: Declarar un `ON CLICK` sin ninguna instrucción dentro.
- **Solución**: Añade al menos un `MOSTRAR` o una instrucción de procesamiento dentro del bloque de evento.

---

## 📖 4. Glosario Específico: Capítulo 2
- **NXG V2**: El motor de interfaz de cristal nativo de Genesis OS.
- **GLASSMORPHISM**: Estética Premium basada en transparencias, desenfoques y bordes definidos.
- **EVENTO DE VOLUNTAD**: Señal generada por el usuario (`CLICK`) que activa un flujo en la lógica.

---

## 🏅 Examen de Ciudadanía II (Desafío Visual)
**Misión**: El arquitecto novato ha dejado esta interfaz "rota". Tu tarea es repararla para que el botón muestre el mensaje correctamente.

### Código Corrupto:
```neurocobol
PROGRAMA AppRota
VENTANA Login
    ON CLICK
        MOSTRAR "Acceso Concedido"
    BOTON "Entrar"
FIN
FIN
```

> [!TIP]
> **Pista**: El evento `ON CLICK` pertenece al **BOTÓN**, no a la ventana general en este contexto. Además, el botón no está cerrado correctamente.

---
*Felicidades, Arquitecto. El cristal de Genesis OS ahora obedece vuestra visión.*
