/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#ifndef _COORDS_H_
#define _COORDS_H_
    
class Coords
{
  public:
  int x;
  int y;
  int piece_number;
      
  Coords(int x, int y)
    {
      this -> x = x;
      this -> y = y;
      this -> piece_number = 0;
    }
      
  Coords(Coords* c)
    {
      this -> x = c->x;
      this -> y = c->y;
      this -> piece_number = c->piece_number;
    }
};

#endif
