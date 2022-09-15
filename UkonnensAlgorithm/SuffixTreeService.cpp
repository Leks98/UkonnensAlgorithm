#include "SuffixTreeService.h"

void SuffixTreeService::setBorder(const std::string& pattern)
{
	if (checkIfPatternExist(pattern) == true) {
		if (this->endingNodeOfPattern->getChildrenArraySize() == 0) {
			this->mostLeftLeafNodeInPatternPath = this->mostRightLeafNodeInPatternPath = this->endingNodeOfPattern;
		}
		this->mostLeftLeafNodeInPatternPath = this->endingNodeOfPattern->useLeftDFSTraversing();
		this->mostRightLeafNodeInPatternPath = this->endingNodeOfPattern->useRightDFSTraversing();
	}
}


SuffixTreeService::SuffixTreeService(const std::string& textToAnalyze): textToAnalyze(textToAnalyze), pattern(""), mostLeftLeafNodeInPatternPath(nullptr), mostRightLeafNodeInPatternPath(nullptr),currentOccurrence(nullptr), positionWherePatternFinishedFromBeginningOfEndingNode(-1), endingNodeOfPattern(nullptr)
{
	tree = new SuffixTree(this->textToAnalyze);
}

SuffixTreeService::SuffixTreeService()
{
}

std::string SuffixTreeService::getTextToAnalyze()
{
	return this->textToAnalyze;
}

std::string SuffixTreeService::getPattern()
{
	return this->pattern;
}

SuffixTree* SuffixTreeService::getTree()
{
	return this->tree;
}

int SuffixTreeService::getPositionWherePatternFinishedFromBeginningOfEndingNode()
{
	return this->positionWherePatternFinishedFromBeginningOfEndingNode;
}

Node* SuffixTreeService::getEndingNodeOfPattern()
{
	return this->endingNodeOfPattern;
}

Node* SuffixTreeService::getMostLeftLeafNodeInPatternPath()
{
	return this->mostLeftLeafNodeInPatternPath;
}

Node* SuffixTreeService::getMostRightLeafNodeInPatternPath()
{
	return this->mostRightLeafNodeInPatternPath;
}

Node* SuffixTreeService::getCurrentOccurrence()
{
	return this->currentOccurrence;
}

void SuffixTreeService::setCurrentOccurrence(Node* currentOccurrence)
{
	this->currentOccurrence = currentOccurrence;
}

void SuffixTreeService::setMostRightLeafNodeInPatternPath(Node* mostRightLeafNodeInPatternPath)
{
	this->mostRightLeafNodeInPatternPath = mostRightLeafNodeInPatternPath;
}

void SuffixTreeService::setMostLeftLeafNodeInPatternPath(Node* mostLeftLeafNodeInPatternPath)
{
	this->mostLeftLeafNodeInPatternPath = mostLeftLeafNodeInPatternPath;
}

void SuffixTreeService::setEndingNodeOfPattern(Node* endingNodeOfPattern)
{
	this->endingNodeOfPattern = endingNodeOfPattern;
}

void SuffixTreeService::setPattern(const std::string& pattern)
{
	this->pattern = pattern;
}


SuffixTreeService::~SuffixTreeService()
{
	delete tree;
}


bool SuffixTreeService::checkIfPatternExist(const std::string& pattern)
{
	int patternIdx = 0;
	Node* node = this->tree->getRoot()->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
	if (node == nullptr) {
		this->endingNodeOfPattern = nullptr;
		this->mostLeftLeafNodeInPatternPath = nullptr;
		this->mostRightLeafNodeInPatternPath = nullptr;
		return false;
	}
	else {
		patternIdx++;
		int iter = 1;
		while (patternIdx < pattern.length()) {

			if (node->getFromIndex() + iter < node->getToIndex()) {
				if (this->textToAnalyze[node->getFromIndex() + iter] != pattern[patternIdx]) {
					this->endingNodeOfPattern = nullptr;
					this->mostLeftLeafNodeInPatternPath = nullptr;
					this->mostRightLeafNodeInPatternPath = nullptr;
					return false;
				}
				else {
					++patternIdx;
					++iter;
				}
			}

			else {
				node = node->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
				if (node == nullptr) {
					this->endingNodeOfPattern = nullptr;
					this->mostLeftLeafNodeInPatternPath = nullptr;
					this->mostRightLeafNodeInPatternPath = nullptr;
					return false;
				}
				patternIdx++;
				iter = 1;
			}

		}
		this->endingNodeOfPattern = node;
		this->positionWherePatternFinishedFromBeginningOfEndingNode = iter;
		return true;
	}
}

int SuffixTreeService::countOccurrencesOfPattern(const std::string& pattern)
{

	if (checkIfPatternExist(pattern) == true) {
		setBorder(pattern);
		if (this->mostLeftLeafNodeInPatternPath == this->mostRightLeafNodeInPatternPath) {
			return 1;
		}
		
		Node* leftLeafPtr = this->mostLeftLeafNodeInPatternPath;
		int occurrencesOfPattern = 2;
		while ((leftLeafPtr->getNodeChildren()[1] != nullptr) && (leftLeafPtr->getNodeChildren()[1] != this->mostRightLeafNodeInPatternPath)) {
			occurrencesOfPattern++;
			leftLeafPtr = leftLeafPtr->getNodeChildren()[1];
		}
		return occurrencesOfPattern;
	}
	else {
		return 0;
	}
}
