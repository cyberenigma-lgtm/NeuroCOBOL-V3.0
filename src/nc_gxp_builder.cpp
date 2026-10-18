#include "nc_gxp_builder.h"
#include <fstream>
#include <cstring>
#include <iostream>

namespace NeuroCOBOL {

bool GXPBuilder::Generate(const std::string& filename, 
                          const std::string& pkgName, 
                          const std::vector<uint8_t>& bytecode) {
    
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo crear el archivo GXP: " << filename << std::endl;
        return false;
    }

    GXPHeader header;
    memset(&header, 0, sizeof(GXPHeader));

    // 'GXP1' en formato Little Endian (coincidente con 0x50584747 si P=0x50, X=0x58, G=0x47)
    // Sin embargo, usaremos el magic literal del kernel
    header.magic = 0x50584747; 
    header.version = 1;

    strncpy(header.package_name, pkgName.c_str(), sizeof(header.package_name) - 1);
    strncpy(header.vendor, "cyberenigma-lgtm (Noxferion)", sizeof(header.vendor) - 1);

    header.payload_size = (uint32_t)bytecode.size();
    header.binary_offset = (uint32_t)sizeof(GXPHeader);

    // Escribir cabecera
    file.write(reinterpret_cast<const char*>(&header), sizeof(GXPHeader));

    // Escribir bytecode
    if (!bytecode.empty()) {
        file.write(reinterpret_cast<const char*>(bytecode.data()), bytecode.size());
    }

    file.close();
    std::cout << "[OK] Paquete GXP generado: " << filename << " (" << bytecode.size() << " bytes de bytecode)" << std::endl;
    return true;
}

} // namespace NeuroCOBOL
