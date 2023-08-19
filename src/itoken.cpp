#include "itoken.h"
#include <cstdio>

ISL_BEGIN

String Position::dump() const {
	char buffer[64] = { 0 };
	sprintf(buffer, "<%lu,%lu>", line, column);
	return String(buffer);
}

TokenKindInfo token_kind_info_list[] = {
#define enum_info(n, s) {#n, s},
#include "itoken.inc"
#undef enum_info
};

String Token::dump() {
	char buffer[256] = { 0 };
	String val_dump;
	switch (kind) {
		using enum TokenKind;
	case l_real:	val_dump = value.dump<dmp::value::as_f64> ();	break;
	case l_int:		val_dump = value.dump<dmp::value::as_i64> ();	break;
	case l_uint:	val_dump = value.dump<dmp::value::as_ui64>();	break;
	case l_string:	val_dump = value.dump<dmp::value::as_str> ();	break;
	default:		val_dump = "null";								break;
	}
	sprintf(buffer, "kind:%-10s extract:%-12s value:%-12s position:%s",
		token_kind_info_list[ui8(kind)].name,
		~String(extract),
		~val_dump,
		~position.dump()
	);
	return String(buffer);
}

ISL_END


