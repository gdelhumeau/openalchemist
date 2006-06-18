/* FreeAlchemist - just a simple game 
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

#ifndef _MISC_H_
#define _MISC_H_

#include <string>
#include <sstream>  
#include <iostream>

template<typename T>
std::string to_string( const T & Value )
{
    // utiliser un flux de sortie pour crÃ©er la chaÃ®ne
    std::ostringstream oss;
    // Ã©crire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}




#endif
