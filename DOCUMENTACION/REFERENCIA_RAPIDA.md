# ⚡ Referencia Rápida: NeuroCOBOL V3.0
### *Guía Oficial de Uso, Implementación y Absorción de Legacy COBOL*
**Estándar UPL+ (Universal Polyglot Layer) · 100% ANSI C99 Nativo · Cero Dependencias de Python**

---

## 📌 1. Principio Fundamental: Absorción de Legacy COBOL

> **Aviso Técnico y Conceptual**:  
> **NeuroCOBOL V3.0 NO es una copia ni un clon de COBOL**, ni se parece en su sintaxis interna, gramática formal, arquitectura de compilador o runtime. Comparte el nombre exclusivamente como un **tributo mnemónico de identidad** hacia la legibilidad estructurada de lógica empresarial y la precisión decimal BCD (`COMP-3`).
> 
> Su propósito tecnológico es **absorber y modernizar** código COBOL legacy de mainframes (IBM, Micro Focus, GNU COBOL) mediante la toolchain nativa `nc_legacy_bridge`, transformándolo en código limpio y compacto dentro de la arquitectura **UPL+ / ANSI C99**.

---

## 🏗️ 2. Anatomía y Estructura de un Programa NeuroCOBOL

Un programa NeuroCOBOL se estructura en bloques declarativos directos:

```neurocobol
PROGRAMA LiquidacionBancaria.

DATOS
    DEFINIR SALDO_CUENTA COMO NUMERO COMPRIMIDO 9(10)V99
    DEFINIR NOMBRE_TITULAR COMO TEXTO TAMAÑO 40
    DEFINIR TRANSACCIONES COMO ENTERO TAMAÑO 6

LOGICA
    MOSTRAR "Iniciando liquidacion de saldo de alta precision..."
    CALCULAR SALDO_CUENTA = SALDO_CUENTA + 1500.25
    SI SALDO_CUENTA > 1000.00
        MOSTRAR "Saldo positivo verificado"
    SINO
        MOSTRAR "Alerta de saldo insuficiente"
    FIN_SI

FIN PROGRAMA.
```

### Tabla de Tipos de Datos Nativos

| Tipo NeuroCOBOL | Representación en C99 / UPL+ | Precisión y Comportamiento |
| :--- | :--- | :--- |
| `NUMERO COMPRIMIDO [pic]` | `NeuroCOBOL_Comp3` (struct) | **BCD Empaquetado a 18 dígitos**. 0% errores de redondeo IEEE-754. |
| `TEXTO TAMAÑO [n]` | `char[n + 1]` | Cadena segura terminada en null. |
| `ENTERO TAMAÑO [n]` | `int64_t` | Entero con signo de 64 bits de alto rango. |
| `NUMERO [pic]` | `double` / Punto Fijo Escalate | Decimal de cálculo científico/general. |

---

## 🛠️ 3. Modos de Uso del CLI (`neurocobol.exe`)

El ejecutable nativo `neurocobol.exe` opera como compilador y runtime autónomo en ANSI C99:

### A. Ejecución Directa en Memoria
Ejecuta el código `.ncb` instantáneamente (<1 ms) sin generar archivos temporales:
```bash
# Ejecución en idioma Español (por defecto)
neurocobol.exe run programa.ncb -l es

# Ejecución en Inglés
neurocobol.exe run program.ncb -l en

# Ejecución en cualquiera de los 154 idiomas disponibles
neurocobol.exe run programme.ncb -l fr
```

### B. Transpilación a Código Nativo ANSI C99
Genera código fuente estándar C99 listo para ser enlazado con GCC, Clang o MSVC:
```bash
# Transpilar a código C99
neurocobol.exe compile programa.ncb -o programa.c

# Compilar a binario ejecutable nativo
gcc -std=c99 -O2 programa.c -o programa.exe
```

