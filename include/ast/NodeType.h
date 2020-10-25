#pragma once 

enum NodeType {
	NODE,
	
	EXPRESSION,
	N_OR_OR,
	N_AND_AND,
	N_EQ,
	N_NOT_EQ,
	N_LT, N_LTEQ,
	N_GT, N_GTEQ,
	

	NUMBER_CONST,
	FLOAT_CONST,
	CHAR_CONST,
	STRING_CONST,
	FUNC_CALL,
	ARRAY,
	ID_NAME,
	VAR,	

	N_ADD, N_SUB, N_MUL, N_DIV, N_MOD,
	N_INC, N_DEC,
	// stmts 
	// var  stmt
	VAR_STMT,

	VAR_DECL,		// var a;
	VAR_DEF,		// var a = 10;
	VAR_ASSIGN,		// a = 10
	VAR_ASSIGN_ADD, // a += 10;
	VAR_ASSIGN_SUB, // ...
	VAR_ASSIGN_MUL, 
	VAR_ASSIGN_DIV, 
	VAR_ASSIGN_MOD, 

	ARR,
	ARR_DECL,		// var a[2];
	ARR_DEF,		// var a[2] = {1,2};
	ARR_ASSIGN,		// a[0] = 10
	ARR_ASSIGN_ADD, // a[1] += 10;
	ARR_ASSIGN_SUB, // ...
	ARR_ASSIGN_MUL,
	ARR_ASSIGN_DIV,
	ARR_ASSIGN_MOD,
	///...

	FUNC,
	FUNC_DEF,
	FUNC_DECL,

	IF,
	IF_THEN,
	IF_ELSE,


	FOR,
	WHILE,

	STMT,
};
