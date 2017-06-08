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
		float len(GearVector const &);						// Returns the length of the vector
		float operator * (GearVector const &);				// Dot product for the vector
		float dot(GearVector const &);						// Same as Dot product
		GearVector operator + (GearVector const &);			// Returns the Addition of the two vector 
		void add(GearVector const &);						// Add the second vector to itself
	};

}