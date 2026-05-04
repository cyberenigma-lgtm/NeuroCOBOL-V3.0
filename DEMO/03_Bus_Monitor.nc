PROGRAMA MonitorNucleo

DATOS
    MODULO SEGURIDAD:GLOBAL
    TEXTO alerta
FIN

LOGICA
    RECIBIR BUS alerta
    SI alerta = "ATTACK_V2"
        NITRO // Activar defensa maxima
        MOSTRAR "Pulsacion Neural Detectada: Contraataque Activo."
    FIN
FIN
