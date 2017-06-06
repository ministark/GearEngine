#include <vector>
#include "GearSettings.h"
#include "GearPhysicsBody.h"
#pragma once

namespace Gear {
	class GearQuadTree
	{
	private:
		// Variables
		float x_min, y_min, x_max, y_max;
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
		GearQuadTree(int, float, float, float, float);
		void clear();
		void insert(GearPhysicsBody *);
		void setMaxObjects(int);
		void setMaxLevels(int);
		~GearQuadTree();
	};

}