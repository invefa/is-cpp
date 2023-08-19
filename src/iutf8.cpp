#include "iutf8.h"
#include "iassert.h"

ISL_BEGIN

ui32 get_byte_count_of_encode_utf8(ui32 val) {
	isl_assert(val > 0, "can't encode negative value!");
	if (val <= 0x7f)
		return 1;
	if (val <= 0x7ff)
		return 2;
	if (val <= 0xffff)
		return 3;
	if (val <= 0x10ffff)
		return 4;
	return 0;
}

ui32 get_byte_count_of_decode_utf8(byte val) {
	if ((val & 0xc0) == 0x80)
		return 0;
	if ((val & 0xf8) == 0xf0)
		return 4;
	if ((val & 0xf0) == 0xe0)
		return 3;
	if ((val & 0xe0) == 0xc0)
		return 2;
	return 1;
}

ISL_END