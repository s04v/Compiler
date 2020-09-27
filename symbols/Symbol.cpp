#include <symbols/Symbol.h>
#include <string>

Symbol::Symbol(SymType t, std::string n) {
	type = t;
	name = n;
}
