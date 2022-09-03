#include "FileService.h"

FileService::FileService(const std::string &filePath): filePath(filePath)
{
}

FileService::~FileService()
{
}

std::string FileService::readFile()
{
    const std::ifstream inputStream(this->filePath);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    return buffer.str();
}