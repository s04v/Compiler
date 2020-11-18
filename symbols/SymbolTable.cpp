#include <symbols/SymbolTable.h>
#include <symbols/SymbolScope.h>

#include <m_assert.h>

SymbolTable::SymbolTable() {}

void SymbolTable::init_scope() {
	SymbolScope s;
	scope.push(s);
}

void SymbolTable::new_scope() {
	SymbolScope s = scope.top();
	
	scope.push(s);
}

void SymbolTable::back_scope() {
	scope.pop();
}

int SymbolTable::get_index(std::string n) {
	return get(n).index;
}

void SymbolTable::add(SymType t, std::string n) {
	if (!contain(n)) {
		scope.top().put(t, n);
		return;
	}
	m_assert(0, "Symbol exists");
}

Symbol SymbolTable::get(std::string n) {
	if(contain(n))
		return scope.top().get(n);
	m_assert(0, "Symbol does not exists");
}



bool SymbolTable::contain(std::string n) {
	return scope.top().contain(n);
}