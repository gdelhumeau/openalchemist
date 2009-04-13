/********************************************************************
                          OpenAlchemist

  File : SkinsMenuState.cpp
  Description :Skins Menu Implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include <fstream>
#include <iostream>

#include "SkinsMenuState.h"
#include "../CommonResources.h"
#include "../GameEngine.h"
#include "../misc.h"
#include "psp_sdl.h"


#define MAX_LENGTH_LINE 100

#define STEP_APPEARING 0
#define STEP_NORMAL 1
#define STEP_DISAPPEARING 2

#define APPEARING_SPEED 0.003

void SkinsMenuState::init()
{
  int fileState=0;
  GameState::init();
  printf("Gamestate init done\n");
// First we load Skin propreties saved in the conf file

  FILE * file;
  FILE * debugfile;
  debugfile = fopen( "debug.log", "a+");
  std::string path = get_save_path();
  std::string file_path = /*path + get_path_separator() + */"skins-" + get_version();
  file = fopen(file_path.c_str(), "r+");

// I choose to create a property file 
// I will have to check whether this could be managed in a save file
//TODO : check the getted path, should be like ms0:\psp\game\savedata ...
  
  
  fprintf(debugfile,"path : %s\n", path.c_str());
  fprintf(debugfile,"file_path : %s\n", file_path.c_str());

  skins_list.clear();
 // try
 // {
    
    // this is the file that contains the list of the available skins
    
    
    
    if(!file)
	{
	  fprintf(debugfile, "could not open properties file\n");
	  printf("could not open properties file\n");
	  
        }
    else
	{
	  fprintf(debugfile, "could open properties file\n");
	  printf("could open properties file\n");
	  
        }
/*    fileState=file.rdstate();
        if (fileState & std::ios::badbit)
            debugfile << "badbit - a fatal I/O error has occurred" << std::endl;      
        if (fileState & std::ios::eofbit)
            debugfile<< "eofbit - end of file is encountered" << std::endl;
        if (fileState & std::ios::failbit)
            debugfile << "failbit - a nonfatal I/O error has occurred" << std::endl;
    debugfile.close();*/
    if(file!=NULL)
    {char temp;
      fprintf(debugfile," we could open : %s \n",file_path.c_str());
      temp = fgetc(file); 
      fprintf(debugfile,"fgetc returned : %c\n",temp);
      while(temp != EOF)
      {
        char tempFilename[64] = "";
        char tempNum[10]="";
        
        while(temp != '\n')
        { 
        sprintf(tempFilename,"%s%c", tempFilename, temp);
        temp = fgetc(file);
        }
        fprintf(debugfile, "line is : %s\n",tempFilename);
        Skin *sp = new Skin();
        sp->filename = std::string(tempFilename);
        temp = fgetc(file);
        while(temp != '\n')
        { 
        sprintf(tempNum,"%s%c", tempNum, temp);
        temp = fgetc(file);
        }
        sp->element = atoi(tempNum);
        fprintf(debugfile, "number line is : %s\n",tempNum);
        temp = fgetc(file);

//         try
//         {
        // We load the logo sprite in the gfx ressources file
        //CL_ResourceManager gfx("general.xml", new CL_Zip_Archive(sp -> filename), true);
	sp -> logo = IMG_Load_fromSkin(sp->filename, "misc/logo.png");
        if(!(sp->logo))
	{
	   psp_sdl_print(70, 50, "Could not load skin logo", 255);
	   fprintf(debugfile,"could not load skin logo \n");
	   fclose(debugfile);
	   return;
	}
	skins_list.insert(skins_list.end(), sp);

   }
//         catch(SDL_Error e)
//         {
//         // We forget this skin
// 	std::cout << "We don't use " << sp -> filename << " because it doesn't exist." << std::endl;
// 	delete sp;
//         }
      
    }
    else
    {
	fprintf(debugfile, "Unable to open skin property file\n");
	fclose(debugfile);
        return;
    }

    fclose(file);
    fclose(debugfile);
    
//   }
//   catch(SDL_Error e)
//   {
//     std::cout << "Error while reading " << file_path << " file, probably doesn't exist yet." << std::endl;
//   }

