#include <assert.h>
#include <iostream>

#include <Parser.h>
#include <ast/NumberConst.h>
#include <ast/FloatConst.h>
#include <ast/CharConst.h>
#include <ast/FuncCall.h>
#include <ast/Array.h>
#include <ast/IDname.h>

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


void* Parser::parse_operand() {
	if (tok.type == NUMBER) {
		next();
		return new NumberConst(tok.val);
	}
	else if (tok.type == FLOAT) {
		next();
		return new FloatConst(tok.val);
	}
	else if (tok.type == ID) {
		std::string name = tok.val;
		next();
		
		
		if (tok.type == LPAREN) { // func
			//bug: only 8 args is allowed to pass to function
			next();

			if (tok.type != RPAREN) { 
				Expression **args =   new Expression*[8]();
				int i = 0;
				do
				{
					if (tok.type == COMMA)
						next();

					args[i++] = (Expression*)parse_operand();// TODO: expr
				} while (tok.type == COMMA && i < 8);

				expect(RPAREN);
				return new FuncCall(name,args);
			} 
		}
		else if (tok.type == LBRACKET) { // array
			next();
			Expression* e = (Expression*)parse_operand(); // TODO: expr
			expect(RBRACKET);

			return new Array(name, e);
		}
		
		return new IDname(name);
	}
	
	
	// TODO: char and string 

	return NULL;
}