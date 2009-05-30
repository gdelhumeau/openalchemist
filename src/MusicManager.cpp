/********************************************************************
                          OpenAlchemist

  File : MusicManager.cpp
  Description : 
  License : GNU General Public License 2 or +
  Author : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>


*********************************************************************/

#include "MusicManager.h"
#include "Preferences.h"
#include "memory.h"
#include <iostream>

MusicManager g_music_manager;

MusicManager::MusicManager()
{
  _p_setup_sound = NULL;
  _p_output = NULL;
  _p_setup_vorbis = NULL;
  for(int i=0; i<NB_SOUNDS; ++i)
  {
    _sounds_p[i] = NULL;
  }
}

MusicManager::~MusicManager()
{
}


void MusicManager::init()
{
  // Getting resources
  Preferences *p_pref = pref_get_instance();

  _p_setup_sound = my_new CL_SetupSound();
  _p_output = my_new CL_SoundOutput(44100);
  _p_setup_vorbis = my_new CL_SetupVorbis();
  CL_SoundBuffer vorbis("music/Cavern_Of_Time.ogg", true);
  _playback = vorbis.prepare();
  _playback.set_looping(true);
  _playback.play();
  _playback.set_volume(p_pref -> music_level / 100.f);
//  _p_sound = my_new CL_SoundBuffer("sounds/ping2.wav", false);
  _sounds_p[SOUND_MOVE] = my_new CL_SoundBuffer("sounds/move.wav", false);
}

void MusicManager::term()
{
  _playback.stop();
		
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

void MusicManager::set_music_volume(float volume)
{
  _playback.set_volume(volume);
}


void MusicManager::set_sounds_volume(float volume)
{
  
}


void MusicManager::play_sound(int sound_index)
{
  if(_sounds_p[sound_index])
  {
    _sounds_p[sound_index] -> play();
  }
}





