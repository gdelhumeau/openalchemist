// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : memory.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _MEMORY_H_K
#define _MEMORY_H_K

void init_memory();

void term_memory();

#ifdef DEBUG

#include <new>

extern const char *delete_FILE;
extern unsigned long delete_LINE;

void* operator new (size_t size, const char* file, const unsigned long line);
//throw (std::bad_alloc);

void* operator new[] (size_t size, const char* file, const unsigned long line);
//throw (std::bad_alloc);

void my_delete_fun(void* ptr, const char* file, const unsigned long line);

void operator delete(void* ptr, const char* file, const unsigned long line);

//void operator delete (void *ptr) throw ();

//void operator delete[] (void *ptr) throw ();

#define my_new new (__FILE__, __LINE__)
//#define my_delete delete (__FILE__, __LINE__)
#define my_delete(a) { my_delete_fun(a, __FILE__, __LINE__); delete a; }
#define my_delete_tab(a) delete[] a

#else

#define my_new new
#define my_delete(a) delete a
#define my_delete_tab(a) delete[] a

#endif

#endif