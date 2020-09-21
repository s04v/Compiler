#pragma once 

#include <vector>
#include <string>
#include <map>

#include <Token.h>


class Lexer {

public:
	Lexer();

	std::vector<Token> tokens;

	std::map<std::string, TokenType> keywords_map;

	void next();
	void skip();
	void expect(char c);

	void init_keywords();

	Token next_token();

	char* scan_number(); 
	char* scan_hex();
	char* scan_float();

	char scan_char();
	char* scan_str();

	TokenType is_keyword(std::string);
};