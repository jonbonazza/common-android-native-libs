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

#include "OpenALStreamSound.h"
#include "OpenALBuffer.h"
#include "OpenALStream.h"

namespace openal
{
	OpenALStreamSound::OpenALStreamSound(unsigned char priority, Stream* _stream) : prio(priority), group(0), stream(_stream), isPlaying(false)
	{
	}

	OpenALStreamSound::~OpenALStreamSound()
	{
		Stop();
		delete stream;
	}

	void OpenALStreamSound::Update(const float& dt)
	{
		if (IsPlaying())
		{
			if (fade.Active())
			{
				source.GainScale(fade.Update(dt));
			}

			if (stream->Update(&source))
			{
				if (source.looping)
				{
					alSourceStop(sources[source.source]);
					stream->Stop();
					stream->Play(&source);
					alSourcePlay(sources[source.source]);
				}
				else
				{
					isPlaying = false;
					alSourceStop(sources[source.source]);
					stream->Stop();
					source.EndSource();
				}
			}
		}
	}

	unsigned char OpenALStreamSound::GetPriority() const
	{
		return prio;
	}

	Buffer* OpenALStreamSound::GetBuffer()
	{
		return stream->GetBuffer();
	}

	int OpenALStreamSound::GetSourceNumber() const
	{
		return source.source;
	}

	const char* OpenALStreamSound::GetName() const
	{
		return stream->GetBuffer()->name;
	}

	int	OpenALStreamSound::GetFrequency() const
	{
		return stream->GetBuffer()->frequency;
	}

	freeslw::soundFormat_e OpenALStreamSound::GetFormat() const
	{
		return stream->GetBuffer()->format;
	}

	bool OpenALStreamSound::IsStream() const
	{
		return true;
	}

	void OpenALStreamSound::SetGroup(unsigned char id)
	{
		group = id;
		if (groupActive[group] == false && IsPlaying())
		{
			Pause();
		}
	}

	unsigned char OpenALStreamSound::GetGroup() const
	{
		return group;
	}

	void OpenALStreamSound::Play()
	{
		if (IsPlaying()) return;

		if (source.BeginSource(group,prio,stream->GetBuffer(),false,false))
		{
			isPlaying = true;
			stream->Play(&source);
			alSourcePlay(sources[source.source]);
			streamPlayList.push_back(this);
		}
	}

	void OpenALStreamSound::Resume()
	{
		if (IsPaused())
		{
			stream->Resume(&source);
			alSourcePlay(sources[source.source]);
			streamPlayList.push_back(this);
		}
	}

	void OpenALStreamSound::Rewind()
	{
		stream->Rewind();
	}

	void OpenALStreamSound::Stop()
	{
		if (source.HasSource())
		{
			isPlaying = false;
			alSourceStop(sources[source.source]);
			stream->Stop();
			source.EndSource();
			streamPlayList.remove(this);
		}
	}

	void OpenALStreamSound::Pause()
	{
		if (source.HasSource())
		{
			stream->Pause();
			alSourcePause(sources[source.source]);
			streamPlayList.remove(this);
		}
	}

	bool OpenALStreamSound::IsPlaying()
	{
		if (source.HasSource())
		{
			ALenum state;
			alGetSourcei(sources[source.source],AL_SOURCE_STATE,&state);
			return (state == AL_PLAYING || (state == AL_STOPPED && isPlaying && source.looping));
		}

		return false;
	}

	bool OpenALStreamSound::IsPaused()
	{
		if (source.HasSource())
		{
			ALenum state;
			alGetSourcei(sources[source.source],AL_SOURCE_STATE,&state);
			return (state == AL_PAUSED);
		}

		return false;
	}

	void OpenALStreamSound::SetLooping(bool doLoop)
	{
		source.Looping(doLoop,false);
	}

	bool OpenALStreamSound::IsLooping() const
	{
		return source.looping == AL_TRUE;
	}

	void OpenALStreamSound::SetPosition(float x, float y, float z)
	{
		source.Position(x,y,z);
	}

	void OpenALStreamSound::SetPosition(const float* xyz)
	{
		source.Position(*xyz,*(xyz+1),*(xyz+2));
	}

	void OpenALStreamSound::GetPosition(float& x, float& y, float& z) const
	{
		x = source.position[0];
		y = source.position[1];
		z = source.position[2];
	}

	void OpenALStreamSound::SetVelocity(float x, float y, float z)
	{
		source.Velocity(x,y,z);
	}

	void OpenALStreamSound::SetVelocity(const float* xyz)
	{
		source.Velocity(*xyz,*(xyz+1),*(xyz+2));
	}

	void OpenALStreamSound::GetVelocity(float& x, float& y, float& z) const
	{
		x = source.velocity[0];
		y = source.velocity[1];
		z = source.velocity[2];
	}

	void OpenALStreamSound::SetPitch(float p)
	{
		source.Pitch(p);
	}

	float OpenALStreamSound::GetPitch() const
	{
		return source.pitch;
	}

	void OpenALStreamSound::SetGain(float g)
	{
		source.Gain(g);
	}

	float OpenALStreamSound::GetGain() const
	{
		return source.gain;
	}

	void OpenALStreamSound::SetRolloff(float r)
	{
		source.Rolloff(r);
	}

	float OpenALStreamSound::GetRolloff() const
	{
		return source.rolloff;
	}

	void OpenALStreamSound::SetDistance(float refDistance, float maxDistance)
	{
		source.RefDistance(refDistance);
		source.MaxDistance(maxDistance);
	}

	void OpenALStreamSound::GetDistance(float& refDistance, float& maxDistance) const
	{
		refDistance = source.refDistance;
		maxDistance = source.maxDistance;
	}

	float OpenALStreamSound::GetPlayDuration() const
	{
		return stream->GetPlayDuration();
	}

	float OpenALStreamSound::GetPlayTime()
	{
		return stream->GetPlayTime();
	}

	void OpenALStreamSound::SetPlayTime(float seconds)
	{
		stream->SetPlayTime(seconds);
	}

	void OpenALStreamSound::FadeIn(float duration)
	{
		fade.Begin(true,duration);
	}

	void OpenALStreamSound::FadeOut(float duration)
	{
		fade.Begin(false,duration);
	}
}