#pragma once

#include <iostream>
#include <vector>
#include <ast/Stmt.h>
#include <ast/NodeType.h>


class Func : public Stmt {
public:
	NodeType type;
	std::string name;
	std::string* args;
	
	std::vector<Stmt*> body; // userd only if definition


	Func(NodeType t, std::string n, std::string* a);
	Func(NodeType t, std::string n, std::string* a, std::vector<Stmt*> &b);

	NodeType get_type();
};