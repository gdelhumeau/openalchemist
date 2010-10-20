// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : RecordGame.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _RECORD_GAME_H_
#define _RECORD_GAME_H_

#include <vector>
#include "misc.h"

/** Record event - base type */
struct RecordEvent{
	enum EventType{
		PIECE_PLACED,
		UNDO
	};

	EventType type;

	int piece_1;
	int	piece_1_x;
	int	piece_1_y;
	int piece_2;
	int	piece_2_x;
	int	piece_2_y;
};

/** Records events all along the game */
class RecordGame{

public:

	/** Constructor */
	RecordGame();
	
	/** New game */
	inline void new_game(RandomSeed seed);

	/** Record game event */
	void record_place_elements( int piece_1, int piece_1_x, int piece_1_y,
								int piece_2, int piece_2_x, int piece_2_y);

	/** Record undo */
	void record_undo();

	void export_to_xml();

	inline bool is_empty() const { return _events.empty(); }

private:

	/** Initial random seed (anti-cheat checker) */
	RandomSeed _initial_random_seed;

	/** Events */
	std::vector<RecordEvent> _events;

};

/************************************************************************/
/* Inline functions                                                     */
/************************************************************************/
inline void RecordGame::new_game(RandomSeed seed)
{
	_initial_random_seed = seed;
	_events.clear();
}


#endif