#define _CRTDBG_MAP_ALLOC 
#include<iostream>
#include<string>
#include<chrono>
#include "FileService.h"
#include "SuffixTree.h"
#include <stdlib.h>  
#include <crtdbg.h> 
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

int main()
{
	FileService service("firstText.txt");
	
	try {
		auto beginningTime = std::chrono::steady_clock::now();
		SuffixTree suffixTree = SuffixTree("xx$");
		auto endTime = std::chrono::steady_clock::now();
		std::cout << "Tree building time in seconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginningTime).count() / 1000.0 << std::endl;
	}
	catch (std::runtime_error) {
		
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}