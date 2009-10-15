// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : Coords.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _COORDS_H_
#define _COORDS_H_

/** 
* Saves a piece coords
*/
class Coords
{
public:

	/** 
	* X coord
	*/
	int x;

	/** 
	* Y coord
	*/
	int y;

	/** 
	* Piece number
	*/
	int piece_number;

	/** 
	* Constructor
	*/
	Coords(int x, int y)
	{
		this -> x = x;
		this -> y = y;
		this -> piece_number = 0;
	}

	/** 
	* Constructor
	*/
	Coords(Coords* c)
	{
		this -> x = c->x;
		this -> y = c->y;
		this -> piece_number = c->piece_number;
	}
};

#endif
