PROGRAMA HolaMundo
DATOS
    DEFINIR mensaje COMO TEXTO = "Hola, mundo genesis"
LOGICA
    // INTENCION:
    // Mostrar un saludo en pantalla

    // CONTRATO:
    // - mensaje no debe estar vacío

    SI mensaje = "" ENTONCES
        ERROR "Mensaje vacío"
    FIN_SI

    MOSTRAR mensaje
FIN
