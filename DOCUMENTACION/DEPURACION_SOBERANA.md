# 🔍 Guía de Depuración Soberana (Módulo 5)
### *Introspección, Trazabilidad y Defensa Cognitiva*

En NeuroCOBOL, depurar no significa “buscar errores”, sino examinar la voluntad que el programa inyecta en el sistema nervioso de **Genesis OS**. Cada instrucción es una señal cognitiva, y cada señal debe respetar la integridad del **NeuroBUS**. Este módulo enseña a inspeccionar, rastrear y validar esa voluntad.

---

## 🟦 1. Logs del NeuroBUS — Trazabilidad Evolutiva
Genesis OS mantiene un registro continuo de toda actividad del bus cognitivo.

*   **Rastreo de Mensajes**: Cada instrucción `ENVIAR BUS` queda registrada con un timestamp evolutivo, módulo emisor, hemisferio objetivo y nivel de integridad (OK / WARNING / ERROR).
*   **Filtrado de Ruido Cognitivo**: Si el compilador detecta un mensaje mal formado, vacío o incoherente, el log marcará la entrada con una bandera de integridad.
*   **Herramienta de Monitoreo**: El SDK incluye `neurobus_monitor`, que permite observar señales en tiempo real para validar flujos hemisféricos y detectar saturación del bus.

## 🟩 2. Inspección del Binario GXP — La Voluntad en Silicio
El formato **GXP (Genesis eXecutable Package)** encapsula el bytecode genesis, metadatos de autoría y la estructura de orquestación.

*   **Cabecera GXP**: Incluye la firma de autoría de **José Manuel Moreno Cano**, versión del compilador, tabla de offsets y huella de integridad.
*   **Sección Neural**: Contiene los opcodes de alto nivel:
    *   `0xD0` → UI (NXG V2)
    *   `0xE0` → I/O industrial
    *   `0xF0` → NeuroBUS
*   **Herramienta de Inspección**: `gxp_inspect --trace archivo.gxp` permite desglosar la secuencia de voluntad y validar la integridad del paquete.

## 🟧 3. Introspección del Runtime NWC — El Motor de Voluntad
El motor **NWC (Neuro World Compiler)** ejecuta el bytecode en tiempo real.

*   **Volcado de Memoria**: Permite inspeccionar variables `TEXTO`, `NUMERO`, buffers de mensajes y estados internos del módulo IA.
*   **Puntos de Interrupción Cognitiva**: Pausa la ejecución cuando un hemisferio recibe una señal concreta, un módulo IA entra en alerta o se activa el modo `NITRO`. Esto permite depurar interacciones cognitivas, no solo código.

## 🛡️ 4. Protocolo de Integridad Soberana
Si un programa no se comporta como se esperaba, siga este protocolo:
1.  **Validar permisos de hemisferio**: Asegúrese de que el módulo está en el hemisferio correcto (`IZQUIERDO` para lógica, `DERECHO` para creatividad, `GLOBAL` para orquestación).
2.  **Revisar saturación del bus**: El comando `ACTIVAR NITRO` puede generar ruido cognitivo si se usa sin control.
3.  **Confirmar registro del módulo**: Un `MODULO` incorrecto provocará fallos de trazabilidad.
4.  **Inspeccionar mensajes**: Use el veredicto genesis (Mal formado = Critical Error, Vacío a IA = Error, etc.).

---

### 🧠 Depuración e Introspección
*Por José Manuel Moreno Cano*

Este módulo convierte al programador en un **Operador Cognitivo**, capaz de rastrear señales, validar la voluntad y comprender cómo **Genesis OS** interpreta cada intención.
