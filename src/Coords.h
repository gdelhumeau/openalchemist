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
