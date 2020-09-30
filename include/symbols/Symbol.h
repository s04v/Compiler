#pragma once
#include <string>


enum SymType {
	VAR_SYM,
	FUNC_SYM,
};

class Symbol {
public:
	SymType type;
	std::string name;
	std::string val;

	Symbol(SymType t, std::string n, std::string v);

};