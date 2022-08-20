#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
using namespace sf;
using namespace std;
class SoundsManager
{
public:
	vector<SoundBuffer> buffers;
	vector<Sound> sounds;
	vector<bool> relativeToListener;
	vector<string> names;

	void DeleteAllSounds()
	{
		for (int i = 0; i < buffers.size(); i++)
			buffers.pop_back();
		for (int i = 0; i < sounds.size(); i++)
			sounds.pop_back();
		for (int i = 0; i < names.size(); i++)
			names.pop_back();
		for (int i = 0; i < relativeToListener.size(); i++)
			relativeToListener.pop_back();
	}
	bool AddSound(string location, string name, bool relativeToListener)
	{
		SoundBuffer a;
		Sound b;
		if (!a.loadFromFile(location))
			exit(0);
		buffers.push_back(a);
		this->relativeToListener.push_back(relativeToListener);
		sounds.push_back(b);
		names.push_back(name);
		return 1;
	}
	void setAttenuation(string name, float value)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				setAttenuation(a, value);
				break;
			}
	}
	void setAttenuation(int ID, float value)
	{
		sounds[ID].setAttenuation(value);
	}
	void setMinDistance(string name, float value)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				setMinDistance(a, value);
				break;
			}
	}
	void setMinDistance(int ID, float value)
	{
		sounds[ID].setMinDistance(value);
	}
	void setPosition(string name, Vector3f pos)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				setPosition(a, pos);
				break;
			}
	}
	void setPosition(int ID, Vector3f pos)
	{
		sounds[ID].setPosition(pos);
	}
	void ReloadAllSounds()
	{
		
		sounds.clear();
		sounds.resize(buffers.size());
		for (int i = 0; i < buffers.size(); i++)
		{
			sounds[i].setBuffer(buffers[i]);
			sounds[i].setRelativeToListener(relativeToListener[i]);
		}
	}
	Sound* getSound(string name)
	{
		Sound* fail;
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
				return &sounds[a];
		return fail;
	}
	Sound* getSound(int ID)
	{
		return &sounds[ID];
	}
	SoundBuffer* getSoundBuffer(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
				return &buffers[a];
		return nullptr;
	}
	SoundBuffer* getSoundBuffer(int ID)
	{
		return &buffers[ID];
	}
	void playSound(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				sounds[a].play();
				break;
			}
	}
	void playSound(int ID)
	{
		sounds[ID].play();
	}
	void stopSound(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				sounds[a].stop();
				break;
			}
	}
	void stopSound(int ID)
	{
		sounds[ID].stop();
	}
	void pauseSound(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				sounds[a].pause();
				break;
			}
	}
	void pauseSound(int ID)
	{
		sounds[ID].pause();
	}
	void reset(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
		{
			if (names[a] == name)
			{
				reset(a);
				break;
			}
		}
	}
	void reset(int ID)
	{
		sounds[ID].stop();
		sounds[ID].play();

	}
	void reset(string name, Vector3f pos)
	{
		for (int a = 0; a < sounds.size(); a++)
		{
			if (names[a] == name)
			{
				reset(a, pos);
				break;
			}
		}
	}
	void reset(int ID, Vector3f pos)
	{
		sounds[ID].stop();
		sounds[ID].play();
		sounds[ID].setPosition(pos);

	}
	void resetIfDone(int ID)
	{
		if (sounds[ID].getStatus() == Sound::Stopped)
		{
			sounds[ID].stop();
			sounds[ID].play();
		}
	}
	void resetIfDone(int ID, Vector3f pos)
	{
		if (sounds[ID].getStatus() == Sound::Stopped)
		{
			sounds[ID].stop();
			sounds[ID].play();
			sounds[ID].setPosition(pos);
		}
	}
	void resetIfDone(string name)
	{
		for (int a = 0; a < sounds.size(); a++)
		{
			if (names[a] == name)
			{
				resetIfDone(a);
				break;
			}
		}
	}
	void resetIfDone(string name, Vector3f pos)
	{
		for (int a = 0; a < sounds.size(); a++)
		{
			if (names[a] == name)
			{
				resetIfDone(a, pos);
				break;
			}
		}
	}
	void setVolumeAll(float volume)
	{
		for (int a = 0; a < sounds.size(); a++)
			sounds[a].setVolume(volume);
	}
	void setVolume(string name, float volume)
	{
		for (int a = 0; a < sounds.size(); a++)
			if (names[a] == name)
			{
				sounds[a].setVolume(volume);
				break;
			}
	}

	void setVolume(int ID, float volume)
	{
		sounds[ID].setVolume(volume);
	}
	void setAttenuationAll(float volume)
	{
		for (int a = 0; a < sounds.size(); a++)
			sounds[a].setAttenuation(volume);
	}
};