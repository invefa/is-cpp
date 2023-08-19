#pragma once
#include "itypes.h"
#include "iutils.h"
#include "ioptions.h"

//Disable warnings for flexible arrays.
#pragma warning(disable: 4200)
//Disable warnings for unused macro parameters.
#pragma warning(disable: 4003)

ISL_BEGIN

//Function as its name.
extern usize global_malloced_memory_size;

//islang malloc function, call malloc.
//And it will add the size to global_malloced_memory_size.
void* malloc(usize size);

//islang calloc function, call calloc.
//And it will add the size to global_malloced_memory_size.
void* calloc(usize size);

//islang free function, call free.
//And it will subtract the released size from global_malloced_memory_size.
void free(void* ptr, usize size);

//This container will store the length of the array at a position
//where the array header address is offset forward by arch bytes.
//It can solve the problem of not being able to obtain the length
//of certain types of arrays.
template<class T>
struct _array_ptr_length_binder {
	//The length of this array.
	usize length{};

	//The data of this array starts from here.
	T data[];

	//Just a setter.
	template<class T>
	inline _array_ptr_length_binder<T>* set_length(usize _length) {
		length = _length; return this;
	}
};

//For ease of use, it has been given an alias.
//apl -> array pointer length
template<class T> using apl_binder = _array_ptr_length_binder<T>;


//Convert array-ptr type conversion to _array_ptr_length_binder type
//AP  -> Array Pointer
//APL -> Array Pointer Length
#define _ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)	((is::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>*)\
										((is::usize*)_ap - 1))

//this is the reserved edition of this macro.
//#define _ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)	((is::memory::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>*)\
//										(((is::type::byte*)_ap) - sizeof(is::memory::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>)))

#ifdef ISL_MANAGE_MEMORY_OPERATION

#define isl_malloc(_type)				((_type*)is::malloc(sizeof(_type)))
#define isl_calloc(_type)				((_type*)is::calloc(sizeof(_type)))

#define isl_malloc_init(_type, ...)		(isl_malloc(_type)->init(__VA_ARGS__))
#define isl_calloc_init(_type, ...)		(isl_calloc(_type)->init(__VA_ARGS__))

#define isl_free(_ptr)					is::free((_ptr),sizeof(_ISL_CAST_PTR_TO_BASE_TYPE(_ptr)))


//This is the flag, place it on the last parameter of
//__IS_XALLOC_ARY to disable cardinality multiplication.
#define ISL_XALLOC_NO_BASE(_) ISL_XALLOC_NO_BASE

#define ISL_XALLOC_NO_BASE_ISL_XALLOC_FLAG1(_)
#define ISL_XALLOC_NO_BASE_ISL_XALLOC_FLAG2(_type) / sizeof(_type)

#define _ISL_XALLOC_FLAG1 *
#define _ISL_XALLOC_FLAG2(_)

//The allocation of arrays will use _array_ptr_length_binder to store array length.
//malloc and free array memory will include this length storage space.

//common macro: different in _x##alloc
#define __ISL_XALLOC_ARY(_x, _type, _count, ...)\
	(((is::apl_binder<_type>*)\
	is::_x##alloc(sizeof(is::apl_binder<_type>) + _count __VA_ARGS__##_ISL_XALLOC_FLAG1(sizeof(_type))))\
	->set_length<_type>(_count __VA_ARGS__##_ISL_XALLOC_FLAG2(_type))->data)

#define isl_malloc_ary(_type, _count, ...) __ISL_XALLOC_ARY(m, _type, _count, ##__VA_ARGS__)
#define isl_calloc_ary(_type, _count, ...) __ISL_XALLOC_ARY(c, _type, _count, ##__VA_ARGS__)

#define isl_free_ary(_ap)\
	do{\
		using __isl_tmp_type_base	= _ISL_CAST_PTR_TO_BASE_TYPE(_ap);\
		using __isl_tmp_type_aplb	= is::apl_binder<__isl_tmp_type_base>;\
		__isl_tmp_type_aplb* aplbp	=_ISL_CAST_AP_TO_APL_BINDER_PTR(_ap);\
		is::free(aplbp, sizeof(__isl_tmp_type_aplb) + aplbp->length * sizeof(__isl_tmp_type_base));\
	}while(0)

#define ISL_GET_ARY_LEN(_ap) (((is::usize*)_ap)[-1])

//this is the reserved edition of this macro.
//#define ISL_GET_ARY_LEN(_ap) (_ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)->length)

#else
//This case will use the cstdlib,
//use the functions of the Standard Library directly without hosting.
#include <cstdlib>

#define NO_BASE(_) NO_BASE

#define isl_malloc(_type)						((_type*)std::malloc(sizeof(_type)))
#define isl_calloc(_type)						((_type*)std::calloc(sizeof(_type),1))

#define isl_malloc_ary(_type, _count, _flag)	((_type*)std::malloc(sizeof(_type)*_count))
#define isl_calloc_ary(_type, _count, _flag)	((_type*)std::calloc(sizeof(_type),_count))

#define isl_malloc_init(_type, ...)				(isl_malloc(_type)->init(__VA_ARGS__))
#define isl_calloc_init(_type, ...)				(isl_calloc(_type)->init(__VA_ARGS__))

#define isl_free(_ptr)							std::free((_ptr))
#define isl_free_ary(_ap)						isl_free(_ap)

#define ISL_GET_ARY_LEN(_ap)					0

#endif

//Using this macro in a class can be specified as the managed memory operation.
#define _ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(_class)\
		void* operator new		(is::usize _base_size_)	{ return isl_calloc		(_class); }\
		void* operator new[]	(is::usize _tota_size_)	{ return isl_calloc_ary	(_class, _tota_size_, ISL_XALLOC_NO_BASE); }\
		void  operator delete	(void* _ptr)			{ isl_free		((_class*)_ptr); }\
		void  operator delete[]	(void* _ptr)			{ isl_free_ary	((_class*)_ptr); }


//Used to distribute memory for various std containers.
template <typename T>
class Allocator {
public:
	using value_type = T;
	Allocator() noexcept {}
	template <typename U> Allocator(const Allocator<U>&) noexcept {}
	inline T* allocate(usize _count) { return isl_calloc_ary(T, _count); }
	inline void deallocate(T* _ptr, usize _count) { isl_free_ary(_ptr); }
	inline void construct(T* _ptr, const T& _val) { new ((void*)_ptr) T(_val); }
	inline void destroy(T* _ptr) { _ptr->~T(); }
};

template <typename T, typename U>
bool operator==(const Allocator<T>&, const Allocator<U>&) noexcept {
	return true;
}

template <typename T, typename U>
bool operator!=(const Allocator<T>&, const Allocator<U>&) noexcept {
	return false;
}

ISL_END