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

bool IsFileExtension(const char* file, const char* extension)
{
	if (file && extension)
	{
		size_t lfile = strlen(file);
		size_t lext = strlen(extension);
		size_t lbegin = lfile - 1;

		if (lext > lfile) return false;
		if (lext == 0) return true;

		while (lbegin > 0)
		{
			if (*(file + lbegin) == '.') break;
			lbegin--;
		}

		if (lbegin == 0) return false;
		
		lbegin++;
		if (lfile - lbegin != lext) return false;
		
		for (size_t i = 0; i < lext; i++)
		{
			if (*(file + lbegin + i) != *(extension + i))
			{
				return false;
			}
		}
		
		return true;
	}

	return false;
}

void GetFileExtension(const char* file, char* extension, size_t maxLength)
{
	if (file && extension)
	{
		size_t lfile = strlen(file);
		size_t lbegin = lfile - 1;

		if (lfile == 0)
		{
			extension[0] = '\0';
			return;
		}

		while (lbegin > 0)
		{
			if (*(file + lbegin) == '.')
			{
				lbegin++;
				break;
			}
			lbegin--;
		}

		maxLength--;
		size_t count = (maxLength > (lfile - lbegin))? (lfile - lbegin) : maxLength;
		for (size_t i = 0; i < count; i++)
		{
			*(extension + i) = *(file + (lbegin + i));
		}

		*(extension + count) = '\0';
	}
}

void FixFileSeparators(char* file)
{
	if (file)
	{
		size_t i = 0;
		while (*(file + i) != '\0')
		{
			if (*(file + i) == '\\')
			{
				*(file + i) = '/';
			}

			i++;
		}
	}
}