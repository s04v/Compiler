#include <vector>
#include <ast/Node.h>
#include <ast/NodeType.h>
#include <ast/Expression.h>
#include <ast/Stmt.h>
#include <ast/IfStmt.h>

IfStmt::IfStmt() {}


IfStmt::IfStmt(Expression* c, std::vector<Stmt*> &t, std::vector<Stmt*> &e, NodeType tp){
	cond = c;
	th = t;
	el = e;
	type = tp;
}


NodeType IfStmt::get_type() {
	return IF;
}