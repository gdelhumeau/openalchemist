/********************************************************************
                          OpenAlchemist

  File : Board.cpp
  Description : Board implementation
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "Board.h"

#include "CommonResources.h"
#include "GameEngine.h"
#include "misc.h"

Board::Board()
{
    
  /* Initializing all to NULL */
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
      board[i][j] = NULL;

}

Board::~Board()
{
  clear();
}

void Board::clear()
{
  /* Initializing all to NULL */
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
      if(board[i][j])
      {
        delete board[i][j];
        board[i][j] = NULL;
      }

}

void Board::apply_skin(SDL_Surface** pieces_normal, SDL_Surface** pieces_appearing, SDL_Surface** pieces_disappearing, SDL_Surface** pieces_mini)
{
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
	int value = board[i][j] -> get_piece_number();
        board[i][j] -> set_sprites(pieces_normal[value], pieces_appearing[value],
				   pieces_disappearing[value], pieces_mini[value]);
      }
    }
}


void Board::draw()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        board[i][j] -> draw(); 
      }
    }

  // Displaying scores
//TODO: find font stuffs to display the scores
  resources -> main_font -> draw(score_right, score_top, str_score);
  resources -> main_font -> draw(bonus_right, bonus_top, str_bonus);
  resources -> main_font -> draw(hightscore_right, hightscore_top, str_hightscore);

}

void Board::add_pieces(Piece* piece1, Piece* piece2)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  // Saving board state for undoing
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        undo_board[i][j] = board[i][j] -> get_piece_number();
      }
      else
      {
        undo_board[i][j] = -1;
      }
    } 

  undo_bonus_score = 0;
  undo_unlocked_pieces = unlocked_pieces;
  undo_visible_pieces = visible_pieces;
  
  Piece *piece_on_top, *piece_on_bottom;
  if(piece1 -> get_y() <= piece2 -> get_y())
  {
    piece_on_top = piece1;
    piece_on_bottom = piece2;
  }
  else
  {
    piece_on_top = piece2;
    piece_on_bottom = piece1;
  }
  
  //resources->pieces_width = 30;
  int piece_top_x = (int)((int)piece_on_top->get_x()-game_left)/(resources->pieces_width);
  float piece_top_xf = (piece_on_top->get_x()-game_left)/(resources->pieces_width);
  
  printf("piece_on_top->get_x() = %f, game_left = %d, resources->pieces_width = %d\n",piece_on_top->get_x(),game_left,resources->pieces_width);
  printf("piece_top_x if pieces_width = %d : %d, %f\n",resources->pieces_width,piece_top_x,piece_top_xf);

  //resources->pieces_width = 25;
  //piece_top_x = (int)((int)piece_on_top->get_x()-game_left)/(resources->pieces_width);

  //piece_top_xf = (piece_on_top->get_x()-game_left)/(resources->pieces_width);
  printf("piece_on_top->get_x() = %f, game_left = %d, resources->pieces_width = %d\n",piece_on_top->get_x(),game_left,resources->pieces_width);
  printf("piece_top_x if pieces_width = %d : %d,%f\n",resources->pieces_width,piece_top_x,piece_top_xf);

  //resources->pieces_width = 30;
  int piece_bottom_x = (int)((int)piece_on_bottom->get_x()-game_left)/(resources->pieces_width);  
  float piece_bottom_xf = (piece_on_bottom->get_x()-game_left)/(resources->pieces_width);  
  printf("piece_bottom_x if pieces_width = %d : %d, %f\n",resources->pieces_width,piece_bottom_x,piece_bottom_xf);
  //resources->pieces_width = 25;
  //piece_bottom_x = (int)((int)piece_on_bottom->get_x()-game_left)/(resources->pieces_width);
  //piece_bottom_xf = (piece_on_bottom->get_x()-game_left)/(resources->pieces_width);    
  printf("piece_bottom_x if pieces_width = %d : %d,%f\n",resources->pieces_width,piece_bottom_x,piece_bottom_xf);
  

  int y_bottom = -1;
  while(y_bottom < NUMBER_OF_LINES-1 && !board[piece_bottom_x][y_bottom+1])
  {
    ++y_bottom;
  }    
        
  if(y_bottom == -1 && board[piece_bottom_x][0])
  {
    calc_score();
     resources -> engine -> set_state_gameover(MODE_GAMEOVER);
  }
  else
  {
    board[piece_bottom_x][y_bottom] = piece_on_bottom;
  }
                
                
  int y_top = -1;
  while(y_top < NUMBER_OF_LINES-1 && !board[piece_top_x][y_top+1])
  {
    ++y_top;
  }      
        
  if(y_top==-1 && board[piece_top_x][0])
  {
    calc_score();
    resources -> engine -> set_state_gameover(MODE_GAMEOVER);
    board[piece_bottom_x][y_bottom] = NULL;
  }
  else
  {          
    board[piece_top_x][y_top] = piece_on_top;
  } 

