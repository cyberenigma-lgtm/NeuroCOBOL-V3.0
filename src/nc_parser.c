#include "nc_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Token current_token;
static int in_ai_module = 0; // Rastreo de estado para validacion de bus
static int defense_integrity_loaded = 0;
static int defense_crypto_loaded = 0;
static int defense_auth_loaded = 0;

static ASTNode* create_node(ASTNodeType type, const char* text) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    memset(node->text, 0, sizeof(node->text));
    if (text) strncpy(node->text, text, sizeof(node->text) - 1);
    node->left = node->right = node->next = NULL;
    return node;
}

static void consume(TokenType type) {
    if (current_token.type == type) {
        current_token = nc_lexer_next_token();
    } else {
        printf("[ERROR] Sintaxis en linea %d: se esperaba %s, se recibio %s (%s)\n", 
               current_token.line, nc_token_type_to_string(type), 
               nc_token_type_to_string(current_token.type), current_token.text);
        current_token = nc_lexer_next_token(); // Intentar recuperar
    }
}

// Prototipos locales
static ASTNode* parse_statement();
static ASTNode* parse_logic_block();
static ASTNode* parse_ui_element();
static ASTNode* parse_file_statement();

static ASTNode* parse_expression() {
    if (current_token.type == TOK_STRING) {
        ASTNode* node = create_node(NODE_STRING_LITERAL, current_token.text);
        consume(TOK_STRING);
        return node;
    } else if (current_token.type == TOK_IDENTIFIER) {
        // --- VALIDACION DE SEGURIDAD SOBERANA (V2.7) ---
        if (strcmp(current_token.text, "VERIFICAR_PARIDAD") == 0 || 
            strcmp(current_token.text, "FIRMAR") == 0 || 
            strcmp(current_token.text, "VALIDAR_FIRMA") == 0) {
            if (!defense_integrity_loaded) {
                printf("[ERROR CRITICO] Integridad Soberana: Intento de usar DEFENSA.INTEGRIDAD sin IMPORTAR.\n");
            }
        } else if (strcmp(current_token.text, "CIFRAR") == 0 || 
                   strcmp(current_token.text, "DESCIFRAR") == 0 || 
                   strcmp(current_token.text, "HASH") == 0) {
            if (!defense_crypto_loaded) {
                printf("[ERROR CRITICO] Integridad Soberana: Intento de usar DEFENSA.CRIPTOGRAFIA sin IMPORTAR.\n");
            }
        } else if (strcmp(current_token.text, "VERIFICAR_MODULO") == 0 || 
                   strcmp(current_token.text, "ES_CIUDADANO") == 0) {
            if (!defense_auth_loaded) {
                printf("[ERROR CRITICO] Integridad Soberana: Intento de usar DEFENSA.AUTENTICACION sin IMPORTAR.\n");
            }
        }

        ASTNode* node = create_node(NODE_IDENTIFIER, current_token.text);
        consume(TOK_IDENTIFIER);
        return node;
    }
    return NULL;
}

