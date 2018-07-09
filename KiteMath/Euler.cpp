#include "stdafx.h"
#include "Euler.h"

namespace kite_math
{
	Euler::Euler()
		: pitch(0), yaw(0), roll(0)
	{
	}

	Euler::Euler(float pitchRad, float yawRad, float rollRad)
		: pitch(pitchRad), yaw(yawRad), roll(rollRad)
	{
	}


	Euler::~Euler()
	{
	}

	void Euler::SetDegree(float pitchDegree, float yawDegree, float rollDegree)
	{
		pitch = Mathf::DegreeToRad(pitchDegree);
		yaw = Mathf::DegreeToRad(yawDegree);
		roll = Mathf::DegreeToRad(rollDegree);
	}
}