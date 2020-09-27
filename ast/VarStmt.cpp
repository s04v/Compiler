#include <ast/NodeType.h>
#include <ast/VarStmt.h>


VarStmt::VarStmt(NodeType t, std::string n, Expression* e) {
	type = t;
	name = n;
	expr = e;
}

NodeType VarStmt::get_type() {
	return VAR_STMT;
}
