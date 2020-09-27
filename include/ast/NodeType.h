#pragma once 

enum NodeType {

	NODE,
	EXPRESSION,
	NUMBER_CONST,
	FLOAT_CONST,
	CHAR_CONST,
	STRING_CONST,
	FUNC_CALL,
	ARRAY,
	ID_NAME,
		

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