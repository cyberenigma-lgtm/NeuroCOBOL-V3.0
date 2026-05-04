# 🏛️ Capítulo 3: I/O Industrial e Integridad de Datos
### *La Persistencia de la Voluntad en Genesis OS*

En Genesis OS, los datos no son efímeros; son registros persistentes dentro del **GFS (Genesis File System)**. NeuroCOBOL permite al arquitecto gestionar archivos con la precisión de un sistema bancario industrial mediante opcodes de bajo nivel (`0xE0`).

---

## 🟦 1. Teoría y Conceptos: El Sistema de Archivos GFS
A diferencia de los sistemas de archivos convencionales, el **GFS** de Genesis OS está diseñado para ser:
- **Resiliente**: Protección contra fallos neurales del sistema.
- **Trazable**: Cada escritura es una señal que puede ser auditada en el NeuroBUS.
- **Estructurado**: Basado en registros fijos que facilitan la migración desde COBOL Legacy.

---

## 🟩 2. Manual de Referencia de Comandos (I/O)

### **A. Apertura de Canal**
- **Sintaxis**: `ABRIR ARCHIVO "[Ruta]"`
- **Modo de Uso**: Conecta el programa con el almacenamiento. Si el archivo no existe, Genesis OS inicia el protocolo de creación.
- **Impacto**: Genera el opcode `0xE0 (io_open)` en el GXP.

### **B. Captura de Datos (LEER)**
- **Sintaxis**: `LEER ARCHIVO [Registro]`
- **Modo de Uso**: Transfiere información del silicio a la memoria del programa.

### **C. Inyección de Persistencia (ESCRIBIR)**
- **Sintaxis**: `ESCRIBIR ARCHIVO [Registro]`
- **Modo de Uso**: Vuelca la voluntad del programa en el GFS.

### **D. Sellado Industrial (CERRAR)**
- **Sintaxis**: `CERRAR ARCHIVO`
- **Modo de Uso**: Acción obligatoria para liberar el canal y asegurar la persistencia.

---

## ⚠️ 3. Diccionario de Errores Industriales
El I/O es el punto donde el programa interactúa con el mundo físico del almacenamiento.

### 🟥 Error A: "Fuga de Manijas" (Missing CERRAR)
- **Signo**: Genesis OS indica que el archivo está "bloqueado" o "en uso" por otro proceso después de que el programa termina.
- **Causa**: Falta el comando `CERRAR ARCHIVO`.
- **Solución**: Siempre cierra cada archivo abierto antes del `FIN`.

### 🟥 Error B: "Lectura en el Vacío" (Leer sin Abrir)
- **Signo**: `[ERROR] Sistema: El canal 0 no es válido para lectura`.
- **Causa**: Intentar `LEER` antes de llamar a `ABRIR ARCHIVO`.
- **Solución**: Asegúrate de que el flujo de comandos respeta el orden lógico: Abrir -> Operar -> Cerrar.

---

## 📖 4. Glosario Específico: Capítulo 3
- **GFS (Genesis File System)**: El sistema de archivos genesis de Genesis OS.
- **REGISTRO**: Unidad mínima de información persistente en disco.
- **IO_HANDLE**: Identificador temporal que el sistema operativo asigna a un archivo abierto para su seguimiento cognitivo.
- **CRITICAL DATA**: Nivel de integridad máximo para registros en el GFS.

---

## 🏅 Examen de Ciudadanía III (Desafío de Persistencia)
**Misión**: Este programa de auditoría está fallando y bloqueando los archivos de Genesis OS. Tu tarea es corregirlo para que sea seguro.

### Código Corrupto:
```neurocobol
PROGRAMA Auditor
DATOS
    TEXTO reporte = "SISTEMA_OK"
LOGICA
    LEER ARCHIVO "config.bin"
    ABRIR ARCHIVO "auditoria.log"
    ESCRIBIR ARCHIVO reporte
FIN
```

> [!TIP]
> **Pista**: Hay un orden lógico invertido en la lectura y falta el comando crucial de sellado del archivo.

---
*Felicidades, Arquitecto. Los datos de Genesis OS están seguros bajo vuestra voluntad.*
