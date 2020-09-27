#include <ast/ForStmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>


ForStmt::ForStmt(Stmt* i, Expression* c, Expression* n, std::vector<Stmt*> &b) {
	init = i;
	cond = c;
	next = n;
	body = b;
}


NodeType ForStmt::get_type() {
	return FOR;
}