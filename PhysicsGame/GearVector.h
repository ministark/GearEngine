#include <cmath>
#pragma once

namespace Gear {
	class GearVector
	{
	public:
		float _x, _y;

		// The Mandatory Functions 
		GearVector();
		GearVector(float, float);
		GearVector(const GearVector &);
		~GearVector();

		//Utilities
		float norm();										// Normalise the vector and returns the length of the vector
		float len(const GearVector  &);						// Returns the length of the vector
		float operator * (const GearVector  &) const;		// Dot product for the vector
		float dot(const GearVector  &);						// Same as Dot product
		GearVector operator + (const GearVector  &) const;	// Returns the Addition of the two vector 
		void add(GearVector const &);						// Add the second vector to itself
		GearVector operator - (const GearVector  &) const;
		void sub(const GearVector  &);
	};

}