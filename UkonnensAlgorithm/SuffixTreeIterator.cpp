#include "SuffixTreeIterator.h"

SuffixTreeIterator::~SuffixTreeIterator()
{
}

SuffixTreeIterator::SuffixTreeIterator(valueType fromIndex, valueType toIndex): /*service(nullptr),*/ fromIndex(fromIndex), toIndex(toIndex)
{
}

//SuffixTreeIterator::referenceType SuffixTreeIterator::operator*() const
//{
//	//return *this;
//}

SuffixTreeIterator::pointerType SuffixTreeIterator::operator->()
{
	return pointerType();
}

//SuffixTreeIterator::SuffixTreeIterator(/*SuffixTreeService service,*/ valueType fromIndex, valueType toIndex): /*service(service),*/ fromIndex(fromIndex), toIndex(toIndex)
//{
//}

//SuffixTreeIterator& SuffixTreeIterator::operator++()
//{
//	//this = iterator = service.findNextOccurrenceOfPattern(service->, const T & pattern, int patternIdx);
//	//return *this;
//}
//
//SuffixTreeIterator SuffixTreeIterator::operator++(int)
//{
//	//SuffixTreeIterator iterator = *this;
//	//iterator = service.findNextOccurrenceOfPattern(Node * searchingNode, const T & pattern, int patternIdx);
//	////++(*this);
//	//return iterator;
//}

//SuffixTreeIterator& SuffixTreeIterator::operator--()
//{
//	// TODO: insert return statement here
//}
//
//SuffixTreeIterator SuffixTreeIterator::operator--(int)
//{
//	/*return SuffixTreeIterator();*/
//}

bool SuffixTreeIterator::operator==(const SuffixTreeIterator& other) const
{
	return (fromIndex == other.fromIndex && toIndex == other.toIndex);
}


bool SuffixTreeIterator::operator!=(const SuffixTreeIterator& other) const
{
	return !(*this == other);
}


SuffixTreeIterator::valueType SuffixTreeIterator::getToIndex()
{
	return toIndex;
}

void SuffixTreeIterator::goThroughTreeInAlphabeticalOrder(Node* node)
{
}

 