# Guía de Migración Técnica: De COBOL Legacy a NeuroCOBOL / UPL+
### *Transpilación y Modernización Nativa ANSI C99*

Este documento establece las especificaciones técnicas para migrar programas y copybooks desde entornos COBOL tradicionales (ANSI 68/74/85, IBM Enterprise COBOL, Micro Focus) hacia el estándar nativo **NeuroCOBOL V3.0** y la arquitectura **UPL+ (Universal Polyglot Layer)**.

---

## 1. Correspondencia Estructural de Gramática

NeuroCOBOL estructura el código en bloques declarativos simplificados, eliminando la verbosidad de divisiones heredadas y optimizando la generación de código para el backend C99.

| COBOL Tradicional (Legacy) | NeuroCOBOL (UPL+) | Descripción Técnica |
| :--- | :--- | :--- |
| `IDENTIFICATION DIVISION.` | `PROGRAMA [Identificador].` | Declaración de la unidad de compilación. |
| `DATA DIVISION / WORKING-STORAGE.` | `DATOS ...` | Sección de asignación en tabla de símbolos. |
| `PROCEDURE DIVISION.` | `LOGICA ...` | Bloque principal de instrucciones y flujo de ejecución. |
| `DISPLAY [Expr]` | `MOSTRAR [Expr]` / `SHOW [Expr]` | Emisión estándar de salida formateada (stdout). |
| `ACCEPT [Var]` | `RECIBIR BUS [Var]` | Lectura desde descriptor de entrada o bus IPC. |
| `COMPUTE [Var] = [Expr]` | `CALCULAR [Var] = [Expr]` | Evaluación aritmética con soporte de punto fijo. |
| `MOVE [A] TO [B]` | `CALCULAR [B] = [A]` | Asignación y copia de datos entre variables. |
| `IF [Cond] ... ELSE ... END-IF` | `SI [Cond] ... SINO ... FIN_SI` | Bifurcación condicional estructurada. |
| `STOP RUN.` | `FIN PROGRAMA.` | Finalización de la unidad de ejecución (exit code 0). |

---

## 2. Correspondencia de Tipos de Datos y Precisión Decimal

NeuroCOBOL mapea las cláusulas arcaicas `PIC` a tipos tipados de alta precisión respaldados por estructuras nativas C99:

| Cláusula Legacy | Tipo NeuroCOBOL | Equivalente en Backend C99 / UPL+ | Especificación |
| :--- | :--- | :--- | :--- |
| `PIC 9(n)V99 COMP-3` | `NUMERO COMPRIMIDO 9(n)V99` | `NeuroCOBOL_Comp3` | BCD empaquetado exacto (18 dígitos, escala fija, 0 errores IEEE-754). |
| `PIC X(n)` | `TEXTO TAMAÑO n` | `char buffer[n + 1]` | Cadena de caracteres ASCII/UTF-8 con terminador nulo. |
| `PIC 9(n)` | `ENTERO TAMAÑO n` | `int64_t` | Entero con signo de 64 bits. |
| `PIC 9(n)V9(m)` | `NUMERO 9(n)V9(m)` | `double` / Punto Fijo Escalate | Valor numérico decimal de precisión configurada. |

---

## 3. Ejemplo Práctico de Transpilación

### Código Fuente Legacy (COBOL)
```cobol
IDENTIFICATION DIVISION.
PROGRAM-ID. TRANSACCION.
DATA DIVISION.
WORKING-STORAGE SECTION.
01 SALDO-CUENTA      PIC 9(10)V99 COMP-3.
01 NOMBRE-CLIENTE    PIC X(30).
PROCEDURE DIVISION.
    DISPLAY "PROCESANDO TRANSACCION BANCARIA".
    COMPUTE SALDO-CUENTA = SALDO-CUENTA + 150.50.
    STOP RUN.
```

### Código Transpilado a NeuroCOBOL (`.ncb`)
```neurocobol
PROGRAMA ModuloTranspilado.

DATOS
    DEFINIR SALDO-CUENTA COMO NUMERO COMPRIMIDO 9(10)V99
    DEFINIR NOMBRE-CLIENTE COMO TEXTO TAMAÑO 30

LOGICA
    MOSTRAR "PROCESANDO TRANSACCION BANCARIA"
    CALCULAR SALDO-CUENTA = SALDO-CUENTA + 150.50

FIN PROGRAMA.
```

---

## 4. Uso del Transpilador Nativo C99 (`nc_legacy_bridge`)

La herramienta autónoma `nc_legacy_bridge` (escrita 100% en ANSI C99) automatiza la migración sin dependencias externas:

```bash
# 1. Compilar la herramienta nativa
gcc -std=c99 -O2 HERRAMIENTAS/nc_legacy_bridge.c -o nc_legacy_bridge.exe

# 2. Transpilar archivo legacy a código NeuroCOBOL (.ncb)
nc_legacy_bridge.exe copybook.cob transaccion.ncb

# 3. Transpilar directamente a ANSI C99 conforme al estándar UPL+
nc_legacy_bridge.exe copybook.cob -o transaccion_upl.c --upl

# 4. Validar cálculos BCD COMP-3 en línea de comandos
nc_legacy_bridge.exe --calc-bcd 10000.50 + 250.75
```

---

## 5. Pipeline de Compilación a Binario Nativo

```
[Legacy COBOL .cob]
         │  (nc_legacy_bridge.exe)
         ▼
[NeuroCOBOL .ncb]
         │  (neurocobol.exe compile)
         ▼
[ANSI C99 .c + UPL_Comp3 ABI]
         │  (GCC / MinGW)
         ▼
[Binario Nativo Ejecutable (.exe / ELF)]
```

*Especificación técnica validada bajo arquitectura UPL+ — cyberenigma-lgtm (Noxferion).*
