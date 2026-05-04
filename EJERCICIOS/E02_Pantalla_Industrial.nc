PROGRAMA PantallaIndustrial
// Ejercicio 2: Interfaz de Cristal (NXG V2)
// Objetivo: Declarar componentes visuales genesiss

DATOS
    TEXTO mensaje_clic = "Boton presionado en el silicio"

LOGICA
    // Declaracion de la ventana con estetica Genesis
    VENTANA PanelControl
        CAMPO Usuario "Introduce ID"
        BOTON Activar
            ON CLICK
                MOSTRAR mensaje_clic
                MOSTRAR "Comando enviado..."
            END_BUTTON
    FIN_VENTANA
    
    MOSTRAR "Interfaz de cristal desplegada."
FIN
