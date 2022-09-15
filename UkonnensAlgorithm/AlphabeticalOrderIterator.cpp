#include "AlphabeticalOrderIterator.h"
#include "SuffixTreeService.h"


AlphabeticalOrderIterator::AlphabeticalOrderIterator(Node* lastNodeInAlphaOrder, SuffixTree* tree, valueType fromIndex, valueType toIndex):  fromIndex(fromIndex), toIndex(toIndex)
{
	this->tree = tree;
	this->lastNodeInAlphaOrder = lastNodeInAlphaOrder;
}
AlphabeticalOrderIterator::AlphabeticalOrderIterator(const std::string& textToAnalyze) :mostLeftLeafNodeInPatternPath(nullptr), mostRightLeafNodeInPatternPath(nullptr), lastNodeInAlphaOrder(nullptr), currentOccurrence(nullptr), positionWherePatternFinishedFromBeginningOfEndingNode(-1), endingNodeOfPattern(nullptr)
{
	tree = new SuffixTree(textToAnalyze);
}

AlphabeticalOrderIterator::AlphabeticalOrderIterator() : fromIndex(-1), toIndex(-1)
{
}

AlphabeticalOrderIterator::AlphabeticalOrderIterator(SuffixTree* tree) {
	this->tree = tree;
}
AlphabeticalOrderIterator::~AlphabeticalOrderIterator()
{
}


AlphabeticalOrderIterator AlphabeticalOrderIterator::operator*() const
{
	return *this;
}


AlphabeticalOrderIterator& AlphabeticalOrderIterator::operator++()
{
	Node* foundNode = nullptr;
	char lastLetterInAlphaOrder = tree->getTextToAnalyze()[this->lastNodeInAlphaOrder->getFromIndex()];

	while (true) {
		Node* parentNode = this->lastNodeInAlphaOrder->getParentNode();
		foundNode = parentNode->getNodeChildren()[0];
		char theEarliestLetter = '\0';
		for (int it = 0; it < parentNode->getChildrenArraySize(); ++it)
		{
			if (abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[it]->getFromIndex()]) > lastLetterInAlphaOrder) {
				theEarliestLetter = abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[it]->getFromIndex()]);
				break;
			}
		}
		if (theEarliestLetter == '\0') {
			if (parentNode == tree->getRoot()) {
				break;
			}
			this->lastNodeInAlphaOrder = parentNode;
			lastLetterInAlphaOrder = abs(tree->getTextToAnalyze()[parentNode->getFromIndex()]);
			continue;
		}
		for (int iter = 0; iter < parentNode->getChildrenArraySize(); ++iter) {
			if ((abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]) <= theEarliestLetter) && (abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]) > lastLetterInAlphaOrder)) {
				theEarliestLetter = abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]);
				foundNode = parentNode->getNodeChildren()[iter];
			}
		}

		while (foundNode->getChildrenArraySize() > 0) {
			Node* tmp = foundNode->getNodeChildren()[0];
			char theEarliestLetter = abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[0]->getFromIndex()]);
			for (int iter = 1; iter < foundNode->getChildrenArraySize(); ++iter) {
				if (abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[iter]->getFromIndex()]) < theEarliestLetter) {
					theEarliestLetter = abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[iter]->getFromIndex()]);
					tmp = foundNode->getNodeChildren()[iter];
				}
			}
			foundNode = tmp;
		}
		break;
	}
	this->endingNodeOfPattern = foundNode;
	int countEdgesLengthFromPatternEndToLeaf = 0;
	foundNode->getParentNode()->useUFSTraversing(tree->getRoot(), countEdgesLengthFromPatternEndToLeaf);
	this->lastNodeInAlphaOrder = foundNode;
	int fromIndex = foundNode->getFromIndex() - countEdgesLengthFromPatternEndToLeaf;
	int toIndex = this->endingNodeOfPattern->getToIndex();
	*this =  AlphabeticalOrderIterator(this->lastNodeInAlphaOrder,this->tree,fromIndex, toIndex);
	return *this;
}

