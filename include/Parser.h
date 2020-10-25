#pragma once
#include <vector>
#include <variant>

#include <Token.h>
#include <ast/Node.h>
#include <ast/NodeType.h>



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




	Node* parse_operand();

	Node* parse_unary();
	Node* parse_mul();
	Node* parse_add();
	Node* parse_great_less();
	Node* parse_cmp();
	Node* parse_and();
	Node* parse_or();
	Node* parse_expr();
	// TODO: add ternary expression 
	/// Expression* parse_ternary(); 


	Node* parse_stmt();


};