#pragma once 
#include <vector>

#include <ast/Stmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>


class ForStmt : public Stmt {

public:
	Stmt* init;
	Expression* cond ;
	Expression* next;
	std::vector<Stmt*> body;

	ForStmt(Stmt* i, Expression* c, Expression* n, std::vector<Stmt*> &b);

	NodeType get_type();
};