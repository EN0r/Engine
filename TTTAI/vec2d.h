#pragma once
#include <limits>
class vec2D
{
public:
	float x,y;
	vec2D(float x = 0.0f, float y = 0.0f)
	{
		this->x = x;
		this->y = y;
	}

	vec2D operator + (vec2D const& obj)
	{
		if (this != &obj) // self assignment check
		{
			vec2D returnval(this->x + obj.x, this->y + obj.y);
			return returnval;
		}
	}

	vec2D operator - (vec2D const& obj)
	{
		if (this != &obj) // self assignment check
		{
			vec2D returnval(this->x - obj.x, this->y - obj.y);
			return returnval;
		}
	}

};