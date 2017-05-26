#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine()
{
}

bool PhysicsEngine::Run(HGE *hge, HTEXTURE &tex, World *gw, float speed)
{
	float dt = hge->Timer_GetDelta();
	float px = gw->ninja->x, py = gw->ninja->y;
	gw->ninja->body->GetBoundingBox(gw->ninja->x, gw->ninja->y, gw->box_ninja);

	//Update the Positions
	if (abs(gw->ninja->vx) > LOW_THRESHOLD) gw->ninja->x = max(min(SCREEN_WIDTH-SCREEN_PADX, gw->ninja->x + speed*gw->ninja->vx), SCREEN_PADX);
	if (abs(gw->ninja->vy) > LOW_THRESHOLD) gw->ninja->y = max(min(SCREEN_HEIGHT-SCREEN_PADY, gw->ninja->y + speed*gw->ninja->vy), SCREEN_PADY);

	//Updates Velocity
	gw->ninja->vx = min((gw->ninja->x - px), HIGH_THRESHOLD);
	gw->ninja->vy = min((gw->ninja->y - py), HIGH_THRESHOLD);
	if (gw->ninja->y ==	SCREEN_HEIGHT-SCREEN_PADY) {
		if (gw->ninja->vx > LOW_THRESHOLD)
			gw->ninja->vx = max(LOW_THRESHOLD, gw->ninja->vx - speed*0.05f);
		else if (gw->ninja->vx < -LOW_THRESHOLD)
			gw->ninja->vx = min(-LOW_THRESHOLD, gw->ninja->vx + speed*0.05f);
	}

	//Gravity on Human
	if (!gw->ninja->play_mode)	gw->ninja->vy += speed*0.1f;

	//Bullets Kinematics
	std::list<Bullet*>::iterator ite = gw->stars.begin();
	while (ite != gw->stars.end())
	{
		(*ite)->star->GetBoundingBox((*ite)->x, (*ite)->y, gw->box_star);
		//killed by enemies
		if ((*ite)->type != 1 && gw->box_ninja->Intersect(gw->box_star)) {
			if ((*ite)->type == BULLET_TYPE_3 && gw->ninja->play_mode)
				return true;
			else if (!gw->ninja->play_mode)
				return true;
		}
		(*ite)->x += speed*(*ite)->vx;
		(*ite)->y += speed*(*ite)->vy;
		(*ite)->vy += speed*0.01f;
		//Removing Bullets out of screen
		if ((*ite)->x > SCREEN_WIDTH+SCREEN_PADX || (*ite)->x < -SCREEN_PADX || (*ite)->y > SCREEN_HEIGHT)
			ite = gw->stars.erase(ite);
		else
			ite++;
	}

	//Adding enemies
	if (gw->enemy_factory->enemies.empty()) {
		gw->enemy_factory->level++;
		gw->enemy_factory->AddEnemy(hge, tex);
		gw->stars.clear();
	}

	//Kinematics of enimes
	for (std::list<Enemy*>::iterator ite = gw->enemy_factory->enemies.begin(); ite != gw->enemy_factory->enemies.end(); ite++) {
		if (abs((*ite)->vx) > LOW_THRESHOLD) (*ite)->x = max(min(SCREEN_WIDTH-SCREEN_PADX, (*ite)->x + speed*(*ite)->vx), SCREEN_PADX);
		if (abs((*ite)->vy) > LOW_THRESHOLD) (*ite)->y = max(min(SCREEN_HEIGHT-SCREEN_PADY, (*ite)->y + speed*(*ite)->vy), SCREEN_PADY);
	}
	hgeRect* box_enemy1 = new hgeRect();
	hgeRect* box_enemy2 = new hgeRect();

	//Collision resolvance
	for (std::list<Enemy*>::iterator ite = gw->enemy_factory->enemies.begin(); ite != gw->enemy_factory->enemies.end(); ite++) {
		std::list<Enemy*>::iterator ite2 = ite;
		(*ite)->body->GetBoundingBox((*ite)->x, (*ite)->y, box_enemy1);
		while (ite2 != gw->enemy_factory->enemies.end()) {
			(*ite2)->body->GetBoundingBox((*ite2)->x, (*ite2)->y, box_enemy2);
			if (box_enemy1->Intersect(box_enemy2)) {
				(*ite)->vx = ((*ite)->x > (*ite2)->x) ? abs((*ite)->vx) : -abs((*ite)->vx);
				(*ite2)->vx = ((*ite2)->x > (*ite)->x) ? abs((*ite2)->vx) : -abs((*ite2)->vx);

			}
			ite2++;
		}
	}

	// Killing enemies
	gw->enemy_factory->FrameFunc(hge, tex, gw->stars, speed, hge->Timer_GetDelta(), gw->ninja->x, gw->ninja->y);
	return false;
}

PhysicsEngine::~PhysicsEngine()
{
}
