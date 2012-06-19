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

#define MAX_BUFFER_NAME 64
#define NO_BUFFER -1
#include <cstdio>

namespace openal
{
	class Buffer
	{
	public:
		ALuint bufferId[2];
		char name[MAX_BUFFER_NAME];
		size_t name_length;
		int frequency;
		size_t length;
		freeslw::soundFormat_e format;
		unsigned char numBuffers;
		unsigned char activeBuffer;

	private:
		int refCount;

	public:
		Buffer(const char* _name);
		~Buffer();

		INLINE void AddRef()		{ refCount++; }
		INLINE int Release()		{ if (refCount > 0) refCount--; return refCount; }
		INLINE int GetRef() const	{ return refCount; }
	};
}
