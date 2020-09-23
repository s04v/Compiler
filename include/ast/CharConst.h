#pragma once

#include <ast/Expression.h>


class CharConst : public Expression {
public:
	char ch;
	
	CharConst(char c);

	virtual NodeType get_type();
};