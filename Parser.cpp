#include <assert.h>
#include <iostream>

#include <Parser.h>
#include <ast/NumberConst.h>
#include <ast/FloatConst.h>
#include <ast/CharConst.h>
#include <ast/StringConst.h>
#include <ast/FuncCall.h>
#include <ast/Array.h>
#include <ast/IDname.h>
#include <ast/ExprType.h>


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
		std::string val = tok.val;
		next();
		return new NumberConst(val);
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
	else if (tok.type == CHAR) {
		return new CharConst(*(tok.val.c_str()));
	} 
	else if (tok.type == STRING) {
		return new StringConst(tok.val);
	}
	else if (tok.type == LPAREN) {
		next();
		Expression* e = parse_expr();
		expect(RPAREN);
		
		return e;
	}

	return NULL;
}

Expression* Parser::parse_unary() {
	
	//TODO: change expression intialization
	Expression* e1 = new Expression();

	e1->expr1 = (Expression*)parse_operand();
	
	if (tok.type == INC) {
		e1->etype = INC;
			return e1;
	}
	else if (tok.type == DEC){
		e1->etype = DEC;
		return e1;
	}

	return e1->expr1;
}

Expression* Parser::parse_mul() {
	Expression* expr = parse_unary();

	while (tok.type == MUL || tok.type == DIV || tok.type == MOD) {
		TokenType t = tok.type;
		next();
		expr = new Expression(t, expr, parse_unary());
	}

	return expr;
}

Expression* Parser::parse_add() {
	Expression* expr = parse_mul();

	while (tok.type == ADD || tok.type == SUB) {
		TokenType t = tok.type;
		next();
		expr = new Expression(t, expr, parse_mul());
	}
	return expr;
}

Expression* Parser::parse_great_less() {
	Expression* expr = parse_add();
	while (tok.type == GT || tok.type == GTEQ || tok.type == LT || tok.type == LTEQ) {
		TokenType t = tok.type;
		next();
		expr = new Expression(t, expr, parse_add());
	}

	return expr;
}

Expression* Parser::parse_cmp() {
	Expression* expr = parse_great_less();
	while (tok.type == EQ || tok.type == NOT_EQ) {
		TokenType t = tok.type;
		next();
		expr = new Expression(t, expr, parse_great_less());
	}
	return expr;
}

Expression* Parser::parse_and() {
	Expression* expr = parse_cmp();
	while (tok.type == AND_AND) {
		TokenType t = tok.type;
		next();
		expr = new Expression(AND_AND, expr, parse_cmp());
	}
	return expr;
}

Expression* Parser::parse_or() {
	Expression* expr = parse_and();
	while (tok.type == OR_OR) {
		TokenType t = tok.type;
		next();
		expr = new Expression(OR_OR, expr, parse_and());
	}
	return expr;
}

Expression* Parser::parse_expr() {
	return parse_or();
}