printf("piece_on_bottom if pieces_width = 25 : x= %f, y=%f\n",piece_on_bottom->get_x(),piece_on_bottom->get_y());
printf("piece_bottom_x : %d, resources->pieces_width : %d, (piece_bottom_x*resources->pieces_width) : %d, game_left : %d, result : %d\n",piece_bottom_x,resources->pieces_width,(piece_bottom_x*resources->pieces_width),game_left,(piece_bottom_x*resources->pieces_width)+game_left);
  piece_on_bottom -> start_fall((piece_bottom_x*resources->pieces_width)+game_left,
                                game_top+(y_bottom-2)*resources->pieces_height);

printf("piece_on_bottom after star_fall if pieces_width = 25 : x= %f, y=%f\n",piece_on_bottom->get_x(),piece_on_bottom->get_y());

  piece_on_top -> start_fall((piece_top_x*resources->pieces_width)+game_left,
                             game_top+(y_top-2)*resources->pieces_height);
        
  falling_list.clear();
  falling_list.push_back(piece_on_top);
  falling_list.push_back(piece_on_bottom);

}

bool Board::fall_and_create()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  bool all_pieces_are_placed = true;
  for(u_int i=0; i<falling_list.size(); ++i)
  {
    if(falling_list[i])
    {
      if(!falling_list[i] -> fall(resources -> time_interval))
        all_pieces_are_placed = false;
    }
  }

  // This part makes pieces appear
  std::list<Piece*>::iterator it = appearing_list.begin();
  while(it != appearing_list.end())
  {
    Piece *p = (Piece*)*it;
    if(p -> appear())
    {
      it = appearing_list.erase(it);
    }
    else
    {
      all_pieces_are_placed = false;
      ++it;
    }
  }

  return all_pieces_are_placed;
  
}

