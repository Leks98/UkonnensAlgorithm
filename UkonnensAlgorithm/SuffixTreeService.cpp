#include "SuffixTreeService.h"

SuffixTreeService::SuffixTreeService(const std::string& textToAnalyze): textToAnalyze(textToAnalyze), lastNodeOfOccurrenceInPattern(nullptr), lastNodeInAlphaOrder(nullptr), indexOfNodeInPattern(0), occurrencesOfPattern(0)
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
SuffixTreeService::iterator SuffixTreeService::findFirstOccurrenceOfPattern(Node* searchingNode, const std::string& pattern, int patternIdx)
{
			Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
			if (node == nullptr) {
				this->indexOfNodeInPattern = 0;
				this->occurrencesOfPattern = 0;
				return nullptr;
			}

			else {

				patternIdx++;
				int idx = 0;
				for (int it = patternIdx; it < pattern.length(); ++it) {

					idx = node->getFromIndex() + it;
					if (idx < node->getToIndex()) {
						if (this->textToAnalyze[idx] != pattern[it]) {
							this->indexOfNodeInPattern = 0;
							this->occurrencesOfPattern = 0;
							return nullptr;
						}
					}
					else {
						findFirstOccurrenceOfPattern(node, pattern, it);
					}

			}
				int fromIndex = idx - pattern.length();
				int toIndex = idx + 1;
				this->lastNodeOfOccurrenceInPattern = node->useDFSTraversing();
				counts(tree->getRoot(), pattern, 0);
				this->indexOfNodeInPattern = 1;
				return new SuffixTreeIterator(fromIndex, toIndex);
		}
}


SuffixTreeService::iterator SuffixTreeService::findNextOccurrenceOfPattern(Node* searchingNode, const std::string& pattern) 
{
	if (searchingNode == nullptr || (searchingNode->getParentNode() == tree->getRoot()) || (this->indexOfNodeInPattern >= this->occurrencesOfPattern)){
		return nullptr;
	}
	else {
			if (searchingNode->getRightBrother() != nullptr) {
				this->lastNodeOfOccurrenceInPattern = searchingNode->getRightBrother();
				int fromIndex = lastNodeOfOccurrenceInPattern->getToIndex() - lastNodeOfOccurrenceInPattern->getFromIndex() + 2;
				int toIndex = fromIndex + pattern.length() + 1;
				++this->indexOfNodeInPattern;
				return new SuffixTreeIterator(fromIndex, toIndex);
			}
			else {
				findNextOccurrenceOfPattern(searchingNode->getParentNode(), pattern);
			}
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


//SuffixTreeService::iterator SuffixTreeService::findNodeInAlphabeticalOrder(Node* node, int idxOfChild)
//{
//	if (node->getChildrenArraySize() == 0 && node == tree->getRoot()) {
//		return nullptr;
//	}
//	//GDZIE ZWALNIAC PAMIEC?????? z tym wszytskich nodow i from index i toIndex
//	else {
//		if (node->getChildrenArraySize() > 1) {
//			char theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[idxOfChild]->getFromIndex()];
//			Node* foundNode = node->getNodeChildren()[idxOfChild];
//			for (int iter = 1 + idxOfChild; iter < node->getChildrenArraySize(); ++iter) {
//				if (this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()] < theEarliestLetter) {
//					theEarliestLetter = this->textToAnalyze[node->getNodeChildren()[iter]->getFromIndex()];
//					foundNode = node->getNodeChildren()[iter];
//				}
//			}
//			//schodzimy do kolejnego poziomu 
//			findNodeInAlphabeticalOrder(foundNode, int idxOfChild);
//		}
//		else if (node->getChildrenArraySize() == 1) {
//			findNodeInAlphabeticalOrder(node->getNodeChildren()[0], 0);
//		}
//		else {
//			iterator foundIterator = new iterator(foundNode->getFromIndex(), foundNode->getToIndex());
//			if (foundIterator == lastNodeInAlphabeticalOrder) {
//				findNodeInAlphabeticalOrder(node, ++idxOfChild);
//			}
//			else {
//				this->lastNodeInAlphabeticalOrder = foundIterator;
//				return this->lastNodeInAlphabeticalOrder;
//			}
//		}
//	}
//}

//jak przechodzic do kolejnego elementu alfabetycznie na poczatku podajemy roota a pozniej jakkolejny element?

