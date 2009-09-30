/********************************************************************
                          OpenAlchemist

  File : FramerateCounter.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : rombust


*********************************************************************/

#include "FrameRateCounter.h"

#include <ClanLib/core.h>

CL_FramerateCounter::CL_FramerateCounter(): impl(new CL_FramerateCounter_Generic)
{
	impl->start_time = CL_System::get_time();
	impl->total_time = 0;
	impl->frame_time = 0;
	impl->fps_result = 0;
	impl->fps_counter = 0;
}

CL_FramerateCounter::~CL_FramerateCounter ()
{
	delete impl;
}

int CL_FramerateCounter::get_fps()
{
	return impl->fps_result;
}

void CL_FramerateCounter::set_fps_limit(int fps)
{
	if (fps > 0)
		impl->frame_time = 1000 / fps;
	else
		impl->frame_time = 0;
}

void CL_FramerateCounter::keep_alive()
{
	int cur_time = CL_System::get_time();
	int delta_time = cur_time - impl->start_time;
	impl->start_time = cur_time;

	if (delta_time < impl->frame_time)
	{
		CL_System::sleep(impl->frame_time - delta_time);
		impl->total_time += impl->frame_time;
	}
	else
	{
		impl->total_time += delta_time;
	}

	if(impl->total_time >= 1000)	// One second has passed
	{
		impl->fps_result = impl->fps_counter + 1;
		impl->fps_counter = impl->total_time = 0;
	}
	impl->fps_counter++;	// Increase fps
}
