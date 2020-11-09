#include <iostream>
#include <fstream>

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
#include <Gen.h>


int main() {

	mInput::load_code("input.txt");
	Lexer l;
	Parser p;
	l.init_keywords();
	
	Gen g;
	g.start();
	/*
	SymbolTable s;
	s.init_scope();
	//test1
	s.add(new Symbol(VAR_SYM, "var1", "val1"));
	s.add(new Symbol(VAR_SYM, "var2", "val2"));
	s.add(new Symbol(VAR_SYM, "var3", "val3"));

	//test2
	std::string s2 = s.get_val("var1");

	//test3
	s.get_val("var4"); // expect error
	*/

	


	
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