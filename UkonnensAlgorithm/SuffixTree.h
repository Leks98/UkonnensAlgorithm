#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include "ActivePoint.h"
#include <list>
class SuffixTree
{
private:
	std::string textToAnalyze;
	ActivePoint* activePoint;
	int remaining;
	Node* pRoot;

public:
	SuffixTree(const std::string& textToAnalize);
	Node* getRoot();
	~SuffixTree();

private:
	void build();
	Node* selectNode(int index);
	char findNextCharacterInActiveNode(int position, int leafEnd);
	void moveDown(int position, int leafEnd);
};



