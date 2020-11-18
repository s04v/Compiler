#pragma once

#include <fstream>
#include <Parser.h>
#include <ast/NodeType.h>
#include <ast/Node.h>

#include <m_assert.h>

#include <symbols/Symbol.h>
#include <symbols/SymbolScope.h>
#include <symbols/SymbolTable.h>


static std::string ret = "";
class Gen {
public:
	
	/*
	0 = R1
	1 = R2
	*/

	short use_reg;
	short prev_reg;
	int freereg[4] = {1, 1, 1, 1};
	const char *reglist[8] = { "eax", "ebx", "ecx", "edx" };
	/*std::string use_reg;
	std::string prev_reg; 
	*/

	SymbolTable st;

	std::ofstream f;

	Gen();
	~Gen();
	void start(std::vector<Node*> p);

	int gen_expr(Node* node);
	void gen_var(Node* node);


	void release_reg();

	
	void new_reg();
	std::string get_reg(int r);
	int alloc_register();
	void free_register(int r);

	int load_const(std::string v);
	int load_var(std::string n);
	int save_var(std::string n, int r);

	int gen_add(int r1, int r2);
	int gen_mul(int r1, int r2);

	int gen_sub(int r1, int r2);
	int gen_div(int r1, int r2);

};

