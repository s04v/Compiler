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
	//test
	int get_index(std::string n);

	void add(SymType t, std::string n);
	Symbol get(std::string n);


	bool contain(std::string n);


};