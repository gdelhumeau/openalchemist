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

#include "headers.h"

void Game::read_scores()
{

  std::string path = get_save_path();

  try
  {
#ifdef WIN32
     CL_InputSource_File file(path+"\hightscores");
#else
     CL_InputSource_File file(path+"/hightscores");
#endif

    file.open();
    for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
    {
      hightscores[i] = file.read_uint32();
    }
    file.close();
  }
  catch(CL_Error e)
  {
    std::cout << "Can't read hightscores file. Probably doesn't exist. \n";
    for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
    {
      hightscores[i] = 0;
    }
  }
  
}

void Game::save_scores()
{
  
  std::string path = get_save_path();

  if(global_score + global_bonus > hightscores[current_difficulty])
  {
    last_hightscore =  hightscores[current_difficulty];
    hightscores[current_difficulty] = global_score + global_bonus;
  }

  try
  {
#ifdef WIN32
    CL_OutputSource_File file(path+"\hightscores");
#else
    CL_OutputSource_File file(path+"/hightscores");
#endif
    
    file.open();
    for(u_int i = 0; i < NUMBER_OF_DIFFICULTIES; ++i)
    {
      file.write_uint32(hightscores[i]);
    }
    file.close();
  }
  catch(CL_Error e)
  {
    std::cout << "Can't write hightscores file. \n";
  }
}
