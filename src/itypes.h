#pragma once
#include <cstdint>

namespace is::type {
	//islang char-string type
	typedef char* cstring;

	//islang wide-char-string type
	typedef wchar_t* wstring;

	//islang unsigned-arch type
	typedef	size_t			usize;

	//islang unsigned-byte type
	typedef std::uint8_t	ubyte;

	//islang signed-byte type
	typedef std::int8_t		byte;

	//islang signed-integer types
	typedef std::int8_t		i8;
	typedef std::int16_t	i16;
	typedef std::int32_t	i32;
	typedef std::int64_t	i64;

	//islang unsigned-integer types
	typedef std::uint8_t	ui8;
	typedef std::uint16_t	ui16;
	typedef std::uint32_t	ui32;
	typedef std::uint64_t	ui64;

	//islang float-number types
	typedef float			f32;
	typedef double			f64;
}