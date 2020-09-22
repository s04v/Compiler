#pragma once
#include <string>
#include <ast/Expression.h>

class ID : public Node {
public:
	std::string val;
	ID(std::string v);

	void print_token();
	void get_val();

	virtual NodeType get_type();

};