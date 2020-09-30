#pragma once

#include <map>
#include <string>
#include <symbols/Symbol.h>

class SymbolScope {
public:
	std::map<std::string, Symbol> symbols;

	SymbolScope();

	void put(SymType t, std::string name, std::string val);
	Symbol get(std::string name);
	bool contain(std::string name);
};