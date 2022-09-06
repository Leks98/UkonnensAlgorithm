#pragma once
#include "SuffixTree.h"
class SuffixTreeService
{
private:
	std::string textToAnalyze;
	SuffixTree* tree;
public:
	SuffixTreeService(const std::string& textToAnalyze);
	~SuffixTreeService();
	bool exists(Node* node, const std::string& pattern, int patternIdx);
	bool checkIfPatternExist(const std::string& pattern);
	int countOccurrencesOfPattern(const std::string& pattern);
	void counts(Node* searchingNode, const std::string& pattern, int patternIdx, int& occurrences);
};