bool Board::detect_pieces_to_destroy()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  // This table is used to know if a piece have been explorated 
  bool board_mark[NUMBER_OF_COLS][NUMBER_OF_LINES];
  for(int k=0; k<NUMBER_OF_COLS; ++k)
    for(int l=0; l<NUMBER_OF_LINES; ++l)
      board_mark[k][l] = false;
      
  // Stack to explore the board
  std::stack<Coords*> stack;
  
  // We clear the list witch will contains the pieces to make disappear
  list_to_destroy.clear();
      
    
  // We will look for all pieces in the table
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(board[i][j] != NULL && !board_mark[i][j])
      {
        int counter = 0;            
        int score_of_root = board[i][j] -> get_piece_number();
        
        std::vector<Coords*> list;
           
        stack.push(new Coords(i,j));
        while(!stack.empty())
        {
          Coords *c = stack.top(); 
          int x = c->x;
          int y = c->y;
          stack.pop(); 
          delete c;
                       
          if(x >= 0 && x < NUMBER_OF_COLS && y >= 0 && y < NUMBER_OF_LINES 
             && board[x][y]!=NULL)
          {
            if(!board_mark[x][y] && board[x][y]->get_piece_number() == score_of_root)
            {
              list.insert(list.end(),new Coords(x,y));
              board_mark[x][y] = true;
              counter ++;
              stack.push(new Coords(x - 1, y));
              stack.push(new Coords(x + 1, y));
              stack.push(new Coords(x, y - 1));
              stack.push(new Coords(x, y + 1));                                                                  
            }
          }              
                             
        }

        if(counter >= 3)
        {
          // In the case we destroy the last element
          std::vector<Coords*>::iterator it = list.begin();
          Coords *c = (Coords*) *it;                 
          u_int score_of_root = board[c->x][c->y]->get_piece_number(); 

	  // Last element
          if(score_of_root == NUMBER_OF_PIECES - 1)
          {
	    std::cout << "You align " << counter << " ultimate elements ! Cheater :p" << std::endl;
            undo_bonus_score += counter*board[i][j]->get_score_value();
            bonus_score += counter*board[i][j]->get_score_value();
          }
	  // If not last element
          else
          {
            undo_bonus_score  += (counter - 3)*board[i][j]->get_score_value();
            bonus_score += (counter - 3)*board[i][j]->get_score_value();
          }
	  Coords new_piece(NUMBER_OF_COLS+1,-1);
          
	  //std::vector<Coords*>::iterator it = list.begin();
	  while(it != list.end())
	  {
	    Coords *c = (Coords*) *it;                 
	    board[c->x][c->y]->start_disappear();                    
	    list_to_destroy.insert(list_to_destroy.end(),c);
                    
	    // Select the lefter and bottomer Coords for create new piece
	    if(c->y > new_piece.y)
	    {
	      new_piece.x = c->x;
	      new_piece.y = c->y;
	    }
	    else if(c->y == new_piece.y)
	    {
	      if(c->x < new_piece.x)
	      {
		new_piece.x = c->x;
		new_piece.y = c->y;
	      }
	    }
	    new_piece.piece_number = board[c->x][c->y]->get_piece_number()+1;    
	    if(new_piece.piece_number >= NUMBER_OF_PIECES)
	    {
	      new_piece.piece_number = NUMBER_OF_PIECES-1;
	    }
            
	    if(new_piece.piece_number > visible_pieces - 1)
	    {
	      ++visible_pieces;
	      resources -> engine -> set_skin_element(visible_pieces);
	    }
	    if(new_piece.piece_number > unlocked_pieces)
	    {
	      unlocked_pieces ++;
	    }

	    ++it;
	  }
                
	  // We don't add a new piece if we align 3 last elements
	  if(score_of_root != NUMBER_OF_PIECES - 1)
	    list_to_create.insert(list_to_create.end(), new Coords(&new_piece));
	}      
        
      }
    }

  return !list_to_destroy.empty();
    
}

bool Board::destroy()
{

  bool end = true;
  for(u_int i=0; i<list_to_destroy.size(); i++)
  {    
    if(list_to_destroy[i])
    {
      Coords *c = list_to_destroy[i];
            
      if(board[c->x][c->y] != NULL && !board[c->x][c->y]->disappear())
      {
        end = false;
      }
      else
      {
        delete board[c->x][c->y];
        board[c->x][c->y] = NULL;
        delete c;
        list_to_destroy[i] = NULL;
      }
    }
  }

  return end;
}

