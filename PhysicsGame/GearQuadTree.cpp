#include "GearQuadTree.h"
using namespace Gear;


void Gear::GearQuadTree::split()
{
	float centerx_ = (x_min + x_max) / 2;
	float centery_ = (y_min + y_max) / 2;
	nodes[0] = new GearQuadTree(level_ + 1, centerx_, centery_, x_max, y_max);
	nodes[1] = new GearQuadTree(level_ + 1, centerx_, y_min, x_max, centery_);
	nodes[2] = new GearQuadTree(level_ + 1, x_min, y_min, centerx_, centery_);
	nodes[3] = new GearQuadTree(level_ + 1, x_min, centery_, centerx_, y_max);
}


int Gear::GearQuadTree::getIndex(GearPhysicsBody &body)
{	
	if (nodes[0]->isInside(body))
		return 0;
	else if (nodes[1]->isInside(body))
		return 1;
	else if (nodes[2]->isInside(body))
		return 2;
	else if (nodes[3]->isInside(body))
		return 3;
	else
		return -1;
}

bool Gear::GearQuadTree::isInside(GearPhysicsBody &body)
{	
	if ((body.x + (body.width / 2)) <= x_max && (body.x - (body.width / 2)) >= x_min && (body.y + (body.width / 2)) <= y_max && (body.y + (body.width / 2)) >= y_min)
		return true;
	return false;
}

GearQuadTree::GearQuadTree()
{
}

Gear::GearQuadTree::GearQuadTree(int level, float xmin, float ymin, float xmax, float ymax)
{
	level_ = level;		x_min = xmin;	y_min = ymin;	x_max = xmax;	y_max = ymax;
}

void Gear::GearQuadTree::clear()
{
	for (size_t i = 0; i < 4; i++) {
		delete nodes[i]; nodes[i] = NULL;
	}
	objects.clear();
}

void Gear::GearQuadTree::insert(GearPhysicsBody * body)
{
	if (nodes[0] != NULL) {
		int inx = getIndex(*body);
		if (inx != -1) {
			nodes[inx]->insert(body);
			return;
		}
	}

	objects.push_back(body);

	if (objects.size() > max_objects && nodes[0] == NULL) {
		split();
		int end = objects.size() - 1, ite = 0;
		while (ite <= end) {
			int inx = getIndex(*objects[ite]);
			if (inx != -1) {
				nodes[inx]->insert(objects[ite]);
				GearPhysicsBody * temp = objects[ite]; objects[ite] = objects[end]; objects[end] = temp;
				--end;
			}
			else
				++ite;
		}
		while (objects.size() != end + 1)
			objects.pop_back();
	}
}

void Gear::GearQuadTree::setMaxObjects(int obj)
{
	max_objects = obj;
}

void Gear::GearQuadTree::setMaxLevels(int lvl)
{
	level_ = lvl;
}


GearQuadTree::~GearQuadTree()
{
	for (size_t i = 0; i < 4; i++)
		delete nodes[i];

}
