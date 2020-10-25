#pragma once
#include <TokenType.h>
#include <ast/NodeType.h>
#include <string>


class Node {
public:
	NodeType type;
	std::string val;
	
	Node* left;
	Node* mid;
	Node* right;


	Node();

	virtual NodeType get_ntype();
};