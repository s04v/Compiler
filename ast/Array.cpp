#include <iostream>

#include <ast/Array.h>
#include <ast/NodeType.h>


Array::Array(std::string v, Expression* i) {
	val = v;
	index = i;
}

NodeType Array::get_token() {
	return ARRAY;
}