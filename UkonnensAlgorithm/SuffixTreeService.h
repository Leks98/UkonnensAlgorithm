#pragma once
#include "SuffixTree.h"
#include <stdio.h>
#include <stdlib.h>
class SuffixTreeService
{
private:
	std::string textToAnalyze;
	std::string pattern;
	SuffixTree* tree;
	int positionWherePatternFinishedFromBeginningOfEndingNode;
	Node* endingNodeOfPattern;
	Node* mostLeftLeafNodeInPatternPath;
	Node* mostRightLeafNodeInPatternPath;
	Node* currentOccurrence;
public:
	SuffixTreeService(const std::string& textToAnalyze);
	SuffixTreeService();
	std::string getTextToAnalyze();
	std::string getPattern();
	SuffixTree* getTree();
	int getPositionWherePatternFinishedFromBeginningOfEndingNode();
	Node* getEndingNodeOfPattern();
	Node* getMostLeftLeafNodeInPatternPath();
	Node* getMostRightLeafNodeInPatternPath();
	Node* getCurrentOccurrence();
	void setCurrentOccurrence(Node* currentOccurrence);
	void setMostRightLeafNodeInPatternPath(Node* mostRightLeafNodeInPatternPath);
	void setMostLeftLeafNodeInPatternPath(Node* mostLeftLeafNodeInPatternPath);
	void setEndingNodeOfPattern(Node* endingNodeOfPattern);
	void setPattern(const std::string& pattern);
	~SuffixTreeService();
public:
	bool checkIfPatternExist(const std::string& pattern);
	int countOccurrencesOfPattern(const std::string& pattern);
	void setBorder(const std::string& pattern);
};

