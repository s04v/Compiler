#include <string>
#include <iostream>
#include <ast/NumberConst.h>


NumberConst::NumberConst(std::string v) {
	val = v;
}

void NumberConst::print_token()  {
	std::cout << "NumberConst";
}

void NumberConst::get_val()
{
	std::cout << "value = "<< val << std::endl;
}

NodeType NumberConst::get_type() {
	return NodeType::NUMBER_CONST;
}