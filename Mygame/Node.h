#ifndef NODE_H
#define NODE_H


class Node
{
public:
	Node();
	Node *parent;
	bool walkability;
	int id;
	int parentId;
	int col;
	int row;

	int gCost;
	int hCost;
	int getFCost() {
		return gCost + hCost;
	}
	int elementNo;
	~Node();
};

#endif // ! NODE_H