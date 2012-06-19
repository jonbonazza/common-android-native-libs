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

#include "OpenALStream.h"

#define OGG_STREAM_BUFFER_SIZE	65536

namespace openal
{
	class StreamOgg : public Stream
	{
	private:
		char* streamData;
		ALenum format;
		FILE* oggFile;
		OggVorbis_File oggStream;
		Source* activeSource;

	private:
		bool Stream(ALuint buffer);
		void Empty(ALuint source);
		void OggError(int code);

	public:
		StreamOgg();
		~StreamOgg();

		bool Load(const char* file);
		bool Update(Source* source);
		void Play(Source* source);
		void Resume(Source* source);
		void Rewind();
		void Stop();
		void Pause();

		float GetPlayDuration() const;
		float GetPlayTime();
		void SetPlayTime(float seconds);
	};
}