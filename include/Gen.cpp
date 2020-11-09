#include <Gen.h>

Gen::Gen() {
	f.open("out.asm", std::ofstream::out);
}

Gen::~Gen() {}

void Gen::start() {
	gen_expr();

	f.close();
}

void Gen::gen_expr() {
	f << "expr";
}
