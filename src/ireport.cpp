#include "ireport.h"
#include "ioptions.h"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

ISL_BEGIN

RepIdInfo rep_id_info_list[] = {
#define enum_info(n, field, level, fmt)\
	{#n, RepField::field, RepLevel::level, fmt},
#include "ireport.inc"
#undef enum_info
};


void report(RepId id, void* ptr, ...) {
	RepIdInfo id_info = rep_id_info_list[ui16(id)];
	char tmp_buf[ISL_REPORT_BUFFER_SIZE] = { 0 };
	char out_buf[ISL_REPORT_BUFFER_SIZE] = { 0 };
	va_list args;
	va_start(args, ptr);
	vsnprintf(out_buf, ISL_REPORT_BUFFER_SIZE, id_info.fmt, args);
	va_end(args);
	const char* format = nullptr;
	switch (id_info.level) {
	case RepLevel::unk:
		//unreachableBranch();
		return;
	case RepLevel::info:
		format = "\033[0m\033[1;32minfo\033[0m: %s";
		break;
	case RepLevel::warning:
		format = "\033[0m\033[1;33mwarning\033[0m: %s";
		break;
	case RepLevel::error:
		format = "\033[0m\033[1;31merror\033[0m: %s";
		break;
	case RepLevel::fatal:
		format = "\033[0m\033[1;31mfatal\033[0m: %s";
		break;
	}
	sprintf(tmp_buf, format, out_buf);
	switch (id_info.field) {
	case RepField::unk:
		//unreachableBranch();
		return;
	case RepField::core:
		sprintf(out_buf, "core %s", tmp_buf);
		break;
	case RepField::lexer: {
		//if (ptr == nullptr) {
		//	//unreachableBranch();
		//	return;
		//}
		//auto* lexer = (Lexer*)ptr;
		//sprintf(out_buf, "%s:%d:%d: %s", ~lexer->fileName,
		//	lexer->pos.line, lexer->pos.column, tmp_buf);
		break;
	}
	case RepField::compiler: {
		//if (ptr == nullptr) {
		//	//unreachableBranch();
		//	return;
		//}
		//auto* cu = (CompileUnit*)ptr;
		//if (id_info.level == RepLevel::error ||
		//	id_info.level == RepLevel::fatal) {
		//	assert(cu->doGenerate, "cu->doGenerate = false.");
		//	cu->errCurFile = true;
		//}
		//sprintf(out_buf, "%s:%d:%d: %s", ~cu->lexer.fileName,
		//	cu->lexer.curToken.pos.line, cu->lexer.curToken.pos.column, tmpbuffer);
		break;
	}
	case RepField::vm:
		sprintf(out_buf, "runtime %s", tmp_buf);
		break;
	}
	printf("%s\n", out_buf);
	if (id_info.level == RepLevel::fatal) { exit((int)id); }
}


ISL_END