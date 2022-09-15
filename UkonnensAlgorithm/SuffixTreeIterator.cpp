#include "SuffixTreeIterator.h"

SuffixTreeIterator::SuffixTreeIterator(SuffixTreeService* service)
{
	this->service = service;
}

SuffixTreeIterator::SuffixTreeIterator() : fromIndex(-1), toIndex(-1)
{
}

SuffixTreeIterator::~SuffixTreeIterator()
{
}

SuffixTreeIterator::SuffixTreeIterator(SuffixTreeService* service, valueType fromIndex, valueType toIndex) : fromIndex(fromIndex), toIndex(toIndex)
{
	this->service = service;
}

SuffixTreeIterator SuffixTreeIterator::find(const std::string& pattern)
{
	if (service->checkIfPatternExist(pattern) == true) {
		int fromIndex = service->getEndingNodeOfPattern()->getFromIndex() - (pattern.length() - service->getPositionWherePatternFinishedFromBeginningOfEndingNode());
		int toIndex = fromIndex + pattern.length();
		service->setBorder(pattern);
		service->setPattern(pattern);
		service->setCurrentOccurrence(service->getMostLeftLeafNodeInPatternPath());
		return SuffixTreeIterator(service,fromIndex, toIndex);
	}
	else {
		return SuffixTreeIterator();
	}
}

SuffixTreeIterator SuffixTreeIterator::findLast(const std::string& pattern)
{
	service->setPattern(pattern);
	if (service->checkIfPatternExist(pattern) == true) {
		service->setBorder(pattern);
		service->setCurrentOccurrence(service->getMostRightLeafNodeInPatternPath());
		SuffixTreeIterator iterator = getIteratorOfOccurrence(pattern);
		return SuffixTreeIterator(iterator.service,iterator.fromIndex, iterator.toIndex);
	}
	else {
		return SuffixTreeIterator();
	}
}

SuffixTreeIterator SuffixTreeIterator::operator*() const
{
	return *this;
}


SuffixTreeIterator SuffixTreeIterator::operator++(int)
{
	SuffixTreeIterator iterator = *this;
	if (service->getCurrentOccurrence() == service->getMostRightLeafNodeInPatternPath()) {
		service->setMostLeftLeafNodeInPatternPath(nullptr);
		service->setMostRightLeafNodeInPatternPath(nullptr);
		service->setCurrentOccurrence(nullptr);
		return SuffixTreeIterator();
	}
	else {
		service->setCurrentOccurrence(service->getCurrentOccurrence()->getNodeChildren()[1]);
		iterator = getIteratorOfOccurrence(service->getPattern());
		return iterator;
	}
}

SuffixTreeIterator SuffixTreeIterator::operator--(int)
{
	SuffixTreeIterator iterator = *this;
	if (service->getCurrentOccurrence() == service->getMostLeftLeafNodeInPatternPath()) {
		return SuffixTreeIterator();
	}
	else {
		service->setCurrentOccurrence(service->getCurrentOccurrence()->getNodeChildren()[0]);
		iterator = getIteratorOfOccurrence(service->getPattern());
		return iterator;
	}
}

bool SuffixTreeIterator::operator==(const SuffixTreeIterator& other) const
{
	return (fromIndex == other.fromIndex && toIndex == other.toIndex);
}


bool SuffixTreeIterator::operator!=(const SuffixTreeIterator& other) const
{
	return !(*this == other);
}
SuffixTreeIterator SuffixTreeIterator::getIteratorOfOccurrence(const std::string& pattern)
{
	if ((service->getCurrentOccurrence() == service->getEndingNodeOfPattern()) || (service->getCurrentOccurrence()->getParentNode() == service->getTree()->getRoot())) {
		service->setCurrentOccurrence(nullptr);
		return SuffixTreeIterator();
	}
	int countEdgesLengthFromPatternEndToLeaf = 0;
	service->getCurrentOccurrence()->getParentNode()->useUFSTraversing(service->getEndingNodeOfPattern(), countEdgesLengthFromPatternEndToLeaf);
	countEdgesLengthFromPatternEndToLeaf += (service->getEndingNodeOfPattern()->getToIndex() - service->getEndingNodeOfPattern()->getFromIndex() - service->getPositionWherePatternFinishedFromBeginningOfEndingNode());

	int fromIndex = service->getCurrentOccurrence()->getFromIndex() - countEdgesLengthFromPatternEndToLeaf - pattern.length();
	int toIndex = fromIndex + pattern.length();
	return SuffixTreeIterator(service,fromIndex, toIndex);
}
