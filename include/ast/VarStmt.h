#pragma once 

#include <string>

#include <ast/Stmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>

class VarStmt : public Stmt {
public:
	NodeType type;
	std::string name; 
	Expression* expr; // assign


	VarStmt(NodeType t, std::string n, Expression* e);

	NodeType get_type();
};