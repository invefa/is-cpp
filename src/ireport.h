#pragma once
#include "iutils.h"
#include "itypes.h"


ISL_BEGIN

//report field
enum class RepField : ui8 { unk, core, lexer, parser, compiler, vm };

//report level
enum class RepLevel : ui8 { unk, info, warning, error, fatal };

//report id
enum class RepId : ui16 {
#define enum_info(n, field, level, fmt) n,
#include "ireport.inc"
#undef enum_info
};

//report id infomation
extern struct RepIdInfo {
	lstring		name	{ nullptr };
	RepField	field	{ RepField::unk };
	RepLevel	level	{ RepLevel::unk };
	lstring		fmt		{ nullptr };
} rep_id_info_list[];

//This fn is the core of report system.
void report(RepId id, void* ptr, ...);

ISL_END