#pragma once
#include <ast/Node.h>

class Expression : public Node {
public:
	Expression* expr1;
	Expression* expr2;


	Expression();

	virtual void print_token();
	virtual NodeType get_type();
	void print_expr();

};

