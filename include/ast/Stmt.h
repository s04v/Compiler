#pragma once
#include <ast/Node.h>
#include <ast/NodeType.h>

class Stmt : public Node {
public:
	virtual NodeType get_type();
};