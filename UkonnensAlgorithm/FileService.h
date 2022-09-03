#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
class FileService
{
private:
	std::string filePath;
public:
	FileService(const std::string& filePath);
	~FileService();
	std::string readFile();
};

