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

#include "AudioManager.h"
#include "Preferences.h"
#include "memory.h"
#include "misc.h"

/************************************************************************/
/* Global                                                               */
/************************************************************************/
AudioManager g_audio_manager;

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
static const std::string SOUND_CREATION_FILE = "creation.wav";
static const std::string SOUND_DESTROY_FILE = "destroy.wav";
static const std::string SOUND_MOVE_FILE = "move.wav";
static const std::string SOUND_FALL_FILE = "fall.wav";
static const std::string MUSIC_FILE = "Cavern_Of_Time.ogg";

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
AudioManager::AudioManager()
{
	_p_setup_sound = NULL;
	_p_output = NULL;
	_p_setup_vorbis = NULL;
	for(int i=0; i<NB_SOUNDS; ++i)
	{
		_sounds_p[i] = NULL;
		_sounds_position[i] = 0;
	}
	_sounds_volume = 1;
}

/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
AudioManager::~AudioManager()
{
}

/************************************************************************/
/* Init                                                                 */
/************************************************************************/
void AudioManager::init()
{
	// Getting resources
	Preferences *p_pref = pref_get_instance();

	_p_setup_sound = my_new CL_SetupSound();
	_p_output = my_new CL_SoundOutput(44100);
	_p_setup_vorbis = my_new CL_SetupVorbis();
	_p_setup_vorbis -> init();
	std::string dir = CL_System::get_exe_path();
	std::string dir_music = dir + "music" + get_path_separator();
	std::string dir_sound = dir + "sounds" + get_path_separator();
	CL_SoundBuffer vorbis(dir_music + MUSIC_FILE, true);
	_playback = vorbis.prepare();
	_playback.set_looping(true);
	_playback.play();
	_playback.set_volume(p_pref -> music_level / 100.f);
	_sounds_volume = p_pref -> sound_level / 100.0f;
	_sounds_p[SOUND_MOVE] = my_new CL_SoundBuffer(dir_sound+SOUND_MOVE_FILE, false);
	_sounds_p[SOUND_FALL] = my_new CL_SoundBuffer(dir_sound+SOUND_FALL_FILE, false);
	_sounds_p[SOUND_CREATION] = my_new CL_SoundBuffer(dir_sound+SOUND_CREATION_FILE, false);
	_sounds_p[SOUND_DESTROY] = my_new CL_SoundBuffer(dir_sound+SOUND_DESTROY_FILE, false);
	_sounds_playback[SOUND_MOVE] = _sounds_p[SOUND_MOVE]->prepare();
	_sounds_playback[SOUND_FALL] = _sounds_p[SOUND_FALL]->prepare();
	_sounds_playback[SOUND_CREATION] = _sounds_p[SOUND_CREATION]->prepare();
	_sounds_playback[SOUND_DESTROY] = _sounds_p[SOUND_DESTROY]->prepare();
}

/************************************************************************/
/* Term                                                                 */
/************************************************************************/
void AudioManager::term()
{
	_playback.stop();
	_p_setup_vorbis -> deinit();

	if(_p_setup_sound)
	{
		my_delete(_p_setup_sound);
		_p_setup_sound = NULL;
	}

	if(_p_output)
	{
		my_delete(_p_output);
		_p_output = NULL;
	}
	if(_p_setup_vorbis)
	{
		my_delete(_p_setup_vorbis);
		_p_setup_vorbis = NULL;
	}
	for(int i=0; i<NB_SOUNDS; ++i)
	{
		if(_sounds_p[i])
		{
			my_delete(_sounds_p[i]);
			_sounds_p[i] = NULL;
		}   

	}
}

/************************************************************************/
/* Set music volume                                                     */
/************************************************************************/
void AudioManager::set_music_volume(float volume)
{
	_playback.set_volume(volume);
}

/************************************************************************/
/* Set sounds volume                                                    */
/************************************************************************/
void AudioManager::set_sounds_volume(float volume)
{
	_sounds_volume = volume;
}

/************************************************************************/
/* Play sound                                                           */
/************************************************************************/
void AudioManager::play_sound(int sound_index)
{
	if(_sounds_p[sound_index])
	{
		_sounds_playback[sound_index] = _sounds_p[sound_index] -> prepare();
		_sounds_playback[sound_index].set_looping(false);
		_sounds_playback[sound_index].set_position(0);
		_sounds_playback[sound_index].play();
		_sounds_playback[sound_index].set_volume(_sounds_volume);
	}
}

/************************************************************************/
/* Pause sounds                                                         */
/************************************************************************/
void AudioManager::pause_sounds()
{
	for(int i=0; i<NB_SOUNDS; ++i)
	{
		if(_sounds_p[i] && _sounds_playback[i].is_playing())
		{
			_sounds_position[i] = _sounds_playback[i].get_position();
			_sounds_playback[i].stop();
		}   

	}
}

/************************************************************************/
/* Resume sounds                                                        */
/************************************************************************/
void AudioManager::resume_sounds()
{
	for(int i=0; i<NB_SOUNDS; ++i)
	{
		if(_sounds_p[i] && _sounds_position[i] > 0)
		{
			_sounds_playback[i].set_position(_sounds_position[i]);
			_sounds_playback[i].play();
			_sounds_playback[i].set_volume(_sounds_volume);
			_sounds_position[i] = 0;
		}  
	}
}