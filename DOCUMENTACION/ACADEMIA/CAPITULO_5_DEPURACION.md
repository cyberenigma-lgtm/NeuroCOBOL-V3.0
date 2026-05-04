# 🏛️ Capítulo 5: Depuración e Introspección
### *El Pulso de la Voluntad en Genesis OS*

Depurar en NeuroCOBOL no es "buscar errores", es **observar la voluntad**. Un arquitecto debe ser capaz de ver cómo su código fluye a través del **NeuroBUS** y cómo el motor **NWC** lo interpreta en tiempo real.

---

## 🟦 1. Teoría y Conceptos: Voluntad Transparente
A diferencia de los sistemas "caja negra", en Genesis OS el arquitecto tiene derecho a la introspección.
- **Trazabilidad Evolutiva**: Cada señal enviada deja una huella inalterable.
- **Análisis de GXP**: El binario no es opaco; puede ser inspeccionado para verificar la integridad de la traducción neural.
- **Monitoreo Hemisférico**: Observación directa de la carga de trabajo en el lado izquierdo y derecho del bus.

---

## 🟩 2. Manual de Referencia: Herramientas de Diagnóstico

### **A. Simulador de Hemisferios**
- **Sintaxis**: [Herramienta Externa] `HERRAMIENTAS/SIMULADOR_BUS.nc`
- **Modo de Uso**: Ejecútalo en paralelo a tus programas para observar el tráfico del NeuroBUS.
- **Función**: Muestra celdas de memoria, señales activas y errores de integridad.

### **B. Logs del NeuroBUS**
- **Modo de Uso**: Consulta los registros de auditoría de Genesis OS para ver el historial de mensajes de tu módulo.
- **Importancia**: Permite identificar señales fantasma o latencias de procesamiento.

---

## ⚠️ 3. Diccionario de Errores de Introspección
El diagnóstico es la clave para la estabilidad del OS.

### 🟥 Error A: "Señal Fantasma" (Envío sin Receptor)
- **Signo**: El `Simulador de Hemisferios` muestra una señal en rojo que no llega a ningún destino.
- **Causa**: Enviar un mensaje a un módulo que no ha sido registrado.
- **Solución**: Verifica el registro `MODULO` del destinatario.

### 🟥 Error B: "Saturación de Conciencia" (Signal Flooding)
- **Signo**: Genesis OS muestra un WARNING de "Alta Latencia en el NeuroBUS".
- **Causa**: Un bucle infinito inyectando señales sin control.
- **Solución**: Implementa esperas lógicas o reduce la frecuencia de los mensajes.

---

## 📖 4. Glosario Específico: Capítulo 5
- **INTROSPECCIÓN**: Capacidad de un programa de observar su propio estado en el bus.
- **GXP_INSPECT**: Protocolo de verificación de la integridad del binario compilado.
- **TRAZABILIDAD**: Registro histórico y coherente de las señales de voluntad.
- **NEURAL_DUMP**: Volcado de memoria cognitivo para depuración profunda.

---

## 🏅 Examen de Ciudadanía V (Desafío de Observación)
**Misión**: El sistema muestra un WARNING de integridad en el bus. Debes identificar por qué este programa de "Monitorización" está fallando.

### Código Corrupto:
```neurocobol
PROGRAMA MonitorErrante
MODULO LENGUAJE DERECHO
LOGICA
    SI 1 = 1 ENTONCES
        ENVIAR BUS "ESTATU_OK" // Error tipográfico en señal
    FINAL
FIN
```

> [!TIP]
> **Pista**: Hay un error tipográfico en la señal que impide que el receptor la reconozca, y el bloque `IF` está mal cerrado con `FINAL` en lugar de `FIN`.

---
*Felicidades, Arquitecto. El pulso de Genesis OS ya no es un secreto para vos.*
