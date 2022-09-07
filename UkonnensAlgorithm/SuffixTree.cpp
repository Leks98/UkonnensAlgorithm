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
}

Node* SuffixTree::getRoot()
{
	return pRoot;
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

char SuffixTree::findNextCharacterInActiveNode(int position, int leafEnd)
{
	Node* nextNode = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
	if (nextNode != nullptr) {
		if (nextNode->getLengthOfNode() >= this->activePoint->getActiveLength()) {
			return this->textToAnalyze[nextNode->getFromIndex() + this->activePoint->getActiveLength()];
		}
		if (nextNode->getLengthOfNode() +1 == this->activePoint->getActiveLength()) {
			if (nextNode->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[position]) != nullptr) {
				return textToAnalyze[position];
			}
		}
		else {
			this->activePoint->setActiveNode(nextNode);
			this->activePoint->setActiveLength(this->activePoint->getActiveLength() - nextNode->getLengthOfNode()-1);
			this->activePoint->setActiveEdge(this->activePoint->getActiveEdge() + nextNode->getLengthOfNode()+1);
			this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
			return findNextCharacterInActiveNode(position, leafEnd);
		}
	}

	return '\0';
}

void SuffixTree::moveDown(int position, int leafEnd)
{
	Node* node = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
		if (node->getLengthOfNode() < this->activePoint->getActiveLength()) { 
			this->activePoint->setActiveNode(node);
			this->activePoint->setActiveLength(this->activePoint->getActiveLength() - node->getLengthOfNode());
			this->activePoint->setActiveEdge(node->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[position])->getFromIndex());
			this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
		}
		else {
			this->activePoint->increaseActiveLength();
		}
	
}

void SuffixTree::build()
{
	int position = 0;
	int leafEnd = position;
	while (position < this->textToAnalyze.length()) {
		Node* lastCreatedNodeInThisPhase = nullptr;
		this->remaining++;
		leafEnd++;
		while (this->remaining > 0) {
			if (this->activePoint->getActiveLength() == 0)
			{

				if (selectNode(position) != nullptr) {

					this->activePoint->setActiveEdge(selectNode(position)->getFromIndex());
					this->activePoint->increaseActiveLength();
					this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
					break;
				}
				else {
					this->activePoint->getActiveNode()->addChildNodeByRange(position, leafEnd);
					this->remaining--;
				}
			}
			else {
				char foundCharacter = findNextCharacterInActiveNode(position, leafEnd);
				if(foundCharacter!='\0'){
					if (foundCharacter == this->textToAnalyze[position]) {
						if (lastCreatedNodeInThisPhase != nullptr) {
							lastCreatedNodeInThisPhase->setNodeSuffixLink(this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]));
						}
						moveDown(position, leafEnd);
						break;
					}
					else {

						Node* nodeStartingWithChar = this->activePoint->getActiveNode()->findNodeWithStartingChar(this->textToAnalyze, textToAnalyze[this->activePoint->getActiveEdge()]);
						int beginningFromIndex = nodeStartingWithChar->getFromIndex();

						nodeStartingWithChar->setFromIndex(beginningFromIndex + this->activePoint->getActiveLength());
						Node* newInternalNode = new Node(beginningFromIndex, beginningFromIndex + this->activePoint->getActiveLength());
						Node* newLeafNode = new Node(position, leafEnd);

						this->activePoint->getActiveNode()->deleteChildNode(nodeStartingWithChar);
						this->activePoint->getActiveNode()->addChildNode(newInternalNode);

						newInternalNode->addChildNode(nodeStartingWithChar);
						newInternalNode->addChildNode(newLeafNode);

						if (lastCreatedNodeInThisPhase != nullptr) {
							lastCreatedNodeInThisPhase->setNodeSuffixLink(newInternalNode);
						}

						lastCreatedNodeInThisPhase = newInternalNode;
						newInternalNode->setNodeSuffixLink(pRoot);


						if (this->activePoint->getActiveNode() != this->pRoot) {
							this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
							this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
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
					
					if (lastCreatedNodeInThisPhase != nullptr) {
						lastCreatedNodeInThisPhase->setNodeSuffixLink(node);
					}
					lastCreatedNodeInThisPhase = node;

					if (this->activePoint->getActiveNode() != this->pRoot) {
						this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
						this->activePoint->getActiveNode()->updateLastToIndexes(leafEnd);
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
	int nodeIndex = 0;
}