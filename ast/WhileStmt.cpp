#include <ast/WhileStmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>


WhileStmt::WhileStmt(Expression* c,  std::vector<Stmt*> &b) {
	cond = c;
	body = b;

}


NodeType WhileStmt::get_type() {
	return WHILE;
}