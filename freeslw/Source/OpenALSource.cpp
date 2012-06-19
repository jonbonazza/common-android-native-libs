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

#include "OpenALSource.h"
#include "OpenALBuffer.h"

namespace openal
{
	Source::Source() : source(NO_SOURCE), looping(AL_FALSE), pitch(1.0f), gain(1.0f), gain_scale(1.0f), rolloff(1.0f), refDistance(0.0f), maxDistance(100.0f)
	{
		position[0] = position[1] = position[2] = 0.0f;
		velocity[0] = velocity[1] = velocity[2] = 0.0f;
	}
		
	Source::~Source()
	{
	}

	bool Source::HasSource() const
	{
		return source != NO_SOURCE;
	}

	bool Source::BeginSource(unsigned char group, unsigned char priority, Buffer* buffer, bool setActiveBuffer, bool setLooping)
	{
		if (buffer->bufferId[0] == NO_BUFFER) return false;

		gain_scale = 1.0f;

		if (source == NO_SOURCE)
		{
			source = AllocSource(group,priority);
			if (source != NO_SOURCE)
			{
				alSourcef(sources[source],AL_PITCH,pitch);
				alSourcef(sources[source],AL_GAIN,gain * gain_scale);
				alSourcef(sources[source],AL_ROLLOFF_FACTOR,rolloff);
				alSourcefv(sources[source],AL_POSITION,position);
				alSourcefv(sources[source],AL_VELOCITY,velocity);
				alSourcef(sources[source],AL_REFERENCE_DISTANCE,refDistance);
				alSourcef(sources[source],AL_MAX_DISTANCE,maxDistance);
				alSourcei(sources[source],AL_LOOPING,(setLooping) ? looping : AL_FALSE);
				if (setActiveBuffer) alSourcei(sources[source],AL_BUFFER,buffer->bufferId[buffer->activeBuffer]);
			}
		}

		return HasSource();
	}

	void Source::EndSource()
	{
		FreeSource(source);
		source = NO_SOURCE;
	}

	void Source::GainScale(float scale)
	{
		gain_scale = scale;
		if (HasSource()) alSourcef(sources[source],AL_GAIN,gain * gain_scale);
	}

	void Source::Looping(bool enabled, bool setLooping)
	{
		looping = (enabled)? AL_TRUE : AL_FALSE;
		if (setLooping && HasSource()) alSourcei(sources[source],AL_LOOPING,looping);
	}

	void Source::Position(float x, float y, float z)
	{
		position[0]=x;
		position[1]=y;
		position[2]=z;
		if (HasSource()) alSourcefv(sources[source],AL_POSITION,position);
	}

	void Source::Velocity(float x, float y, float z)
	{
		velocity[0]=x;
		velocity[1]=y;
		velocity[2]=z;
		if (HasSource()) alSourcefv(sources[source],AL_VELOCITY,velocity);
	}

	void Source::Pitch(float p)
	{
		pitch = p;
		if (HasSource()) alSourcef(sources[source],AL_PITCH,pitch);
	}

	void Source::Gain(float g)
	{
		gain = g;
		if (HasSource()) alSourcef(sources[source],AL_GAIN,gain * gain_scale);
	}

	void Source::Rolloff(float r)
	{
		rolloff = r;
		if (HasSource()) alSourcef(sources[source],AL_ROLLOFF_FACTOR,rolloff);
	}

	void Source::RefDistance(float d)
	{
		refDistance = d;
		if (HasSource()) alSourcef(sources[source],AL_REFERENCE_DISTANCE,refDistance);
	}

	void Source::MaxDistance(float d)
	{
		maxDistance = d;
		if (HasSource()) alSourcef(sources[source],AL_MAX_DISTANCE,maxDistance);
	}
}