// Then, we scan the current ./skins folder
//TODO : do a scan of directory skin to make sure the listed skins are present
// and then catching the error if not
/*
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
          CL_Surface *logo = new CL_Surface("logo", &gfx);

          bool found = false;
          for(u_int i = 0; i < skins_list.size(); ++i)
          {
            if(skins_list[i] -> filename == filename)
            {
              found = true;
              break;
            }
          }
          if(!found)
          {
            Skin *sp = new Skin();
            sp -> filename = filename;
            sp -> element = 3;
            sp -> logo = logo;
            skins_list.insert(skins_list.end(), sp);
          }

        }
        catch(SDL_Error e)
        {
          std::cout << "Skin " << dir << scanner.get_name() << " is not valid." << std::endl;
        }
      }        

    }
  }
*/
  // Sorting skin list by alphabetical order (bubble sort)
  for(u_int i=0; i<skins_list.size(); ++i)
    for(u_int j=i+1; j<skins_list.size(); ++j)
    {
      if(skins_list[i]->filename.compare(skins_list[j]->filename)>0)
      {
	Skin * sk = skins_list[i];
	skins_list[i] = skins_list[j];
	skins_list[j] = sk;
      }
    }

  // Calculating the lines number needed for the board
  number_y = skins_list.size() / 2;
  if(skins_list.size() % 2 > 0)
    number_y += 1;

  // Making the board
  skins_board[0] = new Skin* [number_y];
  skins_board[1] = new Skin* [number_y];

  // Initializing the board
  for(int x=0; x<2; ++x)
    for(int y=0; y<number_y; ++y)
    {
      skins_board[x][y] = NULL;
    }
  
  // Setting skins to the board
  int x= 0, y = 0;
  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    skins_board[x][y] = skins_list[i];
    x++;
    if(x > 1)
    {
      y++;
      x = 0;
    }
  }

  // Initalizing variables
  selection_x = selection_y = 0;
  y_start = 0;
  background       = NULL;
  logo_unavailable = NULL;
  cursor           = NULL;
  arrow_down       = NULL;
  arrow_up         = NULL;
}

void SkinsMenuState::deinit()
{
//TODO : scan skin path and save 
  // Saving progression skin file
/*  std::string file_path = get_save_path() + get_path_separator() + "skins-" + get_version();

  try
  {
    CL_OutputSource_File file(file_path);
    for(u_int i = 0; i < skins_list.size(); ++i)
    {
      file.write_string(skins_list[i]->filename);
      file.write_uint8 (skins_list[i]->element);  
    }
    file.close();
       
  }
  catch(CL_Error e)
  {
    std::cout << "Error while reading " << file_path << "file, probably doesn't exist yet." << std::endl;
  }
*/
  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    delete skins_list[i];
  }

  skins_list.clear();

  delete skins_board[0];
  delete skins_board[1];
}

void SkinsMenuState::load_gfx(std::string skin)
{

SDL_Surface * temp;
  // Getting skins resources
  /*CL_Zip_Archive zip(skin);
  CL_ResourceManager gfx("menu_skins.xml", &zip, false);*/
  unload_gfx();
  // First, the sprites
  //background = new CL_Sprite("menu_skins/background", &gfx); 
  //logo_unavailable = new CL_Surface("menu_skins/logo_unavailable", &gfx); 
  background = IMG_Load_fromSkin(skin, "dialogs/skins/background.png"); 
  logo_unavailable = IMG_Load_fromSkin(skin, "dialogs/skins/logo-unavailable.png"); 


  //cursor = new CL_Sprite("menu_skins/cursor", &gfx);
  //arrow_down = new CL_Sprite("menu_skins/arrow_down/sprite", &gfx);
  cursor = IMG_Load_fromSkin(skin, "dialogs/skins/cursor.png");
  
  arrow_down = IMG_Load_fromSkin(skin, "dialogs/skins/arrow_down.png");
  
  //TODO:
  // Arbitrary position need to be fixed regarding psp rendering
  arrow_down_left = 50; //CL_Integer_to_int("menu_skins/arrow_down/left", &gfx);
  arrow_down_top = 50; //CL_Integer_to_int("menu_skins/arrow_down/top", &gfx);


  //arrow_up = new CL_Sprite("menu_skins/arrow_up/sprite", &gfx);
  arrow_up = IMG_Load_fromSkin(skin, "dialogs/skins/arrow_up.png");
  //TODO:
  // Arbitrary position need to be fixed regarding psp rendering
  arrow_up_left = 50;//CL_Integer_to_int("menu_skins/arrow_up/left", &gfx);
  arrow_up_top = 70;//CL_Integer_to_int("menu_skins/arrow_up/top", &gfx);

  //TODO:
  // Arbitrary position need to be fixed regarding psp rendering
  skins_preview_x = PSP_SDL_SCREEN_WIDTH/2 - (skins_board[0][0]-> logo) -> w;//85;
 //CL_Integer_to_int("menu_skins/skins-preview-coords/left", &gfx);
  skins_preview_y = 80; //CL_Integer_to_int("menu_skins/skins-preview-coords/top", &gfx);
  
  skins_preview_width  = (skins_board[0][0]-> logo) -> w; //CL_Integer_to_int("menu_skins/skins-preview-coords/width", &gfx);
  skins_preview_height = logo_unavailable -> h + 5; //CL_Integer_to_int("menu_skins/skins-preview-coords/height", &gfx);

  cursor_x      = PSP_SDL_SCREEN_WIDTH/2 - (cursor->w); //CL_Integer_to_int("menu_skins/cursor-coords/left", &gfx);
  cursor_y      = 73; //CL_Integer_to_int("menu_skins/cursor-coords/top", &gfx);
  cursor_width  = cursor->w; //CL_Integer_to_int("menu_skins/cursor-coords/width", &gfx);
  cursor_height = cursor->h; //CL_Integer_to_int("menu_skins/cursor-coords/height", &gfx);
 
  
}

