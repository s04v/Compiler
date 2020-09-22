#include <string>
#include <iostream>
#include <ast/FloatConst.h>


FloatConst::FloatConst(std::string v) {
	val = v;
}

void FloatConst::print_token() {
	std::cout << "FloatConst";
}

void FloatConst::get_val()
{
	std::cout << "value = " << val << std::endl;
}

NodeType FloatConst::get_type() {
	return NodeType::NUMBERCONST;
}