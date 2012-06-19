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

class ZipFile
{
private:
	long size;
	char* data;
	long position;

public:
	ZipFile(const char* package, const char* file);
	ZipFile();
	~ZipFile();

	bool LoadFile(const char* package, const char* file);
	int FileSeek(long offset, int origin);
	size_t FileRead(void* b, size_t size, size_t count);
	void FileClose();

	INLINE long		FileTell() const	{ return position; }
	INLINE long		GetFileSize() const	{ return size; }
	INLINE bool		IsEOF() const		{ return (position < size); }
	INLINE char*	GetData() const		{ return data; }
};