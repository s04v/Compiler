#pragma once
#include <string>
#include <ast/Expression.h>

class FloatConst : public Expression {
public:
	std::string val;
	FloatConst(std::string v);
	

	void get_val();

	virtual NodeType get_type();
	void print_token();


};