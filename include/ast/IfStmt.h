#pragma once 
#include <vector>
#include <ast/Node.h>
#include <ast/NodeType.h>
#include <ast/Expression.h>
#include <ast/Stmt.h>

class IfStmt : public Stmt {
public:
	Expression* cond;
	std::vector<Stmt*> th;
	std::vector<Stmt*> el;
	NodeType type;
	
	IfStmt();
	IfStmt(Expression* c, std::vector<Stmt*> &t, std::vector<Stmt*> &e, NodeType tp);
		

	NodeType get_type();


};