// NEUROCOBOL V2.5 - EJEMPLO MAESTRO INDUSTRIAL
// Propiedad de Neuro-OS Genesis

PROGRAMA GenesisIndustrial
DATOS
    DEFINIR usuario COMO TEXTO = "José"
    DEFINIR saldo_actual COMO NUMERO = 2500
    DEFINIR archivo_banca COMO TEXTO = "banca_soberana.dat"
LOGICA
    MOSTRAR "Iniciando Sistema de Gestion Bancaria..."
    
    VENTANA PanelPrincipal
        MOSTRAR "Consola de Administracion - Usuario: " + usuario
        
        CAMPO EntradaSaldo COMO NUMERO
        
        BOTON "GUARDAR TRANSACCION" AL CLIC
            ABRIR ARCHIVO archivo_banca
            ESCRIBIR ARCHIVO saldo_actual
            CERRAR ARCHIVO
            MOSTRAR "Transaccion persistida en GFS"
        FIN_BOTON
        
        BOTON "RESTAURAR SALDO" AL CLIC
            ABRIR ARCHIVO archivo_banca
            LEER ARCHIVO saldo_actual
            CERRAR ARCHIVO
            MOSTRAR "Saldo recuperado con exito"
        FIN_BOTON
        
    FIN_VENTANA

    MOSTRAR "Programa GenesisFinalizado."
FIN
