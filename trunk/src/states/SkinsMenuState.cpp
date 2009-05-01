/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.cpp
  Description :Skins Menu Implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "../memory.h"
#include <ClanLib/core.h>

#include "SkinsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void SkinsMenuState::init()
{
  GameState::init();


// Fist we load Skin propreties saved in the conf file

  std::string path = get_save_path();
  std::string file_path = path + get_path_separator() + "skins-" + get_version();

  _skins_list.clear();
  try
  {
    CL_InputSource_File file(file_path);
    while(file.tell() != file.size())
    {     
      Skin *sp = my_new Skin();
      sp -> filename = file.read_string();
      sp -> element = file.read_uint8();

      try
      {
	// We load the logo sprite in the gfx ressources file
	CL_ResourceManager gfx("general.xml", new CL_Zip_Archive(sp -> filename), true);
	sp -> logo = my_new CL_Surface("logo", &gfx);
	_skins_list.insert(_skins_list.end(), sp);
      }
      catch(CL_Error e)
      {
	// We forget this skin
	std::cout << "We don't use " << sp -> filename << " because it doesn't exist." << std::endl;
	my_delete(sp);
      }
      
    }
    file.close();
    
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << " file, probably doesn't exist yet." << std::endl;
  }

// Then, we scan the current ./skins folder
  std::string dir = get_skins_path() + get_path_separator();

  CL_DirectoryScanner scanner;
  if (scanner.scan(dir, "*.zip"))
  {
    while(scanner.next())
    {
      if(scanner.is_readable())
      {
        try
        {
          std::string filename = dir+scanner.get_name();
          // We load the logo sprite in the gfx ressources file
          CL_ResourceManager gfx("general.xml", new CL_Zip_Archive(filename), true);
          CL_Surface *logo = my_new CL_Surface("logo", &gfx);

          bool found = false;
          for(u_int i = 0; i < _skins_list.size(); ++i)
          {
            if(_skins_list[i] -> filename == filename)
            {
              found = true;
              break;
            }
          }
          if(!found)
          {
            Skin *sp = my_new Skin();
            sp -> filename = filename;
            sp -> element = 3;
            sp -> logo = logo;
            _skins_list.insert(_skins_list.end(), sp);
          }

        }
        catch(CL_Error e)
        {
          std::cout << "Skin " << dir << scanner.get_name() << " is not valid." << std::endl;
        }
      }        

    }
  }

  // Sorting skin list by alphabetical order (bubble sort)
  for(u_int i=0; i<_skins_list.size(); ++i)
    for(u_int j=i+1; j<_skins_list.size(); ++j)
    {
      if(_skins_list[i]->filename.compare(_skins_list[j]->filename)>0)
      {
	Skin * sk = _skins_list[i];
	_skins_list[i] = _skins_list[j];
	_skins_list[j] = sk;
      }
    }

  // Calculating the lines number needed for the board
  _number_y = _skins_list.size() / 2;
  if(_skins_list.size() % 2 > 0)
    _number_y += 1;

  // Making the board
  skins_board[0] = new Skin* [_number_y];
  skins_board[1] = new Skin* [_number_y];

  // Initializing the board
  for(int x=0; x<2; ++x)
    for(int y=0; y<_number_y; ++y)
    {
      skins_board[x][y] = NULL;
    }
  
  // Setting skins to the board
  int x= 0, y = 0;
  for(u_int i = 0; i < _skins_list.size(); ++i)
  {
    skins_board[x][y] = _skins_list[i];
    x++;
    if(x > 1)
    {
      y++;
      x = 0;
    }
  }

  // Initalizing variables
  _selection_x = _selection_y = 0;
  _y_start = 0;
}

void SkinsMenuState::deinit()
{
	
  /*// Saving progression skin file
  std::string file_path = get_save_path() + get_path_separator() + "skins-" + get_version();

  try
  {
    CL_OutputSource_File file(file_path);
    for(u_int i = 0; i < _skins_list.size(); ++i)
    {
      file.write_string(_skins_list[i]->filename);
      file.write_uint8 (_skins_list[i]->element);  
    }
    file.close();
       
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << "file, probably doesn't exist yet." << std::endl;
  }*/

  for(u_int i = 0; i < _skins_list.size(); ++i)
  {
		if(_skins_list[i] -> logo)
		{
			my_delete(_skins_list[i] -> logo);
			_skins_list[i] -> logo = NULL;
		}
		Skin* sk = _skins_list[i];
		if(sk)
		{
			my_delete(sk);
			sk = NULL;
		}
  }

  _skins_list.clear();

	
	/*if(skins_board[0])
	delete[] (skins_board[0]);
	if(skins_board[1])
	delete[] (skins_board[1]);*/
	
}

