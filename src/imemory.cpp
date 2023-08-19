#include "imemory.h"
#include <cstdlib>
#include <cstdio>

ISL_BEGIN

usize global_malloced_memory_size = 0;

void* malloc(usize _size) {
	global_malloced_memory_size += _size;
#ifdef ISL_MANAGE_MEMORY_OPERATION_OUTPUT
	printf("malloc:\tsize + %d = %d.\n",
		_size, global_malloced_memory_size);
#endif
	return std::malloc(_size);
}

void* calloc(usize _size) {
	global_malloced_memory_size += _size;
#ifdef ISL_MANAGE_MEMORY_OPERATION_OUTPUT
	printf("calloc:\tsize + %d = %d.\n",
		_size, global_malloced_memory_size);
#endif
	return std::calloc(_size, 1);
}

void  free(void* _ptr, usize _size) {
	global_malloced_memory_size -= _size;
#ifdef ISL_MANAGE_MEMORY_OPERATION_OUTPUT
	printf("free:\tsize - %d = %d.\n",
		_size, global_malloced_memory_size);
#endif
	std::free(_ptr);
}

ISL_END