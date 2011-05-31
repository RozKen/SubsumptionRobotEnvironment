/**
	@file SRE_test_main.cpp
	@brief Test Program of Subsumption Robot Environment
	@author Kenichi Yorozu
	@ 30th May 2011
 */

//#include "TumblingRobot.h"
#include "World.h"

using namespace std;
using namespace SRE;


//Declaration and Initialization of static member variables of class World
NxPhysicsSDK* World::World::pPhysicsSDK = NULL;
NxScene* World::World::pScene = NULL;
bool World::World::isSimulate = false;
NxVec3 World::World::gEye = NxVec3(50.0f, 50.0f, 50.0f);
NxVec3 World::World::gDir = NxVec3(-1.0f, -1.0f, -1.0f);
NxVec3 World::World::gViewY = NxVec3();
int World::World::gMouseX = 0;
int World::World::gMouseY = 0;
unsigned char World::World::gMouseButton[3] = {0};

void main (int argc, char **argv){
	World::World* world = new World::World(argc, argv);
	
	glutMainLoop();
}