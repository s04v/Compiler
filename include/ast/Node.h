#pragma once
#include <TokenType.h>
#include <ast/NodeType.h>
#include <string>
#include <vector>

class Node {
public:
	NodeType type;
	std::string val;
	
	union {
		Node* left;
		std::vector<Node*> *l;

	};

	Node* mid;
	union{
		Node* right;
		std::vector<Node*> *r;

	};

	Node();

	virtual NodeType get_ntype();
};