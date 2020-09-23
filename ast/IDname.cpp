#include <iostream>


#include <ast/NodeType.h>
#include <ast/Expression.h>
#include <ast/IDname.h>



IDname::IDname(std::string v) {
	val = v;
}


NodeType IDname::get_type() {
	return ID_NAME;
}