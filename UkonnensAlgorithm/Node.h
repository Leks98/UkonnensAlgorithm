#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include<algorithm>

class Node
{
private: 
	Node** children; //lub bracia lewy prawy 
	int childrenArraySize = 0; //
	int from, to;
	Node* suffixLink;
	Node* parentNode;

private:
	void deleteChildrenArray();
public:
	Node();
	Node(int fromIndex, int toIndex, Node* parentNode);
	~Node();
	int getFromIndex();
	void setFromIndex(int fromIndex);
	int getToIndex();
	void setToIndex(int toIndex);
	Node* getNodeSuffixLink();
	void setNodeSuffixLink(Node* suffixLink);
	Node* getParentNode();
	void setParentNode(Node* parentNode);
	Node** getNodeChildren();
	void setNodeChild(Node* child, int position);
	int getLengthOfNode();
	void addChildNodeByRangeBack(const int fromIndex, const int toIndex);
	void addChildNodeBack(Node* node);
	void addInternalNodeInSamePosition(Node* internalNode, Node*& nodeStartingWithCharToRemove);
	void countNumberOfLeaves(int& number);
	int getChildrenArraySize();
	Node* findNodeWithStartingChar(const std::string& textToAnalyze, char character);
	void updateLastToIndexes(const std::string& textToAnalyze, const int charIndex);
	void updateAllLastToIndexes(const std::string& textToAnalyze, const int charIndex, Node*& lastUpdatedLeaf);
	Node* useLeftDFSTraversing(int countEdgesLengthFromPatternEndToLeaf = 0);
	Node* useRightDFSTraversing(int countEdgesLengthFromPatternEndToLeaf = 0);
	void useUFSTraversing(Node* endingNodeOfPattern, int& countEdgesLengthFromPatternEndToLeaf);
	Node* findNodeForPattern(const std::string& textToAnalyze, char pattern);
};

