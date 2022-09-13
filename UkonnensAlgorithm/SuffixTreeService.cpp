#include "SuffixTreeService.h"

SuffixTreeService::SuffixTreeService(const std::string& textToAnalyze): textToAnalyze(textToAnalyze), lastNodeOfOccurrenceInPattern(nullptr), lastNodeInAlphaOrder(nullptr), indexOfNodeInPattern(0), occurrencesOfPattern(0), distanceBetweenLeafAndNodePattern(0), endingNodeOfPattern(nullptr)
{
	tree = new SuffixTree(this->textToAnalyze);
}

SuffixTreeService::~SuffixTreeService()
{
	delete tree;
}

bool SuffixTreeService::exists(Node* searchingNode, const std::string pattern, int patternIdx)
{
	Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
	if (node == nullptr) {
		return false;
	}
	else {
		patternIdx++;
		for (int it = patternIdx; it < pattern.length(); ++it) {

			int idx = node->getFromIndex() + it;
			if (idx < node->getToIndex()) {
				if (this->textToAnalyze[idx] != pattern[it]) {
					return false;
				}
			}
			else {
				exists(node, pattern, it);
			}

		}
		return true;
	}
}

bool SuffixTreeService::checkIfPatternExist(const std::string& pattern)
{
	return exists(tree->getRoot(), pattern, 0);
}

int SuffixTreeService::countOccurrencesOfPattern(const std::string& pattern)
{
	 counts(tree->getRoot(), pattern, 0);
	 return this->occurrencesOfPattern;
}

void SuffixTreeService::counts(Node* searchingNode, const std::string& pattern, int patternIdx){
	Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
	if (node == nullptr) {
		this->occurrencesOfPattern = 0;
		return;
	}
	else {
		patternIdx++;
		for (int it = patternIdx; it < pattern.length(); ++it) {

			int idx = node->getFromIndex() + it;
			if (idx < node->getToIndex()) {
				if (this->textToAnalyze[idx] != pattern[it]) {
					this->occurrencesOfPattern = 0;
					return;
				}
			}
			else {
					counts(node, pattern, it);
			}
		}
		this->occurrencesOfPattern = 0;
			node->countNumberOfLeaves(this->occurrencesOfPattern);
			return;
		}
	
}

//gdzie wyliczac to countsOccurrencesInPattern????
SuffixTreeService::iterator SuffixTreeService::findFirstOccurrenceOfPattern(const std::string& pattern, int patternIdx, Node* searchingNode)
{
	if (searchingNode == nullptr) {
		searchingNode = this->tree->getRoot();
	}
	/*if (searchingNode != tree->getRoot()) {
		++patternIdx;
	}*/
			Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
			if (node == nullptr) {
				this->indexOfNodeInPattern = 0;
				this->occurrencesOfPattern = 0;
				return nullptr;
			}

			else {

				int idx = 0;
				if (searchingNode == tree->getRoot()) {
					++patternIdx;
					++idx;
				}
				for (int it = idx; it < pattern.length() - patternIdx; ++it) {

					idx = node->getFromIndex() + it;
					++patternIdx;
					if (idx < node->getToIndex()) {
						if (this->textToAnalyze[idx] != pattern[patternIdx - 1]) {
							this->indexOfNodeInPattern = 0;
							this->occurrencesOfPattern = 0;
							return nullptr;
						}
					}
					else {
						if (findFirstOccurrenceOfPattern(pattern, patternIdx, node) == nullptr) {
							return nullptr;
						}
					}

				}
				//if (idx == 0) {
				//	this->distanceBetweenLeafAndNodePattern = node->getFromIndex();
				//}
				//else {
				//	this->distanceBetweenLeafAndNodePattern = node->getToIndex() - idx;
				//}
				int countEdgesLengthFromPatternEndToLeaf = 0;
		
				this->endingNodeOfPattern = node->getNodeChildren()[0];

				this->lastNodeOfOccurrenceInPattern = this->endingNodeOfPattern->useDFSTraversing(countEdgesLengthFromPatternEndToLeaf);
				//countEdgesLengthFromPatternEndToLeaf -= node->getToIndex() - node->getFromIndex();
				int fromIndex = idx-1;
				if (countEdgesLengthFromPatternEndToLeaf != 0) {
					if (idx == 0) {

						this->distanceBetweenLeafAndNodePattern = this->endingNodeOfPattern->getToIndex() - this->endingNodeOfPattern->getFromIndex() - 1;
						/*if (this->distanceBetweenLeafAndNodePattern > 0) {
							this->distanceBetweenLeafAndNodePattern -= 1;
						}*/
					}
					else {
						this->distanceBetweenLeafAndNodePattern = this->endingNodeOfPattern->getToIndex() - idx - 1;
					}
					countEdgesLengthFromPatternEndToLeaf += this->distanceBetweenLeafAndNodePattern;
					fromIndex = this->lastNodeOfOccurrenceInPattern->getFromIndex() - countEdgesLengthFromPatternEndToLeaf - pattern.length();

					if (this->lastNodeOfOccurrenceInPattern->getFromIndex() < pattern.length()) {
						fromIndex += idx;
					}
				}
				int toIndex = fromIndex + pattern.length();
				counts(tree->getRoot(), pattern, 0);
				this->indexOfNodeInPattern = 1;
				return new SuffixTreeIterator(fromIndex, toIndex);
		}
}


