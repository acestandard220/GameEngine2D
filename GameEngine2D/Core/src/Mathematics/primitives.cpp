#include "Mathematics/primitives.h"
#include <iostream>
namespace GE2D
{
	namespace GEM
	{
		Point2D::Point2D()
		{
			__x = 0.0f;
			__y = 0.0f;
		}
		Point2D::Point2D(float x, float y)
		{
			__x = x;
			__y = y;
		}
		Point2D::Point2D(const Point2D& other)
		{
		}
		float point_magnitude(const Point2D& p1, const Point2D& p2)
		{
			return float(0.0);
		}

		float gradient(const Line2D& line)
		{
			if (line.start.__x == line.end.__x)
			{
				std::invalid_argument("Cannot find the gradient of a vertical line\n");			
			}
			return float(
				    (line.start.__y - line.end.__y) / 
				    (line.start.__x - line.end.__x)
				);
		}

		float y_intercept(const Line2D& line)
		{
			float m = gradient(line);
			// c = y - mx
			return float(line.start.__y - (line.start.__x * m));
		}

		bool PointOnLine(const Point2D& point, const Line2D& line)
		{
			float m = gradient(line);
			//y = mx + c;
			float out = point.__y - (m * point.__x);
			if (y_intercept(line) == out)
			{
				return true;
			}
			return false;
		}


		Line2D::Line2D(const Point2D& a, const Point2D& b) :start(a),end(b)
		{

		}
		Line2D::Line2D(const Line2D& other)
		{
		}


		Circle::Circle():__radius(1.0f)
		{

		}
		Circle::Circle(const Point2D& center, float radius)
			:__center(center), __radius(radius)
		{
		}
		Circle::Circle(const Circle& other)
		{
		}

		Rectangle::Rectangle() :
			__size(1,1)
		{
		}
		Rectangle::Rectangle(const Point2D& center, vec2 size)
			:__center(center), __size(size)
		{
		}

		Rectangle::Rectangle(const Rectangle& other)
		{
		}
		
		Rectangle Rectangle::FromMinMax(const vec2& min, const vec2& max)
		{
			float sizeX = (max.x() - min.x());
			float sizeY = (max.y() - min.y());
			return Rectangle(Point2D(min.x() + (sizeX / 2), min.y() + (sizeY / 2)), vec2(sizeX, sizeY));
		}
		
		vec2 Rectangle::GetMin() const
		{
			return vec2(
				(__center.__x) - (__size.x() / 2.0),
				(__center.__y) - (__size.y() / 2.0)
			);
		}
		
		vec2 Rectangle::GetMax() const
		{
			return vec2 (
				(__center.__x) + (__size.x() / 2.0),
				(__center.__y) + (__size.y() / 2.0)
			);
		
		}
	}
}