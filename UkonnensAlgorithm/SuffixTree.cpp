#include "SuffixTree.h"
SuffixTree::SuffixTree(const std::string& textToAnalize):
	textToAnalyze(textToAnalize),
	remaining(0),
	pRoot(new Node()),
	lastUpdatedLeaf(nullptr)
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
			this->activePoint->getActiveNode()->updateLastToIndexes(this->textToAnalyze, leafEnd);
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
			this->activePoint->getActiveNode()->updateLastToIndexes(this->textToAnalyze, leafEnd);
		}
		else {
			this->activePoint->increaseActiveLength();
		}
	
}

const std::string& SuffixTree::getTextToAnalyze()
{
	return this->textToAnalyze;
}

void SuffixTree::build()
{
	int position = 0;
	int leafEnd = position;
	while (position < this->textToAnalyze.length()) {
		leafEnd++;
		this->activePoint->getActiveNode()->updateLastToIndexes(this->textToAnalyze, leafEnd);
		Node* lastCreatedNodeInThisPhase = nullptr;
		this->remaining++;

		while (this->remaining > 0) {
			if (this->activePoint->getActiveLength() == 0)
			{

				if (selectNode(position) != nullptr) {

					this->activePoint->setActiveEdge(selectNode(position)->getFromIndex());
					this->activePoint->increaseActiveLength();
					selectNode(position)->updateLastToIndexes(this->textToAnalyze, leafEnd);
					break;
				}
				else {
					this->activePoint->getActiveNode()->addChildNodeByRangeBack(position, leafEnd);
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
						Node* newInternalNode = new Node(beginningFromIndex, beginningFromIndex + this->activePoint->getActiveLength(),this->activePoint->getActiveNode());
						Node* newLeafNode = new Node(position, leafEnd,newInternalNode);


						this->activePoint->getActiveNode()->addInternalNodeInSamePosition(newInternalNode, nodeStartingWithChar);

						nodeStartingWithChar->setParentNode(newInternalNode);
						newInternalNode->addChildNodeBack(nodeStartingWithChar);
						newInternalNode->addChildNodeBack(newLeafNode);
						nodeStartingWithChar->setFromIndex(beginningFromIndex + this->activePoint->getActiveLength());
						if (lastCreatedNodeInThisPhase != nullptr) {
							lastCreatedNodeInThisPhase->setNodeSuffixLink(newInternalNode);
						}

						lastCreatedNodeInThisPhase = newInternalNode;
						newInternalNode->setNodeSuffixLink(pRoot);

						nodeStartingWithChar->updateLastToIndexes(this->textToAnalyze, leafEnd);
						newInternalNode->updateLastToIndexes(this->textToAnalyze, leafEnd);
						
						if (this->activePoint->getActiveNode() != this->pRoot) {
							this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
							this->activePoint->getActiveNode()->updateLastToIndexes(this->textToAnalyze, leafEnd);

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
					Node* newLeafNode = new Node(position, leafEnd, node);
						
					node->addChildNodeBack(newLeafNode);
					if (lastCreatedNodeInThisPhase != nullptr) {
						lastCreatedNodeInThisPhase->setNodeSuffixLink(node);
					}
					lastCreatedNodeInThisPhase = node;

					node->updateLastToIndexes(this->textToAnalyze, leafEnd);
					

					if (this->activePoint->getActiveNode() != this->pRoot) {
						this->activePoint->setActiveNode(this->activePoint->getActiveNode()->getNodeSuffixLink());
						this->activePoint->getActiveNode()->updateLastToIndexes(this->textToAnalyze, leafEnd);

						
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
	pRoot->updateAllLastToIndexes(textToAnalyze, position, this->lastUpdatedLeaf);
}