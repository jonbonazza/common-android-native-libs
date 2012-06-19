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

#include "OpenALGlobals.h"
#include "OpenALSource.h"
#include "Fade.h"

namespace openal
{
	class Buffer;
	class Stream;

	class OpenALStreamSound : public freeslw::Sound
	{
	private:
		Stream* stream;
		unsigned char prio;
		unsigned char group;
		Source source;
		Fade fade;
		bool isPlaying;

	public:
		OpenALStreamSound(unsigned char priority, Stream* _stream);
		~OpenALStreamSound();

		void Update(const float& dt);
		unsigned char GetPriority() const;
		Buffer* GetBuffer();
		int GetSourceNumber() const;

		const char* GetName() const;
		int GetFrequency() const;
		freeslw::soundFormat_e GetFormat() const;

		bool IsStream() const;
		
		void SetGroup(unsigned char id);
		unsigned char GetGroup() const;

		void Play();
		void Resume();
		void Rewind();
		void Stop();
		void Pause();
		bool IsPlaying();
		bool IsPaused();

		void SetLooping(bool doLoop);
		bool IsLooping() const;
		
		void SetPosition(float x, float y, float z);
		void SetPosition(const float* xyz);
		void GetPosition(float& x, float& y, float& z) const;

		void SetVelocity(float x, float y, float z);
		void SetVelocity(const float* xyz);
		void GetVelocity(float& x, float& y, float& z) const;

		void SetPitch(float p);
		float GetPitch() const;

		void SetGain(float g);
		float GetGain() const;

		void SetRolloff(float r);
		float GetRolloff() const;

		void SetDistance(float refDistance, float maxDistance);
		void GetDistance(float& refDistance, float& maxDistance) const;

		float GetPlayDuration() const;
		float GetPlayTime();
		void SetPlayTime(float seconds);

		void FadeIn(float duration);
		void FadeOut(float duration);
	};
}