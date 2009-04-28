/********************************************************************
                          OpenAlchemist

  File : Memory.cpp
  Description : Memory checking inspired from Haypo 
								(http://www.haypocalc.com/wiki/Allocation_de_m%C3%A9moire_s%C3%A9curis%C3%A9e_en_C_et_Cpp)
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

// ! DO NOT INCLUDE memory.h !
#include <iostream>
#include <stdlib.h>
#include <string.h>

struct MemAlloc{
	
	void* ptr;
	char file[256];
	unsigned long line;
	MemAlloc* p_next;
	bool free;
	
};

MemAlloc mem_alloc_first;
MemAlloc * mem_alloc_last;
int comp;

void init_memory()
{
#ifdef DEBUG
	std::cout << "Memory Init" << std::endl;
	comp = 0;
	mem_alloc_first.ptr = NULL;
	mem_alloc_first.line = NULL;
	mem_alloc_first.p_next = NULL;
	mem_alloc_last = &mem_alloc_first;
#endif	
}

void term_memory()
{
#ifdef DEBUG
	std::cout << "Memory Term" << std::endl;
	if(mem_alloc_first.p_next)
	{
		MemAlloc* p_current = mem_alloc_first.p_next;
		while(p_current)
		{
			if(!p_current -> free)
			{
				std::cout << "Memory not free : " << p_current -> file << "("
									<< p_current -> line << ")." << std::endl;
			}
			MemAlloc * p_last = p_current;
			p_current = p_current -> p_next;
			free(p_last);
		}
	}
	std::cout << "Memory not free : " << comp << std::endl;
#endif
}

inline void * my_alloc(int size, const char* file, const unsigned long line)
{
	//if(line==41)
	  //std::cout << "Alloc " << file << " ligne " << line << std::endl;
	
		MemAlloc* alloc = (MemAlloc*) malloc(sizeof(MemAlloc));
		alloc -> ptr = malloc(size);
		strcpy(alloc -> file, file);
		alloc -> line = line;
	  alloc -> p_next = NULL;
	  alloc -> free = false;
	
		mem_alloc_last -> p_next = alloc;
		mem_alloc_last = alloc;

		comp++;
	
		return alloc -> ptr;
}

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
		//std::cout << "Good : " << file << "(" << line << ")" << std::endl;
		p_current -> free = true;
		//p_previous -> p_next = p_current -> p_next;
		//if(p_current != &mem_alloc_first)
		//	free(p_current);
	}
	else
	{
		std::cout << "Unknow memory : " << file << "(" << line << ")" << std::endl;
	}
	comp--;
}

void* operator new (size_t size, const char* file, const unsigned long line)
  throw (std::bad_alloc)
{
	return my_alloc(size, file, line);
}

void* operator new[] (size_t size, const char* file, const unsigned long line)
  throw (std::bad_alloc)
{
	return my_alloc(size, file, line);
}

/*
void operator delete (void *ptr) throw ()
{
	my_delete(ptr);
}

void operator delete[] (void *ptr) throw ()
{
	my_delete(ptr);
}
*/