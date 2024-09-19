#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

namespace FLUtils {
	class SpirVConverter
	{
	public:
		static void compileGLSLToSPIRV(const std::string& hlslFile, const std::string& spirvFile);
		static std::vector<char> loadSPIRV(const std::string& spirvFile);
		static void clearSPIRVDirectory(const std::string& directoryPath);
		// HLSL to Spir-V compiling
		static void compileAllShaders(const std::string& directoryPath);
	};
}
