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
#include <sys/time.h>
/*class Timer
{
public:
	LARGE_INTEGER initTime;
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER currentTime;

public:
	Timer()
	{
		QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&initTime);
	}

	~Timer() {}

	INLINE float GetTotalTime()
	{
		QueryPerformanceCounter(&currentTime);
		float ret = (float)(currentTime.QuadPart - initTime.QuadPart) / (float)ticksPerSecond.QuadPart;
		return (ret < 0.0f)? -ret : ret;
	}
};*/

class Timer
{
public:
	timeval initTime;
	timeval currentTime;

	Timer()
	{
		gettimeofday(&initTime, 0);
	}

	INLINE float GetTotalTime()
	{
		gettimeofday(&currentTime, 0);
		long c_usec = currentTime.tv_usec + currentTime.tv_sec * 1000000;
		long i_usec = initTime.tv_usec + initTime.tv_sec * 1000000;
		float ret = (float)(c_usec - i_usec);
		return (ret < 0.0f) ? -ret : ret;
	}
};
