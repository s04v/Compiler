#include <vector>
#include <ast/NodeType.h>
#include <ast/VarStmt.h>
#include <ast/Array.h>


VarStmt::VarStmt(NodeType t, std::string n, Expression* e) {
	type = t;
	name = n;
	expr = e;
}

VarStmt::VarStmt(NodeType t, std::string n, Expression* i, Expression* e) {
	type = t;
	name = n;
	index = i;
	expr = e;
}

VarStmt::VarStmt(NodeType t, std::string n, Expression* i, std::vector<Expression*> &vals) {
	type = t;
	arr = new Array(n,i,vals);
}


NodeType VarStmt::get_type() {
	return VAR_STMT;
}
