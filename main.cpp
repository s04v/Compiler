#include <iostream>

#include <mInput.h>
#include <Lexer.h>

 int main() {


	mInput::load_code("input.txt");
	Lexer l;
	l.init_keywords();
	
	int i = 0;
	while (i++ < 40) {
		Token t = l.next_token();
		i++;
	}


	//compiler

	return 0;
}