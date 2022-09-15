#pragma once
#include "SuffixTreeService.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>  
#include"Node.h"
class AlphabeticalOrderIterator
{
private:
	using iteratorCategory = std::bidirectional_iterator_tag;
	using differenceType = std::ptrdiff_t;
	using valueType = size_t;
	using pointerType = valueType*;
	using referenceType = valueType&;
	SuffixTree* tree;
	size_t positionWherePatternFinishedFromBeginningOfEndingNode;
	Node* endingNodeOfPattern;
	Node* mostLeftLeafNodeInPatternPath;
	Node* mostRightLeafNodeInPatternPath;
	Node* currentOccurrence;
	Node* lastNodeInAlphaOrder;
	valueType fromIndex;
	valueType toIndex;
public:
	AlphabeticalOrderIterator(Node* lastNodeInAlphaOrder, SuffixTree* tree, valueType fromIndex, valueType toIndex);
	AlphabeticalOrderIterator(SuffixTree* tree);
	AlphabeticalOrderIterator();
	~AlphabeticalOrderIterator();
	AlphabeticalOrderIterator(const std::string& textToAnalyze);
	AlphabeticalOrderIterator find();
	AlphabeticalOrderIterator operator*() const;
	AlphabeticalOrderIterator& operator ++();
	AlphabeticalOrderIterator operator ++(int);
	bool operator==(const AlphabeticalOrderIterator& other) const;
	bool operator!=(const AlphabeticalOrderIterator& other) const;
};

