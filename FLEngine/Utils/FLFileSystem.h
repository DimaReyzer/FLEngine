#pragma once
#include <string>
#include <filesystem>

namespace FLStream {
	class FLFileSystem
	{
	public:
		static inline std::string getMainDirectory()
		{
			std::string filePath = __FILE__;
			std::filesystem::path projectPath = std::filesystem::path(filePath).parent_path();
			return projectPath.string();
		}
	};
}
