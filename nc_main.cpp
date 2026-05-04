#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "src/nc_parser.h"

// Enlace con el puente C++ (Bridge)
extern "C" void nc_execute_neuro(ASTNode* tree);
extern "C" void nc_generate_gxp_bundle(ASTNode* tree, const char* name);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "[NeuroCOBOL-V2] Uso: neurocobolc <archivo.nc> [-gxp]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    bool generateGXP = false;

    if (argc >= 3 && std::string(argv[2]) == "-gxp") {
        generateGXP = true;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir: " << filename << std::endl;
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::cout << "[NeuroCOBOL-V2] Iniciando Compilacion Soberana de " << filename << "..." << std::endl;

    ASTNode* ast = nc_parse(source.c_str());
    if (ast) {
        std::cout << "[OK] Arbol de Sintaxis Abstracta (AST) generado." << std::endl;

        if (generateGXP) {
            std::cout << "[INFO] Generando Paquete GXP (Industrial Deployment)..." << std::endl;
            // Usamos el nombre del programa del AST o el nombre del archivo
            std::string pkgName = ast->text;
            if (pkgName.empty()) pkgName = "NeuroApp";
            nc_generate_gxp_bundle(ast, pkgName.c_str());
        } else {
            std::cout << "[INFO] Ejecutando Inyeccion Neural Directa (Hot Reload)..." << std::endl;
            nc_execute_neuro(ast);
        }

        nc_free_ast(ast);
    } else {
        std::cerr << "[ERROR] Fallo en el analisis sintactico." << std::endl;
    }

    return 0;
}
