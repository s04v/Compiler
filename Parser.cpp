#include <assert.h>
#include <iostream>

#include <Parser.h>
#include <ast/NumberConst.h>
#include <ast/FloatConst.h>

Parser::Parser() {}

void Parser::next() {
	tok = tokens[i++];
}

void Parser::save() {
	s = i;
}

void Parser::restore() {
	i = s-1 ;
	next();
}

void Parser::expect(TokenType t) {
	assert(tok.type == t);
	next();
}



void* Parser::parse_rval() {
	if (tok.type == NUMBER) {
		NumberConst* n = new NumberConst(tok.val);
		return n;
	}
	else if (tok.type == FLOAT) {
		FloatConst* f = new FloatConst(tok.val);
		return f;
	}
	else if (tok.type == ID) {
		std::string name = tok.val;
		next();
		expect(LPAREN);
		
		if (tok.type == RPAREN) {
		
		
		}
			// TODO: func parser
			//next();
		expect(RPAREN);
	 

		return NULL;
	}

	return NULL;
}