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
#include "OpenALBuffer.h"

namespace openal
{
	Buffer::Buffer(const char* _name) : refCount(1), activeBuffer(0), numBuffers(0), frequency(0), format(freeslw::TA_MONO16)
	{
		bufferId[0] = bufferId[1] = NO_BUFFER;
		snprintf(name,MAX_BUFFER_NAME,_name);
		name_length = strlen(name);
		bufferList.push_back(this);
	}

	Buffer::~Buffer()
	{
		if (bufferId[0] != NO_BUFFER) alDeleteBuffers(1,&bufferId[0]);
		if (bufferId[1] != NO_BUFFER) alDeleteBuffers(1,&bufferId[1]);
		bufferList.remove(this);
	}
}
