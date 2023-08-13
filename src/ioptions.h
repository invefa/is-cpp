#pragma once

//#define _DEBUG

//macro _DEBUG can control ISL_DEBUG
#ifdef _DEBUG
//Define ISL_DEBUG to enable debug-mode.
//In debug-mode, functions such as assertions will be enabled to test code bugs.
#define ISL_DEBUG
#endif

//Define this macro to use is::memory functions to manage memory operations.
#define ISL_MANAGE_MEMORY_OPERATION

//Define this macro to enable output when memory operations.
#define ISL_MANAGE_MEMORY_OPERATION_OUTPUT
