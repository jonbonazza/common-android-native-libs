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

#include "Common.h"

class Fade
{
private:
	enum fadeState_e
	{
		FADE_IN = 0,
		FADE_OUT,
		FADE_NONE
	};

	float			duration;
	float			totalTime;
	fadeState_e		state;

public:
	Fade() : duration(0.0f), totalTime(0.0f), state(FADE_NONE) {}
	~Fade() {}

	void Begin(bool fadeIn, float _duration)
	{
		if (duration <= 0.0f) duration = 0.001f;
		duration = _duration;
		totalTime = 0.0f;
		state = (fadeIn)? FADE_IN : FADE_OUT;
	}

	INLINE bool Active() const
	{
		return state != FADE_NONE;
	}

	float Update(float deltaTime)
	{
		totalTime += deltaTime;

		if (totalTime >= duration)
		{
			float r = (state == FADE_IN)? 1.0f : 0.0f;
			state = FADE_NONE;
			return r;
		}

		if (state == FADE_IN) return totalTime / duration;
		return 1.0f - (totalTime / duration);
	}
};