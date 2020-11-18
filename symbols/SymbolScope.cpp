#include <symbols/SymbolScope.h>
#include <symbols/Symbol.h>

#include <m_assert.h>


SymbolScope::SymbolScope() { i = 0; }

void SymbolScope::put(SymType t, std::string name) {
	Symbol s(t, name, i++);
	symbols.insert( std::pair<std::string, Symbol>(name, s) );
}

Symbol SymbolScope::get(std::string name) {
	if (contain(name)) {
		Symbol s = symbols.find(name)->second;
		return s;
	}
	std::cerr << "Symbols does not exists" << std::endl;
	exit(1);
}

bool SymbolScope::contain(std::string name) {
	return !(symbols.find(name) == symbols.end());
}

short SymbolScope::get_index(std::string name) {
	return this->get(name).index;
}
