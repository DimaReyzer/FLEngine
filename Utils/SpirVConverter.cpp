#include "SpirVConverter.h"
#include <filesystem>

namespace FLUtils {
    void SpirVConverter::compileGLSLToSPIRV(const std::string& glslFile, const std::string& spirvFile)
    {
        std::string command = "glslangValidator -V " + glslFile + " -o " + spirvFile;
        int result = system(command.c_str());
        if (result != 0) {
            throw std::runtime_error("Failed to compile GLSL to SPIR-V: " + glslFile);
        }
    }

    std::vector<char> SpirVConverter::loadSPIRV(const std::string& spirvFile)
    {
        std::ifstream file(spirvFile, std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open SPIR-V file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }

    void SpirVConverter::clearSPIRVDirectory(const std::string& directoryPath)
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath + "\\Spir-V"))
        {
            if (entry.path().extension() == ".spv")
            {
                std::filesystem::remove(entry.path());
            }
        }
    }

    void SpirVConverter::compileAllShaders(const std::string& directoryPath)
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            const auto extension = entry.path().extension();
            if (extension == ".vert" || extension == ".frag")
            {
                std::string glslFile = entry.path().string();
                std::string spirvFile = directoryPath + "\\Spir-V\\" + entry.path().stem().string() + extension.string() + ".spv";

                compileGLSLToSPIRV(glslFile, spirvFile);
            }
        }
    }
}
