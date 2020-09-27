#include <assert.h>
#include <iostream>

#include <Lexer.h>
#include <mInput.h>


#define CASE1(c1, k1) \
    case c1: \
        tok.type = k1; \
        mInput::code++; \
        break;

#define CASE2(c1, k1, c2, k2) \
    case c1: \
        tok.type = k1; \
        mInput::code++; \
        if (*mInput::code == c2) { \
            tok.type = k2; \
            mInput::code++; \
        } \
        break;

#define CASE3(c1, k1, c2, k2, c3, k3) \
    case c1: \
        tok.type = k1; \
        mInput::code++; \
        if (*mInput::code == c2) { \
            tok.type = k2; \
            mInput::code++; \
        } else if (*mInput::code == c3) { \
            tok.type = k3; \
            mInput::code++; \
        } \
        break;



Lexer::Lexer() {};

void Lexer::next() {
	*mInput::code++;
}

void Lexer::skip() {
	while(*mInput::code == ' ' || *mInput::code == '\n' || *mInput::code == '\r' || *mInput::code == '\t')
		next();
}

void Lexer::expect(char c) {
	assert(*mInput::code == c);
	next();
	skip();
}

void Lexer::init_keywords() {
	keywords_map["let"] = LET_KEY;
	keywords_map["const"] = CONST_KEY;
	keywords_map["static"] = STATIC_KEY;
	keywords_map["struct"] = STRUCT_KEY;
	keywords_map["func"] = FUNC_KEY;
	keywords_map["if"] = IF_KEY;
	keywords_map["else"] = ELSE_KEY;

	keywords_map["for"] = FOR_KEY;
	keywords_map["while"] = WHILE_KEY;
	keywords_map["continue"] = CONTINUE_KEY;
	keywords_map["break"] = BREAK_KEY;

	
}



Token Lexer::next_token() {
	skip();
	Token tok;
	char* start = mInput::code;
	switch (*mInput::code) {
	case '0': case '1': case '2': case '3': case '4': case '5':case '6': case '7':case '8': case '9': {
		mInput::code++;
		if (*mInput::code == 'x')
		{
			mInput::code = start;
			tok.val = scan_hex();

			tok.type = NUMBER_HEX;
			break;
		}
		else {
			mInput::code = start;
			while (isdigit(*mInput::code)) {
				mInput::code++;
			}
			
			char c = *mInput::code;
			mInput::code = start;
			if (c == '.') {
				tok.val = scan_float(); 
				tok.type = FLOAT;	
				break;
			} else {
				tok.val = scan_number(); 
				tok.type = NUMBER;
				break;
			}

		}
	}
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
	case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
	case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case '_': {
		while (isalnum(*mInput::code) || *mInput::code == '_') {
			tok.val += *mInput::code++;
		}

		if ((tok.type = is_keyword(tok.val)) == NULL_TOKEN) {
			tok.type = ID;
		}

		break;
	}

	case '\'': {
		tok.val = scan_char(); 
		tok.type = CHAR;
		break;
	}
	case '"': {
		tok.val = scan_str(); 
		tok.type = STRING;
		next();
		break;
	}


	CASE1('(', LPAREN)
	CASE1(')', RPAREN)
	CASE1('{', LBRACE)
	CASE1('}', RBRACE)
	CASE1('[', LBRACKET)
	CASE1(']', RBRACKET)
	CASE1(',', COMMA)
	CASE1('?', QUESTION)
	CASE1(';', SEMICOLON)
	CASE1('~', NEG)
	CASE2('!', NOT, '=', NOT_EQ)
	CASE2('=', ASSIGN, '=', EQ)
	CASE2('<', LT, '=', LTEQ)
	CASE2('>', GT, '=', GTEQ)
	CASE2('^', XOR, '=', XOR_ASSIGN)
	CASE2('*', MUL, '=', MUL_ASSIGN)
	CASE2('/', DIV, '=', DIV_ASSIGN)
	CASE2('%', MOD, '=', MOD_ASSIGN)
	CASE3('+', ADD, '=', ADD_ASSIGN, '+', INC)
	CASE3('-', SUB, '=', SUB_ASSIGN, '-', DEC)
	CASE3('&', AND, '=', AND_ASSIGN, '&', AND_AND)
	CASE3('|', OR, '=', OR_ASSIGN, '|', OR_OR)
	default:
		std::cout << "Invalid" << *mInput::code << "token, skipping" << std::endl;
		// stream++;
		exit(1);
	}
	tokens.push_back(tok);
	return tok;
}



