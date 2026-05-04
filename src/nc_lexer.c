#include "nc_lexer.h"
#include <string.h>
#include <ctype.h>

static const char* source_code;
static int current_pos = 0;
static int current_line = 1;

void nc_lexer_init(const char* source) {
    source_code = source;
    current_pos = 0;
    current_line = 1;
}

static char peek() {
    return source_code[current_pos];
}

static char advance() {
    char c = source_code[current_pos++];
    if (c == '\n') current_line++;
    return c;
}

static int is_at_end() {
    return source_code[current_pos] == '\0';
}

static void skip_whitespace() {
    while (!is_at_end()) {
        char c = peek();
        if (isspace(c)) {
            advance();
        } else if (c == '/' && source_code[current_pos + 1] == '/') {
            // Comentario
            while (peek() != '\n' && !is_at_end()) advance();
        } else {
            break;
        }
    }
}

static TokenType check_keyword(const char* word) {
    // SOPORTE MULTILINGÜE (ES/EN) CON PORTABILIDAD UNIVERSAL
    if (NC_STRICMP(word, "PROGRAMA") == 0 || NC_STRICMP(word, "PROGRAM") == 0) return TOK_PROGRAM;
    if (NC_STRICMP(word, "DATOS") == 0 || NC_STRICMP(word, "DATA") == 0) return TOK_DATA;
    if (NC_STRICMP(word, "LOGICA") == 0 || NC_STRICMP(word, "LOGIC") == 0) return TOK_LOGIC;
    if (NC_STRICMP(word, "FIN") == 0 || NC_STRICMP(word, "END") == 0) return TOK_END;
    if (NC_STRICMP(word, "DEFINIR") == 0 || NC_STRICMP(word, "DEFINE") == 0 || NC_STRICMP(word, "VAR") == 0) return TOK_DEFINE;
    if (NC_STRICMP(word, "COMO") == 0 || NC_STRICMP(word, "AS") == 0) return TOK_AS;
    if (NC_STRICMP(word, "MOSTRAR") == 0 || NC_STRICMP(word, "SHOW") == 0) return TOK_SHOW;
    if (NC_STRICMP(word, "SI") == 0 || NC_STRICMP(word, "IF") == 0) return TOK_IF;
    if (NC_STRICMP(word, "ENTONCES") == 0 || NC_STRICMP(word, "THEN") == 0) return TOK_THEN;
    if (NC_STRICMP(word, "SINO") == 0 || NC_STRICMP(word, "ELSE") == 0) return TOK_ELSE;
    if (NC_STRICMP(word, "FIN_SI") == 0 || NC_STRICMP(word, "END_IF") == 0) return TOK_END_IF;
    if (NC_STRICMP(word, "VENTANA") == 0 || NC_STRICMP(word, "WINDOW") == 0) return TOK_WINDOW;
    if (NC_STRICMP(word, "BOTON") == 0 || NC_STRICMP(word, "BUTTON") == 0) return TOK_BUTTON;
    if (NC_STRICMP(word, "CAMPO") == 0 || NC_STRICMP(word, "FIELD") == 0) return TOK_FIELD;
    if (NC_STRICMP(word, "AL") == 0 || NC_STRICMP(word, "ON") == 0) return TOK_ON;
    if (NC_STRICMP(word, "CLIC") == 0 || NC_STRICMP(word, "CLICK") == 0) return TOK_CLICK;
    if (NC_STRICMP(word, "FIN_VENTANA") == 0 || NC_STRICMP(word, "END_WINDOW") == 0) return TOK_END;
    if (NC_STRICMP(word, "FIN_BOTON") == 0 || NC_STRICMP(word, "END_BUTTON") == 0) return TOK_END;
    if (NC_STRICMP(word, "ABRIR") == 0 || NC_STRICMP(word, "OPEN") == 0) return TOK_OPEN;
    if (NC_STRICMP(word, "LEER") == 0 || NC_STRICMP(word, "READ") == 0) return TOK_READ;
    if (NC_STRICMP(word, "ESCRIBIR") == 0 || NC_STRICMP(word, "WRITE") == 0) return TOK_WRITE;
    if (NC_STRICMP(word, "CERRAR") == 0 || NC_STRICMP(word, "CLOSE") == 0) return TOK_CLOSE;
    if (NC_STRICMP(word, "ARCHIVO") == 0 || NC_STRICMP(word, "FILE") == 0) return TOK_FILE;
    if (NC_STRICMP(word, "REGISTRO") == 0 || NC_STRICMP(word, "RECORD") == 0) return TOK_RECORD;

    // --- NEUROBUS (V2.6) ---
    if (NC_STRICMP(word, "MODULO") == 0 || NC_STRICMP(word, "MODULE") == 0) return TOK_MODULE;
    if (NC_STRICMP(word, "BUS") == 0) return TOK_BUS;
    if (NC_STRICMP(word, "ENVIAR") == 0 || NC_STRICMP(word, "SEND") == 0) return TOK_SEND;
    if (NC_STRICMP(word, "RECIBIR") == 0 || NC_STRICMP(word, "RECEIVE") == 0) return TOK_RECEIVE;
    if (NC_STRICMP(word, "NITRO") == 0 || NC_STRICMP(word, "OVERDRIVE") == 0) return TOK_NITRO;
    if (NC_STRICMP(word, "IZQUIERDO") == 0 || NC_STRICMP(word, "LEFT") == 0) return TOK_LEFT;
    if (NC_STRICMP(word, "DERECHO") == 0 || NC_STRICMP(word, "RIGHT") == 0) return TOK_RIGHT;
    if (NC_STRICMP(word, "GLOBAL") == 0) return TOK_GLOBAL;
    
    // --- V2.7 INDUSTRIAL Y DEFENSA ---
    if (NC_STRICMP(word, "IMPORTAR") == 0 || NC_STRICMP(word, "IMPORT") == 0) return TOK_IMPORT;
    if (NC_STRICMP(word, "COMPRIMIDO") == 0 || NC_STRICMP(word, "COMPRESSED") == 0 || NC_STRICMP(word, "COMP-3") == 0) return TOK_COMPRESSED;
    if (NC_STRICMP(word, "DEFENSA") == 0 || NC_STRICMP(word, "DEFENSE") == 0) return TOK_DEFENSE;
    if (NC_STRICMP(word, "INTEGRIDAD") == 0 || NC_STRICMP(word, "INTEGRITY") == 0) return TOK_INTEGRITY;
    if (NC_STRICMP(word, "CRIPTOGRAFIA") == 0 || NC_STRICMP(word, "CRYPTO") == 0 || NC_STRICMP(word, "CRYPTOGRAPHY") == 0) return TOK_CRYPTO;
    if (NC_STRICMP(word, "AUTENTICACION") == 0 || NC_STRICMP(word, "AUTH") == 0 || NC_STRICMP(word, "AUTHENTICATION") == 0) return TOK_AUTH;

    if (NC_STRICMP(word, "ERROR") == 0) return TOK_ERROR;

    return TOK_IDENTIFIER;
}

