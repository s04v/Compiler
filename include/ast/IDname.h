#pragma once
#include <string>
#include <ast/Expression.h>

class IDname : public Expression{
public:
	std::string val;
	IDname(std::string v);



	virtual NodeType get_type();

};