### C. Verificación y Consulta Técnica
```bash
# Ejecutar suite de pruebas internas (BCD, SIMD, paridad de firma)
neurocobol.exe --test

# Listar los 154 lenguajes del mundo soportados
neurocobol.exe --langs

# Consultar palabras clave técnicas en un idioma específico
neurocobol.exe --glossary es
neurocobol.exe --glossary en
```

---

## 🔄 4. Cómo Absorber COBOL Antiguo con `nc_legacy_bridge`

El puente nativo C99 [`HERRAMIENTAS/nc_legacy_bridge.c`](../HERRAMIENTAS/nc_legacy_bridge.c) ingiere archivos COBOL tradicionales (`.cob`, `.cbl`, copybooks) y absorbe su lógica sin dependencias de Python:

### Constructos Absorbidos Automáticamente:
1. **Divisiones y Secciones**: Detecta `PROGRAM-ID`, descarta divisiones superfluas (`ENVIRONMENT`, `DATA`) y estructura las secciones `DATOS` y `LOGICA`.
2. **Definición de Variables**:
   - `01 SALDO PIC 9(10)V99 COMP-3.` ➔ `DEFINIR SALDO COMO NUMERO COMPRIMIDO 9(10)V99`
   - `01 CLIENTE PIC X(30).` ➔ `DEFINIR CLIENTE COMO TEXTO TAMAÑO 30`
   - `01 CONTADOR PIC 9(5).` ➔ `DEFINIR CONTADOR COMO NUMERO 9(5)`
3. **Instrucciones Aritméticas y Verbos**:
   - `DISPLAY "TEXTO"` ➔ `MOSTRAR "TEXTO"`
   - `COMPUTE X = Y + Z` ➔ `CALCULAR X = Y + Z`
   - `MOVE A TO B` ➔ `CALCULAR B = A`
   - `ADD A TO B` ➔ `CALCULAR B = B + A`
   - `SUBTRACT A FROM B` ➔ `CALCULAR B = B - A`
   - `MULTIPLY A BY B` ➔ `CALCULAR B = B * A`
   - `DIVIDE A INTO B` ➔ `CALCULAR B = B / A`
   - `IF ... ELSE ... END-IF` ➔ `SI ... SINO ... FIN_SI`
   - `STOP RUN.` ➔ `FIN PROGRAMA.`

### Comandos de Absorción:
```bash
# 1. Absorber copybook y generar código NeuroCOBOL (.ncb)
nc_legacy_bridge.exe cuenta_legacy.cob cuenta_migrada.ncb

# 2. Absorber y emitir directamente código ANSI C99 con canarios de memoria UPL+
nc_legacy_bridge.exe transaccion.cob -o transaccion_upl.c --upl

# 3. Calculadora BCD COMP-3 de precisión exacta en terminal
nc_legacy_bridge.exe --calc-bcd 10000.50 + 250.75
```

---

## 🔌 5. Cómo Implementarlo en Proyectos

### Paso 1: Compilar la Toolchain
```bash
# En Windows (MinGW GCC)
build.bat
# O en Linux / macOS / POSIX
make all
```

### Paso 2: Flujo de Integración en el Pipeline UPL+
```
[Código COBOL Legacy]
         │
         ▼  (nc_legacy_bridge.exe)
[Código NeuroCOBOL .ncb]
         │
         ▼  (neurocobol.exe compile)
[Código ANSI C99 .c con struct NeuroCOBOL_Comp3]
         │
         ▼  (gcc -std=c99 -O2)
[Binario Nativo Autónomo .exe / ELF]
```

### Paso 3: Ventajas de la Implementación
- **Cero Runtimes Externos**: 0% Python, 0% JVM, 0% emuladores de mainframe.
- **Portabilidad Total**: ANSI C99 estándar ejecutable en x86_64, ARM64, RISC-V o microkernels.
- **Integridad Matemática**: 18 dígitos de precisión contable exacta.
- **Soberanía Multilingüe**: Mantenimiento de código en el idioma nativo de la organización.

---
*NeuroCOBOL V3.0 — Arquitectura de Sistemas UPL+ · cyberenigma-lgtm (Noxferion)*