void SkinsMenuState::load_gfx(std::string skin)
{
	unload_gfx();
	
  // Getting skins resources
  CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_skins.xml", &zip, false);

  // First, the sprites
  _p_background = my_new CL_Sprite("menu_skins/background", &gfx); 
  _p_logo_unavailable = my_new CL_Surface("menu_skins/logo_unavailable", &gfx); 

  _p_cursor = my_new CL_Sprite("menu_skins/cursor", &gfx);
  _p_arrow_down = my_new CL_Sprite("menu_skins/arrow_down/sprite", &gfx);
  _arrow_down_left = CL_Integer_to_int("menu_skins/arrow_down/left", &gfx);
  _arrow_down_top = CL_Integer_to_int("menu_skins/arrow_down/top", &gfx);

  _p_arrow_up = my_new CL_Sprite("menu_skins/arrow_up/sprite", &gfx);
  _arrow_up_left = CL_Integer_to_int("menu_skins/arrow_up/left", &gfx);
  _arrow_up_top = CL_Integer_to_int("menu_skins/arrow_up/top", &gfx);

  _skins_preview_x = CL_Integer_to_int("menu_skins/skins-preview-coords/left", &gfx);
  _skins_preview_y = CL_Integer_to_int("menu_skins/skins-preview-coords/top", &gfx);
  _skins_preview_width = CL_Integer_to_int("menu_skins/skins-preview-coords/width", &gfx);
  _skins_preview_height = CL_Integer_to_int("menu_skins/skins-preview-coords/height", &gfx);

  _cursor_x      = CL_Integer_to_int("menu_skins/cursor-coords/left", &gfx);
  _cursor_y      = CL_Integer_to_int("menu_skins/cursor-coords/top", &gfx);
  _cursor_width  = CL_Integer_to_int("menu_skins/cursor-coords/width", &gfx);
  _cursor_height = CL_Integer_to_int("menu_skins/cursor-coords/height", &gfx);
 
  
}

void SkinsMenuState::unload_gfx()
{
	if(_p_background)
	{
		my_delete(_p_background);
		_p_background = NULL;
	}
	
	if(_p_logo_unavailable)
	{
		my_delete( _p_logo_unavailable);
		_p_logo_unavailable = NULL;
	}
	
	if(_p_cursor)
	{
		my_delete( _p_cursor);
		_p_cursor = NULL;
	}
	
	if(_p_arrow_down)
	{
		my_delete( _p_arrow_down);
		_p_arrow_down = NULL;
	}

	if(_p_arrow_up)
	{
		my_delete( _p_arrow_up);
		_p_arrow_up = NULL;
	}
	
}

void SkinsMenuState::draw()
{
  int x = 400 - _p_background -> get_width()/2;
  int y = 300 - _p_background -> get_height()/2;
  _p_background -> draw(x,y);

  // Drawing logo skins
  for(int i=0; i<2; ++i)
    for(int j=0; j<2 && j+_y_start<_number_y; ++j)
    {
      if(skins_board[i][j+_y_start])
      { 
        if(skins_board[i][j] -> logo)
          skins_board[i][j+_y_start] -> logo -> draw(_skins_preview_x+i*_skins_preview_width,
						    _skins_preview_y+j*_skins_preview_height);

        // If the skin is not available, we draw logo_unavailable
        if(_p_common_resources -> skin != skins_board[i][j+_y_start] -> filename
           && skins_board[i][j] -> element < (u_int) _p_common_resources->player1.get_visible_pieces())
          _p_logo_unavailable -> draw(_skins_preview_x+i*_skins_preview_width,
						    _skins_preview_y+j*_skins_preview_height);
      }
    }

  // Drawing the cursor
  _p_cursor -> draw(_cursor_x+_selection_x*_cursor_width, 
		 _cursor_y+(_selection_y-_y_start)*_cursor_height);

  // Drawig arrows, if needed
  if(_y_start + 2 < _number_y)
  {
    _p_arrow_down -> draw(_arrow_down_left, _arrow_down_top);
  }

  if(_y_start > 0)
  {
    _p_arrow_up -> draw(_arrow_up_left, _arrow_up_top);
  }

}

void SkinsMenuState::update()
{
  switch(_step)
  {
  case STEP_APPEARING:
    _appear();
    break;
  case STEP_DISAPPEARING:
    _disappear();
    break;
  }
}

