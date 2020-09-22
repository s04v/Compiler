#include <ast/Node.h>
#include <iostream>

void Node::print_token() {
	std::cout << "node";
}

NodeType Node::get_type() {
	return NodeType::NODE;
}