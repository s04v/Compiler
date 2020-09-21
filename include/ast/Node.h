#pragma once
#include <TokenType.h>

class Node {
public:
	TokenType type;
	

	virtual void print_token();
};