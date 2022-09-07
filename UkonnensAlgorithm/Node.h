#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include<algorithm>

class Node
{
private: 
	Node** children;
	int childrenArraySize = 0;
	int from, to;
	Node* suffixLink;
private:
	void deleteChildrenArray();
public:
	Node();
	Node(int fromIndex, int toIndex);
	~Node();
	int getFromIndex();
	void setFromIndex(int fromIndex);
	int getToIndex();
	void setToIndex(int toIndex);
	Node* getNodeSuffixLink();
	void setNodeSuffixLink(Node* suffixLink);
	Node** getNodeChildren();
	void setNodeChild(Node* child, int position);
	int getLengthOfNode();
	void addChildNodeByRange(const int fromIndex, const int toIndex);
	void deleteChildNode(Node* node);
	void addChildNode(Node* node);
	void countNumberOfLeaves(int& number);
	int getChildrenArraySize();
	Node* findNodeWithStartingChar(const std::string& textToAnalyze, char character);
	void updateLastToIndexes(const int charIndex);
};