void Board::create_new_pieces(SDL_Surface **pieces_normal, SDL_Surface **pieces_appearing, SDL_Surface **pieces_disappearing, SDL_Surface **pieces_mini)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  list_to_destroy.clear(); 
  appearing_list.clear();
    
  std::list<Coords*>::iterator it = list_to_create.begin();
  while(it != list_to_create.end())
  {
    Coords *c = (Coords*) *it;
    if(c && c->x >= 0 && c->x < NUMBER_OF_COLS
       && c->y >=0 && c->y < NUMBER_OF_LINES
       && !board[c->x][c->y])
    {
      

      int score = c->piece_number;
      Piece *p = new Piece(score);  
      p -> set_position(c->x*resources->pieces_width+game_left,
                        game_top+(c->y-2)*resources->pieces_height);
               
      p -> set_sprites(pieces_normal[score], pieces_appearing[score],
                       pieces_disappearing[score], pieces_mini[score]);

                        
      p -> start_appear();
                
      board[c->x][c->y] = p; 
      appearing_list.insert(appearing_list.begin(), p);

      delete c;
      it = list_to_create.erase(it);
    }
  }
}

void Board::detect_pieces_to_fall()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  falling_list.clear();
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=NUMBER_OF_LINES-2; j>=0; --j)
    {
      if(board[i][j] != NULL)
      {
        int k = 1;
        while(j+k < NUMBER_OF_LINES && board[i][j+k] == NULL)
        {
          board[i][j+k] = board[i][j+k-1];
          board[i][j+k-1] = NULL;
          board[i][j+k] -> start_fall((int)(board[i][j+k]->get_x()),
                                      (int)(game_top+(j+k-2)*resources->pieces_height));
          k++;
        }
        if(k>1)
        {
          falling_list.insert(falling_list.end(), board[i][j+k-1]);
        }
      }
    }
}

bool Board::is_game_over()
{
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<2; ++j)
    {
    
      if(board[i][j] != NULL)
      {
        //game_mode = GAME_MODE_GAME_OVER;
        /*if(global_score + global_bonus > hightscores[current_difficulty])
          {
          game_mode = GAME_MODE_NEW_HIGHTSCORE;
          save_scores();
          }*/
	calc_score();
        return true;
      }
    }

  return false;

}


void Board::calc_score()
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  score = 0;
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=2; j<NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        score += board[i][j]->get_score_value();                           
      }
    }
  printf("Score : %d\n", score);
  str_score = /*format_number(*/to_string(score)/*)*/;
  str_bonus = /*format_number(*/to_string(bonus_score)/*)*/;
  str_hightscore = /*format_number(*/to_string(resources->highscore)/*)*/; 
  printf("HighScore string : %s\n",str_hightscore.c_str());
//font stuffs
  int score_width      = (resources->main_font->charSize) * str_score.length();
  int bonus_width      = (resources->main_font->charSize) * str_bonus.length();
  int hightscore_width = (resources->main_font->charSize) * str_hightscore.length();

//TODO : Cleaning useless
  score_left = score_right - score_width;
  bonus_left = bonus_right - bonus_width;
  hightscore_left = hightscore_right - hightscore_width;
}

void Board::undo(SDL_Surface **pieces_normal, SDL_Surface** pieces_appearing, SDL_Surface** pieces_disappearing, SDL_Surface** pieces_mini)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();

  if(score + bonus_score == resources -> highscore)
  {
    resources -> highscore = resources -> old_highscore;
    resources -> save_scores();
  }

  // Delete the pieces in the board and replace by new ones
  for(int i=0; i<NUMBER_OF_COLS; ++i)
    for(int j=0; j<NUMBER_OF_LINES; ++j)
    {
      if(board[i][j]) delete board[i][j];
      board[i][j] = NULL;
      
      if(undo_board[i][j] >= 0)
      {
        board[i][j] = new Piece(undo_board[i][j]);
        board[i][j] -> set_sprites(pieces_normal[undo_board[i][j]], pieces_appearing[undo_board[i][j]],
                                   pieces_disappearing[undo_board[i][j]], pieces_mini[undo_board[i][j]]);
        board[i][j] -> set_position(i*resources->pieces_width+game_left,game_top+(j-2)*resources->pieces_height);
      }
    } 

  bonus_score -= undo_bonus_score;
  // Penality !
  bonus_score /= 2;

  unlocked_pieces = undo_unlocked_pieces;
  visible_pieces =  undo_visible_pieces;

  calc_score();
}
