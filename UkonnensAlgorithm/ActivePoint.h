#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include "Node.h"
class ActivePoint
{
private:
	int activeEdge, activeLength;
	Node* activeNode;
public:
	ActivePoint(Node* activeNode);
	~ActivePoint();
	int getActiveEdge();
	void setActiveEdge(int activeEdge);
	int getActiveLength();
	void setActiveLength(int activeLength);
	void increaseActiveLength();
	void decreaseActiveLength();
	void increaseActiveEdge();
	Node* getActiveNode();
	void setActiveNode(Node* activeNode);
};


