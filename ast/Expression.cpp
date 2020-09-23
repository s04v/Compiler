#include <ast/Expression.h>
#include <iostream>

Expression::Expression() {}

void Expression::print_token() {
	std::cout << "Expression" << std::endl;
}

void Expression::print_expr() {
	std::cout << "Expression true" << std::endl;
}

NodeType Expression::get_type() {
	return NodeType::EXPRESSION;
}