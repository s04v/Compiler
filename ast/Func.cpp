#include <ast/Func.h>
#include <ast/NodeType.h>

Func::Func(NodeType t, std::string n, std::string* a) {
	type = t;
	name = n;
	args = a;
}

Func::Func(NodeType t, std::string n, std::string* a, std::vector<Stmt*> &b) {
	type = t;
	name = n;
	args = a;
	body = b;
}
NodeType Func::get_type() {
	return FUNC;
}