void SkinsMenuState::events()
{
  if(_step != STEP_NORMAL)
    return;

  if(_p_common_resources->key.escape->get() || _p_common_resources->key.skins->get())
  {   
    _step = STEP_DISAPPEARING;
  }

  // KEY DOWN
  if(_p_common_resources -> key.down -> get())
  {
    // If we don't go outline
    if(_selection_y + 1 < _number_y)
    {
      // If there is a skin in this place
      if(skins_board[_selection_x][_selection_y + 1])
      {
        _selection_y++;

        if(_selection_y > _y_start + 1)
          _y_start ++;
      }
      // Else, we juste increment y_start
      else if(_selection_y > _y_start && _selection_x == 1 && !skins_board[1][_selection_y+1] && skins_board[0][_selection_y+1])
      {
        _y_start ++;
      }
    }
  }

  // KEY UP
  if(_p_common_resources -> key.up -> get())
  {
    if(_selection_y > 0 && skins_board[_selection_x][_selection_y-1])
    {
      _selection_y--;

      if(_selection_y < _y_start)
        _y_start --;
    }
  }

  // KEY RIGHT
  if(_p_common_resources -> key.right -> get())
  {
    if(_selection_x == 0 && skins_board[1][_selection_y])
    {
      _selection_x = 1;
    }
  }

  // KEY LEFT
  if(_p_common_resources -> key.left -> get())
  {
    if(_selection_x == 1 && skins_board[0][_selection_y])
    {
      _selection_x = 0;
    }
  }

  // KEY ENTER
  if(_p_common_resources -> key.enter -> get())
  {
    // Can we see all pieces ?
    if(skins_board[_selection_x][_selection_y] -> element >= (u_int) _p_common_resources->player1.get_visible_pieces()
       // Is this the current skin ?
       && _p_common_resources -> skin != skins_board[_selection_x][_selection_y] -> filename)
    {
      _p_common_resources -> p_engine -> set_skin(skins_board[_selection_x][_selection_y] -> filename);
    }
  }

}

void SkinsMenuState::_appear()
{ 
  if(_alpha + APPEARING_SPEED*_p_common_resources -> time_interval >= 1.0)
  {
    _step = STEP_NORMAL;
    _alpha = 1.0;
  }
  else
    _alpha += APPEARING_SPEED * _p_common_resources -> time_interval;

  _p_background -> set_alpha(_alpha);
  _p_arrow_up   -> set_alpha(_alpha);
  _p_arrow_down -> set_alpha(_alpha);
  _p_cursor     -> set_alpha(_alpha);
  _p_logo_unavailable -> set_alpha(_alpha);

  for(u_int i = 0; i < _skins_list.size(); ++i)
  {
    _skins_list[i] -> logo -> set_alpha(_alpha);
  }


}

void SkinsMenuState::_disappear()
{  
  _alpha -= APPEARING_SPEED * _p_common_resources -> time_interval;

  _p_background -> set_alpha(_alpha);
  _p_arrow_up   -> set_alpha(_alpha);
  _p_arrow_down -> set_alpha(_alpha);
  _p_cursor     -> set_alpha(_alpha);
  _p_logo_unavailable -> set_alpha(_alpha);

  for(u_int i = 0; i < _skins_list.size(); ++i)
  {
    _skins_list[i] -> logo -> set_alpha(_alpha);
  }

  if(_alpha <= 0.0 || !_p_common_resources -> p_engine -> is_opengl_used())
  {
    _p_common_resources -> p_engine -> stop_current_state();
    start();
  }

}

void SkinsMenuState::start()
{
  if(_p_common_resources -> p_engine -> is_opengl_used())
  {
    _step = STEP_APPEARING;
    _alpha = 0.0;
  }
  else
  {
    _step = STEP_NORMAL;
  }
}

bool SkinsMenuState::front_layer_behind()
{
  return true;
}

void SkinsMenuState::set_skin_elements(u_int element)
{
  for(u_int i = 0; i < _skins_list.size(); ++i)
  {
    if(_skins_list[i] -> filename == _p_common_resources -> skin)
    {
      if(_skins_list[i] -> element < element)
        _skins_list[i] -> element = element;
    }
  }
}

SkinsMenuState::SkinsMenuState()
{
	_p_background				= NULL;
	_p_logo_unavailable = NULL;
	_p_cursor						= NULL;
	_p_arrow_down				= NULL;
	_p_arrow_up					= NULL;
	
}

SkinsMenuState::~SkinsMenuState()
{
  deinit();
	unload_gfx();

}



    
