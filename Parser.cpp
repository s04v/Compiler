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
#include <ast/VarStmt.h>
#include <ast/Func.h>
#include <ast/IfStmt.h>
#include <ast/ForStmt.h>
#include <ast/WhileStmt.h>

#include <m_assert.h>

Parser::Parser() {}

void Parser::next() {
	tok = tokens[i_tok++];
}

void Parser::save() {
	s_tok = i_tok;
}

void Parser::restore() {
	i_tok = s_tok-1 ;
	next();
}

void Parser::expect(TokenType t, std::string msg = "") {
	if (!msg.empty()) {
		m_assert(tok.type == t, msg);
		next();
		return;
	}
	assert(tok.type == t);
	next();
}


Expression* Parser::parse_operand() {
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
			//TODO: fix bug - only 8 args is allowed to pass to function
			next();

			if (tok.type != RPAREN) { 
				Expression **args =   new Expression*[8]();
				int i = 0;
				do
				{
					if (tok.type == COMMA)
						next();

					args[i++] = parse_expr();
				} while (tok.type == COMMA && i < 8);

				expect(RPAREN);
				return new FuncCall(name,args);
			} 
			next();
			return new FuncCall(name, NULL);
		}
		else if (tok.type == LBRACKET) { // array
			next();
			Expression* e = parse_expr(); // index
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
		next();
		return e1;
	}
	else if (tok.type == DEC){
		e1->etype = DEC;
		next();
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


Stmt* Parser::parse_stmt() {
	
	std::string name;


	switch (tok.type) {
	case ID: {
		save();
		Expression* e = parse_unary();
		TokenType t = e->etype;
		if (t == INC || t == DEC || e->get_type() == FUNC_CALL) {
			//next();
			expect(SEMICOLON, "Missing ;");
			return e;
		}
		restore();
		name = tok.val;
		next();

		// array
		if (tok.type == LBRACKET) {
			next();

			Expression* index = parse_expr();
			
			expect(RBRACKET, "Missing ]");

			NodeType nt;
			switch (tok.type) {
			case ASSIGN:
				nt = ARR_ASSIGN;
				break;
			case ADD_ASSIGN:
				nt = ARR_ASSIGN_ADD;
				break;
			case SUB_ASSIGN:
				nt = ARR_ASSIGN_SUB;
				break;
			case MUL_ASSIGN:
				nt = ARR_ASSIGN_MUL;
				break;
			case DIV_ASSIGN:
				nt = ARR_ASSIGN_DIV;
				break;
			case MOD_ASSIGN:
				nt = ARR_ASSIGN_MOD;
				break;
			default:
				m_assert(0, "Error token");
			}

			next();
			VarStmt* s = new VarStmt(nt, name,index, parse_expr());
			expect(SEMICOLON, "Missing ;");
			return s;

		}

		// if not an array
		NodeType nt;
		switch (tok.type) {
		case ASSIGN:
			nt = VAR_ASSIGN;
			break;
		case ADD_ASSIGN:
			nt = VAR_ASSIGN_ADD;
			break;
		case SUB_ASSIGN:
			nt = VAR_ASSIGN_SUB;
			break;
		case MUL_ASSIGN:
			nt = VAR_ASSIGN_MUL;
			break;
		case DIV_ASSIGN:
			nt = VAR_ASSIGN_DIV;
			break;
		case MOD_ASSIGN:
			nt = VAR_ASSIGN_MOD;
			break;
		default :
			m_assert(0, "Error token");
		}
		next();
		VarStmt* s = new VarStmt(nt, name, parse_expr());
		expect(SEMICOLON, "Missing ;");
		return s;

		//m_assert(0, "Invalid expression");
	}
	case LET_KEY: {
		next();
		m_assert(tok.type == ID, "Invalid ID");
		name = tok.val;
		next();
		if (tok.type == SEMICOLON)
			return new VarStmt(VAR_DECL, name, NULL);


		// let arr[10] = {12,3, 4, 5, 6, 7}
		// TODO: check size  of init list  and index


		if (tok.type == LBRACKET) {
			next();
			Expression* index = parse_operand();
			m_assert(index->get_type() == NUMBER_CONST, "Index must be constant value");
			expect(RBRACKET, "Missing ]");

			if (tok.type == SEMICOLON)
				return new VarStmt(ARR_DECL, name, index, NULL);

			next();
			expect(ASSIGN, "Expect assing operator");
			expect(LBRACE, "Missing { ");
			
			std::vector<Expression*> vals;
			
			do
			{
				if (tok.type == COMMA)
					next();
				
				vals.push_back(parse_expr());
//					next();
				
			} while (tok.type == COMMA);

			expect(RBRACE, "Missing } ");
			expect(SEMICOLON, "Missing ; ");

			return new VarStmt(ARR_DEF, name, index, vals);
			
		} 

		expect(ASSIGN," Expect assing operator");
		VarStmt* s = new VarStmt(VAR_DEF, name, parse_expr());
		
		m_assert(tok.type == SEMICOLON, "Missing ;");
		next();

		return s;
		// TODO: var assing ...
	}
	case FUNC_KEY: {
		next();
		m_assert(tok.type == ID, "Invalid ID");
		name = tok.val;
		next();
		expect(LPAREN, "Missing (");
		
	

		std::string* args = new std::string[8];
		int i = 0;
		do
		{
			if (tok.type == COMMA)
				next();
			if (tok.type == ID) {
				args[i++] = tok.val;
				next();
			}
			else {
				m_assert(0, "Invalid ID");
			}
		} while (tok.type == COMMA && i < 8);
		expect(RPAREN, "Missing )");

		if (tok.type == SEMICOLON)
			return new Func(FUNC_DECL, name, args); 
		else if (tok.type == LBRACE) {
			next();
			std::vector<Stmt*> body;

			while (tok.type != RBRACE) {
				body.push_back(parse_stmt());
				NodeType st = body[0]->get_type();
				if (st == FUNC)
					m_assert(0, "Invalid Statment");
			}

			expect(RBRACE, "Missing }");

			return new Func(FUNC_DEF, name, args, body);
		}

		
	}
	case IF_KEY: {
		next();
		IfStmt* s = new IfStmt();
		expect(LPAREN, "Missing (");
		s->cond = parse_expr();
		expect(RPAREN, "Missing )");
		
		expect(LBRACE, "Missing {");
		
		std::vector<Stmt*> body_th;

		while (tok.type != RBRACE) {
			body_th.push_back(parse_stmt());
			NodeType st = body_th[0]->get_type();
			if (st == FUNC)
				m_assert(0, "Invalid Statment");
		}
		s->th = body_th;
		expect(RBRACE, "Missing }");

		if (tok.type != ELSE_KEY){
			s->type = IF_THEN;
			return s;
		}
		next();
		
		expect(LBRACE, "Missing {");

		std::vector<Stmt*> body_el;

		while (tok.type != RBRACE) {
			body_el.push_back(parse_stmt());
			NodeType st = body_el[0]->get_type();
			if (st == FUNC)
				m_assert(0, "Invalid Statment");
		}
		s->el = body_el;

		expect(RBRACE, "Missing }");
		s->type = IF_ELSE;

		return s;
	}
	case FOR_KEY: {
		next();
		Stmt* init = NULL;
		Expression* cond = NULL;
		Expression* next = NULL;
		std::vector<Stmt*> body;

		expect(LPAREN, "Missing (");
		init = parse_stmt();
		cond = parse_expr();
		expect(SEMICOLON, "Missing ;");
		next = parse_expr();
		expect(RPAREN, "Missing )");
		expect(LBRACE, "Missing {");

		

		while (tok.type != RBRACE) {
			body.push_back(parse_stmt());
			NodeType st = body[0]->get_type();
			if (st == FUNC)
				m_assert(0, "Invalid Statment");
		}

		expect(RBRACE, "Missing }");
		return new ForStmt(init, cond, next,body);
	}
	case WHILE_KEY: {
		next();
		Expression* cond = NULL;
		std::vector<Stmt*> body;

		expect(LPAREN, "Missing (");
		cond = parse_expr();
		expect(RPAREN, "Missing )");
		expect(LBRACE, "Missing {");

		while (tok.type != RBRACE) {
			body.push_back(parse_stmt());
			NodeType st = body[0]->get_type();
			if (st == FUNC)
				m_assert(0, "Invalid Statment");
		}

		expect(RBRACE, "Missing }");

		return new WhileStmt(cond, body);
	}
	case CONTINUE_KEY:
	case BREAK_KEY: {
		Expression* e = new Expression();
		e->etype = tok.type;
		next();
		expect(SEMICOLON, "Missing ;");
		return e;
	}
	
	default:
		
		std::cout << "[parse_stmt] invalid token" << std::endl;
		exit(1);
	}
}