void SkinsMenuState::unload_gfx()
{
  if(background)
  {
    SDL_FreeSurface(background);
    background=NULL;
  }
  if(logo_unavailable)
  {
    SDL_FreeSurface(logo_unavailable);
    logo_unavailable=NULL;
  }
  if(cursor)
  {
    SDL_FreeSurface(cursor);
    cursor=NULL;
  }
  if(arrow_down)
  {
    SDL_FreeSurface(arrow_down);
    arrow_down=NULL;
  }
  if(arrow_up)
  {
    SDL_FreeSurface(arrow_up);
    arrow_up=NULL;
  }
}

void SkinsMenuState::draw()
{
   int x = PSP_SDL_SCREEN_WIDTH/2 - (background->w + background->w%2)/2;
   int y = PSP_SDL_SCREEN_HEIGHT/2 - (background->h + background->h%2)/2;;
   psp_sdl_blit_on_screen_at_XY(background, x, y);


  // Drawing logo skins
  for(int i=0; i<2; ++i)
    for(int j=0; j<2 && j+y_start<number_y; ++j)
    {
      if(skins_board[i][j+y_start])
      { 
        if(skins_board[i][j] -> logo)
         /* skins_board[i][j+y_start] -> logo -> draw(skins_preview_x+i*skins_preview_width,
						    skins_preview_y+j*skins_preview_height);*/
	  psp_sdl_blit_on_screen_at_XY(skins_board[i][j+y_start] -> logo,
					skins_preview_x+i*skins_preview_width,
					skins_preview_y+j*skins_preview_height);

        // If the skin is not available, we draw logo_unavailable
        if(common_resources -> skin != skins_board[i][j+y_start] -> filename
           && skins_board[i][j] -> element < (u_int) common_resources->player1.get_visible_pieces())
          /*logo_unavailable -> draw(skins_preview_x+i*skins_preview_width,
						    skins_preview_y+j*skins_preview_height);*/
	psp_sdl_blit_on_screen_at_XY(logo_unavailable, 
				     skins_preview_x+i*skins_preview_width,
                                     skins_preview_y+j*skins_preview_height);
      }
    }

  // Drawing the cursor
  //cursor -> draw(cursor_x+selection_x*cursor_width, 
  //		 cursor_y+(selection_y-y_start)*cursor_height);
  psp_sdl_blit_on_screen_at_XY(cursor,
			       cursor_x+selection_x*cursor_width,
                               cursor_y+(selection_y-y_start)*cursor_height);

  // Drawig arrows, if needed
  if(y_start + 2 < number_y)
  {
    //arrow_down -> draw(arrow_down_left, arrow_down_top);
    psp_sdl_blit_on_screen_at_XY(arrow_down, arrow_down_left, arrow_down_top);
  }

  if(y_start > 0)
  {
    //arrow_up -> draw(arrow_up_left, arrow_up_top);
    psp_sdl_blit_on_screen_at_XY(arrow_up, arrow_up_left, arrow_up_top);
  }

}

void SkinsMenuState::update()
{
  switch(step)
  {
  case STEP_APPEARING:
    appear();
    break;
  case STEP_DISAPPEARING:
    disappear();
    break;
  }
}

