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

#include "OpenALStaticSound.h"
#include "OpenALGlobals.h"
#include "OpenALBuffer.h"

namespace openal
{
	OpenALStaticSound::OpenALStaticSound(Buffer* b, unsigned char priority) : buffer(b), prio(priority), group(0)
	{
	}

	OpenALStaticSound::~OpenALStaticSound()
	{
		Stop();
		if (buffer->Release() == 0) delete buffer;
	}

	void OpenALStaticSound::Update(const float& dt)
	{
		if (fade.Active() && IsPlaying())
		{
			source.GainScale(fade.Update(dt));
		}
	}

	unsigned char OpenALStaticSound::GetPriority() const
	{
		return prio;
	}

	Buffer* OpenALStaticSound::GetBuffer()
	{
		return buffer;
	}

	int OpenALStaticSound::GetSourceNumber() const
	{
		return source.source;
	}

	const char* OpenALStaticSound::GetName() const
	{
		return buffer->name;
	}

	int	OpenALStaticSound::GetFrequency() const
	{
		return buffer->frequency;
	}

	freeslw::soundFormat_e OpenALStaticSound::GetFormat() const
	{
		return buffer->format;
	}

	bool OpenALStaticSound::IsStream() const
	{
		return false;
	}

	void OpenALStaticSound::SetGroup(unsigned char id)
	{
		group = id;
		if (groupActive[group] == false && IsPlaying())
		{
			Pause();
		}
	}

	unsigned char OpenALStaticSound::GetGroup() const
	{
		return group;
	}

	void OpenALStaticSound::Play()
	{
		if (IsPlaying()) return;

		if (source.BeginSource(group,prio,buffer))
		{
			alSourcePlay(sources[source.source]);
			staticPlayList.push_back(this);
		}
	}

	void OpenALStaticSound::Resume()
	{
		if (IsPaused())
		{
			alSourcePlay(sources[source.source]);
			staticPlayList.push_back(this);
		}
	}

	void OpenALStaticSound::Rewind()
	{
		if (source.HasSource())
		{
			alSourceRewind(sources[source.source]);
		}
	}

	void OpenALStaticSound::Stop()
	{
		if (source.HasSource())
		{
			alSourceStop(sources[source.source]);
			source.EndSource();
			staticPlayList.remove(this);
		}
	}

	void OpenALStaticSound::Pause()
	{
		if (source.HasSource())
		{
			alSourcePause(sources[source.source]);
			staticPlayList.remove(this);
		}
	}

	bool OpenALStaticSound::IsPlaying()
	{
		if (source.HasSource())
		{
			ALenum state;
			alGetSourcei(sources[source.source],AL_SOURCE_STATE,&state);
			return (state == AL_PLAYING);
		}

		return false;
	}

	bool OpenALStaticSound::IsPaused()
	{
		if (source.HasSource())
		{
			ALenum state;
			alGetSourcei(sources[source.source],AL_SOURCE_STATE,&state);
			return (state == AL_PAUSED);
		}

		return false;
	}

	void OpenALStaticSound::SetLooping(bool doLoop)
	{
		source.Looping(doLoop,true);
	}

	bool OpenALStaticSound::IsLooping() const
	{
		return source.looping == AL_TRUE;
	}

	void OpenALStaticSound::SetPosition(float x, float y, float z)
	{
		source.Position(x,y,z);
	}

	void OpenALStaticSound::SetPosition(const float* xyz)
	{
		source.Position(*xyz,*(xyz+1),*(xyz+2));
	}

	void OpenALStaticSound::GetPosition(float& x, float& y, float& z) const
	{
		x = source.position[0];
		y = source.position[1];
		z = source.position[2];
	}

	void OpenALStaticSound::SetVelocity(float x, float y, float z)
	{
		source.Velocity(x,y,z);
	}

	void OpenALStaticSound::SetVelocity(const float* xyz)
	{
		source.Velocity(*xyz,*(xyz+1),*(xyz+2));
	}

	void OpenALStaticSound::GetVelocity(float& x, float& y, float& z) const
	{
		x = source.velocity[0];
		y = source.velocity[1];
		z = source.velocity[2];
	}

	void OpenALStaticSound::SetPitch(float p)
	{
		source.Pitch(p);
	}

	float OpenALStaticSound::GetPitch() const
	{
		return source.pitch;
	}

	void OpenALStaticSound::SetGain(float g)
	{
		source.Gain(g);
	}

	float OpenALStaticSound::GetGain() const
	{
		return source.gain;
	}

	void OpenALStaticSound::SetRolloff(float r)
	{
		source.Rolloff(r);
	}

	float OpenALStaticSound::GetRolloff() const
	{
		return source.rolloff;
	}

	void OpenALStaticSound::SetDistance(float refDistance, float maxDistance)
	{
		source.RefDistance(refDistance);
		source.MaxDistance(maxDistance);
	}

	void OpenALStaticSound::GetDistance(float& refDistance, float& maxDistance) const
	{
		refDistance = source.refDistance;
		maxDistance = source.maxDistance;
	}

	float OpenALStaticSound::GetPlayDuration() const
	{
		return (float)buffer->length / 1000.0f;
	}

	float OpenALStaticSound::GetPlayTime()
	{
		if (source.HasSource())
		{
			float m;
			alGetSourcef(sources[source.source],AL_SEC_OFFSET,&m);
			return m;
		}

		return 0.0f;
	}

	void OpenALStaticSound::SetPlayTime(float seconds)
	{
		if (source.HasSource())
		{
			alSourcef(sources[source.source],AL_SEC_OFFSET,seconds);
		}
	}

	void OpenALStaticSound::FadeIn(float duration)
	{
		fade.Begin(true,duration);
	}

	void OpenALStaticSound::FadeOut(float duration)
	{
		fade.Begin(false,duration);
	}
}