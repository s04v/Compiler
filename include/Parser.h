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
	unsigned long long  i_tok = 0;
	unsigned long long  s_tok = 0;

	Token tok;
public:
	
	std::vector<Token> tokens;


	Parser();

	void next();
	void save();
	void restore();

	void expect(TokenType t, std::string msg);




	Expression* parse_operand();

	Expression* parse_unary();
	Expression* parse_mul();
	Expression* parse_add();
	Expression* parse_great_less();
	Expression* parse_cmp();
	Expression* parse_and();
	Expression* parse_or();
	Expression* parse_expr();
	// TODO: add ternary expression 
	/// Expression* parse_ternary(); 


	Stmt* parse_stmt();


};