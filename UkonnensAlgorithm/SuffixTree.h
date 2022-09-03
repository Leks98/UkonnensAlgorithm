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
	~SuffixTree();

private:
	void build();
	Node* selectNode(int index);
	char findNextCharacterInActiveNode(int position);
	void moveDown(int position);
	void setIndexNodeUsingDFSMethod(Node* node, int& nodeIndex);
	void implementDFSTraversing(Node* node, std::list<char> result);
	void applyDFSTraversing();
	bool validateBuildingProcess(Node* node, int index, int& currentPos);
	bool validate();
};



