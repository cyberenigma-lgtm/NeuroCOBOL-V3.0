#include "nc_parser.h"
#include "nc_gxp_builder.h"
#include "../../Neurowill-Code-NWC/nwcore/bridge.h"
#include <iostream>
#include <string>

namespace NeuroCOBOL {

class CompilerBridge {
public:
    CompilerBridge() : m_lang("es") {}

    void SetLanguage(const std::string& lang) { m_lang = lang; }

    // Ejecucion inmediata (Inyeccion en Caliente)
    void CompileAndExecute(ASTNode* node) {
        if (!node) return;
        GenerateWill(node);
        std::cout << "[NeuroCOBOL-NWC] Inyectando Voluntad al Silicio..." << std::endl;
        m_nwc.Execute();
    }

    // Generacion de Paquete Industrial (GXP)
    void CompileToGXP(ASTNode* node, const std::string& pkgName) {
        if (!node) return;
        GenerateWill(node);
        std::string gxpFile = pkgName + ".gxp";
        GXPBuilder::Generate(gxpFile, pkgName, m_nwc.GetBytecode());
    }

private:
    NWC::NeuralBinaryBridge m_nwc;
    std::string m_lang;

    void GenerateWill(ASTNode* node) {
        if (!node) return;

        switch (node->type) {
            case NODE_PROGRAM: {
                std::cout << "[NeuroCOBOL-NWC] Procesando Programa Genesis: " << node->text << std::endl;
                // --- MODELO HIBRIDO: Registro automatico de bus como ciudadano ---
                m_nwc.TranslateWill((m_lang == "es" ? "bus init" : "bus init"), m_lang);
                
                if (node->left) GenerateWill(node->left);   // Bloque DATA
                if (node->right) GenerateWill(node->right); // Bloque LOGIC
                break;
            }

            case NODE_DEFINE:
                std::cout << "[NeuroCOBOL-NWC] Definiendo Variable: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "definir " : "define ") + std::string(node->text), m_lang);
                break;

            case NODE_COMPRESSED_DATA:
                std::cout << "[NeuroCOBOL-NWC] Definiendo Variable INDUSTRIAL (BCD): " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "bcd_def " : "bcd_def ") + std::string(node->text), m_lang);
                break;

            case NODE_IMPORT:
                std::cout << "[NeuroCOBOL-NWC] Vinculando Biblioteca de Defensa: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "vincular_defensa " : "link_defense ") + std::string(node->text), m_lang);
                break;

            case NODE_SHOW:
                if (node->left) {
                    std::string cmd = (m_lang == "es") ? "enseña " : "show ";
                    if (node->left->type == NODE_STRING_LITERAL) {
                        cmd += "\"" + std::string(node->left->text) + "\"";
                    } else {
                        cmd += node->left->text;
                    }
                    m_nwc.TranslateWill(cmd, m_lang);
                }
                break;

            case NODE_IF:
                std::cout << "[NeuroCOBOL-NWC] Intencion Neural (IF): " << node->left->text << std::endl;
                {
                    std::string cond = node->left->text;
                    if (node->left->right) {
                         cond += " = ";
                         cond += node->left->right->text;
                    }
                    m_nwc.TranslateWill((m_lang == "es" ? "si " : "if ") + cond, m_lang);
                }
                if (node->right) GenerateWill(node->right); 
                break;

            case NODE_WINDOW:
                std::cout << "[NeuroCOBOL-NWC] Creando Ventana Soberana: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "ventana " : "window ") + std::string(node->text), m_lang);
                if (node->right) GenerateWill(node->right); // Elementos de UI internos
                break;

            case NODE_BUTTON:
                std::cout << "[NeuroCOBOL-NWC] Creando Boton Interactivo: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "boton " : "button ") + std::string(node->text), m_lang);
                if (node->right) GenerateWill(node->right); // Codigo AL HACER CLIC
                break;

            case NODE_FIELD:
                std::cout << "[NeuroCOBOL-NWC] Creando Campo de Texto: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "campo " : "field ") + std::string(node->text), m_lang);
                break;

            case NODE_OPEN:
                std::cout << "[NeuroCOBOL-NWC] Abriendo Archivo Genesis: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "archivo abrir " : "file open ") + std::string(node->text), m_lang);
                break;

            case NODE_READ:
                std::cout << "[NeuroCOBOL-NWC] Leyendo Registro: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "archivo leer " : "file read ") + std::string(node->text), m_lang);
                break;

            case NODE_WRITE:
                std::cout << "[NeuroCOBOL-NWC] Escribiendo Registro: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "archivo escribir " : "file write ") + std::string(node->text), m_lang);
                break;

            case NODE_CLOSE:
                std::cout << "[NeuroCOBOL-NWC] Cerrando Archivo Industrial" << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "archivo cerrar" : "file close"), m_lang);
                break;

            case NODE_MODULE_DECL: {
                std::cout << "[NeuroCOBOL-NWC] Registrando Modulo de IA: " << node->text << std::endl;
                // Formato "TIPO:HEMISFERIO"
                m_nwc.TranslateWill((m_lang == "es" ? "bus registrar " : "bus register ") + std::string(node->text), m_lang);
                break;
            }

            case NODE_BUS_SEND: {
                std::string msg = "MSG";
                if (node->left && node->left->type == NODE_STRING_LITERAL) msg = node->left->text;
                std::cout << "[NeuroCOBOL-NWC] Enviando al Bus: " << msg << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "bus enviar " : "bus send ") + msg, m_lang);
                break;
            }

            case NODE_BUS_RECV:
                std::cout << "[NeuroCOBOL-NWC] Recibiendo del Bus en: " << node->text << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "bus recibir " : "bus receive ") + std::string(node->text), m_lang);
                break;

            case NODE_NITRO:
                std::cout << "[NeuroCOBOL-NWC] ACTIVANDO OVERDRIVE (NITRO)" << std::endl;
                m_nwc.TranslateWill((m_lang == "es" ? "bus nitro" : "bus nitro"), m_lang);
                break;

            case NODE_BLOCK:
                if (node->left) GenerateWill(node->left);
                break;

            case NODE_IDENTIFIER:
            case NODE_STRING_LITERAL:
            case NODE_DATA:
            case NODE_LOGIC:
            case NODE_ELSE:
            case NODE_ERROR:
                // Estos nodos se procesan como hijos de otros comandos
                break;
        }

        if (node->next) GenerateWill(node->next);
    }
};

} // namespace NeuroCOBOL

extern "C" void nc_execute_neuro(ASTNode* tree) {
    NeuroCOBOL::CompilerBridge bridge;
    bridge.CompileAndExecute(tree);
}

extern "C" void nc_generate_gxp_bundle(ASTNode* tree, const char* name) {
    NeuroCOBOL::CompilerBridge bridge;
    bridge.CompileToGXP(tree, name);
}
