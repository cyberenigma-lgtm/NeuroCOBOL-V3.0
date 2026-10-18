# 🌐 NeuroCOBOL V3.0 Specification: Chinese / 中文 (zh)

## Introduction
Welcome to the sovereign **Chinese / 中文** reference for **NeuroCOBOL V3.0**, the cognitive orchestration and enterprise computing layer of the **Universal Polyglot Layer (UPL+)** and **Genesis OS**.

---

## 🏛️ Cognitive Keywords in Chinese / 中文

| NeuroCOBOL Standard | Keyword in Chinese / 中文 | Purpose |
| :--- | :--- | :--- |
| **PROGRAM** | `程序` | Defines cognitive program scope |
| **DATA** | `数据` | Variable and BCD COMP-3 data section |
| **LOGIC** | `逻辑` | Procedure and execution logic block |
| **DEFINE** | `定义` | Variable declaration |
| **SHOW** | `显示` | Display output to stdout / terminal |
| **COMPUTE** | `计算` | High-precision arithmetic calculation |
| **IF / THEN / ELSE**| `如果 / 那么 / 否则` | Conditional branching |
| **PERFORM** | `执行` | Routine iteration or invocation |
| **MODULE** | `模块` | AI neural module registration |
| **BUS / SEND / RECEIVE** | `总线 / 发送 / 接收` | Inter-agent NeuroBUS communication |
| **COMPRESSED (COMP-3)** | `压缩` | 18-digit exact fixed-point BCD math |
| **SIMD-KNN** | `SIMD_KNN` | AVX2 SIMD vector search (0.82 ms latency) |
| **NEURAL-INSPECT** | `神经检查` | Introspective telemetry of network weights |

---

## 💻 Sample Program in Chinese / 中文

```cobol
程序 GENESIS_CORE.

数据
    定义 SALDO 作为 压缩(12,2).
    定义 ESTADO 作为 TEXTO.

逻辑
    显示 "Iniciando Nucleo NeuroCOBOL..."
    计算 SALDO = 1500.50 + 250.25
    显示 SALDO
    
    如果 SALDO > 1000 那么
        显示 "Nivel de liquidez verificado soberano."
    否则
        显示 "Alerta de liquidez."
    结束_如果

结束
```