SuffixTreeIterator* SuffixTreeService::findNextOccurrenceOfPattern(const std::string& pattern, Node* searchingNode)
{
	if (searchingNode == nullptr || (searchingNode->getParentNode() == tree->getRoot()) || (this->indexOfNodeInPattern >= this->occurrencesOfPattern)){
		return nullptr;
	}
	else {

		this->lastNodeOfOccurrenceInPattern = searchingNode->getNodeChildren()[1];
		int countEdgesLengthFromPatternEndToLeaf = 0;
		if (searchingNode != this->endingNodeOfPattern) {
			this->lastNodeOfOccurrenceInPattern->useUFSTraversing(this->endingNodeOfPattern, countEdgesLengthFromPatternEndToLeaf);
			countEdgesLengthFromPatternEndToLeaf -= (this->lastNodeOfOccurrenceInPattern->getToIndex() - this->lastNodeOfOccurrenceInPattern->getFromIndex());
		}
		countEdgesLengthFromPatternEndToLeaf += this->distanceBetweenLeafAndNodePattern;
		int fromIndex = lastNodeOfOccurrenceInPattern->getFromIndex() - countEdgesLengthFromPatternEndToLeaf - pattern.length();
		int toIndex = fromIndex + pattern.length();
		++this->indexOfNodeInPattern;
		return new SuffixTreeIterator(fromIndex, toIndex);
			
	}
}
	//else {
	//	if (searchingNode->childrenArraySize() == 0) {
	//		//uaktualnic indeks polozenie parenta w stosunku do jego rodzica 
	//		findNextOccurrenceOfPattern(searchingNode->getParentNode());
	//	}
	//	else if (searchingNode->getParentNode()->getToIndex >= this->toIndexOfLastPatternNode) {

	//		if (this-> > idxOfLastChild + 1 = > searchingNode->childrenArraySize()) {
	//			//uaktualnic indeks polozenie parenta w stosunku do jego rodzica 
	//			findNextOccurrenceOfPattern(searchingNode->getParentNode());
	//		}
	//		else {
	//			//musimy mx zejsc do liscia 
	//			this->lastNodeOfOccurrenceInPattern = searchingNode->getNodeChildren()[++this->idxOfLastChild]->useDFSTraversing();
	//			int fromIndex = lastNodeOfOccurrenceInPattern->getToIndex() - leafNode->getFromIndex() + 2;
	//			int toIndex = fromIndex + pattern.length() + 1;

	//			return new iterator(fromIndex, toIndex);

	//		}
	//	}
	//	return nullptr;
	//}
	//Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
	//if (searchingNode->childrenArraySize <= 1 ) {
	//	return nullptr;
	//}
	////Node* node = searchingNode->getNodeChildren()[0]; 
	////bool ifNodeWasFound = false;
	////while (ifNodeWasFound == false) {
	////	node = node->findNodeForPattern(this->textToAnalyze, pattern[patternIdx]);
	////	Node*  tmp = node;
	////	if (node == nullptr) {
	////		return nullptr;
	////	}
	//	else {
	//		patternIdx++;
	//		for (int it = patternIdx; it < pattern.length(); ++it) {

	//			int idx = tmp->getFromIndex() + it;
	//			if (idx < tmp->getToIndex()) {
	//				if (this->textToAnalyze[idx] != pattern[it]) {
	//					//continue;
	//					return nullptr;
	//				}
	//			}
	//			else {
	//				/*tmp = this->findNodeWithStartingChar(tmp, pattern, it, occurrences);
	//				if (tmp == nulptr) {
	//					continue;
	//				}*/
	//				findFirstOccurrenceOfPattern(node, pattern, it);
	//			}
	//		}

	//			Node* leafNode = node->useDFSTraversing(this->lastOccurrenceOfPattern->getToIndex());
	//			int fromIndex = leafNode->getToIndex() - leafNode->getFromIndex() + 2;
	//			int toIndex = fromIndex + pattern.length() + 1;

	//			this->lastOccurrenceOfPattern = iterator(fromIndex, toIndex);
	//			return this->lastOccurrenceOfPattern;
	//		
	//	}
	////}
	//return nullptr;


