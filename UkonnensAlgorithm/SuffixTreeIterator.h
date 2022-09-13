#pragma once
#include<iostream>
#include <iterator> 
#include <cstddef>  
#include<vector>
#include"Node.h"

class SuffixTreeIterator
{
public:
	//SuffixTreeService service;
	using iteratorCategory = std::bidirectional_iterator_tag;
	using differenceType = std::ptrdiff_t;
	using valueType = int;
	using pointerType = valueType*;
	using referenceType = valueType&;

	~SuffixTreeIterator();
	//SuffixTreeIterator(const SuffixTreeIterator&) = default;
	SuffixTreeIterator() = default;
	SuffixTreeIterator(valueType fromIndex, valueType toIndex);

	referenceType operator*() const;
	pointerType operator->();
	//SuffixTreeIterator(/*SuffixTreeService service*/ valueType fromIndex, valueType toIndex); 

	SuffixTreeIterator& operator ++();
	SuffixTreeIterator operator ++(int);
	SuffixTreeIterator& operator --();
	SuffixTreeIterator operator --(int);
	bool operator==(const SuffixTreeIterator& other) const;
	bool operator!=(const SuffixTreeIterator& other) const;
	valueType getToIndex();

private:
	valueType fromIndex;
	valueType toIndex;
	//store the nodes in alphabetical order
	void goThroughTreeInAlphabeticalOrder(Node* node);

};



