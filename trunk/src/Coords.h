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

	/** X coord	*/
	int x;

	/** Y coord	*/
	int y;

	/** Piece number */
	int piece_number;

	/** Constructor	*/
	Coords(int x, int y)
	{
		this -> x = x;
		this -> y = y;
		this -> piece_number = 0;
	}

	/** Constructor	*/
	Coords(Coords* p_c)
	{
		this -> x = p_c->x;
		this -> y = p_c->y;
		this -> piece_number = p_c->piece_number;
	}
};

#endif
