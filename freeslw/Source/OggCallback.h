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

extern "C"
{
	#include "vorbis/vorbisfile.h"
}

#define OGG_STATIC_BUFFER_SIZE	32768

class OggStaticFile
{
public:
	long		position;
	long		size;
	const void*	data;

public:
	OggStaticFile(const void* _data, long _size) : position(0), size(_size), data(_data)	{}
	~OggStaticFile() {}
};

size_t OggStaticReadCallback(void* ptr, size_t size, size_t nmemb, void* datasource);
int OggStaticSeekCallback(void* datasource, ogg_int64_t offset, int whence);
int OggStaticCloseCallback(void* datasource);
long OggStaticTellCallback(void* datasource);
ov_callbacks OggStaticGetCallback();
