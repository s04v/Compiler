#include <symbols/Symbol.h>
#include <string>

Symbol::Symbol(SymType t, std::string n, std::string v, short i) {
	type = t;
	name = n;
	val = v;
	index = i;
}