static ASTNode* parse_ui_element() {
    if (current_token.type == TOK_WINDOW) {
        consume(TOK_WINDOW);
        char winName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(winName, current_token.text, sizeof(winName)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* node = create_node(NODE_WINDOW, winName);
        
        ASTNode* head = NULL;
        ASTNode* current = NULL;
        while (current_token.type != TOK_END && current_token.type != TOK_END_WINDOW && current_token.type != TOK_EOF) {
            if (current_token.type == TOK_END || current_token.type == TOK_END_WINDOW) break;

            ASTNode* item = parse_ui_element();
            if (!item) item = parse_statement();
            
            if (item) {
                if (!head) head = item;
                else current->next = item;
                current = item;
            } else {
                 current_token = nc_lexer_next_token();
            }
        }
        node->right = head;
        if (current_token.type == TOK_END_WINDOW) {
            consume(TOK_END_WINDOW);
        } else {
            consume(TOK_END);
            if (current_token.type == TOK_IDENTIFIER && NC_STRICMP(current_token.text, "VENTANA") == 0) {
                consume(TOK_IDENTIFIER);
            }
        }
        return node;
    } else if (current_token.type == TOK_BUTTON) {
        consume(TOK_BUTTON);
        char btnText[64] = {0};
        if (current_token.type == TOK_STRING) {
            strncpy(btnText, current_token.text, sizeof(btnText)-1);
            consume(TOK_STRING);
        } else if (current_token.type == TOK_IDENTIFIER) {
            strncpy(btnText, current_token.text, sizeof(btnText)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* node = create_node(NODE_BUTTON, btnText);
        
        if (current_token.type == TOK_ON) {
            consume(TOK_ON);
            consume(TOK_CLICK);
        }
        
        node->right = parse_logic_block();
        if (current_token.type == TOK_END_BUTTON) {
            consume(TOK_END_BUTTON);
        } else {
            consume(TOK_END);
            if (current_token.type == TOK_IDENTIFIER && NC_STRICMP(current_token.text, "BOTON") == 0) {
                consume(TOK_IDENTIFIER);
            }
        }
        return node;
    } else if (current_token.type == TOK_FIELD) {
        consume(TOK_FIELD);
        char fieldName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(fieldName, current_token.text, sizeof(fieldName)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* node = create_node(NODE_FIELD, fieldName);
        consume(TOK_AS);
        consume(TOK_IDENTIFIER); // TIPO
        return node;
    }
    return NULL;
}

static ASTNode* parse_file_statement() {
    if (current_token.type == TOK_OPEN) {
        consume(TOK_OPEN);
        consume(TOK_FILE);
        char fname[64] = {0};
        if (current_token.type == TOK_STRING || current_token.type == TOK_IDENTIFIER) {
            strncpy(fname, current_token.text, sizeof(fname)-1);
            consume(current_token.type);
        }
        ASTNode* node = create_node(NODE_OPEN, fname);
        return node;
    } else if (current_token.type == TOK_READ) {
        consume(TOK_READ);
        consume(TOK_FILE);
        char regName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(regName, current_token.text, sizeof(regName)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* node = create_node(NODE_READ, regName);
        return node;
    } else if (current_token.type == TOK_WRITE) {
        consume(TOK_WRITE);
        consume(TOK_FILE);
        char regName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(regName, current_token.text, sizeof(regName)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* node = create_node(NODE_WRITE, regName);
        return node;
    } else if (current_token.type == TOK_CLOSE) {
        consume(TOK_CLOSE);
        consume(TOK_FILE);
        return create_node(NODE_CLOSE, "CLOSE");
    } else if (current_token.type == TOK_MODULE) {
        consume(TOK_MODULE);
        char type[32] = "GENERIC";
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(type, current_token.text, 31);
            consume(TOK_IDENTIFIER);
        }
        char hemi[32] = "GLOBAL";
        if (current_token.type == TOK_LEFT || current_token.type == TOK_RIGHT || current_token.type == TOK_GLOBAL) {
            strncpy(hemi, current_token.text, 31);
            consume(current_token.type);
        }
        char composite[128];
        snprintf(composite, sizeof(composite), "%s:%s", type, hemi);
        in_ai_module = 1; // Registro de estado activo
        return create_node(NODE_MODULE_DECL, composite);
    } else if (current_token.type == TOK_SEND) {
        consume(TOK_SEND);
        consume(TOK_BUS);
        ASTNode* expr = parse_expression();
        
        // --- VALIDACION SOBERANA DE ERRORES ---
        if (expr && expr->type == NODE_STRING_LITERAL) {
            // Un literal de cadena vacio es "" (longitud 0 o solo comillas)
            if (strlen(expr->text) == 0 || strcmp(expr->text, "\"\"") == 0) {
                if (in_ai_module) {
                    printf("[ERROR] Integridad: Mensaje de BUS vacio enviado a MODULO IA. Bloqueando ruido cognitivo.\n");
                } else {
                    printf("[WARNING] Semantica: Mensaje de BUS vacio detectado. Ineficiencia detectada.\n");
                }
            }
        }
        
        ASTNode* node = create_node(NODE_BUS_SEND, "SEND");
        node->left = expr;
        return node;
    } else if (current_token.type == TOK_RECEIVE) {
        consume(TOK_RECEIVE);
        consume(TOK_BUS);
        char varName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(varName, current_token.text, 63);
            consume(TOK_IDENTIFIER);
        }
        return create_node(NODE_BUS_RECV, varName);
    } else if (current_token.type == TOK_NITRO) {
        consume(TOK_NITRO);
        return create_node(NODE_NITRO, "NITRO");
    }
    return NULL;
}

static ASTNode* parse_statement() {
    if (current_token.type == TOK_SHOW) {
        consume(TOK_SHOW);
        ASTNode* node = create_node(NODE_SHOW, "SHOW");
        node->left = parse_expression();
        return node;
    } else if (current_token.type == TOK_IF) {
        consume(TOK_IF);
        ASTNode* node = create_node(NODE_IF, "IF");
        node->left = parse_expression();
        if (current_token.type == TOK_EQUALS) {
            consume(TOK_EQUALS);
            node->left->right = parse_expression();
        }
        consume(TOK_THEN);
        node->right = parse_logic_block();
        if (current_token.type == TOK_END_IF) {
            consume(TOK_END_IF);
        } else if (current_token.type == TOK_END) {
             consume(TOK_END);
        }
        return node;
    } else if (current_token.type == TOK_WINDOW || current_token.type == TOK_BUTTON || current_token.type == TOK_FIELD) {
        return parse_ui_element();
    } else if (current_token.type == TOK_OPEN || current_token.type == TOK_READ || current_token.type == TOK_WRITE || current_token.type == TOK_CLOSE) {
        return parse_file_statement();
    }
    return NULL;
}

static ASTNode* parse_logic_block() {
    ASTNode* head = NULL;
    ASTNode* current = NULL;
    
    while (current_token.type != TOK_END && current_token.type != TOK_END_IF && current_token.type != TOK_EOF) {
        ASTNode* stmt = parse_statement();
        if (stmt) {
            if (!head) head = stmt;
            else current->next = stmt;
            current = stmt;
        } else {
            break;
        }
    }
    return head;
}

ASTNode* nc_parse(const char* source) {
    nc_lexer_init(source);
    current_token = nc_lexer_next_token();
    
    if (current_token.type == TOK_PROGRAM) {
        consume(TOK_PROGRAM);
        char progName[64] = {0};
        if (current_token.type == TOK_IDENTIFIER) {
            strncpy(progName, current_token.text, sizeof(progName)-1);
            consume(TOK_IDENTIFIER);
        }
        ASTNode* prog = create_node(NODE_PROGRAM, progName);
        
        while (current_token.type != TOK_EOF) {
            if (current_token.type == TOK_IMPORT) {
                consume(TOK_IMPORT);
                if (current_token.type == TOK_DEFENSE) {
                    consume(TOK_DEFENSE);
                    // Soporte para DEFENSA.MODULO
                    if (current_token.type == TOK_UNKNOWN && strcmp(current_token.text, ".") == 0) {
                        consume(TOK_UNKNOWN); // Consumir punto
                    }
                    if (current_token.type == TOK_INTEGRITY) {
                        defense_integrity_loaded = 1;
                        consume(TOK_INTEGRITY);
                    } else if (current_token.type == TOK_CRYPTO) {
                        defense_crypto_loaded = 1;
                        consume(TOK_CRYPTO);
                    } else if (current_token.type == TOK_AUTH) {
                        defense_auth_loaded = 1;
                        consume(TOK_AUTH);
                    }
                }
                ASTNode* impNode = create_node(NODE_IMPORT, "IMPORT");
                if (!prog->left) prog->left = impNode;
                else {
                    ASTNode* tmp = prog->left;
                    while(tmp->next) tmp = tmp->next;
                    tmp->next = impNode;
                }
            } else if (current_token.type == TOK_DATA) {
                consume(TOK_DATA);
                while (current_token.type != TOK_LOGIC && current_token.type != TOK_EOF) {
                    if (current_token.type == TOK_DEFINE) {
                        consume(TOK_DEFINE);
                        ASTNode* decl = create_node(NODE_DEFINE, current_token.text);
                        consume(TOK_IDENTIFIER);
                        consume(TOK_AS);
                        consume(TOK_IDENTIFIER); // Tipo base (NUMERO)
                        
                        if (current_token.type == TOK_COMPRESSED) {
                            consume(TOK_COMPRESSED);
                            decl->type = NODE_COMPRESSED_DATA;
                            // Capturar precisión (ej: 9(12)V99 como identificador/texto)
                            if (current_token.type == TOK_IDENTIFIER || current_token.type == TOK_NUMBER) {
                                consume(current_token.type);
                            }
                        }

                        if (current_token.type == TOK_EQUALS) {
                            consume(TOK_EQUALS);
                            decl->left = parse_expression();
                        }
                        if (!prog->left) prog->left = decl;
                        else {
                            ASTNode* tmp = prog->left;
                            while(tmp->next) tmp = tmp->next;
                            tmp->next = decl;
                        }
                    } else {
                        current_token = nc_lexer_next_token();
                    }
                }
            } else if (current_token.type == TOK_LOGIC) {
                consume(TOK_LOGIC);
                prog->right = parse_logic_block();
            } else if (current_token.type == TOK_END) {
                consume(TOK_END);
                break;
            } else {
                current_token = nc_lexer_next_token();
            }
        }
        return prog;
    }
    return NULL;
}

void nc_free_ast(ASTNode* node) {
    if (!node) return;
    nc_free_ast(node->left);
    nc_free_ast(node->right);
    nc_free_ast(node->next);
    free(node);
}