void SkinsMenuState::events()
{
  if(step != STEP_NORMAL)
    return;

 switch(common_resources->CurrentKeyPressed)
  {

  case KEY_ESCAPE:
  case KEY_SKINS:
  {   
    step = STEP_DISAPPEARING;
    common_resources->CurrentKeyPressed = 0;
    break;
  }

  // KEY DOWN
  case KEY_DOWN:
  {
    // If we don't go outline
    if(selection_y + 1 < number_y)
    {
      // If there is a skin in this place
      if(skins_board[selection_x][selection_y + 1])
      {
        selection_y++;

        if(selection_y > y_start + 1)
          y_start ++;
      }
      // Else, we juste increment y_start
      else if(selection_y > y_start && selection_x == 1 && !skins_board[1][selection_y+1] && skins_board[0][selection_y+1])
      {
        y_start ++;
      }
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }

  // KEY UP
  case KEY_UP:
  {
    if(selection_y > 0 && skins_board[selection_x][selection_y-1])
    {
      selection_y--;

      if(selection_y < y_start)
        y_start --;
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }

  // KEY RIGHT
  case KEY_RIGHT:
  {
    if(selection_x == 0 && skins_board[1][selection_y])
    {
      selection_x = 1;
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }

  // KEY LEFT
  case KEY_LEFT:
  {
    if(selection_x == 1 && skins_board[0][selection_y])
    {
      selection_x = 0;
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }

  // KEY ENTER
  case KEY_ENTER:
  {
    // Can we see all pieces ?
    if(skins_board[selection_x][selection_y] -> element >= (u_int) common_resources->player1.get_visible_pieces()
       // Is this the current skin ?
       && common_resources -> skin != skins_board[selection_x][selection_y] -> filename)
    {
      common_resources -> engine -> set_skin(skins_board[selection_x][selection_y] -> filename);
    }
  common_resources->CurrentKeyPressed = 0;
  break;
  }
 }
}

void SkinsMenuState::appear()
{

 printf("alpha : %d\n",alpha);
 
  if(alpha + ( (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED*common_resources -> time_interval)) >= SDL_ALPHA_OPAQUE)
  {
    step = STEP_NORMAL;
    alpha = SDL_ALPHA_OPAQUE;
  }
  else
    alpha += (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);


  //background -> set_alpha(alpha);
  SDL_SetAlpha(background , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //arrow_up   -> set_alpha(alpha);
  SDL_SetAlpha(arrow_up , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //arrow_down -> set_alpha(alpha);
  SDL_SetAlpha(arrow_down , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //cursor     -> set_alpha(alpha);
  SDL_SetAlpha(cursor , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //logo_unavailable -> set_alpha(alpha);
  SDL_SetAlpha(logo_unavailable , SDL_SRCALPHA | SDL_RLEACCEL, alpha);

  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    //skins_list[i] -> logo -> set_alpha(alpha);
    SDL_SetAlpha(skins_list[i] -> logo , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  }


}

void SkinsMenuState::disappear()
{  
  alpha -= (int)(SDL_ALPHA_OPAQUE * APPEARING_SPEED * common_resources -> time_interval);

  //background -> set_alpha(alpha);
  SDL_SetAlpha(background , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //arrow_up   -> set_alpha(alpha);
  SDL_SetAlpha(arrow_up , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //arrow_down -> set_alpha(alpha);
  SDL_SetAlpha(arrow_down , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //cursor     -> set_alpha(alpha);
  SDL_SetAlpha(cursor , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  //logo_unavailable -> set_alpha(alpha);
  SDL_SetAlpha(logo_unavailable , SDL_SRCALPHA | SDL_RLEACCEL, alpha);

  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    //skins_list[i] -> logo -> set_alpha(alpha);
    SDL_SetAlpha(skins_list[i] -> logo , SDL_SRCALPHA | SDL_RLEACCEL, alpha);
  }

  if(alpha <= SDL_ALPHA_TRANSPARENT || !common_resources -> engine -> is_opengl_used())
  {
    common_resources -> engine -> stop_current_state();
    start();
  }

}

void SkinsMenuState::start()
{
  if(common_resources -> engine -> is_opengl_used())
   {
    step = STEP_APPEARING;
    alpha = SDL_ALPHA_TRANSPARENT;
  }
  else
  {
    step = STEP_NORMAL;
  }
}

bool SkinsMenuState::front_layer_behind()
{
  return true;
}

void SkinsMenuState::set_skin_elements(u_int element)
{
  for(u_int i = 0; i < skins_list.size(); ++i)
  {
    if(skins_list[i] -> filename == common_resources -> skin)
    {
      if(skins_list[i] -> element < element)
        skins_list[i] -> element = element;
    }
  }
}

void SkinsMenuState::print()
{
  printf("SkinsMenuState\n");
}


SkinsMenuState::SkinsMenuState()
{

}

SkinsMenuState::~SkinsMenuState()
{
  deinit();

}



    
