#pragma once
#include "SuffixTree.h"
#include"SuffixTreeIterator.h"
#include <stdio.h>
#include <stdlib.h>
class SuffixTreeService
{
private:
	std::string textToAnalyze;
	std::string pattern;
	SuffixTree* tree;
	using iterator = SuffixTreeIterator*;
	char lastLetterInAlphaOrder;
	int positionWherePatternFinishedFromBeginningOfEndingNode;
	Node* endingNodeOfPattern;
	Node* mostLeftLeafNodeInPatternPath;
	Node* mostRightLeafNodeInPatternPath;
	Node* currentOccurrence;
	Node* lastNodeInAlphaOrder;
	void setBorder(const std::string& pattern);
	iterator getIteratorOfOccurrence(const std::string& pattern);
public:
	SuffixTreeService(const std::string& textToAnalyze);
	~SuffixTreeService();
	//ukryc node'a wewnatrz, przekazujemy inny rodzaj iteratora 
	bool checkIfPatternExist(const std::string& pattern);

	int countOccurrencesOfPattern(const std::string& pattern);
	iterator findFirstOccurrenceOfPattern(const std::string& pattern); //wszystkie funkcje w kontenerach powinny byc typu size_t
	iterator findNextOccurrenceOfPattern();
	iterator findPreviousOccurrenceOfPattern();
	iterator findLastOccurrenceOfPattern(const std::string& pattern);
	iterator findFirstNodeInAlphabeticalOrder();
	iterator findNextNodeInAlphabeticalOrder();
	//find zwracq pierwsze wystapienie 
};

