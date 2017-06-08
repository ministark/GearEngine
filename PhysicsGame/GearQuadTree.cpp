#include "GearQuadTree.h"
using namespace Gear;


void Gear::GearQuadTree::split()
{
	GearVector center = (_min + _max)*(0.5);
	nodes[0] = new GearQuadTree(level_ + 1, center, _max);
	nodes[1] = new GearQuadTree(level_ + 1, GearVector(center._x, _min._y), GearVector(_max._x, center._y) );
	nodes[2] = new GearQuadTree(level_ + 1, _min, center);
	nodes[3] = new GearQuadTree(level_ + 1,GearVector( _min._x, center._y), GearVector(center._x, _max._y) );
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
	if ((body._pos._x + (body.width / 2)) <= _max._x && (body._pos._x - (body.width / 2)) >= _min._x && (body._pos._y + (body.width / 2)) <= _max._y && (body._pos._y + (body.width / 2)) >= _min._y)
		return true;
	return false;
}

GearQuadTree::GearQuadTree()
{
}

Gear::GearQuadTree::GearQuadTree(int level, const GearVector &vec1, const GearVector &vec2)
{
	level_ = level; _min = vec1; _max = vec2;
}

void Gear::GearQuadTree::clear()
{
	for (size_t i = 0; i < 4; ++i) {
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

std::vector<GearPhysicsBody*> Gear::GearQuadTree::solve()
{	
	std::vector<GearPhysicsBody*> scope;
	if (nodes[0] != NULL) {
		for (size_t i = 0; i < 4; i++) {
			std::vector<GearPhysicsBody*> temp = nodes[i]->solve();
			scope.insert(scope.end(), temp.begin(), temp.end());
		}
	}
	scope.insert(scope.end(), objects.begin(), objects.end());
	
	for (auto ite = objects.begin(); ite != objects.end(); ++ite) {
		for (auto nite = scope.begin(); nite != scope.end(); ++nite) {
			if ((*ite) != (*nite)) {
				if ((*ite)->state == PHYSICS_AWAKE || (*nite)->state == PHYSICS_AWAKE) {
					float normal = (*ite)->Collide((*nite));
					float min_e = min((*ite)->e, (*nite)->e);
					GearVector impulse = ((*nite)->_vel - (*ite)->_vel)*((1.0f + min_e) / ((*nite)->invmass + (*ite)->invmass));
					
					if (normal != 0 && ((*nite)->_vel - (*ite)->_vel)*((*nite)->_pos - (*ite)->_pos) <= 0) {

					}

					////Resolve the collisions
					//if (normal > 0 && ((*nite)->vx - (*ite)->vx)*((*nite)->x - (*ite)->x) <= 0) {
					//	float j = (1.0f + min_e) * ((*nite)->vx - (*ite)->vx); j /= (*nite)->invmass + (*ite)->invmass;
					//	(*ite)->vx += j*(*ite)->invmass; (*nite)->vx += (-j)*(*nite)->invmass;
					//	float corr = max(normal - PHYSICS_SLOP, 0.0f)*PHYSICS_PEN / ((*nite)->invmass + (*ite)->invmass);
					//	if ((*ite)->state == PHYSICS_AWAKE) ((*ite)->x) += (((*ite)->x - (*nite)->x) > 0) ? (*ite)->invmass*corr : -(*ite)->invmass*corr;
					//	if ((*nite)->state == PHYSICS_AWAKE) ((*nite)->x) += (((*nite)->x - (*ite)->x) > 0) ? (*nite)->invmass*corr : -(*nite)->invmass*corr;
					//	if ((*ite)->OnCollision != 0)	 (*ite)->OnCollision((void*)(*ite), (void*)(*nite));
					//	if ((*nite)->OnCollision != 0)	(*nite)->OnCollision((void*)(*nite), (void*)(*ite));
					//}
					//else if (normal < 0 && ((*nite)->vy - (*ite)->vy)*((*nite)->y - (*ite)->y) <= 0) {
					//	float j = (1.0f + min_e) * ((*nite)->vy - (*ite)->vy); j /= (*nite)->invmass + (*ite)->invmass;
					//	(*ite)->vy += j*(*ite)->invmass; (*nite)->vy += (-j)*(*nite)->invmass;
					//	float corr = max(-normal - PHYSICS_SLOP, 0.0f)*PHYSICS_PEN / ((*nite)->invmass + (*ite)->invmass);
					//	if ((*ite)->state == PHYSICS_AWAKE) ((*ite)->y) += (((*ite)->y - (*nite)->y) > 0) ? (*ite)->invmass*corr : -(*ite)->invmass*corr;
					//	if ((*nite)->state == PHYSICS_AWAKE) ((*nite)->y) += (((*nite)->y - (*ite)->y) > 0) ? (*nite)->invmass*corr : -(*nite)->invmass*corr;
					//	if ((*ite)->OnCollision != 0)	(*ite)->OnCollision((void*)(*ite), (void*)(*nite));
					//	if ((*nite)->OnCollision != 0)(*nite)->OnCollision((void*)(*nite), (void*)(*ite));
					//}
				}
			}
		}
	}
	return scope;
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
	for (size_t i = 0; i < 4; ++i)
		delete nodes[i];

}