AlphabeticalOrderIterator AlphabeticalOrderIterator::operator++(int)
{
	AlphabeticalOrderIterator iterator = *this;
	Node* foundNode = nullptr;
	char lastLetterInAlphaOrder = tree->getTextToAnalyze()[this->lastNodeInAlphaOrder->getFromIndex()];

	while (true) {
		Node* parentNode = this->lastNodeInAlphaOrder->getParentNode();
		foundNode = parentNode->getNodeChildren()[0];
		char theEarliestLetter = '\0';
		for (int it = 0; it < parentNode->getChildrenArraySize(); ++it)
		{
			if (abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[it]->getFromIndex()]) > lastLetterInAlphaOrder) {
				theEarliestLetter = abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[it]->getFromIndex()]);
				break;
			}
		}
		if (theEarliestLetter == '\0') {
			if (parentNode == tree->getRoot()) {
				break;
			}
			this->lastNodeInAlphaOrder = parentNode;
			lastLetterInAlphaOrder = abs(tree->getTextToAnalyze()[parentNode->getFromIndex()]);
			continue;
		}
		for (int iter = 0; iter < parentNode->getChildrenArraySize(); ++iter) {
			if ((abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]) <= theEarliestLetter) && (abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]) > lastLetterInAlphaOrder)) {
				theEarliestLetter = abs(tree->getTextToAnalyze()[parentNode->getNodeChildren()[iter]->getFromIndex()]);
				foundNode = parentNode->getNodeChildren()[iter];
			}
		}

		while (foundNode->getChildrenArraySize() > 0) {
			Node* tmp = foundNode->getNodeChildren()[0];
			char theEarliestLetter = abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[0]->getFromIndex()]);
			for (int iter = 1; iter < foundNode->getChildrenArraySize(); ++iter) {
				if (abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[iter]->getFromIndex()]) < theEarliestLetter) {
					theEarliestLetter = abs(tree->getTextToAnalyze()[foundNode->getNodeChildren()[iter]->getFromIndex()]);
					tmp = foundNode->getNodeChildren()[iter];
				}
			}
			foundNode = tmp;
		}
		break;
	}
	this->endingNodeOfPattern = foundNode;
	int countEdgesLengthFromPatternEndToLeaf = 0;
	foundNode->getParentNode()->useUFSTraversing(tree->getRoot(), countEdgesLengthFromPatternEndToLeaf);
	this->lastNodeInAlphaOrder = foundNode;
	int fromIndex = foundNode->getFromIndex() - countEdgesLengthFromPatternEndToLeaf;
	int toIndex = this->endingNodeOfPattern->getToIndex();
	iterator = AlphabeticalOrderIterator(this->lastNodeInAlphaOrder,this->tree,fromIndex, toIndex);
	return iterator;
}

bool AlphabeticalOrderIterator::operator==(const AlphabeticalOrderIterator& other) const
{
	return (fromIndex == other.fromIndex && toIndex == other.toIndex);
}


bool AlphabeticalOrderIterator::operator!=(const AlphabeticalOrderIterator& other) const
{
	return !(*this == other);
}

AlphabeticalOrderIterator AlphabeticalOrderIterator::find()
{
	Node* node = tree->getRoot();
	if (node->getChildrenArraySize() == 0) {
		return nullptr;
	}
	else {

		while (node->getChildrenArraySize() > 0) {
			Node* foundNode = node->getNodeChildren()[0];
			char theEarliestLetter = abs(tree->getTextToAnalyze()[node->getNodeChildren()[0]->getFromIndex()]);
			for (int iter = 1; iter < node->getChildrenArraySize(); ++iter) {
				if (abs(tree->getTextToAnalyze()[node->getNodeChildren()[iter]->getFromIndex()]) < theEarliestLetter) {
					theEarliestLetter = abs(tree->getTextToAnalyze()[node->getNodeChildren()[iter]->getFromIndex()]);
					foundNode = node->getNodeChildren()[iter];
				}
			}
			node = foundNode;
		}
		this->endingNodeOfPattern = node;
		int countEdgesLengthFromPatternEndToLeaf = 0;
		node->getParentNode()->useUFSTraversing(tree->getRoot(), countEdgesLengthFromPatternEndToLeaf);
		this->lastNodeInAlphaOrder = node;
		int fromIndex = node->getFromIndex() - countEdgesLengthFromPatternEndToLeaf;
		int toIndex;
		if (node->getParentNode() == tree->getRoot()) {
			toIndex = node->getToIndex();
		}
		else {
			toIndex = this->endingNodeOfPattern->getToIndex();
		}
		return AlphabeticalOrderIterator(this->lastNodeInAlphaOrder,this->tree,fromIndex, toIndex);
	}
}
