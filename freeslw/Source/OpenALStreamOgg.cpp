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

#include "OpenALStreamOgg.h"
#include "OpenALBuffer.h"
#include "OpenALSource.h"

namespace openal
{
	StreamOgg::StreamOgg() : activeSource(0), oggFile(0)
	{
		streamData = new char[OGG_STREAM_BUFFER_SIZE];
		oggStream.datasource = 0;
	}

	StreamOgg::~StreamOgg()
	{
		fclose(oggFile);
		ov_clear(&oggStream);

		if (buffer)
		{
			while (buffer->Release() != 0) {}
			delete buffer;
		}

		delete [] streamData;
	}

	void StreamOgg::OggError(int code)
	{
		switch (code)
		{
			case OV_EREAD: freeslw::ErrorPrintf("Ogg: read from media."); break;
			case OV_ENOTVORBIS: freeslw::ErrorPrintf("Ogg: not Vorbis data."); break;
			case OV_EVERSION: freeslw::ErrorPrintf("Ogg: Vorbis version mismatch."); break;
			case OV_EBADHEADER: freeslw::ErrorPrintf("Ogg: invalid Vorbis header."); break;
			case OV_EFAULT: freeslw::ErrorPrintf("Ogg: internal logic fault (bug or heap/stack corruption."); break;
			default: freeslw::ErrorPrintf("Ogg: unknown error.");
		}
	}

	bool StreamOgg::Load(const char* file)
	{
		vorbis_info* vorbisInfo;
		int result;
		oggFile = fopen(file,"rb");
		if (oggFile == 0)
		{
			freeslw::ErrorPrintf("Failed to load \"%s\".",file);
			return false;
		}

		buffer = new Buffer(file);
		alGenBuffers(2,buffer->bufferId);
		buffer->activeBuffer = 0;
		buffer->numBuffers = 2;
		
		result = ov_open(oggFile,&oggStream,0,0);
		if (result != 0)
		{
			OggError(result);
			fclose(oggFile);
			oggFile = 0;
			return false;
		}

		vorbisInfo = ov_info(&oggStream,-1);

		format = (vorbisInfo->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		buffer->format = (vorbisInfo->channels == 1) ? freeslw::TA_MONO16 : freeslw::TA_STEREO16;
		buffer->frequency = vorbisInfo->rate;
		buffer->length = (size_t)(ov_time_total(&oggStream,-1) * 1000.0);

		return true;
	}

	bool StreamOgg::Update(Source* source)
	{
		activeSource = source;

		bool active = true;
		ALenum state; 
		alGetSourcei(sources[activeSource->source],AL_SOURCE_STATE,&state);

		if (state == AL_PAUSED) return false;

		int processed;
		alGetSourcei(sources[activeSource->source],AL_BUFFERS_PROCESSED,&processed);

		while (processed-- > 0)
		{
			ALuint b;
			alSourceUnqueueBuffers(sources[activeSource->source],1,&b);
			active = Stream(b);
			alSourceQueueBuffers(sources[activeSource->source],1,&b);
		}

		return !active;
	}

	void StreamOgg::Play(Source* source)
	{
		activeSource = source;

		Stream(buffer->bufferId[0]);
		Stream(buffer->bufferId[1]);

		alSourceQueueBuffers(sources[activeSource->source],2,buffer->bufferId);
	}

	void StreamOgg::Resume(Source* source)
	{
		activeSource = source;
	}

	void StreamOgg::Rewind()
	{
		if (activeSource && activeSource->HasSource())
		{
			SetPlayTime(0.0f);
			Empty(sources[activeSource->source]);
		}
	}

	void StreamOgg::Stop()
	{
		if (activeSource && activeSource->HasSource())
		{
			SetPlayTime(0.0f);
			Empty(sources[activeSource->source]);
			activeSource = 0;
		}
	}

	void StreamOgg::Pause()
	{
		// TODO: pause may (in the future) result in deallocation of the source so we need to handle this
	}

	float StreamOgg::GetPlayDuration() const
	{
		return (float)buffer->length / 1000.0f;
	}

	float StreamOgg::GetPlayTime()
	{
		return (float)ov_time_tell(&oggStream);
	}

	void StreamOgg::SetPlayTime(float seconds)
	{
		Empty(sources[activeSource->source]);
		ov_time_seek(&oggStream,seconds);
	}

	bool StreamOgg::Stream(ALuint buffer)
	{
		int size = 0;
		int section;
		int result;

		while (size < OGG_STREAM_BUFFER_SIZE)
		{
			result = ov_read(&oggStream,streamData + size,OGG_STREAM_BUFFER_SIZE - size, 0, 2, 1, &section);

			     if (result > 0) size += result;
			else if (result < 0) return false; // we have error
			else break;
		}

		if (size == 0) return false;

		alBufferData(buffer,format,streamData,size,GetBuffer()->frequency);

		return true;
	}

	void StreamOgg::Empty(ALuint source)
	{
		ALuint b;
		int queued;

		alGetSourcei(source,AL_BUFFERS_QUEUED,&queued);

		while (queued-- > 0)
		{
			alSourceUnqueueBuffers(source,1,&b);
		}
	}
}
