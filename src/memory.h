/********************************************************************
                          OpenAlchemist

  File : Memory.h
  Description : Memory checking inspired from Haypo 
								(http://www.haypocalc.com/wiki/Allocation_de_m%C3%A9moire_s%C3%A9curis%C3%A9e_en_C_et_Cpp)
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MEMORY_H_K
#define _MEMORY_H_K

void init_memory();

void term_memory();

#ifdef DEBUG

#include <new>

extern const char *delete_FILE;
extern unsigned long delete_LINE;

void* operator new (size_t size, const char* file, const unsigned long line)
  throw (std::bad_alloc);

void* operator new[] (size_t size, const char* file, const unsigned long line)
  throw (std::bad_alloc);

//void operator delete (void *ptr) throw ();

//void operator delete[] (void *ptr) throw ();

void my_delete_fun(void* ptr, const char* file, const unsigned long line);

#define my_new new (__FILE__, __LINE__)
#define my_delete(a) my_delete_fun(a, __FILE__, __LINE__); delete a
#define my_delete_tab(a) delete[] a

#else

#define my_new new
#define my_delete(a) delete a
#define my_delete_tab(a) delete[] a

#endif

#endif