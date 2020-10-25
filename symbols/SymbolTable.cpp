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

void SymbolTable::add(Symbol* s) {
	if (!contain(s->name)) {
		scope.top().put(s->type, s->name, s->val);
		return;
	}
	m_assert(0, "Symbol exists");
}

Symbol SymbolTable::get(std::string n) {
	if(contain(n))
		return scope.top().get(n);
	m_assert(0, "Symbol does not exists");
}

std::string SymbolTable::get_val(std::string n) {
	return get(n).val;
}


bool SymbolTable::contain(std::string n) {
	return scope.top().contain(n);
}