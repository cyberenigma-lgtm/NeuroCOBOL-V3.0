#include "nc_lexer.h"
#include "nc_parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Prototipo de la pasarela C++
extern "C" void nc_execute_neuro(ASTNode* tree);

// No definir nc_token_type_to_string aqui, esta en nc_lexer.c

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: neurocobolc <archivo.nc> [--lang es|en]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string lang = "es";

    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--lang" && i + 1 < argc) {
            lang = argv[++i];
        }
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    file.close();

    std::cout << "[NeuroCOBOL-V2] Iniciando Compilacion Soberana de " << filename << "..." << std::endl;
    std::cout << "[INFO] Perfil: STANDARD | Lenguaje: " << lang << std::endl;
    std::cout << "================================================" << std::endl;

    nc_lexer_init(source.c_str());

    ASTNode* tree = nc_parse();
    if (!tree) {
        std::cerr << "[ERROR] Fallo en el analisis sintactico. Revisar gramatica." << std::endl;
        return 1;
    }
    std::cout << "[OK] Arbol de Sintaxis Abstracta (AST) generado." << std::endl;

    std::cout << "[INFO] Invocando NeuralBinaryBridge (NWC)..." << std::endl;
    nc_execute_neuro(tree);

    nc_ast_free(tree);

    std::cout << "================================================" << std::endl;
    std::cout << "[EXITO] Proceso genesis finalizado." << std::endl;

    return 0;
}
