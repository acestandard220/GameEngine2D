#pragma once
#include "vec.h"
namespace GE2D
{
	namespace GEM
	{
		struct Point2D
		{
			float __x;
			float __y;

			Point2D();
			Point2D(float x, float y);
			Point2D(const Point2D& other);
		};



		struct Line2D
		{
			Point2D start;
			Point2D end;

			Line2D(const Point2D& a, const Point2D& b);
			Line2D(const Line2D& other);
		};

		struct Circle
		{
			Point2D __center;
			float __radius;

			Circle();
			Circle(const Point2D& center, float radius);
			Circle(const Circle& other);
		};

		struct Rectangle
		{
			Point2D __center;
			vec2 __size;

			Rectangle();
			Rectangle(const Point2D& center, vec2 size);
			Rectangle(const Rectangle& other);
			static Rectangle FromMinMax(const vec2& min, const vec2& max);
            
			vec2 GetMin()const;
			vec2 GetMax()const;
		};
		float point_magnitude(const Point2D& p1, const Point2D& p2);

		float gradient(const Line2D& line);
		float y_intercept(const Line2D& line);

		bool PointOnLine(const Point2D& point, const Line2D& line);
	}
}