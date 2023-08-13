#pragma once
#include "itypes.h"
#include "iutils.h"
#include "ioptions.h"

//Disable warnings for flexible arrays.
#pragma warning(disable: 4200)
//Disable warnings for unused macro parameters.
#pragma warning(disable: 4003)

namespace is::memory {
	//Function as its name.
	extern type::usize global_malloced_memory_size;

	//islang malloc function, call malloc.
	//And it will add the size to global_malloced_memory_size.
	void* malloc(type::usize size);

	//islang calloc function, call calloc.
	//And it will add the size to global_malloced_memory_size.
	void* calloc(type::usize size);

	//islang free function, call free.
	//And it will subtract the released size from global_malloced_memory_size.
	void free(void* ptr, type::usize size);

	//This container will store the length of the array at a position
	//where the array header address is offset forward by arch bytes.
	//It can solve the problem of not being able to obtain the length
	//of certain types of arrays.
	template<class T>
	struct _array_ptr_length_binder {
		//The length of this array.
		type::usize length{};

		//The data of this array starts from here.
		T data[];

		//Just a setter.
		template<class T>
		inline _array_ptr_length_binder<T>* set_length(type::usize _length) {
			length = _length; return this;
		}
	};

	//For ease of use, it has been given an alias.
	//apl -> array pointer length
	template<class T> using apl_binder = _array_ptr_length_binder<T>;
}

//Convert array-ptr type conversion to _array_ptr_length_binder type
//AP  -> Array Pointer
//APL -> Array Pointer Length
#define _ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)	((is::memory::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>*)\
										((is::type::usize*)_ap - 1))

//this is the reserved edition of this macro.
//#define _ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)	((is::memory::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>*)\
//										(((is::type::byte*)_ap) - sizeof(is::memory::apl_binder<_ISL_CAST_PTR_TO_BASE_TYPE(_ap)>)))

#ifdef ISL_MANAGE_MEMORY_OPERATION

#define ISL_MALLOC(_type)				((_type*)is::memory::malloc(sizeof(_type)))
#define ISL_CALLOC(_type)				((_type*)is::memory::calloc(sizeof(_type)))

#define ISL_MALLOC_INIT(_type, ...)		(ISL_MALLOC(_type)->init(__VA_ARGS__))
#define ISL_CALLOC_INIT(_type, ...)		(ISL_CALLOC(_type)->init(__VA_ARGS__))

#define ISL_FREE(_ptr)					is::memory::free((_ptr),sizeof(_ISL_CAST_PTR_TO_BASE_TYPE(_ptr)))


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
	(((is::memory::apl_binder<_type>*)\
	is::memory::_x##alloc(sizeof(is::memory::apl_binder<_type>) + _count __VA_ARGS__##_ISL_XALLOC_FLAG1(sizeof(_type))))\
	->set_length<_type>(_count __VA_ARGS__##_ISL_XALLOC_FLAG2(_type))->data)

#define ISL_MALLOC_ARY(_type, _count, ...) __ISL_XALLOC_ARY(m, _type, _count, ##__VA_ARGS__)
#define ISL_CALLOC_ARY(_type, _count, ...) __ISL_XALLOC_ARY(c, _type, _count, ##__VA_ARGS__)

#define ISL_FREE_ARY(_ap)\
	do{\
		using __isl_tmp_type_base	= _ISL_CAST_PTR_TO_BASE_TYPE(_ap);\
		using __isl_tmp_type_aplb	= is::memory::apl_binder<__isl_tmp_type_base>;\
		__isl_tmp_type_aplb* aplbp	=_ISL_CAST_AP_TO_APL_BINDER_PTR(_ap);\
		is::memory::free(aplbp, sizeof(__isl_tmp_type_aplb) + aplbp->length * sizeof(__isl_tmp_type_base));\
	}while(0)

#define ISL_GET_ARY_LEN(_ap) (((is::type::usize*)_ap)[-1])

//this is the reserved edition of this macro.
//#define ISL_GET_ARY_LEN(_ap) (_ISL_CAST_AP_TO_APL_BINDER_PTR(_ap)->length)

#else
//This case will use the cstdlib,
//use the functions of the Standard Library directly without hosting.
#include <cstdlib>

#define NO_BASE(_) NO_BASE

#define ISL_MALLOC(_type)						((_type*)std::malloc(sizeof(_type)))
#define ISL_CALLOC(_type)						((_type*)std::calloc(sizeof(_type),1))

#define ISL_MALLOC_ARY(_type, _count, _flag)	((_type*)std::malloc(sizeof(_type)*_count))
#define ISL_CALLOC_ARY(_type, _count, _flag)	((_type*)std::calloc(sizeof(_type),_count))

#define ISL_MALLOC_INIT(_type, ...)				(ISL_MALLOC(_type)->init(__VA_ARGS__))
#define ISL_CALLOC_INIT(_type, ...)				(ISL_CALLOC(_type)->init(__VA_ARGS__))

#define ISL_FREE(_ptr)							std::free((_ptr))
#define ISL_FREE_ARY(_ap)						ISL_FREE(_ap)

#define ISL_GET_ARY_LEN(_ap)					0

#endif

//Using this macro in a class can be specified as the managed memory operation.
#define _ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(_class)\
		void* operator new		(usize _base_size_)	{ return ISL_CALLOC		(_class); }\
		void* operator new[]	(usize _tota_size_)	{ return ISL_CALLOC_ARY	(_class, _tota_size_, ISL_XALLOC_NO_BASE); }\
		void  operator delete	(void* _ptr)		{ ISL_FREE		((_class*)_ptr); }\
		void  operator delete[]	(void* _ptr)		{ ISL_FREE_ARY	((_class*)_ptr); }

namespace is::memory {
	//Used to distribute memory for various std containers.
	template <typename T>
	class Allocator {
	public:
		using value_type = T;
		Allocator() noexcept {}
		template <typename U> Allocator(const Allocator<U>&) noexcept {}
		inline T* allocate(type::usize _count) { return ISL_CALLOC_ARY(T, _count); }
		inline void deallocate(T* _ptr, type::usize _count) { ISL_FREE_ARY(_ptr); }
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
}
