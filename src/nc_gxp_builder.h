#ifndef NC_GXP_BUILDER_H
#define NC_GXP_BUILDER_H

#include <stdint.h>
#include <string>
#include <vector>

#pragma pack(push, 1)
typedef struct {
    uint32_t magic;
    uint32_t version;
    char package_name[64];
    char vendor[64];
    uint32_t payload_size;
    uint32_t binary_offset;
    uint8_t signature[32];
} GXPHeader;
#pragma pack(pop)

namespace NeuroCOBOL {

class GXPBuilder {
public:
    static bool Generate(const std::string& filename, 
                         const std::string& pkgName, 
                         const std::vector<uint8_t>& bytecode);
};

} // namespace NeuroCOBOL

#endif