const char* nc_token_type_to_string(TokenType type) {
    switch (type) {
        case TOK_PROGRAM: return "PROGRAM";
        case TOK_DATA: return "DATA";
        case TOK_LOGIC: return "LOGIC";
        case TOK_END: return "END";
        case TOK_DEFINE: return "DEFINE";
        case TOK_AS: return "AS";
        case TOK_SHOW: return "SHOW";
        case TOK_IF: return "IF";
        case TOK_THEN: return "THEN";
        case TOK_ELSE: return "ELSE";
        case TOK_END_IF: return "END_IF";
        case TOK_WINDOW: return "WINDOW";
        case TOK_BUTTON: return "BUTTON";
        case TOK_FIELD: return "FIELD";
        case TOK_ON: return "ON";
        case TOK_CLICK: return "CLICK";
        case TOK_OPEN: return "OPEN";
        case TOK_READ: return "READ";
        case TOK_WRITE: return "WRITE";
        case TOK_CLOSE: return "CLOSE";
        case TOK_FILE: return "FILE";
        case TOK_RECORD: return "RECORD";
        case TOK_MODULE: return "MODULE";
        case TOK_BUS: return "BUS";
        case TOK_SEND: return "SEND";
        case TOK_RECEIVE: return "RECEIVE";
        case TOK_NITRO: return "NITRO";
        case TOK_LEFT: return "LEFT";
        case TOK_RIGHT: return "RIGHT";
        case TOK_GLOBAL: return "GLOBAL";
        case TOK_IMPORT: return "IMPORT";
        case TOK_COMPRESSED: return "COMPRESSED";
        case TOK_DEFENSE: return "DEFENSE";
        case TOK_INTEGRITY: return "INTEGRITY";
        case TOK_CRYPTO: return "CRYPTO";
        case TOK_AUTH: return "AUTH";
        case TOK_ERROR: return "ERROR";
        case TOK_IDENTIFIER: return "IDENTIFIER";
        case TOK_STRING: return "STRING";
        case TOK_NUMBER: return "NUMBER";
        case TOK_EQUALS: return "EQUALS";
        case TOK_PLUS: return "PLUS";
        case TOK_MINUS: return "MINUS";
        case TOK_STAR: return "STAR";
        case TOK_SLASH: return "SLASH";
        case TOK_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

Token nc_lexer_next_token() {
    skip_whitespace();
    
    Token token;
    token.line = current_line;
    memset(token.text, 0, sizeof(token.text));
    
    if (is_at_end()) {
        token.type = TOK_EOF;
        strcpy(token.text, "EOF");
        return token;
    }
    
    char c = advance();
    
    if (isalpha(c) || c == '_') {
        int start = current_pos - 1;
        while (isalnum(peek()) || peek() == '_') advance();
        int length = current_pos - start;
        strncpy(token.text, source_code + start, length);
        token.type = check_keyword(token.text);
        return token;
    }
    
    if (isdigit(c)) {
        int start = current_pos - 1;
        while (isdigit(peek()) || peek() == '.') advance();
        int length = current_pos - start;
        strncpy(token.text, source_code + start, length);
        token.type = TOK_NUMBER;
        return token;
    }
    
    if (c == '"') {
        int start = current_pos;
        while (peek() != '"' && !is_at_end()) advance();
        int length = current_pos - start;
        strncpy(token.text, source_code + start, length);
        if (!is_at_end()) advance(); // Cerrar comillas
        token.type = TOK_STRING;
        return token;
    }
    
    // Operadores simples
    switch (c) {
        case '=': token.type = TOK_EQUALS; strcpy(token.text, "="); break;
        case '+': token.type = TOK_PLUS; strcpy(token.text, "+"); break;
        case '-': token.type = TOK_MINUS; strcpy(token.text, "-"); break;
        case '*': token.type = TOK_STAR; strcpy(token.text, "*"); break;
        case '/': token.type = TOK_SLASH; strcpy(token.text, "/"); break;
        default: token.type = TOK_UNKNOWN; token.text[0] = c; break;
    }
    
    return token;
}
