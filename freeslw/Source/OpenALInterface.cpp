// Copyright (c) 2012 Lukas Heise (http://www.lukasheise.com)
//
// This file is part of FreeSLW.
//
// FreeSLW is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// FreeSLW is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#include "OpenALGlobals.h"
#include "OpenALInterface.h"
#include "OpenALListener.h"
#include "OpenALStreamSound.h"
#include "OpenALStaticSound.h"
#include "OpenALStreamOgg.h"
#include "OpenALBuffer.h"
#include "ZipFile.h"
#include "File.h"
#include "Functions.h"
#include <strings.h>

namespace openal
{
	OpenALInterface::OpenALInterface()
	{
		bool alutContext = false;

		if (ContextInit("DirectSound3D") == false)
		{
			if (ContextInit("DirectSound") == false)
			{
				if (ContextInit("MMSYSTEM") == false)
				{
					freeslw::ErrorPrintf("Failed to create Context");

					if (alutInit(NULL,0) == AL_FALSE)
					{
						freeslw::ErrorPrintf("Failed when calling alutInit");
					}

					alutContext = true;
				}
			}
		}

		if (alutContext == false)
		{
			if (alutInitWithoutContext(NULL,0) == AL_FALSE)
			{
				freeslw::ErrorPrintf("Failed when calling alutInitWithoutContext");
			}
		}

		for (int i = 0; i < MAX_OPENAL_SOURCES; i++) freeSources[i] = true;
		for (int i = 1; i < 256; i++) groupActive[i] = false;

		groupActive[0] = true;
		alGenSources(MAX_OPENAL_SOURCES,sources);
		alListenerf(AL_GAIN,1.0f);
		oldTime = -1.0f;

		listener = new OpenALListener();
	}

	OpenALInterface::~OpenALInterface()
	{
		StopAllSounds();
		delete listener;

		alDeleteSources(MAX_OPENAL_SOURCES,sources);
		alutExit();

		for (std::list<freeslw::Sound*>::iterator w = soundList.begin(); w != soundList.end(); w++)
		{
			delete (*w);
		}

		if (alContext) { alcDestroyContext(alContext); alContext = 0; }
		if (alDevice) { alcCloseDevice(alDevice); alDevice = 0; }
	}

	freeslw::audioSubsystem_e OpenALInterface::GetSubsystem() const
	{
		return freeslw::AS_OPENAL;
	}

	void OpenALInterface::Update()
	{
		float newTime = timer.GetTotalTime();
		if (oldTime < 0.0f) oldTime = newTime;
		float dt = newTime - oldTime;
		oldTime = newTime;

		for (std::list<OpenALStreamSound*>::iterator w = streamPlayList.begin(); w != streamPlayList.end(); )
		{
			(*w)->Update(dt);
			if (!(*w)->IsPlaying()) w = streamPlayList.erase(w); else w++;
		}

		for (std::list<OpenALStaticSound*>::iterator w = staticPlayList.begin(); w != staticPlayList.end(); )
		{
			(*w)->Update(dt);
			if (!(*w)->IsPlaying()) w = staticPlayList.erase(w); else w++;
		}
	}

	freeslw::Listener* OpenALInterface::GetListener()
	{
		return listener;
	}

	freeslw::audioStatistics_t OpenALInterface::GetStatistics()
	{
		freeslw::audioStatistics_t ret;
		ret.soundsPlaying = staticPlayList.size();
		ret.soundsStreaming = streamPlayList.size();
		ret.soundCount = soundList.size();
		
		ret.soundMemory = 0;
		for (std::list<freeslw::Sound*>::iterator w = soundList.begin(); w != soundList.end(); w++)
		{
			if ((*w)->IsStream() == false)
			{
				size_t d = 1;

				     if ((*w)->GetFormat() == freeslw::TA_MONO16 || (*w)->GetFormat() == freeslw::TA_STEREO8) d = 2l;
				else if ((*w)->GetFormat() == freeslw::TA_STEREO16) d = 4l;

				ret.soundMemory += ((size_t)((*w)->GetPlayDuration() * (float)(*w)->GetFrequency() * (float)d) / 1024l);
			}
		}

		return ret;
	}

	const char* OpenALInterface::GetSupportedStaticSoundFormats() const
	{
		return "wav,ogg";
	}

	const char* OpenALInterface::GetSupportedStreamSoundFormats() const
	{
		return "ogg";
	}

	void OpenALInterface::SetVolume(float v)
	{
		alListenerf(AL_GAIN,v);
	}

	float OpenALInterface::GetVolume() const
	{
		float v = 0.0f;
		alGetListenerf(AL_GAIN,&v);
		return v;
	}

	void OpenALInterface::SetMetersPerUnit(float s)
	{
		alListenerf(AL_METERS_PER_UNIT,s);
	}

	float OpenALInterface::GetMetersPerUnit() const
	{
		float v = 0.0f;
		alGetListenerf(AL_METERS_PER_UNIT,&v);
		return v;
	}

