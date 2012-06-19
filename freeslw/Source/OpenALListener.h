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
	class OpenALListener : public freeslw::Listener
	{
	private:
		freeslw::audioEnvironment_e activeEnvironment;
		freeslw::distanceModel_e activeDistanceModel;

	public:
		OpenALListener();
		~OpenALListener();

		void SetPosition(float x, float y, float z);
		void SetPosition(const float* xyz);
		void GetPosition(float& x, float& y, float& z) const;

		void SetOrientation(float ax, float ay, float az, float ux, float uy, float uz);
		void SetOrientation(const float* a, const float* u);
		void GetOrientation(float& ax, float& ay, float& az, float& ux, float& uy, float& uz) const;

		void SetVelocity(float x, float y, float z);
		void SetVelocity(const float* xyz);
		void GetVelocity(float& x, float& y, float& z) const;

		void SetDistanceModel(freeslw::distanceModel_e m);
		freeslw::distanceModel_e GetDistanceModel() const;

		void SetDopplerParameters(float factor, float velocity);
		void GetDopplerParameters(float& factor, float& velocity) const;
		void SetEnvironment(freeslw::audioEnvironment_e env) {}
		freeslw::audioEnvironment_e GetEnvironment() const;
	};
}
