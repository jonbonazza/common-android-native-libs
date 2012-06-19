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
	class Source;

	class Stream
	{
	protected:
		Buffer* buffer;

	public:
		Stream() : buffer(0) {}
		virtual ~Stream() {}

		INLINE Buffer* GetBuffer() { return buffer; }

		virtual bool Load(const char* file) = 0;
		virtual bool Update(Source* source) = 0;
		virtual void Play(Source* source) = 0;
		virtual void Resume(Source* source) = 0;
		virtual void Rewind() = 0;
		virtual void Stop() = 0;
		virtual void Pause() = 0;

		virtual float GetPlayDuration() const = 0;
		virtual float GetPlayTime() = 0;
		virtual void SetPlayTime(float seconds) = 0;
	};
}