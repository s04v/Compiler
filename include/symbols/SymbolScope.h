#pragma once

#include <map>
#include <string>
#include <symbols/Symbol.h>

class SymbolScope {
public:
	std::map<std::string, Symbol> symbols;
	short i;

	SymbolScope();

	void put(SymType t, std::string name);
	Symbol get(std::string name);
	bool contain(std::string name);

	short get_index(std::string name);
};