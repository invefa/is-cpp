#include "itoken.h"
#include <cstdio>

ISL_BEGIN

TokenKindInfo token_kind_info_list[] = {
#define enum_info(n, s) {#n, s},
#include "itoken.inc"
#undef enum_info
};

String Token::dump() const {
	char buffer[256] = { 0 };
	if (kind == TokenKind::l_real) {
		sprintf(buffer, "kind:%-10s extract:%-8s value:%-18f pos:[%u,%u]",
			token_kind_info_list[ui8(kind)].name, ~String(extract),
			value.f64, position.line, position.column);
	}
	if (kind == TokenKind::l_int) {
		sprintf(buffer, "kind:%-10s extract:%-8s value:%-18d pos:[%u,%u]",
			token_kind_info_list[ui8(kind)].name, ~String(extract),
			value.i32, position.line, position.column);
	}
	else if (kind == TokenKind::l_string) {
		sprintf(buffer, "kind:%-10s extract:%-8s value:%-18s pos:[%u,%u]",
			token_kind_info_list[ui8(kind)].name, ~String(extract),
			~String(*value.rsp), position.line, position.column);
	}
	else {
		sprintf(buffer, "kind:%-10s extract:%-8s value:%-18s pos:[%u,%u]",
			token_kind_info_list[ui8(kind)].name, ~String(extract),
			"null", position.line, position.column);
	}
	return String(buffer);
}

ISL_END