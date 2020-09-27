#pragma once
#include <string>


enum SymType {
	VAR,
	FUNC
};

class Symbol {
public:
	SymType type;
	std::string name;
	std::string val;

	Symbol(SymType t, std::string n);

};