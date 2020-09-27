#pragma once 
#include <vector>

#include <ast/Stmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>


class WhileStmt : public Stmt {

public:
	Expression* cond;
	std::vector<Stmt*> body;

	WhileStmt(Expression* c, std::vector<Stmt*> &b);

	NodeType get_type();
};