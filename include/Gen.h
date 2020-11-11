#pragma once

#include <fstream>
#include <Parser.h>
#include <ast/NodeType.h>
#include <ast/Node.h>

#include <m_assert.h>

#include <symbols/Symbol.h>
#include <symbols/SymbolScope.h>
#include <symbols/SymbolTable.h>



class Gen {
public:
	
	/*
	0 = eax
	1 = ebx
	2 = ecx
	3 = edx
	*/
	short reg;
	std::string use_reg;
	std::string prev_reg; 
	

	SymbolTable st;

	std::ofstream f;

	Gen();
	~Gen();
	void start(Node* node);

	std::string gen_expr(Node* node);
	void gen_var(Node* node);


	void release_reg();

	void get_reg();
	void new_reg();
};

