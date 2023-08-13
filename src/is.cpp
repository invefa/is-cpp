#include <cstdio>
#include "iassert.h"
#include "imemory.h"
#include "iutils.h"
#include "icontainers.h"

int main()
{
	using namespace is;
	using namespace is::type;
	using namespace is::memory;
	//FILE* fp = nullptr;
	//errno_t err = fopen_s(&fp, "E:\\projects\\is\\script\\test.is", "r");
	//is_assert(fp);

#define printf_1(a)		printf("%d\n",a)
#define printf_2(a,b)	printf("%d%d\n",a,b)
#define printf_3(a,b,c) printf("%d%d%d\n",a,b,c)
#define printf_(...)	_ISL_MACRO_OVERLOAD(printf,__VA_ARGS__)

	_ISL_MACRO_FORWARD_CALL(printf, 1);
	_ISL_MACRO_FORWARD_CALL(printf, 1, 2);
	_ISL_MACRO_FORWARD_CALL(printf, 1, 2, 3);

	printf_(1);
	printf_(1, 2);
	printf_(1, 2, 3);


	println("awa");

	isl_wssert(1 == 2, "one is not equal two.");
	isl_wssert(1 == 2);

	//isl_assert(1 == 2, "one is not equal two.");
	//isl_assert(1 == 2);

	map<int, int> m;
	m[123] = 123;
	printf("%d\n", m[123]);
	hash_map<int, int> hm;
	printf("%d\n", sizeof(decltype(hm)));
	hm[1] = 2;
	printf("%d\n", hm[1]);
	hm.insert_or_assign(1, 6);
	printf("%d\n", hm[1]);

	vector<int> vector;
	vector.push_back(1);

	ISL_CALLOC_ARY(int, 12);

	//_ISL_MACRO_CALL_FORWARD(printf, 1, 2, 3);

	// -> __ISL_MACRO_INVOKE(__ISL_MACRO_CONCAT(__ISL_MACRO_CONCAT(printf,_),__ISL_MACRO_GET_VARG_COUNT( 1, 2, 3)), 1, 2, 3)

	// -> __ISL_MACRO_INVOKE_UNPACK(__ISL_MACRO_CONCAT_WRAP(__ISL_MACRO_CONCAT_WRAP(printf,_),__ISL_MACRO_GET_TENTH_ARG( 1, 2, 3,9,8,7,6,5,4,3,2,1,0)),( 1, 2, 3))

	// -> __ISL_MACRO_CONCAT_WRAP(__ISL_MACRO_CONCAT_WRAP(printf,_),__ISL_MACRO_GET_TENTH_ARG_UNPACK(( 1, 2, 3,9,8,7,6,5,4,3,2,1,0)))( 1, 2, 3)

	// -> __ISL_MACRO_CONCAT_IMPL(__ISL_MACRO_CONCAT_IMPL(printf,_),__ISL_MACRO_GET_TENTH_ARG_IMPL( 1, 2, 3,9,8,7,6,5,4,3,2,1,0))( 1, 2, 3)

	// -> printf_3( 1, 2, 3)

	//isl_assert(1 == 2);


//#define __ISL_MACRO_INERT_1(_1) _1
//#define __ISL_MACRO_INERT_2(_2) __ISL_MACRO_INERT_1(_2)
//#define __ISL_MACRO_INERT_3(_3) __ISL_MACRO_INERT_2(_3)
//#define __ISL_MACRO_INERT_4(_4) __ISL_MACRO_INERT_3(_4)
//#define __ISL_MACRO_INERT_5(_5) __ISL_MACRO_INERT_4(_5)
//
//#define __ISL_MACRO_LPARE() (
//#define __ISL_MACRO_RPARE() )
//
//#define __ISL_MACRO_UNPACK_IMPL(...) __VA_ARGS__
//#define __ISL_MACRO_UNPACK(_pack) __ISL_MACRO_UNPACK_IMPL _pack
//
//#define __ISL_MACRO_GET_EIGHTH_ARG_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _8
//#define __ISL_MACRO_GET_EIGHTH_ARG_UNPACK(_args) __ISL_MACRO_GET_EIGHTH_ARG_IMPL _args
//#define __ISL_MACRO_GET_EIGHTH_ARG(...) __ISL_MACRO_GET_EIGHTH_ARG_UNPACK((__VA_ARGS__))
//
//#define __ISL_MACRO_GET_VARG_COUNT(...) __ISL_MACRO_GET_EIGHTH_ARG(__VA_ARGS__,7,6,5,4,3,2,1,0)
//
//#define __ISL_MACRO_INVOKE_IMPL(_fn, _arg_pack) _fn _arg_pack
//#define __ISL_MACRO_INVOKE(_fn, ...) __ISL_MACRO_INVOKE_IMPL(_fn,(__VA_ARGS__))
//
//#define __ISL_MACRO_OVERLOAD(_fn, ...)\
//			__ISL_MACRO_INVOKE __ISL_MACRO_LPARE()\
//				__ISL_MACRO_CONCAT(__ISL_MACRO_INERT_2(_fn),__ISL_MACRO_GET_VARG_COUNT(__VA_ARGS__)),__VA_ARGS__ __ISL_MACRO_RPARE()
//
//#define _overload_println_2(_fmt, _1) printf(_fmt"\n",_1)
//#define _overload_println_3(_fmt, _1, _2) printf(_fmt"\n",_1,_2)
//#define println(...) __ISL_MACRO_OVERLOAD(_overload_println_,__VA_ARGS__)
	//println("a%d", 1);
	//printf("%d\n",
		//__ISL_MACRO_GET_VARG_COUNT(1,2));
	//struct Custom {
	//	int		a{};
	//	cstring	b{};

	//	inline Custom* init(int _a, cstring _b) {
	//		a = _a, b = _b; return this;
	//	}

	//	cstring dump() {
	//		constexpr is::type::usize buf_size = 64;
	//		char* buf = ISL_MALLOC_ARY(char, buf_size);
	//		isl_assert(buf);
	//		sprintf_s(buf, buf_size,
	//			b ?
	//			"Custom{ a:%d, b:\"%s\" }" :
	//			"Custom{ a:%d, b:%s }",
	//			a, b ? b : "<nullptr>");
	//		return buf;
	//	}

	//	_ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(Custom);

	//	/*void* operator new(usize _unused_) {
	//		return ISL_CALLOC(Custom);
	//	}

	//	void* operator new[](usize _total_size) {
	//		return ISL_CALLOC_ARY(Custom, _total_size, NO_BASE);
	//	}

	//		void operator delete(void* ptr) {
	//		ISL_FREE((Custom*)ptr);
	//	}

	//	void operator delete[](void* ptr) {
	//		ISL_FREE_ARY((Custom*)ptr);
	//	}*/
	//};


	//auto capn = new Custom[8];

	//printf("global_malloced_memory_size: %d\n", memory::global_malloced_memory_size);

	//ISL_FREE_ARY(capn);

	//printf("global_malloced_memory_size: %d\n", memory::global_malloced_memory_size);

	//isl_assert(false == true);

	//printf("global_malloced_memory_size: %d\n", memory::global_malloced_memory_size);
	class string {
		char* data{};
	public:
		_ISL_DELETE_DEFAULT_MOVE_AND_COPY_FN(string);
		_ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(string);
		string(){}
		inline char* operator~() { return data; }
	};

	//string* str = new string;
	//printf("str_data_ptr: %p\n", ~*str);

	//usize* usp = ISL_CALLOC_ARY(usize, 8);
	//isl_assert(usp);

	//ISL_FREE_ARY(usp);
}