#include <iostream>

#include <mInput.h>
#include <Lexer.h>

#include <ast/Node.h>
#include <ast/NumberConst.h>
 int main() {


	mInput::load_code("input.txt");
	Lexer l;
	l.init_keywords();
	
/*	int i = 0;
	while (i++ < 40) {
		Token t = l.next_token();
		i++;
	}
	*/


	Node* n = new Node();
	NumberConst* num = new NumberConst("123");

	num->print_token();
	n = num;
	std::cout << std::endl;
	n->print_token();
	((NumberConst*)n)->get_val();


	//compiler

	return 0;
}