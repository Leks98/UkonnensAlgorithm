#define _CRTDBG_MAP_ALLOC 
#include<iostream>
#include<string>
#include<chrono>
#include "FileService.h"
#include <stdlib.h>  
#include <crtdbg.h> 
#include"SuffixTreeIterator.h"
#include"AlphabeticalOrderIterator.h"

int main()
{
	FileService service("test3.txt");
	try {
		std::string text = service.readFile();


		auto start = std::chrono::steady_clock::now();
		SuffixTreeService* treeService = new SuffixTreeService(text + "€");
		auto end = std::chrono::steady_clock::now();
		std::cout << "Tree building time in seconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << std::endl;

		start = std::chrono::steady_clock::now();
		int countElektro = treeService->countOccurrencesOfPattern("elektro");
		end = std::chrono::steady_clock::now();
		std::cout << "Counted " << countElektro << " 'elektro' words in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
		
		start = std::chrono::steady_clock::now();
		int countStrzelone = treeService->countOccurrencesOfPattern("strzelone");
		end = std::chrono::steady_clock::now();
		std::cout << "Counted " << countStrzelone << " 'strzelo' words in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		bool checkIfwsedrftgyqExists = treeService->checkIfPatternExist("wsedrftgyq");
		end = std::chrono::steady_clock::now();
		std::cout << "Word 'wsedrftgyq'" << (checkIfwsedrftgyqExists ? " exists " : " do not exist ") << " in text. Found in: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		bool checkIfArowExists = treeService->checkIfPatternExist("arow");
		end = std::chrono::steady_clock::now();
		std::cout << "Word 'arow'" << (checkIfArowExists ? " exists " : " do not exist ") << " in text. Found in: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		SuffixTreeIterator iter = SuffixTreeIterator(treeService);
		SuffixTreeIterator iterFirst = iter.find("elek");	
		end = std::chrono::steady_clock::now();
		std::cout << "Iterator pointing to first word 'elek' found in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		SuffixTreeIterator iterNext = iterFirst++;
		end = std::chrono::steady_clock::now();
		std::cout << "Iterator pointing to next word 'elek' found in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		SuffixTreeIterator iterPrev = iterNext--;
		end = std::chrono::steady_clock::now();
		std::cout << "Iterator pointing to previous word 'elek' found in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;


		AlphabeticalOrderIterator alphaIter = AlphabeticalOrderIterator(treeService->getTree());

		start = std::chrono::steady_clock::now();
		AlphabeticalOrderIterator firstAlphaIter = alphaIter.find();
		end = std::chrono::steady_clock::now();
		std::cout << "Iterator pointing to first word in alphabetical order found in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		start = std::chrono::steady_clock::now();
		AlphabeticalOrderIterator nextAlphaIter = firstAlphaIter++;
		end = std::chrono::steady_clock::now();
		std::cout << "Iterator pointing to next word in alphabetical order found in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

		delete treeService;
	}
	catch (std::runtime_error) {
		
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}