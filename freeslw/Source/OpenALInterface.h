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

#pragma once

#include "FreeSLW.h"
#include "Timer.h"

namespace openal
{
	class OpenALInterface : public freeslw::AudioInterface
	{
	private:
		freeslw::Listener* listener;
		Timer timer;
		float oldTime;

	public:
		OpenALInterface();
		~OpenALInterface();

		freeslw::audioSubsystem_e GetSubsystem() const;

		void Update();

		freeslw::Listener* GetListener();
		freeslw::audioStatistics_t GetStatistics();
		const char* GetSupportedStaticSoundFormats() const;
		const char* GetSupportedStreamSoundFormats() const;

		void SetVolume(float v);
		float GetVolume() const;

		void SetMetersPerUnit(float s);
		float GetMetersPerUnit() const;

		void SetGroup(unsigned char id, bool active);
		bool IsGroupActive(unsigned char id) const;

		void StopAllSounds();

		freeslw::Sound* DuplicateSound(freeslw::Sound* s);
		freeslw::Sound* LoadSound(const char* file, unsigned char group, unsigned char priority);
		freeslw::Sound* LoadSoundFromZip(const char* file, const char* package, unsigned char group, unsigned char priority);
		freeslw::Sound* LoadSoundFromData(const char* name, const char* type, const char* data, size_t size, unsigned char group, unsigned char priority);
		freeslw::Sound* StreamSound(const char* file, unsigned char group, unsigned char priority);
		freeslw::Sound* CreateSound(const char* name, const void* data, size_t size, freeslw::soundFormat_e format, int frequency, unsigned char group, unsigned char priority);
		void ReleaseSound(freeslw::Sound* snd);
	};
}