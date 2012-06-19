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

#include <stdio.h>

#include "FreeSLW.h"
#include "OpenALInterface.h"

namespace freeslw
{
	AudioInterface* g_interface = 0;
	void (*error_callback)(const char* str) = 0;

	void ErrorPrintf(const char* message, ...)
	{
		if (error_callback)
		{
			char buff[512];
			va_list argptr;
			va_start(argptr,message);
			vsprintf(buff,message,argptr);
			va_end(argptr);

			error_callback(buff);
		}
	}

	FSLWAPI int FSLWAPIENTRY GetVersion()
	{
		return FSLW_VERSION;
	}

	FSLWAPI void FSLWAPIENTRY SetErrorCallback(void (*_error_callback)(const char* message))
	{
		error_callback = _error_callback;
	}

	FSLWAPI AudioInterface* FSLWAPIENTRY GetInterface(audioSubsystem_e subsystem)
	{
		if (g_interface) return g_interface;

		switch (subsystem)
		{
			case AS_OPENAL: g_interface = new openal::OpenALInterface(); break;
			// we can add more interfaces here
		}

		return g_interface;
	}

	FSLWAPI void FSLWAPIENTRY ReleaseInterface()
	{
		delete g_interface;
		g_interface = 0;
	}
}
