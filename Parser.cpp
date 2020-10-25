#include <assert.h>
#include <iostream>
#include <string>

#include <Parser.h>

#include <ast/Node.h>
#include <ast/NodeType.h>
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


Node* Parser::parse_operand() {
	if (tok.type == NUMBER) {
		Node* r = new Node();
		r->type = NodeType::NUMBER_CONST;
		r->val = tok.val;
		next();
		
		return r;
	}
	else if (tok.type == FLOAT) {
		next();
		Node* r = new Node();
		r->type = NodeType::FLOAT_CONST;
		r->val = tok.val;
		next();
		return r;
	}
	else if (tok.type == ID) {
		std::string name = tok.val;
		next();
	
		
		if (tok.type == LPAREN) { // func
			//TODO: fix bug - only 8 args is allowed to pass to function
			next();

			if (tok.type != RPAREN) { 
				Node** args = new Node*[8]();
				int i = 0;
				do
				{
					if (tok.type == COMMA)
						next();

					args[i++] = parse_expr();
				} while (tok.type == COMMA && i < 8);

				expect(RPAREN);
				Node* r = new Node();
				r->type = NodeType::FUNC_CALL;
				r->val = name;
				r->mid = *args;
				return r;
			} 
			Node* r = new Node();
			r->type = NodeType::FUNC_CALL;
			r->val = name;

			next();
			return r;
		}
		/*else if (tok.type == LBRACKET) { // array
			next();
			Node* e = parse_expr(); // index
			expect(RBRACKET);

			//return new Array(name, e);
		}*/
		Node* r = new Node();
		r->type = NodeType::ID_NAME;
		r->val = name;

		return r;
	}

	else if (tok.type == CHAR) {
		Node* r = new Node();
		r->type = NodeType::CHAR_CONST;
		r->val = tok.val;
		return r;
	} 
	else if (tok.type == STRING) {
		Node* r = new Node();
		r->type = NodeType::STRING_CONST;
		r->val = tok.val;
		return r;
	}

	else if (tok.type == LPAREN) {
		next();
		Node* e = parse_expr();
		expect(RPAREN);
		
		return e;
	}

	return NULL;
}
Node* Parser::parse_unary() {
	
	//TODO: change expression intialization
	Node* e1 = new Node();

	e1->left = parse_operand();
	
	if (tok.type == TokenType::INC) {
		e1->type = NodeType::N_INC;
		next();
		return e1;
	}
	else if (tok.type == TokenType::DEC){
		e1->type = NodeType::N_DEC;
		next();
		return e1;
	}

	return e1->left;
}

Node* Parser::parse_mul() {
	Node* expr = parse_unary();

	//Node* r = new Node();
	while (tok.type == TokenType::MUL || tok.type == TokenType::DIV || tok.type == TokenType::MOD) {
		TokenType t = tok.type;
		next();
		
		expr->left = new Node(*expr);

		switch (t) {
		case TokenType::MUL:
			expr->type = NodeType::N_MUL;
			break;
		case TokenType::DIV:
			expr->type = NodeType::N_DIV;
			break;
		case TokenType::MOD:
			expr->type = NodeType::N_MOD;
		}
		
		expr->right = parse_unary();
	}

	return expr;
}

Node* Parser::parse_add() {
	Node* expr = parse_mul();
	
	while (tok.type == TokenType::ADD || tok.type == TokenType::SUB) {
		TokenType t = tok.type;
		next();
		expr->left = new Node(*expr);
		expr->type = t == TokenType::ADD ? NodeType::N_ADD : NodeType::N_SUB;

		expr->right = parse_mul();
	}
	return expr;
}

Node* Parser::parse_great_less() {
	Node* expr = parse_add();
	Node* r = new Node();

	while (tok.type == TokenType::GT || tok.type == TokenType::GTEQ || tok.type == TokenType::LT || tok.type == TokenType::LTEQ) {
		TokenType t = tok.type;
		next();
		
		
		expr->left = new Node(*expr);

		switch (t) {
		case TokenType::GT:
			expr->type = NodeType::N_GT;
			break;
		case TokenType::GTEQ:
			expr->type = NodeType::N_GTEQ;
			break;
		case TokenType::LT:
			expr->type = NodeType::N_LT;
			break;
		case TokenType::LTEQ:
			expr->type = NodeType::N_LTEQ;
			break;
		}
		expr->right = parse_add();
	}

	return expr;
}

Node* Parser::parse_cmp() {
	Node* expr = parse_great_less();

	while (tok.type == TokenType::EQ || tok.type == TokenType::NOT_EQ) {
		TokenType t = tok.type;
		next();

		expr->left = new Node(*expr);
		expr->type = t == TokenType::EQ ? NodeType::N_EQ : NodeType::N_NOT_EQ;

		expr->right = parse_great_less();
	}
	return expr;
}

Node* Parser::parse_and() {
	Node* expr = parse_cmp();

	while (tok.type == TokenType::AND_AND) {
		TokenType t = tok.type;
		next();
		expr->left = new Node(*expr);


		expr->type = NodeType::N_AND_AND;

		expr->right = parse_cmp();
	}
	return expr;
}

Node* Parser::parse_or() {
	Node* expr = parse_and();
	Node* r = new Node();

	while (tok.type == TokenType::OR_OR) {
		TokenType t = tok.type;
		next();
		r->type = NodeType::N_OR_OR;

		r->left = new Node(*expr);;
		r->right = parse_and();
	}
	return expr;
}

Node* Parser::parse_expr() {
	return parse_or();
}


//stmt
/*
Node* Parser::parse_stmt() {
	
	std::string name;


	switch (tok.type) {
	case ID: {
		save();
		Node* e = parse_unary();
		NodeType t = e->type;
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

*/
