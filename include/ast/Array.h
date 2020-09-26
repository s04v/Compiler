#pragma once 
#include <string>

#include <ast/NodeType.h>
#include <ast/Expression.h>


class Array : public Expression {
public:
	std::string val;
	Expression* index; 

	Array(std::string v, Expression* i);

	NodeType get_type();
};