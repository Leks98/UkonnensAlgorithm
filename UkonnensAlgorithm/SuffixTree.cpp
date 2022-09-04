#include "SuffixTree.h"
//#ifdef _DEBUG
//#define new new( 16, __FILE__ , __LINE__ )
//#else
//#define new new
//#endif

SuffixTree::SuffixTree(const std::string& textToAnalize):
	textToAnalyze(textToAnalize),
	remaining(0),
	pRoot(new Node())
{
	this->activePoint = new ActivePoint(pRoot);
	this->build();
	this->applyDFSTraversing();
	//std::cout << this->validate();
}



SuffixTree::~SuffixTree()
{
	delete this->activePoint;
	delete this->pRoot;
}

Node* SuffixTree::selectNode(int position)
{

	return this->activePoint->getActiveNode()->getNodeChildren() != nullptr ? this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[position]) : nullptr;
}

char SuffixTree::findNextCharacterInActiveNode(int position)
{
	Node* nextNode = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
	if (nextNode->getLengthOfNode() >= this->activePoint->getActiveLength()) {
		return this->textToAnalyze[nextNode->getFromIndex() + this->activePoint->getActiveLength()];
	}
	if (nextNode->getLengthOfNode() + 1 == this->activePoint->getActiveLength()) {
		if (nextNode->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[position]) != nullptr) {
			return textToAnalyze[position];
		}
	}
	else {
		this->activePoint->setActiveNode(nextNode);
		this->activePoint->setActiveLength(this->activePoint->getActiveLength() - nextNode->getLengthOfNode() - 1);
		this->activePoint->setActiveEdge(this->activePoint->getActiveEdge() + nextNode->getLengthOfNode() + 1);
		return findNextCharacterInActiveNode(position);
	}

	return '\0';
}

void SuffixTree::moveDown(int position)
{
	Node* node = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
		if (node->getLengthOfNode() < this->activePoint->getActiveLength()) {
			this->activePoint->setActiveNode(node);
			this->activePoint->setActiveLength(this->activePoint->getActiveLength() - node->getLengthOfNode());
			this->activePoint->setActiveEdge(node->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[position])->getFromIndex());
		}
		else {
			this->activePoint->increaseActiveLength();
		}
	
}
void SuffixTree::setIndexNodeUsingDFSMethod(Node* node, int& nodeIndex)
{ //x$   index 0 $ | index 1 
	if (node == nullptr) {
		return;
	}

	nodeIndex += node->getToIndex() - node->getFromIndex(); // 0 + (1-0) = 1

	if (node->getChildrenArraySize() == 0) {
		//if (node->getNodeIndex() != -1) { /////////////////////////////////////////////CHECK
			node->setNodeIndex(this->textToAnalyze.length() - nodeIndex);
			return;
	//	}
	}
	else {
		for (int iter = 0; iter < node->getChildrenArraySize(); ++iter) {
			setIndexNodeUsingDFSMethod(node->getNodeChildren()[iter], nodeIndex);
		}
	}
}

void SuffixTree::build()
{
	int position = 0;
	int leafEnd = position;
	Node* lastCreatedNodeInThisPhase = nullptr;
	while (position < this->textToAnalyze.length()) {
		this->remaining++;
		leafEnd++;
		while (this->remaining > 0) {
			this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
			if (this->activePoint->getActiveLength() == 0)
			{

				if (selectNode(position) != nullptr) {

					this->activePoint->setActiveEdge(selectNode(position)->getFromIndex());
					this->activePoint->increaseActiveLength();
					break;
				}
				else {
					this->activePoint->getActiveNode()->addChildNodeByRange(position, leafEnd);
					this->remaining--;
				}
			}
			else {
				char foundCharacter = findNextCharacterInActiveNode(position);
				if (foundCharacter != '\0') {
					if (foundCharacter == this->textToAnalyze[position]) {
						if (lastCreatedNodeInThisPhase != nullptr) {
							lastCreatedNodeInThisPhase->setNodeSuffixLink(this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]));
						}
						moveDown(position);
						break;
					}
					else {

						Node* tmp = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
						Node* node = new Node();

						memcpy(node, tmp, sizeof(Node));

						int beginningFromIndex = node->getFromIndex();
						node->setFromIndex(node->getFromIndex() + this->activePoint->getActiveLength());
						//usunac z active node z children
						//this->activePoint->getActiveNode()->deleteChildNode(node);

						Node* newInternalNode = new Node(beginningFromIndex, beginningFromIndex + this->activePoint->getActiveLength());
						Node* newLeafNode = new Node(position, leafEnd);

						newInternalNode->addChildNode(node);
						//newInternalNode->setNodeChild(node, newInternalNode->getFromIndex() + this->activePoint->getActiveLength());
						newInternalNode->addChildNode(newLeafNode);
						//newInternalNode->setNodeChild(newLeafNode, position);
						newInternalNode->setNodeIndex(0);
						tmp = newInternalNode;
						//this->activePoint->getActiveNode()->addChildNode(newInternalNode);
						//this->activePoint->getActiveNode()->setNodeChild(newInternalNode,newInternalNode->getFromIndex());


						if (lastCreatedNodeInThisPhase != nullptr) {
							lastCreatedNodeInThisPhase->setNodeSuffixLink(newInternalNode);
						}

						lastCreatedNodeInThisPhase = newInternalNode;
						newInternalNode->setNodeSuffixLink(pRoot);


						if (this->activePoint->getActiveNode() != this->pRoot) {
							this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
						}
						else {
							this->activePoint->increaseActiveEdge();
							this->activePoint->decreaseActiveLength();
						}
						this->remaining--;
					}
				}
				else {
					Node* node = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
					Node* newLeafNode = new Node(position, leafEnd);
					node->addChildNode(newLeafNode);
					//node->setNodeChild(newLeafNode, position);

					if (lastCreatedNodeInThisPhase != nullptr) {
						lastCreatedNodeInThisPhase->setNodeSuffixLink(node);
					}
					lastCreatedNodeInThisPhase = node;

					if (this->activePoint->getActiveNode() != this->pRoot) {
						this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
					}
					else {
						this->activePoint->increaseActiveEdge();
						this->activePoint->decreaseActiveLength();
					}
					this->remaining--;
				}

			}

		}
		position++;

	}
	if (this->remaining != 0) {
		std::cout<< "During building the tree something was wrong\n";
	}
	int nodeIndex = 0;
	//setIndexNodeUsingDFSMethod(this->pRoot, nodeIndex);
}

