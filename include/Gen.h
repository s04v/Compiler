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
	
	std::ofstream f;

	Gen();
	~Gen();
	void start();
	void gen_expr();

};

