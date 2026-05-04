PROGRAMA TestFalloSeguridad
// OBJETIVO: Verificar el bloqueo de seguridad V2.7
// Este programa DEBE fallar al compilar por falta de IMPORTAR.

LOGICA
    MOSTRAR "Intentando operacion protegida sin permiso..."
    
    // Intento de usar INTEGRIDAD sin IMPORTAR
    VERIFICAR_PARIDAD "Señal sensible"
    
    MOSTRAR "Si ves esto, la seguridad ha fallado."
FIN
