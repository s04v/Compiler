#pragma once 
#include <ast/Node.h>

class IfStmt : public Node {
public:
	const ConditionalStmt* cond;

};