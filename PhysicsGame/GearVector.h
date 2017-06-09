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
		//Static
		static GearVector ZERO;
		//Utilities
		float norm();										// Normalise the vector 
		float len();										// Returns the length of the vector
		float operator * (const GearVector  &) const;		// Dot product for the vector
		float dot(const GearVector  &);						// Same as Dot product
		GearVector operator * (const float &) const;		// Multiples a scalar and return new vector
		void s_mul(const float&);							// Multiplies a scalar to this vector
		GearVector operator + (const GearVector  &) const;	// Returns the Addition of the two vector 
		void add(GearVector const &);						// Add the second vector to itself
		void operator += (const GearVector  &);		// Adds the second vector to itself
		GearVector operator - (const GearVector  &) const;
		void sub(const GearVector  &);
		void operator -= (const GearVector  &);
		bool zero() const;
		void clear();
	};

}