	void OpenALInterface::SetGroup(unsigned char id, bool active)
	{
		if (groupActive[id] != active)
		{
			for (std::list<freeslw::Sound*>::iterator w = soundList.begin(); w != soundList.end(); w++)
			{
				if ((*w)->GetGroup() == id)
				{
					if (active)
					{
						(*w)->Resume();
					}
					else
					{
						(*w)->Pause();
					}
				}
			}

			groupActive[id] = active;
		}
	}

	bool OpenALInterface::IsGroupActive(unsigned char id) const
	{
		return groupActive[id];
	}

	void OpenALInterface::StopAllSounds()
	{
		std::list<freeslw::Sound*> p;

		for (std::list<OpenALStreamSound*>::iterator w = streamPlayList.begin(); w != streamPlayList.end(); w++)
		{
			p.push_back(*w);
		}

		for (std::list<OpenALStaticSound*>::iterator w = staticPlayList.begin(); w != staticPlayList.end(); w++)
		{
			p.push_back(*w);
		}

		for (std::list<freeslw::Sound*>::iterator w = p.begin(); w != p.end(); w++)
		{
			(*w)->Stop();
		}
	}

	freeslw::Sound* OpenALInterface::DuplicateSound(freeslw::Sound* s)
	{
		if (!s) return 0;

		if (s->IsStream())
		{
			OpenALStreamSound* n = static_cast<OpenALStreamSound*>(s);
			return StreamSound(n->GetName(),n->GetGroup(),n->GetPriority());
		}
		else
		{
			OpenALStaticSound* n = static_cast<OpenALStaticSound*>(s);
			n->GetBuffer()->AddRef();
			freeslw::Sound* snd = new OpenALStaticSound(n->GetBuffer(),n->GetPriority());
			snd->SetGroup(n->GetGroup());
			soundList.push_back(snd);
			return snd;
		}

		return 0;
	}

	freeslw::Sound* OpenALInterface::LoadSound(const char* file, unsigned char group, unsigned char priority)
	{
		Buffer* b = GetBuffer(file);
		if (!b)
		{
			File fp;
			if (fp.Read(file))
			{
				char typ[8];
				GetFileExtension(file,typ,8);
				b = LoadBuffer(file,typ,fp.GetData(),fp.GetLength());
				fp.Close();
			}
			else return 0;
		}

		if (!b) return 0;

		freeslw::Sound* snd = new OpenALStaticSound(b,priority);
		snd->SetGroup(group);
		soundList.push_back(snd);

		return snd;
	}

	freeslw::Sound* OpenALInterface::LoadSoundFromZip(const char* file, const char* package, unsigned char group, unsigned char priority)
	{
		Buffer* b = GetBuffer(file);
		if (!b)
		{
			ZipFile fp;
			if (fp.LoadFile(package,file))
			{
				char typ[8];
				GetFileExtension(file,typ,8);
				b = LoadBuffer(file,typ,fp.GetData(),fp.GetFileSize());
				fp.FileClose();
			}
			else return 0;
		}

		if (!b) return 0;

		freeslw::Sound* snd = new OpenALStaticSound(b,priority);
		snd->SetGroup(group);
		soundList.push_back(snd);

		return snd;
	}

	freeslw::Sound* OpenALInterface::LoadSoundFromData(const char* name, const char* type, const char* data, size_t size, unsigned char group, unsigned char priority)
	{
		Buffer* b = GetBuffer(name);
		if (!b) b = LoadBuffer(name,type,data,size);
		if (!b) return 0;

		freeslw::Sound* snd = new OpenALStaticSound(b,priority);
		snd->SetGroup(group);
		soundList.push_back(snd);

		return snd;
	}

	freeslw::Sound* OpenALInterface::StreamSound(const char* file, unsigned char group, unsigned char priority)
	{
		Stream* stream = 0;
		char typ[8];
		GetFileExtension(file,typ,8);

		if (strcasecmp(typ,"ogg") == 0) stream = new StreamOgg();
		// add more file formats here

		if (stream)
		{
			if (stream->Load(file))
			{
				freeslw::Sound* snd = new OpenALStreamSound(priority,stream);
				snd->SetGroup(group);
				soundList.push_back(snd);
				return snd;
			}

			freeslw::ErrorPrintf("Failed to load \"%s\"",file);
			delete stream;
			return 0;
		}

		freeslw::ErrorPrintf("File extension \"%s\" is not supported for streaming",typ);
		return 0;
	}

	freeslw::Sound* OpenALInterface::CreateSound(const char* name, const void* data, size_t size, freeslw::soundFormat_e format, int frequency, unsigned char group, unsigned char priority)
	{
		Buffer* b = GetBuffer(name);
		if (!b) b = CreateBuffer(name,data,size,format,frequency);
		if (!b) return 0;

		freeslw::Sound* snd = new OpenALStaticSound(b,priority);
		snd->SetGroup(group);
		soundList.push_back(snd);
		
		return snd;
	}

	void OpenALInterface::ReleaseSound(freeslw::Sound* snd)
	{
		soundList.remove(snd);
		delete snd;
	}
}
