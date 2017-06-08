#include <vector>
#include "GearSettings.h"
#include "GearPhysicsBody.h"
#pragma once

namespace Gear {
	class GearQuadTree
	{
	private:
		// Variables
		Gear::GearVector _min, _max;
		std::vector<GearPhysicsBody*> objects;
		int max_objects = 10;
		int max_levels = 10;
		int level_;
		GearQuadTree* nodes[4];
		// Function
		void split();
		int  getIndex(GearPhysicsBody&);
		bool isInside(GearPhysicsBody&);
	public:
		GearQuadTree();
		GearQuadTree(int, const GearVector &, const GearVector &);
		void clear();
		void insert(GearPhysicsBody *);
		std::vector<GearPhysicsBody*> solve();
		void setMaxObjects(int);
		void setMaxLevels(int);
		~GearQuadTree();
	};

}