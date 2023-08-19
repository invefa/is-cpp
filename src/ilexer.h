#pragma once
#include "iutils.h"
#include "itoken.h"

ISL_BEGIN

//This is the lexical analyzer for this programming language.
class Lexer {
public:
	//Basic token table. If these are not enough, we will use lookahead.
	Token preToken{}, curToken{}, nexToken{}, secToken{};


	TokenKind advance();

};


ISL_END