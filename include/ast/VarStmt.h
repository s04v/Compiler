#pragma once 

#include <string>

#include <ast/Stmt.h>
#include <ast/Expression.h>
#include <ast/NodeType.h>
#include <ast/Array.h>

class VarStmt : public Stmt {
public:
	NodeType type;
	std::string name; 
	Expression* expr; // assign
	Expression* index; // arr[0] = 10;
	Array* arr; 

	VarStmt(NodeType t, std::string n, Expression* e);
	VarStmt(NodeType t, std::string n, Expression* i, Expression* e); // assign
	VarStmt(NodeType t, std::string n, Expression* i, std::vector<Expression*> &vals); // for arrays

	NodeType get_type();
};