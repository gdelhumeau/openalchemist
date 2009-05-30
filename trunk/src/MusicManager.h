/********************************************************************
                          OpenAlchemist

  File : MusicManager.h
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#ifndef _MUSIC_MANAGER_H_
#define _MUSIC_MANAGER_H_

#include <ClanLib/sound.h> 
#include <ClanLib/vorbis.h>

enum SOUNDS{

  SOUND_MOVE = 0,
  SOUND_FALL,
  SOUND_DESTROY,
  SOUND_CREATION,
  
  NB_SOUNDS

};

class MusicManager{

private:

	CL_SetupSound * _p_setup_sound;
	CL_SoundOutput * _p_output;
	CL_SetupVorbis * _p_setup_vorbis;
	CL_SoundBuffer_Session _playback;
	CL_SoundBuffer* _sounds_p[NB_SOUNDS];

public:

	MusicManager();
	~MusicManager();

	void set_music_volume(float volume);
	void set_sounds_volume(float volume);

	void init();
	void term();

	void play_sound(int sound_index);

};

extern MusicManager g_music_manager;

#endif
