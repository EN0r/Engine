#pragma once
#include "vec2d.h"
#include "componentSystem.h"

class RdTransform : public Component
{
public:
	vec2D position;
	vec2D scale;
	float rotation;
	RdTransform()
	{
		rotation = 0.0f;
	}

private:

};