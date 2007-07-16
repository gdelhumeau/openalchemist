#include "Board.h"

#include "CommonResources.h"

Board::Board()
{
    
  /* Initializing all to NULL */
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
      board[i][j] = NULL;

}

void Board::apply_skin(CL_Sprite** pieces_normal, CL_Sprite** pieces_appearing, CL_Sprite** pieces_disappearing, CL_Sprite** pieces_mini)
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
  for(int i = 0; i < NUMBER_OF_COLS; ++i)
    for(int j = 0; j < NUMBER_OF_LINES; ++j)
    {
      if(board[i][j])
      {
        board[i][j] -> draw(); 
      }
    }
}

void Board::add_pieces(Piece* piece1, Piece* piece2)
{
  // Getting resources
  static CommonResources *resources = common_resources_get_instance();
  
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
  
  
  int piece_top_x = (int)((int)piece_on_top->get_x()-game_left)/(resources->pieces_width);
  int piece_bottom_x = (int)((int)piece_on_bottom->get_x()-game_left)/(resources->pieces_width);  

  int y_bottom = -1;
  while(y_bottom < NUMBER_OF_LINES-1 && !board[piece_bottom_x][y_bottom+1])
  {
    ++y_bottom;
  }    
        
  if(y_bottom == -1 && board[piece_bottom_x][0])
  {
    //game_mode = GAME_MODE_GAME_OVER;
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
    //game_mode = GAME_MODE_GAME_OVER;
    board[piece_bottom_x][y_bottom] = NULL;
  }
  else
  {          
    board[piece_top_x][y_top] = piece_on_top;
  } 

  piece_on_bottom -> start_fall(piece_bottom_x*resources->pieces_width+game_left,
                                game_top+(y_bottom-2)*resources->pieces_height);
  piece_on_top -> start_fall(piece_top_x*resources->pieces_width+game_left,
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

          if(score_of_root == NUMBER_OF_PIECES)
          {
            //undo.global_bonus += counter*board[i][j]->get_score_value();
            //global_bonus += counter*board[i][j]->get_score_value();
          }
          else
          {
            //undo.global_bonus += (counter - 3)*board[i][j]->get_score_value();
            //global_bonus += (counter - 3)*board[i][j]->get_score_value();
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
              //skins_selector.set_skin_value(skin, visible_pieces);
            }
            if(new_piece.piece_number > unlocked_pieces)
            {
              unlocked_pieces ++;
            }

            ++it;
          }
                
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

void Board::create_new_pieces(CL_Sprite **pieces_normal, CL_Sprite **pieces_appearing, CL_Sprite **pieces_disappearing,
                       CL_Sprite **pieces_mini)
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

