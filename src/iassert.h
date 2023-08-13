#pragma once
#include <cstdio>
#include <cstdlib>
#include "ioptions.h"
#include "iansictrl.h"
#include "iutils.h"

#ifdef ISL_DEBUG

#define	_ISL_XSSERT_FLAG(_expl)

#define _ISL_XSSERT_a_ISL_XSSERT_FLAG exit(-1);
#define _ISL_XSSERT_w_ISL_XSSERT_FLAG

#define ISL_XSSERT_EXIST_EXPL	ISL_XSSERT_EXIST_EXPL
#define ISL_XSSERT_EXIST_EXPL_ISL_XSSERT_FLAG(_expl)\
			"\tit can be explained as: " ANSI_HIL _expl ANSI_RST "\n"

#define __isl_xssert(_x, _expr, _expl, _flag)\
do{\
	if(!(_expr)){\
		printf(\
			ANSI_HIR #_x "ssert failure:\n\t" ANSI_RST\
			"in file '%s':\n\tat fn %s(...): expression: "\
			ANSI_HIL "%s" ANSI_RST " <line:%d>.\n" _flag##_ISL_XSSERT_FLAG(_expl)\
			,__FILE__,__FUNCTION__,#_expr,__LINE__);\
			_ISL_XSSERT_##_x##_ISL_XSSERT_FLAG\
	}\
} while(0)

#define _isl_assert_1(_expr)		__isl_xssert(a,_expr)
#define _isl_assert_2(_expr, _expl)	__isl_xssert(a,_expr,_expl,ISL_XSSERT_EXIST_EXPL)

#define _isl_wssert_1(_expr)		__isl_xssert(w,_expr)
#define _isl_wssert_2(_expr, _expl)	__isl_xssert(w,_expr,_expl,ISL_XSSERT_EXIST_EXPL)

//islang macro assert
//first arg is expr: Logical expression that requires assertion.
//second arg is expl: Explanation of assertion failure (can be ignored).
#define isl_assert(...)	_ISL_MACRO_OVERLOAD(_isl_assert,__VA_ARGS__)

//islang macro weak assert (abbreviate it as wssert)
//The function of weak assertions is the same as assertions,
//except that they do not interrupt program operation.
#define isl_wssert(...)	_ISL_MACRO_OVERLOAD(_isl_wssert,__VA_ARGS__)


#else

#define isl_assert(...)
#define isl_wssert(...)

#endif
