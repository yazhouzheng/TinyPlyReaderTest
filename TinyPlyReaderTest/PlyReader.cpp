#include <chrono>
#include <iostream>
#include <fstream>
#include "PlyReader.h"

PlyReader::PlyReader(std::shared_ptr<PCLDisplay>& pclDisplay):
    m_spPclDisplayInReader(pclDisplay)
{
}

PlyReader::~PlyReader()
{
}

void PlyReader::ReadPlyFile(const std::string & filepath)
{
    try
    {
        std::ifstream ss(filepath, std::ios::binary);
        if (ss.fail())
        { 
            throw std::runtime_error("failed to open " + filepath);
        }

        tinyply::PlyFile file;
        file.parse_header(ss);

        std::shared_ptr<tinyply::PlyData> vertices, colors;

        try 
        { 
            vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); 
        }
        catch (const std::exception & e)
        {
            std::cerr << "tinyply exception: " << e.what() << std::endl;
        }

        try 
        {
            colors = file.request_properties_from_element("vertex", { "red", "green", "blue" });
        }
        catch (const std::exception & e) 
        {
            std::cerr << "tinyply exception: " << e.what() << std::endl; 
        }

        file.read(ss);

        if (vertices)
        {
            std::cout << "\tRead " << vertices->count << " total vertices " << std::endl;
        }

        for (int i = 0; i < colors->buffer.size_bytes(); i = i + 3)
        {
            unsigned char temp = colors->buffer.get()[i];
            colors->buffer.get()[i] = colors->buffer.get()[i + 2];
            colors->buffer.get()[i + 2] = temp;
        }

        m_spPclDisplayInReader->SendPointCloud((float*)vertices->buffer.get(), (unsigned char*)colors->buffer.get(), vertices->count);
    }
    catch (const std::exception & e)
    {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
    }
}