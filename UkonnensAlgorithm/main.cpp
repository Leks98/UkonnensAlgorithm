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
#include "SuffixTreeService.h"

int main()
{
	FileService service("firstText.txt");
/*	SuffixTreeService treeService("b");
	bool patternExists = treeService.checkIfPatternExist("cabag");
	int patternOccurrences = treeService.countOccurrencesOfPattern("c"); *///xxxx

	//findPattern zwraca iterator do pierwszego wystapienia slowa ++ do kolejnego slowa
	//referencja zwraca cos np wskaznik lub iterator do tekstu co jest przed co jest za ta pozycja
	//szablon parametryzowany typ 
	//iterator umozliwiajacy przejscie przez wszytskie sufiksyw porzadku leksykograficznym 
	//findFirst/FindLast
	


	//iterator w porzadku leksyograficnzym ale dla poddrzewa
	//jaki jest rozmiar poddrzewa
	//reczne nawigowanie po drzewie poziomy drzewa dla korzenia lokal begin iterator do wszyskich wezlow ktore sa dziecmi tego korzenia i dla tego znowu local begin i moge chodzic po poziomach 


	try {
		std::string text = service.readFile();
		auto beginningTime = std::chrono::steady_clock::now();
		SuffixTree suffixTree = SuffixTree(text+"$");
		auto endTime = std::chrono::steady_clock::now();
		std::cout << "Tree building time in seconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginningTime).count() / 1000.0 << std::endl;
	}
	catch (std::runtime_error) {
		
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}