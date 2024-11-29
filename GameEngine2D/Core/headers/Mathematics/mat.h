#pragma once


namespace GE2D
{
	namespace GEM
	{
		struct mat2
		{
			float __e[2][2];

			float* operator[] (int i) { return (__e[i]); }
		};

		struct mat3
		{
			float __e[3][3];
			float* operator[] (int i) { return (__e[i]); }
		};

	}
}