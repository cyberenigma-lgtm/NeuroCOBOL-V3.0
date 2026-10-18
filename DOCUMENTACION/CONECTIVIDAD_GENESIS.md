# 🔗 Guía de Conectividad e Integración de Sistemas
### *NeuroCOBOL V3.0 en el Ecosistema UPL+ y Genesis OS*

NeuroCOBOL V3.0 actúa como la capa de alto nivel para lógica de negocio y orquestación dentro del ecosistema **Universal Polyglot Layer (UPL+)** y **Genesis OS**. Su arquitectura ANSI C99 autónoma permite una integración directa y de alto rendimiento entre la capa de compilación, el bus de comunicación inter-procesos (IPC), el ensamblador multilingüe y el kernel de aislamiento de hardware.

---

## 1. Conexión con el Pipeline Compilador UPL+ (Dragon Book)

NeuroCOBOL V3.0 comparte los estándares formales del compilador UPL+ (ISO/IEC 9899:1999):

*   **Interoperabilidad ABI**: Las definiciones de punto fijo BCD se generan bajo la estructura canónica con canarios de protección:
    ```c
    typedef struct {
        uint8_t landing_pad_head[6];
        int64_t valor_entero;
        uint32_t escala;
        uint8_t landing_pad_tail[6];
    } NeuroCOBOL_Comp3;
    ```
*   **Transpilación Directa**: El comando `neurocobol compile <archivo.ncb> -o <salida.c>` emite código C99 puro enlazable directamente con cualquier toolchain estándar (GCC, Clang, MSVC).
*   **Repositorio Central**: [`UNIVERSAL-POLYGLOT-LAYER-UPL`](https://github.com/cyberenigma-lgtm/UNIVERSAL-POLYGLOT-LAYER-UPL).

---

## 2. Integración con el Ecosistema MultiLang-ASM

NeuroCOBOL y MultiLang-ASM comparten la misma tabla poliglotizada de tokens y directivas a través de los 154 idiomas registrados:

*   **Paridad Léxica**: Cada palabra clave en español, inglés, francés, etc., se resuelve en identificadores unificados, garantizando que un módulo de cálculo financiero en NeuroCOBOL interactúe con rutinas de bajo nivel ensambladas por MultiLang-ASM.
*   **Repositorio Central**: [`MultiLang-ASM`](https://github.com/cyberenigma-lgtm/MultiLang-ASM).

---

## 3. Bus de Comunicación Inter-Procesos (IPC) y Kernel Ring 0

NeuroCOBOL se comunica con el núcleo de Genesis OS y los micro-agentes distribuidos mediante descriptores y sobres de mensajes IPC:

*   **Sello de Autoridad**: Cada unidad binaria compilada valida la firma criptográfica **`0x4359454E`** (*CYEN*) en el offset 8 antes de adquirir privilegios de ejecución en el kernel.
*   **Directivas de Bus**:
    - `MODULO`: Registra la unidad de compilación en la tabla de procesos activos.
    - `ENVIAR BUS`: Despacha un sobre de datos con paridad verificada hacia otro servicio.
    - `RECIBIR BUS`: Escucha eventos y mensajes desde el descriptor IPC.

---

## 4. Motor Aritmético de Alta Precisión BCD COMP-3

Para operaciones financieras, bancarias y de misión crítica:

*   **Cero Redondeo IEEE-754**: La aritmética se ejecuta en punto fijo mediante enteros escalados de 64 bits y algoritmos de coma decimal exacta a 18 dígitos.
*   **Herramienta de Diagnóstico**: Invocable en terminal mediante `nc_legacy_bridge --calc-bcd <v1> <op> <v2>`.

---

## 5. Ingestión y Absorción de Código COBOL Tradicional

El transpilador nativo [`HERRAMIENTAS/nc_legacy_bridge.c`](../HERRAMIENTAS/nc_legacy_bridge.c) absorbe copybooks y programas legacy (IBM, Micro Focus, GNU COBOL):

*   **Ingestión sin Dependencias**: 100% C99 nativo, sustituyendo scripts residuales de Python.
*   **Emisión Flexible**: Genera fuentes `.ncb` para el motor NeuroCOBOL o fuentes `.c` compatibles con la ABI de UPL+.

---
*Especificación Técnica de Integración — cyberenigma-lgtm (Noxferion) · Genesis OS / UPL+*
