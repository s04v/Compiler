#pragma once
#include <string>
#include <ast/Node.h>

class NumberConst : public Node {
public:
	std::string val;
	NumberConst(std::string v);


	void print_token();

	void get_val();
	
};