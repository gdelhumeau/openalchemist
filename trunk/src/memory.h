// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : memory.h
//  Description : Custom memory allocator (to check memory leaks)
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MEMORY_H_
#define _MEMORY_H_

/** Init memory - must be called */
void init_memory();

/** Term memory - perform memory leaks check */
void term_memory();

// Memory check is only used with DEBUG option
#ifdef DEBUG

#include <new>

/** Custom allocator */
void* operator new (size_t size, const char* file, const unsigned long line);

/** Custom allocator */
void* operator new[] (size_t size, const char* file, const unsigned long line);

/** Custom delete function */
void my_delete_fun(void* ptr, const char* file, const unsigned long line);

/** Custom delete */
void operator delete(void* ptr, const char* file, const unsigned long line);

/** Declaring new keywords */
#define my_new new (__FILE__, __LINE__)
#define my_delete(a) { my_delete_fun(a, __FILE__, __LINE__); delete a; }
#define my_delete_tab(a) delete[] a

#else
// No debug so we use default allocator

/** Declaring new keywords */
#define my_new new
#define my_delete(a) delete a
#define my_delete_tab(a) delete[] a

#endif

#endif