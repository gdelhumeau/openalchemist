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
	size_t size;
	
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
#endif
}

inline void * my_alloc(int size, const char* file, const unsigned long line)
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
		strcpy(p_current -> file, file);		
		p_current -> size = size;
	}
	else
	{	
		MemAlloc* alloc = (MemAlloc*) malloc(sizeof(MemAlloc));
		alloc -> ptr = ptr;
		strcpy(alloc -> file, file);
		alloc -> line = line;
		alloc -> p_next = NULL;
		alloc -> free = false;
		alloc -> size = size;
	
		mem_alloc_last -> p_next = alloc;
		mem_alloc_last = alloc;
	}

  comp++;
	
  return ptr;
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
		if(p_current -> free)
		{
			std::cout << "Already deleted : " << ptr << " in " << file << "(" << line << ")" << std::endl;	
			comp++;
		}
    //std::cout << "Good : " << file << "(" << line << ")" << std::endl;
    p_current -> free = true;
  }
  else
  {
    std::cout << "Unknow memory : " << ptr << " in " << file << "(" << line << ")" << std::endl;
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
