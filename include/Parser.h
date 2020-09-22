#pragma once
#include <vector>
#include <variant>

#include <Token.h>
#include <ast/Node.h>
#include <ast/NodeType.h>
#include <ast/Stmt.h>
#include <ast/Expression.h>
#include <ast/NumberConst.h>
#include <ast/FloatConst.h>


class Parser {
	unsigned long long  i = 0;
	unsigned long long  s = 0;

	Token tok;
public:
	
	std::vector<Token> tokens;


	Parser();

	void next();
	void save();
	void restore();

	void expect(TokenType t);


	void* parse_rval();
};