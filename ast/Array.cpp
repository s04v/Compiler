#include <iostream>
#include <vector>
#include <ast/Array.h>
#include <ast/NodeType.h>



Array::Array(std::string n, Expression* i) {
	name = n;
	index = i;
}

Array::Array(std::string n, Expression* i, std::vector<Expression*> &v) {
	name = n;
	index = i;
	vals = v;
}

NodeType Array::get_type() {
	return ARRAY;
}