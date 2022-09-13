#include "Node.h"
//#ifdef _DEBUG
//#define new new(16, __FILE__ , __LINE__ )
//#else
//#define new new
//#endif


Node::Node(): from(-1), to(-1), suffixLink(nullptr), childrenArraySize(0), children(nullptr), parentNode(nullptr) {
};

Node::Node(int fromIndex, int toIndex, Node* parentNode) : from(fromIndex), to(toIndex), suffixLink(nullptr), childrenArraySize(0), children(nullptr), parentNode(parentNode) {
};

Node::~Node()
{
	//delete this->suffixLink;
		this->deleteChildrenArray();
}

int Node::getFromIndex() {
	return this->from;
}

void Node::setFromIndex(int fromIndex) {
	this->from = fromIndex;
}

int Node::getToIndex()
{
	return this->to;
}

void Node::setToIndex(int toIndex)
{
	this->to = toIndex;
}

Node* Node::getNodeSuffixLink()
{
	return this->suffixLink;
}

void Node::setNodeSuffixLink(Node* suffixLink)
{
	this->suffixLink = suffixLink;
}

Node* Node::getParentNode()
{
	return this->parentNode;
}

void Node::setParentNode(Node* parentNode)
{
	this->parentNode = parentNode;
}

Node** Node::getNodeChildren()
{
	return this->children;
}

void Node::setNodeChild(Node* child, int position)
{
	this->children[position] = child;
}

int Node::getLengthOfNode()
{
	return this->to - this->from-1;
}

void Node::deleteChildrenArray()
{
	for (int iter = 0; iter < this->childrenArraySize; ++iter) {
		delete this->children[iter];
	}
	delete[] this->children;
}

void Node::addChildNodeByRangeBack(const int fromIndex, const int toIndex)
{
	Node** increasedArray = new Node*[this->childrenArraySize + 1];

	//std::cout << *increasedArray;
	
	//for (int iter = 0; iter < childrenArraySize; ++iter)
	//{
	//	increasedArray[iter] = this->children[iter];
	//}
	memcpy(increasedArray, this->children, this->childrenArraySize * sizeof(Node*));
	delete[] this->children;
	this->children = increasedArray;
	increasedArray = nullptr;
	++this->childrenArraySize;
	Node* childNode = new Node(fromIndex, toIndex, this);
	this->children[this->childrenArraySize - 1] = childNode;
	//this->updateLastToIndexes(toIndex);
}

void Node::addChildNodeBack(Node* node)
{
	Node** increasedArray = new Node * [this->childrenArraySize + 1];

	//std::cout << *increasedArray;

	//for (int iter = 0; iter < childrenArraySize; ++iter)
	//{
	//	
	//	increasedArray[iter] = this->children[iter];
	//}
	memcpy(increasedArray, this->children, this->childrenArraySize * sizeof(Node*));
	delete[] this->children;
	this->children = increasedArray;
	increasedArray = nullptr;
	++this->childrenArraySize;
	this->children[this->childrenArraySize - 1] = node;
	//this->updateLastToIndexes(node->getToIndex());
}

void Node::addInternalNodeFront(Node* node)
{
	Node** increasedArray = new Node * [this->childrenArraySize + 1];

	//std::cout << *increasedArray;

	for (int iter = 1; iter < childrenArraySize; ++iter)
	{
		
		increasedArray[iter] = this->children[iter];
	}
	//memcpy(increasedArray, this->children, this->childrenArraySize * sizeof(Node*));
	delete[] this->children;
	this->children = increasedArray;
	increasedArray = nullptr;
	++this->childrenArraySize;
	this->children[0] = node;
	//this->updateLastToIndexes(node->getToIndex());
}
void Node::countNumberOfLeaves(int& number)
{
	if (this->childrenArraySize == 0) {
		number += 1;
	}
	for (int iter = 0; iter < this->childrenArraySize; ++iter) {
		this->children[iter]->countNumberOfLeaves(number);
	}
}

void Node::deleteChildNode(Node* node)
{
		Node** decreasedArray = new Node * [this->childrenArraySize - 1];
		int tmp = 0;
		for (int iter = 0; iter < this->childrenArraySize; ++iter)
		{
			if (this->children[iter] != node) {
				decreasedArray[iter - tmp] = this->children[iter];
			}
			else {
				++tmp;
			}
		}
		delete[] this->children;
		this->children = decreasedArray;
		--this->childrenArraySize;
}

int Node::getChildrenArraySize()
{
	return this->childrenArraySize;
}

Node* Node::findNodeWithStartingChar(const std::string& textToAnalyze, char character)
{
	for (int iter = 0; iter < this->childrenArraySize; ++iter) {
		if (textToAnalyze[this->children[iter]->getFromIndex()] == character) {
			return this->children[iter];
		}
	}
	return nullptr;
}

void Node::updateLastToIndexes(const std::string& textToAnalyze, const int charIndex)
{
	if (this->childrenArraySize > 0) {
		for (int iter = 0; iter < this->childrenArraySize; ++iter) {
			if (this->children[iter]->childrenArraySize == 0) {
				this->children[iter]->setToIndex(charIndex);
			}
		}
	}
	else {
		this->setToIndex(charIndex);
	}
}

void Node::updateAllLastToIndexes(const std::string& textToAnalyze, const int charIndex, Node*& lastUpdatedLeaf)
{
	if (this->childrenArraySize > 0) {
		for (int iter = 0; iter < this->childrenArraySize; ++iter) {
			this->getNodeChildren()[iter]->updateAllLastToIndexes(textToAnalyze, charIndex, lastUpdatedLeaf);
		}
	}
	else {
		this->setToIndex(charIndex);
		if (textToAnalyze[charIndex-1] == '$') {
			(this)->children = new Node * [2];
			if (lastUpdatedLeaf == nullptr) {
				(this)->children[0] = nullptr;
				(this)->children[1] = nullptr;
			}
			else {
				lastUpdatedLeaf->children[1] = this;
				(this)->children[0] = lastUpdatedLeaf;
				(this)->children[1] = nullptr;
			}
			lastUpdatedLeaf = this;

		}
	}
}

Node* Node::useDFSTraversing(int& countEdgesLengthFromPatternEndToLeaf)
{
	if (this->childrenArraySize == 0) {
		return this;
	}
	else{
		countEdgesLengthFromPatternEndToLeaf += this->getToIndex() - this->getFromIndex();
		return this->children[0]->useDFSTraversing(countEdgesLengthFromPatternEndToLeaf);
	}
	
}
void Node::useUFSTraversing(Node* endingNodeOfPattern, int& countEdgesLengthFromPatternEndToLeaf)
{
	if (this!=nullptr && this->parentNode!=nullptr && this->parentNode != endingNodeOfPattern) {
		countEdgesLengthFromPatternEndToLeaf += this->getToIndex() - this->getFromIndex();
		this->getParentNode()->useUFSTraversing(endingNodeOfPattern, countEdgesLengthFromPatternEndToLeaf);
	}
}

Node* Node::findNodeForPattern(const std::string& textToAnalyze, char pattern)
{
	for (int iter = this->getFromIndex(); iter < this->getToIndex(); ++iter) {
		if (textToAnalyze[iter] == pattern) {
			return this;
		}
	}	
	for (int iter = 0; iter < this->getChildrenArraySize(); ++iter) {
		Node* foundNode = this->getNodeChildren()[iter]->findNodeForPattern(textToAnalyze, pattern);
		if (foundNode != nullptr) {
			return foundNode;
		}
	}	
	return nullptr;
}

