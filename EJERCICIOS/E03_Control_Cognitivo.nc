PROGRAMA ControlCognitivo
// Ejercicio 3: El Sistema Nervioso (NeuroBUS)
// Objetivo: Orquestar modulos de IA y activar el modo Nitro

DATOS
    TEXTO comando = "Iniciación de protocolo genesis"
    TEXTO respuesta = "RESPUESTA_BUS"

LOGICA
    // Registro explicito como modulo de IA en el hemisferio izquierdo (Logica)
    MODULO SEGURIDAD IZQUIERDO
    
    MOSTRAR "Conectando al NeuroBUS..."
    
    // Envío de señal al sistema
    ENVIAR BUS comando
    
    // Captura de respuesta del sistema
    RECIBIR BUS respuesta
    
    // El comando de soberanía definitiva
    ACTIVAR NITRO
    
    MOSTRAR "Sistema en modo Overdrive (Nitro activo)"
FIN
