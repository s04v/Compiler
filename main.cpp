#include <iostream>

#include <mInput.h>
#include <Lexer.h>
#include <Parser.h>
#include <ast/NodeType.h>

#include <ast/Node.h>

#include <m_assert.h>

#include <symbols/Symbol.h>
#include <symbols/SymbolScope.h>
#include <symbols/SymbolTable.h>
#include <vector>

class test {

	test* t1;
	test* t2;
	std::string val;

	test(){}

};
int main() {

	mInput::load_code("input.txt");
	Lexer l;
	Parser p;
	l.init_keywords();


	//lexer
	int i = 0;
	//TODO: fix bug with space in end of line

	while (*mInput::code ) {
		Token t = l.next_token();
		i++;
	}
	Token end;
	end.type = END_TOKEN;
	l.tokens.push_back(end);
	p.tokens = l.tokens;
	p.next();
	

	
	Node* e = p.parse_stmt();


	int a = 10;
	// compiler

	return 0;
}