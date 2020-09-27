#pragma once 
#include <string>
#include <vector>
#include <ast/NodeType.h>
#include <ast/Expression.h>


class Array : public Expression {
public:
	std::string name;
	Expression* index; 
	std::vector<Expression*> vals;
	
	Array(std::string n, Expression* i, std::vector<Expression*> &v);
	Array(std::string n, Expression* i);

	NodeType get_type();
};