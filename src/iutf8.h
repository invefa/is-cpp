#pragma once
#include "iutils.h"
#include "itypes.h"

ISL_BEGIN

ui32 get_byte_count_of_encode_utf8(ui32 val);
ui32 get_byte_count_of_decode_utf8(byte val);

ui8 encode_utf8(uint8_t* buf, int value);
i32 decode_utf8(const uint8_t* byte_ptr, uint32_t length);

ISL_END