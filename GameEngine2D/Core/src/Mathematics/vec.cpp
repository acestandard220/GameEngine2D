#include "Mathematics/vec.h"

namespace GE2D
{
	namespace GEM
	{
		vec2::vec2()
		{
			__e[0] = 0.0f;
			__e[1] = 0.0f;
		}
		vec2::vec2(float x,float y)
		{
			__e[0] = x;
			__e[1] = y;
		}


		vec2::vec2(float xy)
		{
			__e[0] = xy;
			__e[1] = xy;
		}


		///////////////////
		vec3::vec3()
		{
			__e[0] = 0.0f;
			__e[1] = 0.0f;
		}
		vec3::vec3(float x, float y,float z)
		{
			__e[0] = x;
			__e[1] = y;
		}


		vec3::vec3(float xy)
		{
			__e[0] = xy;
			__e[1] = xy;
		}
	}
}