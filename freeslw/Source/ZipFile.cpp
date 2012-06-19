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

#include "ZipFile.h"

extern "C"
{
	#include "zlib/zlib.h"
	#include "zlib/unzip.h"
	#pragma comment(lib,"zlibstat.lib")
}

ZipFile::ZipFile(const char* package, const char* file) : size(0), position(0), data(0)
{
	LoadFile(package,file);
}

ZipFile::ZipFile() : size(0), position(0), data(0)
{
}

ZipFile::~ZipFile()
{
	FileClose();
}

bool ZipFile::LoadFile(const char* package, const char* file)
{
	FileClose();

	unzFile fp = unzOpen(package);
	if (!fp) return false;

	if (unzLocateFile(fp,file,0) != UNZ_OK)
	{
		unzClose(fp);
		return false;
	}

	if (unzOpenCurrentFile(fp) != UNZ_OK)
	{
		unzClose(fp);
		return false;
	}

	unz_file_info nfo;
	unzGetCurrentFileInfo(fp,&nfo,0,0,0,0,0,0);

	size = (long)nfo.uncompressed_size;

	data = new char[size];
	unzReadCurrentFile(fp,data,size);

	unzCloseCurrentFile(fp);
	unzClose(fp);

	return true;
}

int ZipFile::FileSeek(long offset, int origin)
{
	if (origin == SEEK_SET)
	{
		position = (size >= offset)? offset : size;
	}
	else if (origin == SEEK_CUR)
	{
		long steof = size - position;
		position += (offset < steof)? offset : steof;
	}
	else if (origin == SEEK_END)
	{
		position = size + 1;
	}

	return 0;
}

size_t ZipFile::FileRead(void* b, size_t size, size_t count)
{
	size_t read_size;
	size_t space_to_eof = (size_t)(size - position);

	if ((size * count) < space_to_eof)
		read_size = size * count;
	else
		read_size = space_to_eof;

	if (read_size)
	{
		memcpy(b,data + position,read_size);
		position += (long)read_size;
	}

	return read_size;
}

void ZipFile::FileClose()
{
	delete [] data;
	position = 0;
	size = 0;
	data = 0;
}