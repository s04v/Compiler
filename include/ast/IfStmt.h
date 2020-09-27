#pragma once 

#include <ast/Node.h>
#include <ast/NodeType.h>
#include <ast/Expression.h>
#include <ast/Stmt.h>

class IfStmt : public Stmt {
public:
	Expression* cond;
	Stmt* th;
	Stmt* el;
	NodeType type;
	
	IfStmt();
	IfStmt(Expression* c, Stmt* t, Stmt* e, NodeType tp);
		

	NodeType get_type();


};