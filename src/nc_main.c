#include "nc_lexer.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: neurocobolc <archivo.nc>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = (char*)malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);

    printf("[NeuroCOBOL] Iniciando Analisis Lexico de %s...\n", argv[1]);
    printf("================================================\n");

    nc_lexer_init(source);
    
    Token token;
    do {
        token = nc_lexer_next_token();
        printf("[%03d] %-15s | %s\n", token.line, nc_token_type_to_string(token.type), token.text);
    } while (token.type != TOK_EOF);

    printf("================================================\n");
    printf("[NeuroCOBOL] Analisis finalizado con exito.\n");

    free(source);
    return 0;
}
