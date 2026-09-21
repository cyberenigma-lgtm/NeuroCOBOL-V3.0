#ifndef NC_LEXER_H
#define NC_LEXER_H

#include <stdio.h>
#include <string.h>

// MACRO DE PORTABILIDAD UNIVERSAL
#ifdef _WIN32
#define NC_STRICMP _stricmp
#else
#define NC_STRICMP strcasecmp
#endif

typedef enum {
    TOK_PROGRAM,    // PROGRAMA / PROGRAM
    TOK_DATA,       // DATOS / DATA
    TOK_LOGIC,      // LOGICA / LOGIC
    TOK_END,        // FIN / END
    TOK_DEFINE,     // DEFINIR / DEFINE / VAR
    TOK_AS,         // COMO / AS
    TOK_SHOW,       // MOSTRAR / SHOW
    TOK_IF,         // SI / IF
    TOK_THEN,       // ENTONCES / THEN
    TOK_ELSE,       // SINO / ELSE
    TOK_END_IF,     // FIN_SI / END_IF
    TOK_WINDOW,     // VENTANA / WINDOW
    TOK_BUTTON,     // BOTON / BUTTON
    TOK_END_WINDOW, // FIN_VENTANA / END_WINDOW
    TOK_END_BUTTON, // FIN_BOTON / END_BUTTON
    TOK_FIELD,      // CAMPO / FIELD
    TOK_ON,         // AL / ON
    TOK_CLICK,      // CLIC / CLICK
    TOK_OPEN,       // ABRIR / OPEN
    TOK_READ,       // LEER / READ
    TOK_WRITE,      // ESCRIBIR / WRITE
    TOK_CLOSE,      // CERRAR / CLOSE
    TOK_FILE,       // ARCHIVO / FILE
    TOK_RECORD,     // REGISTRO / RECORD
    TOK_MODULE,     // MODULO / MODULE
    TOK_BUS,        // BUS
    TOK_SEND,       // ENVIAR / SEND
    TOK_RECEIVE,    // RECIBIR / RECEIVE
    TOK_NITRO,      // NITRO / OVERDRIVE
    TOK_LEFT,       // IZQUIERDO / LEFT
    TOK_RIGHT,      // DERECHO / RIGHT
    TOK_GLOBAL,     // GLOBAL
    
    // V2.7 - Industrial y Defensa
    TOK_IMPORT,     // IMPORTAR / IMPORT
    TOK_COMPRESSED, // COMPRIMIDO / COMPRESSED / COMP-3
    TOK_DEFENSE,    // DEFENSA / DEFENSE
    TOK_INTEGRITY,  // INTEGRIDAD / INTEGRITY
    TOK_CRYPTO,     // CRIPTOGRAFIA / CRYPTO
    TOK_AUTH,       // AUTENTICACION / AUTH
    
    TOK_ERROR,      // ERROR
    TOK_IDENTIFIER, // Nombres de variables, etc.
    TOK_STRING,     // "Texto"
    TOK_NUMBER,     // 123, 45.6
    TOK_EQUALS,     // =
    TOK_PLUS,       // +
    TOK_MINUS,      // -
    TOK_STAR,       // *
    TOK_SLASH,      // /
    TOK_COMMENT,    // // ... (Intención/Contrato)
    TOK_EOF,        // Fin del archivo
    TOK_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char text[256];
    int line;
} Token;

// Funciones del Lexer
void nc_lexer_init(const char* source);
Token nc_lexer_next_token();
const char* nc_token_type_to_string(TokenType type);

#endif