char* Lexer::scan_number() {
	char* buf = new char[20];
	memset(buf, 0, 20);
	int i = 0;
	while (isdigit(*mInput::code)) {
		buf[i++] = *mInput::code++;
	}
	return buf;
}

char* Lexer::scan_hex() {
	char* buf = new char[20];
	memset(buf, 0, 20);
	int i = 0;
	
	expect('0');
	expect('x');
	buf[i++] = '0';
	buf[i++] = 'x';
	char c = *mInput::code;
	if (isdigit(c) || c == 'A' || c == 'a' || c == 'B' || c == 'b' || c == 'C' || c == 'c' || c == 'D' || c == 'd' || c == 'E' || c == 'e' || c == 'F' || c == 'f') {
		while (isdigit(c) || c == 'A' || c == 'a' || c == 'B' || c == 'b' || c == 'C' || c == 'c' || c == 'D' || c == 'd' || c == 'E' || c == 'e' || c == 'F' || c == 'f') {
			buf[i++] = c = *mInput::code++;
		}
	} else {
		std::cout << "expect hex, but not " << *mInput::code << std::endl;
		exit(1);
	}

	return buf;
	
}

char* Lexer::scan_float() {
	char* buf = new char[20];
	memset(buf, 0, 20);
	int i = 0;
	if (isdigit(*mInput::code)) {	
		while (isdigit(*mInput::code)) {
			buf[i++] = *mInput::code++;
		}
		expect('.');
		buf[i++] = '.';
		if (isdigit(*mInput::code)) {
			while (isdigit(*mInput::code)) {
				buf[i++] = *mInput::code++;
			}
		}
		else {
			std::cout << "expect num, but not " << *mInput::code << std::endl;
			exit(1);
		}

	} else {
		std::cout << "expect num, but not " << *mInput::code << std::endl;
		exit(1);
	}

	return buf;
}

char Lexer::scan_char() {
	assert(*mInput::code == '\'');
	mInput::code++;
	char c;
	
	if (*mInput::code == '\'') {
		std::cout << "character literal cannot be empty" << std::endl;
		exit(1);
	} else if (*mInput::code == '\n') {
		std::cout << "character literal cannot contain new line " << std::endl;
		exit(1);
	} else if (*mInput::code == '\\') {
		mInput::code++;
		if (*mInput::code == '\'') {
			c = *mInput::code;
		}
	} else {
		c = *mInput::code;
	}
	mInput::code++;

	expect('\'');

	return c;

}

char* Lexer::scan_str() {
	expect('"');
	char* buf = (char*)malloc(126);
	memset(buf, 0, 126);

	//mInput::code++;

	int i = 0;
	while (*mInput::code != '"') {
		if (*mInput::code == '\\') {
			mInput::code++;
			if (*mInput::code == '"') {
				buf[i++] = *mInput::code++;
				continue;
			}
		}
		buf[i++] = *mInput::code++;

	}
	*mInput::code++;
	buf[i] = '\0';

	size_t len = strlen(buf);
	char *ret = (char*)malloc(len);

	memset(ret, 0, (int)len);
	for (i = 0; i < len+1; i++) {
		ret[i] = buf[i];
	}
	delete[] buf;	
	
	return ret;
}

TokenType Lexer::is_keyword(std::string s) {
	if(keywords_map.count(s))
		return keywords_map[s];
	return NULL_TOKEN;
}