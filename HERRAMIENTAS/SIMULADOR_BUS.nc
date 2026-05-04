PROGRAMA SimuladorHemisferios
// HERRAMIENTA: SIMULADOR_BUS.nc
// OBJETIVO: Monitoreo visual del NeuroBUS en tiempo real

DATOS
    TEXTO log_bus = "ESPERANDO SEÑALES..."
    TEXTO estado_izq = "IDLE"
    TEXTO estado_der = "IDLE"

LOGICA
    // Paso 1: Registro como Monitor de Sistema
    MODULO MONITOR GLOBAL
    
    MOSTRAR "Iniciando Simulador de Hemisferios Genesis v2.7..."
    ENVIAR BUS "SIMULATOR_READY"
    
    // Paso 2: Interfaz Visual NXG V2
    VENTANA TableroControl
        MOSTRAR "MONITOR DE NEUROBUS GENESIS"
        
        CAMPO log_bus AS "TRAFICO_BUS"
        
        BOTON Refrescar
            ON CLICK
                RECIBIR BUS log_bus
                MOSTRAR "Señales capturadas del bus."
            END_BUTTON
            
        BOTON Limpiar
            ON CLICK
                log_bus = "REINICIANDO..."
            END_BUTTON
    FIN_VENTANA
    
    // --- Lógica de Simulación de Hemisferios ---
    SI log_bus = "IZQ_ALERTA" ENTONCES
        estado_izq = "ACTIVE"
    FIN_SI
    
    SI log_bus = "DER_CRITICAL" ENTONCES
        estado_der = "OVERDRIVE"
    FIN_SI

    MOSTRAR "Simulacion de Red Neuronal ACTIVA."
FIN
