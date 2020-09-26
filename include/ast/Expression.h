#pragma once
#include <ast/Node.h>
#include <TokenType.h>


class Expression : public Node {
public:
	
	
	
	Expression* expr1;
	Expression* expr2;

	TokenType etype;

	Expression(TokenType et, Expression* e1, Expression* e2);
	Expression();

	virtual void print_token();
	virtual NodeType get_type();
	void print_expr();

};

