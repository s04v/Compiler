#include <symbols/Symbol.h>
#include <string>

Symbol::Symbol(SymType t, std::string n, short i) {
	type = t;
	name = n;
	index = i;
}
