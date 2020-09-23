#include <ast/StringConst.h>
#include <ast/NodeType.h>

StringConst::StringConst(std::string v) {
	val = v;
}

NodeType StringConst::get_type() {
	return NodeType::STRING_CONST;
}