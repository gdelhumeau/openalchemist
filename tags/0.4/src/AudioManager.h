// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : AudioManager.h
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

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

/** Audio manager */
class AudioManager{

public:

	/** Constructor */
	AudioManager();

	/** Destructor */
	~AudioManager();

	/** Init */
	void init();

	/** Term */
	void term();

	/** Set music volume */
	void set_music_volume(float volume);

	/** Set sounds volume */
	void set_sounds_volume(float volume);

	/** Play a sound */
	void play_sound(int sound_index);
	
	/** Pause sounds */
	void pause_sounds();

	/** Resume sounds */
	void resume_sounds();

private:

	/** Clan sound */
	CL_SetupSound* _p_setup_sound;

	/** Sound outpur */
	CL_SoundOutput* _p_output;

	/** Clan vorbis */
	CL_SetupVorbis* _p_setup_vorbis;

	/** Sound buffer */
	CL_SoundBuffer_Session _playback;

	/** Sounds */
	CL_SoundBuffer* _sounds_p[NB_SOUNDS];

	/** Sounds buffers */
	CL_SoundBuffer_Session _sounds_playback[NB_SOUNDS];

	/** Sounds position (where are the sounds) */
	int _sounds_position[NB_SOUNDS];

	/** Sounds volume */
	float _sounds_volume;

};

/** Audio Manager instance */
extern AudioManager g_audio_manager;

#endif
