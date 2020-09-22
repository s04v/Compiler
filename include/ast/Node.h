#pragma once
#include <TokenType.h>
#include <ast/NodeType.h>
class Node {
public:
	TokenType type;
	
	virtual void print_token();
	virtual NodeType get_type();


	static Node* parse_node() {}
};