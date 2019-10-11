#ifndef _PLY_READER_H_
#define _PLY_READER_H_
#include "tinyply.h"
#include "PCLDisplay.h"

class PlyReader
{
public:
    PlyReader(std::shared_ptr<PCLDisplay>& pclDisplay);
    ~PlyReader();
    void ReadPlyFile(const std::string & filepath);

private:
    struct float2 { float x, y; };
    struct float3 { float x, y, z; };
    struct double3 { double x, y, z; };
    struct uint3 { uint32_t x, y, z; };
    struct uint4 { uint32_t x, y, z, w; };

    struct geometry
    {
        std::vector<float3> vertices;
        std::vector<float3> normals;
        std::vector<float2> texcoords;
        std::vector<uint3> triangles;
    };

    std::shared_ptr<PCLDisplay> m_spPclDisplayInReader;
};
#endif /*_PLY_READER_H_*/