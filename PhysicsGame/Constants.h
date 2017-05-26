#include "GearEngine.h"


/*SCREEN SETTINGS*/
#define SCREEN_PADX			20
#define SCREEN_PADY			40
/*PHYSICS*/
//Objects
#define	PLAYER				2
#define	FOE					3
#define BULLET				4
#define WALL				5
#define GROUND				6
//Velocity Threshold
#define	VELOCITY_LOW		10.0f
/*PLAYER*/
//Player movement
#define PLAYER_SENSITIVITY	6.0f	//Input sensitivity
#define PLAYER_FLY			3.0f	//Input sensitivity
#define PLAYER_FLYX			100.0f	//Fly speed limit
#define PLAYER_FLYY			100.0f	//Fly speed limit
#define PLAYER_JUMP			200.0f	//JUMP Velocity
#define PLAYER_FRICTION		3.0f	//Friction on grounded player
#define PLAYER_SPEEDX		100.0f	//Max X Velocity
#define PLAYER_SPEEDY		200.0f	//Max Y Velocity
#define PLAYER_RECOIL		0.1f	//Recoil	
#define PLAYER_HEALTH		100				
#define PLAYER_INVMASS		1
/*ENEMY*/
//Enemy Max velocity
#define FOE_SPEEDX			200
#define FOE_SPEEDY			200
#define FOE_HEALTH			100
#define FOE_INVMASS			1
/*BULLETS*/
//Bullet types
#define BULLET_TYPE_1		1		//Ninja stars
#define BULLET_TYPE_2		2		//Enemies stars
#define BULLET_TYPE_3		3		//Enimes Fireball
#define	BULLET_INVMASS		10		//Inverse mass of the bullet
#define BULLET_E			1.0f	//Restitution of the Bullets		
#define BULLET_SPEED		0.5f	//Factor to control speed
#define BULLET_DAMAGE		20	

#pragma once
