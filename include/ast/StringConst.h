#pragma once
#include <iostream>
#include <ast/NodeType.h>
#include <ast/Expression.h>

class StringConst : public Expression {
public:
	std::string val;
	StringConst(std::string v) ;// TODO:

	virtual NodeType get_type();
};