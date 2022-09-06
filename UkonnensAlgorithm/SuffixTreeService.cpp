#include "SuffixTreeService.h"

SuffixTreeService::SuffixTreeService(const std::string& textToAnalyze): textToAnalyze(textToAnalyze)
{
	tree = new SuffixTree(this->textToAnalyze);
}

SuffixTreeService::~SuffixTreeService()
{
	delete tree;
}

bool SuffixTreeService::exists(Node* searchingNode, const std::string& pattern, int patternIdx)
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
	int patternOccurrences = 0;
	 counts(tree->getRoot(), pattern, 0, patternOccurrences);
	 return patternOccurrences;
}
void SuffixTreeService::counts(Node* searchingNode, const std::string& pattern, int patternIdx, int& occurrences){
	Node* node = searchingNode->findNodeWithStartingChar(this->textToAnalyze, pattern[patternIdx]);
	if (node == nullptr) {
		return;
	}
	else {
		patternIdx++;
		for (int it = patternIdx; it < pattern.length(); ++it) {

			int idx = node->getFromIndex() + it;
			if (idx < node->getToIndex()) {
				if (this->textToAnalyze[idx] != pattern[it]) {
					return;
				}
			}
			else {
					counts(node, pattern, it, occurrences);
			}
		}
		if (occurrences == 0) {
			node->countNumberOfLeaves(occurrences);
		}
	}
}
