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

SuffixTreeIterator* SuffixTreeService::getIteratorOfOccurrence(const std::string& pattern)
{
	if ((this->currentOccurrence == this->endingNodeOfPattern) || (this->currentOccurrence->getParentNode() == tree->getRoot())) {
		this->currentOccurrence = nullptr;
		return nullptr;
	}
	int countEdgesLengthFromPatternEndToLeaf = 0;
	this->currentOccurrence->getParentNode()->useUFSTraversing(this->endingNodeOfPattern, countEdgesLengthFromPatternEndToLeaf);
	countEdgesLengthFromPatternEndToLeaf += (this->endingNodeOfPattern->getToIndex() - this->endingNodeOfPattern->getFromIndex() - this->positionWherePatternFinishedFromBeginningOfEndingNode);

	int fromIndex = this->currentOccurrence->getFromIndex() - countEdgesLengthFromPatternEndToLeaf - this->pattern.length();
	int toIndex = fromIndex + pattern.length();
	return new SuffixTreeIterator(fromIndex, toIndex);
}

SuffixTreeService::SuffixTreeService(const std::string& textToAnalyze): textToAnalyze(textToAnalyze), pattern(""), mostLeftLeafNodeInPatternPath(nullptr), mostRightLeafNodeInPatternPath(nullptr), lastNodeInAlphaOrder(nullptr),currentOccurrence(nullptr), positionWherePatternFinishedFromBeginningOfEndingNode(-1), endingNodeOfPattern(nullptr)
{
	tree = new SuffixTree(this->textToAnalyze);
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

SuffixTreeService::iterator SuffixTreeService::findFirstOccurrenceOfPattern(const std::string& pattern)
{
	if (checkIfPatternExist(pattern) == true) {
		int fromIndex = this->endingNodeOfPattern->getFromIndex() - (pattern.length() - this->positionWherePatternFinishedFromBeginningOfEndingNode);
		int toIndex = fromIndex + pattern.length();
		setBorder(pattern);
		this->pattern = pattern;
		this->currentOccurrence = this->mostLeftLeafNodeInPatternPath;
		return new SuffixTreeIterator(fromIndex, toIndex);
	}
	else {
		return nullptr;
	}			
}


SuffixTreeIterator* SuffixTreeService::findNextOccurrenceOfPattern()
{
	if (this->currentOccurrence == this->mostRightLeafNodeInPatternPath){
		this->mostLeftLeafNodeInPatternPath = nullptr;
		this->mostRightLeafNodeInPatternPath = nullptr;
		this->currentOccurrence = nullptr;
		return nullptr;
	}
	else {
		this->currentOccurrence = this->currentOccurrence->getNodeChildren()[1];
		return getIteratorOfOccurrence(pattern);
	}
}
SuffixTreeIterator* SuffixTreeService::findPreviousOccurrenceOfPattern()
{
	if (this->currentOccurrence == this->mostLeftLeafNodeInPatternPath) {
		return nullptr;
	}
	else {
		this->currentOccurrence = this->currentOccurrence->getNodeChildren()[0];
		return getIteratorOfOccurrence(pattern);
	}
}
SuffixTreeIterator* SuffixTreeService::findLastOccurrenceOfPattern(const std::string& pattern)
{
	this->pattern = pattern;
	if (checkIfPatternExist(pattern) == true) {
		setBorder(pattern);
		this->currentOccurrence = this->mostRightLeafNodeInPatternPath;

		return getIteratorOfOccurrence(pattern);
	}
	else {
		return nullptr;
	}
}
SuffixTreeIterator* SuffixTreeService::findNextNodeInAlphabeticalOrder()
{
	Node* parentNode = this->lastNodeInAlphaOrder->getParentNode();
	if (this->lastNodeInAlphaOrder != tree->getRoot()) {
		this->lastLetterInAlphaOrder = this->textToAnalyze[this->lastNodeInAlphaOrder->getFromIndex()];


		while (this->lastNodeInAlphaOrder->getChildrenArraySize() > 0) {
			Node* foundNode = parentNode->getNodeChildren()[0];
			char theEarliestLetter = this->lastLetterInAlphaOrder;
			for (int iter = 0; iter < node->getChildrenArraySize(); ++iter) {
				if (this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()] < this->lastLetterInAlphaOrder) {
					theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()];
					foundNode = node->getNodeChildren()[iter];
				}
			}
			//schodzimy do kolejnego poziomu 
			node = foundNode;
		}
		this->endingNodeOfPattern = node;
		int countEdgesLengthFromPatternEndToLeaf = 0;
		node->getParentNode()->useUFSTraversing(tree->getRoot(), countEdgesLengthFromPatternEndToLeaf);
		countEdgesLengthFromPatternEndToLeaf += (this->endingNodeOfPattern->getToIndex() - this->endingNodeOfPattern->getFromIndex() - this->positionWherePatternFinishedFromBeginningOfEndingNode);
		this->lastNodeInAlphaOrder = node;
		int fromIndex = node->getFromIndex() - countEdgesLengthFromPatternEndToLeaf;
		int toIndex;
		if (node->getParentNode() == tree->getRoot()) {
			toIndex = node->getToIndex();
		}
		else {
			toIndex = fromIndex + countEdgesLengthFromPatternEndToLeaf;
		}
		return new SuffixTreeIterator(fromIndex, toIndex);


		int countEdgesLengthFromPatternEndToLeaf = 0;
		this->currentOccurrence->getParentNode()->useUFSTraversing(this->endingNodeOfPattern, countEdgesLengthFromPatternEndToLeaf);
		countEdgesLengthFromPatternEndToLeaf += (this->endingNodeOfPattern->getToIndex() - this->endingNodeOfPattern->getFromIndex() - this->positionWherePatternFinishedFromBeginningOfEndingNode);

		int fromIndex = this->currentOccurrence->getFromIndex() - countEdgesLengthFromPatternEndToLeaf - this->pattern.length();
		int toIndex = fromIndex + pattern.length();
		return new SuffixTreeIterator(fromIndex, toIndex);
	}
}
SuffixTreeIterator* SuffixTreeService::findFirstNodeInAlphabeticalOrder()
{
	Node* node = tree->getRoot();
	if (node->getChildrenArraySize() == 0) {
		return nullptr;
	}
	else {

		while (node->getChildrenArraySize() > 0) {
			Node* foundNode = node->getNodeChildren()[0];
			char theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[0]->getFromIndex()];
			for (int iter = 1; iter < node->getChildrenArraySize(); ++iter) {
				if (this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()] < theEarliestLetter) {
					theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()];
					foundNode = node->getNodeChildren()[iter];
				}
			}
			//schodzimy do kolejnego poziomu 
			node = foundNode;
		}
		this->endingNodeOfPattern = node;
		int countEdgesLengthFromPatternEndToLeaf = 0;
		node->getParentNode()->useUFSTraversing(tree->getRoot(), countEdgesLengthFromPatternEndToLeaf);
		countEdgesLengthFromPatternEndToLeaf += (this->endingNodeOfPattern->getToIndex() - this->endingNodeOfPattern->getFromIndex() - this->positionWherePatternFinishedFromBeginningOfEndingNode);
		this->lastNodeInAlphaOrder = node;
		int fromIndex = node->getFromIndex() - countEdgesLengthFromPatternEndToLeaf;
		int toIndex;
		if (node->getParentNode() == tree->getRoot()) {
			toIndex = node->getToIndex();
		}
		else {
			toIndex = fromIndex + countEdgesLengthFromPatternEndToLeaf;
		}
		return new SuffixTreeIterator(fromIndex, toIndex);
	}
}
