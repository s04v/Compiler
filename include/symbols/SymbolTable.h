#pragma once 

#include <stack>
#include <string>

#include <symbols/Symbol.h>
#include <symbols/SymbolScope.h>


class SymbolTable {
private:
	std::stack<SymbolScope> scope;
public:

	SymbolTable();

	void init_scope();
	void new_scope();
	void back_scope();

	void add(Symbol* s);
	Symbol get(std::string n);
	std::string get_val(std::string n);

	bool contain(std::string n);


};