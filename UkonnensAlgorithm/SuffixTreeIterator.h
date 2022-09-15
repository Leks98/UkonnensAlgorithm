#pragma once
#include "SuffixTreeService.h"
#include<iostream>
#include <iterator> 
#include <cstddef>  
#include<vector>

class SuffixTreeIterator
{
private:	
	using iteratorCategory = std::bidirectional_iterator_tag;
	using differenceType = std::ptrdiff_t;
	using valueType = size_t;
	using pointerType = valueType*;
	using referenceType = valueType&;
	valueType fromIndex;
	valueType toIndex;
	SuffixTreeService* service;
	SuffixTreeIterator getIteratorOfOccurrence(const std::string& pattern);
public:
	SuffixTreeIterator();
	~SuffixTreeIterator();
	SuffixTreeIterator(SuffixTreeService* service);
	SuffixTreeIterator(SuffixTreeService* service, valueType fromIndex, valueType toIndex);
	SuffixTreeIterator find(const std::string& pattern);
	SuffixTreeIterator findLast(const std::string& pattern);
	SuffixTreeIterator operator*() const;
	SuffixTreeIterator operator ++(int);
	SuffixTreeIterator operator --(int);
	bool operator==(const SuffixTreeIterator& other) const;
	bool operator!=(const SuffixTreeIterator& other) const;
};



