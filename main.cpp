#include <iostream>

#include <mInput.h>
#include <Lexer.h>
#include <Parser.h>
#include <ast/NodeType.h>

#include <ast/Node.h>
#include <ast/Expression.h>
#include <ast/NumberConst.h>
#include <ast/FuncCall.h>

void* func() {
	NumberConst* n = new NumberConst("123");
	return n;
}


int main() {

	

	mInput::load_code("input.txt");
	Lexer l;
	Parser p;
	l.init_keywords();


	//lexer
	int i = 0;
	while (*mInput::code) {
		Token t = l.next_token();
		i++;
	}
	Token end;
	end.type = END_TOKEN;
	l.tokens.push_back(end);
	p.tokens = l.tokens;
	p.next();
	Expression* e = (Expression*)p.parse_operand();
	NodeType t = e->get_type();	

	//Expression* n = parse_expr(); // TODO:



	//compiler

	return 0;
}