void SuffixTree::applyDFSTraversing()
{
	std::list<char> result;
	for (int iter = 0; iter < this->pRoot->getChildrenArraySize(); ++iter) {
		implementDFSTraversing(this->pRoot->getNodeChildren()[iter], result);
	}
}
bool SuffixTree::validate()
{
	for (int iter = 0; iter< this->textToAnalyze.length(); ++iter) {
		if (!validateBuildingProcess(this->pRoot,iter, iter)) {
			std::cout<< "Verification failed";
			return false;
		}
	}
	return true;

}
bool SuffixTree::validateBuildingProcess(Node* node, int index, int& currentPos)
{
	if (node == nullptr) {
		std::cout<< "Failed at "<< currentPos << " for index " << index;
		return false;
	}

	if (node->getNodeIndex() != -1) {
		if (node->getNodeIndex() != index) {
			std::cout<< "Different indexes. Failed at "<< currentPos << " for index " << index;
			return false;
		}
		else {
			return true;
		}
	}
	if (currentPos >= this->textToAnalyze.length()) {
		std::cout << "Different indexes. Failed at " << currentPos << " for index " << index;
		return false;
	}

	Node* childNode = node->getNodeChildren()[this->textToAnalyze[currentPos]];
	if (childNode == nullptr) {
		std::cout<< "Failed at " << currentPos << " for index " << index;
		return false;
	}
	int shift = 0;
	for (int iter = childNode->getFromIndex(); iter <= childNode->getToIndex(); ++iter) {
		if (this->textToAnalyze[currentPos + shift] != this->textToAnalyze[iter]) {
			std::cout<< "The signs are dirrefent. Failed at " << this->textToAnalyze[currentPos + shift] << " " << this->textToAnalyze[iter];
			return false;
		}
		shift++;
	}
	currentPos += childNode->getToIndex() - childNode->getFromIndex() + 1;
	return validateBuildingProcess(childNode, index, currentPos);
}
void SuffixTree::implementDFSTraversing(Node* node, std::list<char> result) {
	if (node == nullptr) {
		return;
	}
	if (node->getNodeIndex() != -1) {
		for (int iter = node->getFromIndex(); iter <= node->getToIndex(); ++iter) {
			result.push_back(this->textToAnalyze[iter]);
		}
		std::list<char>::const_iterator pos;
		for (pos = result.begin(); pos != result.end(); ++pos) {
			std::cout << *pos << " ";
		}
		std::cout << node->getNodeIndex() << " = index \n";

		for (int iter = node->getFromIndex(); iter <= node->getToIndex(); ++iter) {
			result.remove(result.size() - 1);
		}
		return;
	}

	for (int iter = node->getFromIndex(); iter <= node->getToIndex(); ++iter) {
		result.push_back(this->textToAnalyze[iter]);
	}

	for (int iter = 0; iter < node->getChildrenArraySize(); ++iter) {
		implementDFSTraversing(node->getNodeChildren()[iter], result);
	}

	for (int iter = node->getFromIndex(); iter <= node->getToIndex(); ++iter) {
		result.remove(result.size() - 1);
	}

}
