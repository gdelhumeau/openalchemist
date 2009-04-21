/********************************************************************
                          OpenAlchemist

  File : CommonResources.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

//#include <ClanLib/core.h>

#include "CommonResources.h"
#include "Preferences.h"
#include "misc.h"
#include "Piece.h"

const int Piece::score[12] = { 1, 3, 9, 30, 90, 300, 900, 3000, 9000, 30000, 90000, 300000 };

CommonResources::CommonResources()
{
//TODO font stuffs
  main_font         = NULL;
  current_player    = NULL;
  CurrentKeyPressed = 0;
}

CommonResources::~CommonResources()
{
  unload_gfx();
}

void CommonResources::init(GameEngine *engine)
{
  this -> engine = engine;
  read_scores();
  
}

void CommonResources::load_gfx(std::string skin)
{
#ifndef LINUX_MODE
  FILE * debugFile;
  debugFile=fopen("debug.log", "a+");
  fprintf(debugFile, "Load gfx common resources began\n");
  fclose(debugFile);
#else
  printf("Load gfx common resources began\n");
#endif
  this -> skin = skin;
#ifndef LINUX_MODE
  freopen(  "debug.log","a+",debugFile);
  fprintf(debugFile, "Common resources skin %s ok\n",skin.c_str());
  fclose(debugFile);
#else
  printf("Common resources skin %s ok\n",skin.c_str());
#endif
  main_font=NULL;
  unload_gfx();
#ifndef LINUX_MODE
  freopen(  "debug.log","a+",debugFile);
  fprintf(debugFile, "Unloadgfx done\n");
  fclose(debugFile);
#else
  printf("Unloadgfx done\n");
#endif
//TODO: find a way to manage this with zlib driectly
//      and resources manager
//  CL_Zip_Archive zip(skin);
//  CL_ResourceManager gfx("general.xml",&zip, false);
//  CL_ResourceManager gfx_pieces("pieces.xml", &zip, false);

  main_font = new BitmapFont(skin, SCORE_FONT);
#ifndef LINUX_MODE
  freopen(  "debug.log","a+",debugFile);
  fprintf(debugFile, "New bitmap created\n");
  fclose(debugFile);
#else
  printf("New bitmap created\n");
#endif
  // Then, propreties
  //pieces_width = CL_Integer_to_int("pieces/width", &gfx_pieces);
  //pieces_height = CL_Integer_to_int("pieces/height", &gfx_pieces);
  // TODO: size chosen in pixels, see whether needed to be set other way
  // and be or not managed
  pieces_width = 26;
  pieces_height = 25;
#ifndef LINUX_MODE
  freopen(  "debug.log","a+",debugFile);
  fprintf(debugFile, "Piece sizes ok\n");
  fclose(debugFile);
#else
  printf("Piece sizes ok\n");
#endif
  player1.load_gfx(skin);
#ifndef LINUX_MODE
  freopen(  "debug.log","a+",debugFile);
  fprintf(debugFile, "Player 1 load gfx ok\n");
  fclose(debugFile);
#else
  printf("Player 1 load gfx ok\n");
#endif
  /// Do not managing skin using front layer for the moment
  front_layer.load_gfx(skin);

}


void CommonResources::unload_gfx()
{
 /// Build bitmapfont class
  if(main_font != NULL)
  {
    //delete main_font;
    //main_font->unload_gfx();
    delete main_font;
    main_font = NULL;
  }

  player1.unload_gfx();
  /// Do not managing skin using front layer for the moment
  front_layer.unload_gfx();
printf("common resources unload_gfx done\n");
}

void CommonResources::read_scores()
{
  highscore = 0;
    
  std::string path = get_save_path();
  
/*  try
  {*/
     
     /*FILE * file = fopen((path+get_path_separator()+"hightscores-"+get_version()).c_str(), "r+");*/
    FILE * HighScoreFile = fopen("highscore-0.3", "r+");

    if(HighScoreFile)
    {
       char digit;
       char tempHighScore[10]="";
       digit = fgetc(HighScoreFile);
       while(digit != '\n')
       {
	  sprintf(tempHighScore,"%s%c",tempHighScore,digit);
	  digit = fgetc(HighScoreFile);
       }
    
      highscore = atoi(tempHighScore);
      printf("HighScore ridden : %d\n",highscore);
      fclose(HighScoreFile);
    }
  /*}
  catch(CL_Error e)
  {*/
    else
    {
        std::cout << "Can't read hightscores file. Probably doesn't exist. \n";
        highscore = 0;
    }
 /* }*/
}

void CommonResources::save_scores()
{
  //std::string path = get_save_path();
    FILE * HighScoreFile = fopen("highscore-0.3", "w");

    if(HighScoreFile)
    {
	fprintf(HighScoreFile,"%d\n",highscore);
	fclose(HighScoreFile);
    }

}


CommonResources* common_resources_get_instance()
{
  static CommonResources instance;
  return &instance;
}
