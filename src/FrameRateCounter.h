// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : FrameRateCounter.h
//  Description : 
//  Author      : rombust (from the ClanLib team)
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#ifndef _FRAME_RATE_COUNTER_H_
#define _FRAME_RATE_COUNTER_H_

class CL_FramerateCounter_Generic;

/** 
* Counts framerate
*/
class CL_FramerateCounter
{
public:

	/** 
	* Constructor
	*/
	CL_FramerateCounter();

	/** 
	* Destructor
	*/
	~CL_FramerateCounter ();

	/** 
	* Returns framerate
	*/
	int get_fps();

	/** 
	* Set the max framerate authorised
	*/
	void set_fps_limit(int fps);

	/** 
	* Keep alive windows
	*/
	void keep_alive();

	/**
	* Clanlib implementation
	*/
	CL_FramerateCounter_Generic *impl;
};

class CL_FramerateCounter_Generic
{
public:
	CL_FramerateCounter_Generic() { }

	int start_time;
	int total_time;
	int frame_time;
	int fps_result;
	int fps_counter;
};

#endif