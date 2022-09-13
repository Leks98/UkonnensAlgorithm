#pragma once
#include "SuffixTree.h"
#include"SuffixTreeIterator.h"
#include <stdio.h>
#include <stdlib.h>
class SuffixTreeService
{
private:
	std::string textToAnalyze;
	SuffixTree* tree;
	using iterator = SuffixTreeIterator*;
	Node* lastNodeInAlphaOrder;
	int indexOfNodeInPattern;
	int occurrencesOfPattern;
	int distanceBetweenLeafAndNodePattern;
	Node* endingNodeOfPattern;
public:
	Node* lastNodeOfOccurrenceInPattern;
	SuffixTreeService(const std::string& textToAnalyze);
	~SuffixTreeService();
	bool exists(Node* searchingNode, const std::string pattern, int patternIdx);
	bool checkIfPatternExist(const std::string& pattern);
	int countOccurrencesOfPattern(const std::string& pattern);
	void counts(Node* searchingNode, const std::string& pattern, int patternIdx);
	iterator findFirstOccurrenceOfPattern(const std::string& pattern, int patternIdx = 0, Node* searchingNode = nullptr);
	iterator findNextOccurrenceOfPattern(const std::string& pattern, Node* searchingNode = nullptr);
	iterator findNodeInAlphabeticalOrder(Node* node, int lengthOfEdgesFromAlphaLetterToLeaf = 0);
};

