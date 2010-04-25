// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : memory.cpp
//  Description : Custom memory allocator (to check memory leaks)
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

// ! DO NOT INCLUDE memory.h !
#include <iostream>
#include <stdlib.h>
#include <string.h>

/** Memory allocation reference */
struct MemAlloc{

	/** Next memory allocation (it is a linked list) */
	MemAlloc* p_next;

	/** Memory address */
	void* ptr;

	/** File where the allocation were performed */
	char file[256];

	/** File line where the allocation were performed */
	unsigned long line;

	/** Check if this allocation were deleted */
	bool free;

	/** Size of the memory allocation */
	size_t size;

};

/************************************************************************/
/* Static global variables                                              */
/************************************************************************/
static MemAlloc mem_alloc_first;
static MemAlloc* mem_alloc_last;
static int comp;
static int comp_size;
static int max_size;

/************************************************************************/
/* Init Memory                                                          */
/************************************************************************/
void init_memory()
{
#ifdef DEBUG
	std::cout << "Memory Init" << std::endl;
	comp = 0;
	comp_size = 0;
	max_size = 0;
	mem_alloc_first.ptr = NULL;
	mem_alloc_first.line = NULL;
	mem_alloc_first.p_next = NULL;
	mem_alloc_last = &mem_alloc_first;
#endif	
}

/************************************************************************/
/* Term memory                                                          */
/************************************************************************/
void term_memory()
{
#ifdef DEBUG
	std::cout << "Memory Term" << std::endl;
	size_t s = 0;
	if(mem_alloc_first.p_next)
	{
		MemAlloc* p_current = mem_alloc_first.p_next;
		while(p_current)
		{
			if(!p_current -> free)
			{
				std::cout << "Memory not free : " << p_current -> ptr 
					<< " of size : " << p_current -> size
					<< " in "
					<< p_current -> file << "("
					<< p_current -> line << ")." << std::endl;
				s += p_current -> size;
			}
			MemAlloc * p_last = p_current;
			p_current = p_current -> p_next;
			free(p_last);
		}
	}
	std::cout << "Memory not free counter : " << comp 
		<< " of size : " << s << std::endl;
	std::cout << "Max memory size : " << max_size << std::endl;
#endif
}

/************************************************************************/
/* My alloc                                                             */
/************************************************************************/
inline void* my_alloc(int size, const char* file, const unsigned long line)
{
	//if(line==41)
	//std::cout << "Alloc " << file << " ligne " << line << std::endl;

	void* ptr = malloc(size);

	MemAlloc* p_current = &mem_alloc_first;
	while(p_current && p_current -> ptr != ptr)
	{
		p_current = p_current -> p_next;
	}
	if(p_current && p_current -> ptr == ptr)
	{
		p_current -> free = false;
		p_current -> line = line;
#ifdef WIN32
		strcpy_s(p_current -> file, file);		
#else
		strcpy(p_current -> file, file);		
#endif		
		p_current -> size = size;
	}
	else
	{	
		MemAlloc* alloc = (MemAlloc*) malloc(sizeof(MemAlloc));
		alloc -> ptr = ptr;
#ifdef WIN32
		strcpy_s(alloc -> file, file);
#else
		strcpy(alloc -> file, file);
#endif
		alloc -> line = line;
		alloc -> p_next = NULL;
		alloc -> free = false;
		alloc -> size = size;

		mem_alloc_last -> p_next = alloc;
		mem_alloc_last = alloc;
	}

	comp++;
	comp_size+=size;
	if(comp_size > max_size)
	{
		max_size = comp_size;
	}

	return ptr;
}

/************************************************************************/
/* My delete function                                                   */
/************************************************************************/
void my_delete_fun(void* ptr, const char* file, const unsigned long line)
{
	if(ptr == NULL)
		return;

	MemAlloc* p_current = &mem_alloc_first;
	MemAlloc* p_previous = p_current;	

	while(p_current && p_current -> ptr != ptr)
	{
		p_previous = p_current;
		p_current = p_current -> p_next;
	}
	if(p_current && p_current -> ptr == ptr)
	{
		if(p_current -> free)
		{
			std::cout << "Already deleted : " << ptr << " in " << file << "(" << line << ")" << std::endl;	
			comp++;
		}
		//std::cout << "Good : " << file << "(" << line << ")" << std::endl;
		p_current -> free = true;
		comp_size -= p_current -> size;
	}
	else
	{
		std::cout << "Unknow memory : " << ptr << " in " << file << "(" << line << ")" << std::endl;
	}
	comp--;
}

/************************************************************************/
/* New                                                                  */
/************************************************************************/
void* operator new (size_t size, const char* file, const unsigned long line)
{
	return my_alloc(size, file, line);
}

/************************************************************************/
/* New[]                                                                */
/************************************************************************/
void* operator new[] (size_t size, const char* file, const unsigned long line)
{
	return my_alloc(size, file, line);
}

/************************************************************************/
/* Delete                                                               */
/************************************************************************/
void operator delete(void* ptr, const char* file, const unsigned long line)
{
	my_delete_fun(ptr, file, line);
	free(ptr);
}