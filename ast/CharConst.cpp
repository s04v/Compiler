#include <ast/CharConst.h>

CharConst::CharConst(char c) {
	ch = c;
}

NodeType CharConst::get_type() {
	return CHAR_CONST;
}

