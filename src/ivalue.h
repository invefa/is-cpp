#pragma once
#include "iutils.h"
#include "itypes.h"
#include "istring.h"

ISL_BEGIN

union Value;

namespace cmp::value {
	//bool as_i64_fn(Value a, Value b);
	//bool as_str_fn(Value a, Value b);

//macro for value cmp class and its implements.
#define __ISL_GEN_VALUE_CMP_CLASS(_type)\
class as_##_type { public: bool operator()(Value a, Value b); }

#define __ISL_GEN_VALUE_CMP_CLASS_IMPL(_type)\
bool cmp::value::as_##_type::operator()(Value a, Value b) {return a._type == b._type;}

	__ISL_GEN_VALUE_CMP_CLASS(i8);
	__ISL_GEN_VALUE_CMP_CLASS(i16);
	__ISL_GEN_VALUE_CMP_CLASS(i32);
	__ISL_GEN_VALUE_CMP_CLASS(i64);

	__ISL_GEN_VALUE_CMP_CLASS(ui8);
	__ISL_GEN_VALUE_CMP_CLASS(ui16);
	__ISL_GEN_VALUE_CMP_CLASS(ui32);
	__ISL_GEN_VALUE_CMP_CLASS(ui64);

	__ISL_GEN_VALUE_CMP_CLASS(ptr);

	class as_str {
	public:
		bool operator()(Value a, Value b);
	};
}

namespace dmp::value {

#define __ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(_type)\
	class as_##_type { public:String operator()(Value val); }

#define __ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS_IMPL(_type, _fmt)\
	String dmp::value::as_##_type::operator()(Value val) {\
	char buffer[32] = { 0 }; sprintf(buffer, _fmt, val._type);\
	return String(buffer);}

#define __ISL_GEN_VALUE_DMP_AS_TYPE_CLASS(_type)\
	class as_##_type { public:String operator()(Value val); }

#define __ISL_GEN_VALUE_DMP_AS_TYPE_CLASS_IMPL(_type, _impl)\
	String dmp::value::as_##_type::operator()(Value val) _impl

	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(i8);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(i16);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(i32);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(i64);

	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(ui8);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(ui16);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(ui32);
	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(ui64);

	__ISL_GEN_VALUE_DMP_AS_INTEGER_CLASS(ptr);

	__ISL_GEN_VALUE_DMP_AS_TYPE_CLASS(str);
}

//This is the basic unit of the virtual machine runtime stack.
union Value {

	//basic pointer
	is::cptr		ptr;
	is::Value*		vp;
	is::String*		sp;
	is::RefString*	rsp;

	//integer pointer
	is::i8* ip8;	is::i16* ip16;	is::i32* ip32;	is::i64* ip64;
	is::ui8* up8;	is::ui16* up16;	is::ui32* up32;	is::ui64* up64;

	//integer number
	is::i8  i8;		is::i16  i16;	is::i32  i32;	is::i64  i64;
	is::ui8 ui8;	is::ui16 ui16;	is::ui32 ui32;	is::ui64 ui64;

	//float number
	is::f32 f32;	is::f64 f64;

	Value();
	//explicit Value(is::cptr _ptr);
	//explicit Value(is::f64 _real);
	//explicit Value(is::i64 _int);
	//explicit Value(is::ui64 _uint);
	//explicit Value(is::String& _str);
	//explicit Value(is::RefString& _refstr);

	bool is_equal(is::ui64 another);
	bool is_equal(is::StringMeta another);
	//bool is_equal(is::Value another,
	//				bool (*cmp_fn)(Value, Value) = is::cmp::value::as_i64_fn);

	template<class method = cmp::value::as_i64>
	bool is_equal(is::Value another) { return method()(*this, another); }

	template<class method = dmp::value::as_i64>
	String dump() { return method()(*this); }

	bool operator==(Value another);
};



ISL_END