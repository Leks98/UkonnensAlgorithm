#include "ActivePoint.h"
ActivePoint::ActivePoint(Node* activeNode): activeEdge(-1), activeLength(0), activeNode(activeNode) {}

ActivePoint::~ActivePoint()
{
	//delete activeNode;
}

int ActivePoint::getActiveEdge()
{
	return this->activeEdge;
}

void ActivePoint::setActiveEdge(int activeEdge)
{
	this->activeEdge = activeEdge;
}

int ActivePoint::getActiveLength()
{
	return this->activeLength;
}

void ActivePoint::setActiveLength(int activeLength)
{
	this->activeLength = activeLength;
}

void ActivePoint::increaseActiveLength()
{
	++this->activeLength;
}

void ActivePoint::decreaseActiveLength()
{
	--this->activeLength;
}


void ActivePoint::increaseActiveEdge()
{
	++this->activeEdge;
}

Node* ActivePoint::getActiveNode()
{
	return this->activeNode;
}

void ActivePoint::setActiveNode(Node* activeNode)
{
	this->activeNode = activeNode;
}
