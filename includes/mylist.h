/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef _MYLIST_H_
#define _MYLIST_H_

namespace MyList{

  template<typename T>
  class Iterator;

  template<typename T>
  class Node
  {
  public:
    T value;
    Node<T> *next; 
    Node<T> *prec;

    Node<T>(T _value)
      {
        value = _value;
        next = NULL;
        prec = NULL;
      }

  };

  class EmptyListException {
  };

  template<typename T>
  class List{

  public:
    Node<T> *first;
    Node<T> *last;
  
    List()
      {
        first = NULL;
        last = NULL;
      }

    void add(T new_value)
      {
        Node<T> *next = new Node<T>(new_value);
        if(last == NULL)
        {
          first = next;
          last = next;
        }
        else
        {
          last -> next = next;
          next -> prec = last;
          last = next;
        }
      }

    void remove(Node<T> *node)
      {
        if(node == NULL)
          return;
        if(first == NULL)
          return;
        
        if(first == node)
        {
          if(first == last)
          {
            last = NULL;
          }
          else
          {
            first -> next -> prec = NULL;
          }
          first = first -> next;
          delete node;
        }
        else if(last == node)
        {
          last -> prec -> next = NULL;
          last = last -> prec;
          delete node;
        }
        else
        {
          Node<T> *n = first;        
          while(n != NULL && n != node)
            {
              n = n -> next;
            }
          if(n == node)
          {
            n -> prec -> next = n -> next;
            n -> next -> prec = n -> prec;
            delete n;
          }
        }      
 
        
      } 

     void remove_last()
      {
        remove(last);
      }

     void clear()
       {
         while(first != NULL)
           remove_last();
       }

    Iterator<T>* get_iterator()
      {
        Iterator<T> *it = new Iterator<T>(first, this);
        return it;
      }

    

  };


  template<typename T>
  class Iterator
  {
  private:
    Node<T> *node;
    List<T> *lst;
  public:
    
    Iterator<T>(Node<T> *_node, List<T> *_list)
      {
        node = _node;
        lst = _list;
      }

    bool hasNext()
      {
        return (node != NULL);
      }

    T next()
      {
        if(node != NULL)
        {
          T to_return = node -> value;
          node = node -> next;
          return to_return;
        }
        else
        {
          throw new EmptyListException();
        }
        
      }

    void erase()
      {
        if(node == NULL)
        {
          lst -> remove_last();
        }
        else
        {
          lst -> remove(node -> prec);
        }

      }
  };

  

}

#endif
