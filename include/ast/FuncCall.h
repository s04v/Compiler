#pragma once
#include <iostream>
#include <ast/NodeType.h>
#include <ast/Expression.h>

class FuncCall : public Expression {
public:
	std::string val;
	Expression** args;


	FuncCall(std::string v, Expression** a);// TODO:

	 NodeType get_type();
};