#include <symbols/Symbol.h>
#include <string>

Symbol::Symbol(SymType t, std::string n, std::string v) {
	type = t;
	name = n;
	val = v;
}