SuffixTreeService::iterator SuffixTreeService::findNodeInAlphabeticalOrder(Node* node, int lengthOfEdgesFromAlphaLetterToLeaf)
{
	if (node->getChildrenArraySize() == 0 && node == tree->getRoot()) {
		return nullptr;
	}
	//GDZIE ZWALNIAC PAMIEC????
	else {
		if (node->getChildrenArraySize() > 1) {
			Node* foundNode = node->getNodeChildren()[0];
			char theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[0]->getFromIndex()];
			for (int iter = 1; iter < node->getChildrenArraySize(); ++iter) {
				if (node->getNodeChildren()[iter] == this->lastNodeInAlphaOrder) {
					findNodeInAlphabeticalOrder(node->getParentNode(), 0);
				}
				else
				{
					if (this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()] < theEarliestLetter) {
						theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()];
						foundNode = node->getNodeChildren()[iter];
					}
				}
			}
			lengthOfEdgesFromAlphaLetterToLeaf += (foundNode->getToIndex() - foundNode->getFromIndex() - 1);
			//schodzimy do kolejnego poziomu 
			findNodeInAlphabeticalOrder(foundNode, lengthOfEdgesFromAlphaLetterToLeaf);
		}
		else if (node->getChildrenArraySize() == 1) {
			lengthOfEdgesFromAlphaLetterToLeaf += (node->getNodeChildren()[0]->getToIndex() - node->getNodeChildren()[0]->getFromIndex() - 1);
			findNodeInAlphabeticalOrder(node->getNodeChildren()[0], lengthOfEdgesFromAlphaLetterToLeaf);
		}
		else {
			
			//countEdgesLengthFromPatternEndToLeaf += this->distanceBetweenLeafAndNodePattern;

			int fromIndex = node->getFromIndex() - lengthOfEdgesFromAlphaLetterToLeaf;
			int toIndex = node->getToIndex();

			iterator foundIterator = new SuffixTreeIterator(fromIndex, toIndex);
			if (node == this->lastNodeInAlphaOrder) {
				findNodeInAlphabeticalOrder(node->getParentNode(), 0);
			}
			else {
				this->lastNodeInAlphaOrder = node;
				return foundIterator;
			}
		}
	}
}

//jak przechodzic do kolejnego elementu alfabetycznie na poczatku podajemy roota a pozniej jakkolejny element?

