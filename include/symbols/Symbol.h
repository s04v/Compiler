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

	short index;

	Symbol(SymType t, std::string n, short i);

};