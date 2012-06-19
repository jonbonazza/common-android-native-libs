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

#include "Common.h"
#include "OggCallback.h"

size_t OggStaticReadCallback(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	OggStaticFile* fp = static_cast<OggStaticFile*>(datasource);

	size_t read_size;
	size_t space_to_eof = fp->size - fp->position;

	if (nmemb * size < space_to_eof)
		read_size = nmemb * size;
	else
		read_size = space_to_eof;

	if (read_size)
	{
		memcpy(ptr,static_cast<const char*>(fp->data) + fp->position,read_size);
		fp->position += (long)read_size;
	}

	return read_size;
}

int OggStaticSeekCallback(void* datasource, ogg_int64_t offset, int whence)
{
	OggStaticFile* fp = static_cast<OggStaticFile*>(datasource);

	if (whence == SEEK_SET)
	{
		if (fp->size >= offset)
			fp->position = (long)offset;
		else
			fp->position = fp->size;
	}
	else if (whence == SEEK_CUR)
	{ 
		long space_to_eof = fp->size - fp->position;
		if (offset < space_to_eof)
			fp->position += (long)offset;
		else
			fp->position += space_to_eof;
	}
	else if (whence == SEEK_END) 
	{ 
		fp->position = fp->size + 1;
	}

	return 0;
}

int OggStaticCloseCallback(void* datasource)
{
	return 0;
}

long OggStaticTellCallback(void* datasource)
{
	OggStaticFile* fp = static_cast<OggStaticFile*>(datasource);
	return fp->position;
}

ov_callbacks OggStaticGetCallback()
{
	ov_callbacks callbacks;

	callbacks.close_func = OggStaticCloseCallback;
	callbacks.read_func = OggStaticReadCallback;
	callbacks.seek_func = OggStaticSeekCallback;
	callbacks.tell_func = OggStaticTellCallback;

	return callbacks;
}