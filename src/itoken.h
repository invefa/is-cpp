#pragma once
#include "iutils.h"
#include "itypes.h"
#include "istring.h"
#include "ivalue.h"

ISL_BEGIN

struct Position {
	usize line{ 1 };
	usize column{ 1 };
};

enum class TokenKind : ui8 {
#define enum_info(n, s) n,
#include "itoken.inc"
#undef enum_info
};

extern struct TokenKindInfo {
	const char* name{ nullptr };
	const char* symbol{ nullptr };
} token_kind_info_list[];


struct Token {
	using enum TokenKind;

	TokenKind	kind	{ unk };
	RefString	extract	{};
	Position	position{};
	Value		value	{};

	String dump() const;
};


ISL_END