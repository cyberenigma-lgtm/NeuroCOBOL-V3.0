# 🌐 NeuroCOBOL V3.0 Specification: Portuguese / Português (pt)

## Introduction
Welcome to the sovereign **Portuguese / Português** reference for **NeuroCOBOL V3.0**, the cognitive orchestration and enterprise computing layer of the **Universal Polyglot Layer (UPL+)** and **Genesis OS**.

---

## 🏛️ Cognitive Keywords in Portuguese / Português

| NeuroCOBOL Standard | Keyword in Portuguese / Português | Purpose |
| :--- | :--- | :--- |
| **PROGRAM** | `PROGRAMA` | Defines cognitive program scope |
| **DATA** | `DADOS` | Variable and BCD COMP-3 data section |
| **LOGIC** | `LOGICA` | Procedure and execution logic block |
| **DEFINE** | `DEFINIR` | Variable declaration |
| **SHOW** | `MOSTRAR` | Display output to stdout / terminal |
| **COMPUTE** | `CALCULAR` | High-precision arithmetic calculation |
| **IF / THEN / ELSE**| `SE / ENTAO / SENAO` | Conditional branching |
| **PERFORM** | `EXECUTAR` | Routine iteration or invocation |
| **MODULE** | `MODULO` | AI neural module registration |
| **BUS / SEND / RECEIVE** | `BUS / ENVIAR / RECEBER` | Inter-agent NeuroBUS communication |
| **COMPRESSED (COMP-3)** | `COMPRIMIDO` | 18-digit exact fixed-point BCD math |
| **SIMD-KNN** | `SIMD_KNN` | AVX2 SIMD vector search (0.82 ms latency) |
| **NEURAL-INSPECT** | `INSPECAO_NEURONAL` | Introspective telemetry of network weights |

---

## 💻 Sample Program in Portuguese / Português

```cobol
PROGRAMA GENESIS_CORE.

DADOS
    DEFINIR SALDO COMO COMPRIMIDO(12,2).
    DEFINIR ESTADO COMO TEXTO.

LOGICA
    MOSTRAR "Iniciando Nucleo NeuroCOBOL..."
    CALCULAR SALDO = 1500.50 + 250.25
    MOSTRAR SALDO
    
    SE SALDO > 1000 ENTAO
        MOSTRAR "Nivel de liquidez verificado soberano."
    SENAO
        MOSTRAR "Alerta de liquidez."
    FIM_SE

FIM
```
