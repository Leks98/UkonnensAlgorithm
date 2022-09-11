#pragma once
#include "SuffixTree.h"
#include"SuffixTreeIterator.h"
class SuffixTreeService
{
private:
	std::string textToAnalyze;
	SuffixTree* tree;
	using iterator = SuffixTreeIterator*;
	Node* lastNodeOfOccurrenceInPattern;
	Node* lastNodeInAlphaOrder;
	int indexOfNodeInPattern;
	int occurrencesOfPattern;
public:
	SuffixTreeService(const std::string& textToAnalyze);
	~SuffixTreeService();
	bool exists(Node* searchingNode, const std::string pattern, int patternIdx);
	bool checkIfPatternExist(const std::string& pattern);
	int countOccurrencesOfPattern(const std::string& pattern);
	void counts(Node* searchingNode, const std::string& pattern, int patternIdx);
	iterator findFirstOccurrenceOfPattern(Node* searchingNode, const std::string& pattern, int patternIdx);
	iterator findNextOccurrenceOfPattern(Node* searchingNode, const std::string& pattern);
	iterator findNodeInAlphabeticalOrder(Node* node, int idxOfChild);
};

