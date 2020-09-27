#include <iostream>
#include <ast/NodeType.h>
#include <ast/FuncCall.h>

FuncCall::FuncCall(std::string v, Expression** a) {
	val = v;
	args = a;
}

NodeType FuncCall::get_type() {
	return FUNC_CALL;
}

