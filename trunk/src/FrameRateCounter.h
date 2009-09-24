/********************************************************************
                          OpenAlchemist

  File : FramerateCounter.h
  Description : 
  License : GNU General Public License 2 or +
  Author : rombust


*********************************************************************/

#ifndef _FRAME_RATE_COUNTER_H_
#define _FRAME_RATE_COUNTER_H_

class CL_FramerateCounter_Generic;

class CL_FramerateCounter
{
public:
	CL_FramerateCounter();
	~CL_FramerateCounter ();

public:
	int get_fps();
	void set_fps_limit(int fps);
	void keep_alive();

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