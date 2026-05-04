PROGRAMA PanelControl
DATOS
    VENTANA pnlInmunidad "Consola de Defensa v2.7"
        BOTON "Auditar Silicio" AL CLIC
            MOSTRAR "Iniciando Auditoria..."
            ENVIAR BUS "SCAN_HARDWARE"
        FIN
    FIN
FIN

LOGICA
    ABRIR VENTANA pnlInmunidad
FIN
