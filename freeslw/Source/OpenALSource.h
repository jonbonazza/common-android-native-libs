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

namespace openal
{
	class Buffer;

	class Source
	{
	public:
		int source;	// this is not the actual OpenAL source, just an id to it
		int looping;
		float position[3];
		float velocity[3];
		float pitch;
		float gain;
		float gain_scale;
		float rolloff;
		float refDistance;
		float maxDistance;

	public:
		Source();
		~Source();

		bool HasSource() const;

		bool BeginSource(unsigned char group, unsigned char priority, Buffer* buffer, bool setActiveBuffer = true, bool setLooping = true);
		void EndSource();

		void GainScale(float scale);
		void Looping(bool enabled, bool setLooping);
		void Position(float x, float y, float z);
		void Velocity(float x, float y, float z);
		void Pitch(float p);
		void Gain(float g);
		void Rolloff(float r);
		void RefDistance(float d);
		void MaxDistance(float d);
	};
}