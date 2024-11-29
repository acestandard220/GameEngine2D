#pragma once
#include "../core.h"
#include <cmath>


namespace GE2D {
	namespace GEM {



		struct vec2
		{
			vec2();
			vec2(const vec2& other) = default;

			vec2(float);
			vec2(float, float);

			GAME_ENGINE_2D_FORCE_INLINE const float& x()const {    return __e[0];    }
			GAME_ENGINE_2D_FORCE_INLINE const float& y()const {    return __e[1];    };

			GAME_ENGINE_2D_FORCE_INLINE const float& r()const {    return __e[0];    };
			GAME_ENGINE_2D_FORCE_INLINE const float& g()const {    return __e[1];    };
		
			GAME_ENGINE_2D_FORCE_INLINE const float& u()const {    return __e[0];    };
			GAME_ENGINE_2D_FORCE_INLINE const float& v()const {    return __e[1];    };

			
			vec2 operator+ (const vec2& a) const {    return { this->__e[0] + a.__e[0], this->__e[1] + a.__e[1] };    }
			vec2 operator- (const vec2& a) const {    return { this->__e[0] - a.__e[0], this->__e[1] - a.__e[1] };    }
			vec2 operator* (const vec2& a) const {    return { this->__e[0] * a.__e[0], this->__e[1] * a.__e[1] };    }
			vec2 operator/ (const vec2& a) const {    return { this->__e[0] / a.__e[0], this->__e[1] / a.__e[1] };    }
			vec2 operator* (const float& a) const  {   return { this->__e[0] * a, this->__e[1] * a };    }
			vec2 operator/ (const float& a) const  { return { this->__e[0] / a, this->__e[1] / a }; }
			bool operator== (const vec2& a) const  { return GEM_CMP(this->__e[0], a.__e[0]) && GEM_CMP(this->__e[1], a.__e[1]); }
			float operator[] (int i) const { return __e[i]; }

		private:
			float __e[2];
		};
		struct vec3
		{
			vec3();
			vec3(const vec3& other) = default;

			vec3(float);
			vec3(float, float,float);

			GAME_ENGINE_2D_FORCE_INLINE const float& x()const { return __e[0]; }
			GAME_ENGINE_2D_FORCE_INLINE const float& y()const { return __e[1]; }
			GAME_ENGINE_2D_FORCE_INLINE const float& z()const { return __e[2]; }

			GAME_ENGINE_2D_FORCE_INLINE float& x(){ return __e[0]; }
			GAME_ENGINE_2D_FORCE_INLINE float& y(){ return __e[1]; }
			GAME_ENGINE_2D_FORCE_INLINE float& z(){ return __e[2]; }

			GAME_ENGINE_2D_FORCE_INLINE const float& r()const { return __e[0]; }
			GAME_ENGINE_2D_FORCE_INLINE const float& g()const { return __e[1]; }
			GAME_ENGINE_2D_FORCE_INLINE const float& b()const { return __e[2]; }

			

			vec3 operator+ (const vec3& a) const { return { this->__e[0] + a.__e[0],  this->__e[1] + a.__e[1],  this->__e[2] + a.__e[2] }; }
			vec3 operator- (const vec3& a) const { return { this->__e[0] - a.__e[0],  this->__e[1] - a.__e[1],  this->__e[2] - a.__e[2] };  }
			vec3 operator* (const vec3& a) const { return { this->__e[0] * a.__e[0],  this->__e[1] * a.__e[1],  this->__e[2] * a.__e[2] };  }
			vec3 operator/ (const vec3& a) const { return { this->__e[0] / a.__e[0],  this->__e[1] / a.__e[1],  this->__e[2] / a.__e[2] };  }
			
			vec3 operator* (const float& a) const { return { this->__e[0] * a, this->__e[1] * a ,this->__e[2] / a}; }
			vec3 operator/ (const float& a) const { return { this->__e[0] / a, this->__e[1] / a ,this->__e[2] / a}; }
			float operator[] (int i) const { return __e[i]; }

			bool operator== (const vec3& a) 
			{
				return GEM_CMP(this->__e[0], a.__e[0]) && GEM_CMP(this->__e[1], a.__e[1]) && GEM_CMP(this->__e[2], a.__e[2]);
			}
		private:
			float __e[3];

		};


		GAME_ENGINE_2D_FORCE_INLINE float dot(const vec2& a, const vec2& b) { return a[0] * b[0] + a[1] * b[1]; }
		GAME_ENGINE_2D_FORCE_INLINE float dot(const vec3& a, const vec3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }

		GAME_ENGINE_2D_FORCE_INLINE float magnitude(const vec2& a) { return GEM_SQR(dot(a,a)); }
		GAME_ENGINE_2D_FORCE_INLINE float magnitude(const vec3& a) { return GEM_SQR(dot(a, a)); }

		GAME_ENGINE_2D_FORCE_INLINE float sqr_magnitude(const vec2& a) { return dot(a, a); }
		GAME_ENGINE_2D_FORCE_INLINE float sqr_magnitude(const vec3& a) { return dot(a, a); }

		GAME_ENGINE_2D_FORCE_INLINE float length(const vec2& a, const vec2& b) { vec2 t = a-b; return magnitude(t); }

		GAME_ENGINE_2D_FORCE_INLINE const vec2& normalize(const vec2& a) { return a * (1 / magnitude(a)); }
		GAME_ENGINE_2D_FORCE_INLINE const vec3& normalize(const vec3& a) { return a * (1 / magnitude(a)); }

		GAME_ENGINE_2D_FORCE_INLINE const vec3& cross(const vec3& a) 
		{
			vec3 result;
			result.x() = (a.y() * a.z()) - (a.z() * a.y());
			result.y() = (a.z() * a.x()) - (a.x() * a.z());
			result.z() = (a.x() * a.y()) - (a.y() * a.x());
			
			return result;
		}

		GAME_ENGINE_2D_FORCE_INLINE float Angle(const vec2& l, const vec2& r) {
			float m = sqrtf(sqr_magnitude(l) * sqr_magnitude(r));
			return GEM_ACOS(dot(l, r) / m);
		}

		GAME_ENGINE_2D_FORCE_INLINE float Angle(const vec3& l, const vec3& r) {
			float m = sqrtf(sqr_magnitude(l) * sqr_magnitude(r));
			return GEM_ACOS(dot(l, r) / m);
		}
	}												

}