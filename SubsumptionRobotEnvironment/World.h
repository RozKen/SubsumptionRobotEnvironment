/******************************************************************************
@file main.cpp
@brief Declaration of Functions related to PhysX and OpenGL
- Test on Implentation of PhysX to Parallel Mimic System 
@author Kenichi Yorozu
@date 23th April 2011
******************************************************************************/

#ifndef SRE_World_World_H_
#define SRE_World_World_H_

#include <vector>		//Used for TumblingRobot Array
#include <iostream>		//Used for Console Message I/O
#include <string>		//Used for Console Window Closing Stopper
#include <GL/glut.h>	//Used for OpenGL (GLUT)

#include "Robot.h"		//Robots

#ifdef _WIN64
#pragma comment(lib, "glut64.lib")
#pragma comment(lib, "PhysXLoader64.lib")
#else //WIN32
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "PhysXLoader.lib")
#endif //WIN32

namespace SRE{
	namespace ExtendedSA{
		class Server;				//Prototype Declaration
	}
namespace World{

	#define FPS 20.0		///Frame Per Second
	#define DENSITY 0.5f	///Density of Mass Objects
	#define MASS 1.0f		///Default Mass
	class World{
	public:
		World(int argc, char **argv);
		/*
		 * for PhysX
		 */
		bool InitNx();
		static void CleanUpNx();
		bool InitScene();
		void CreateGroundPlane();
		//NxActor* CreateBox(float w, float d, float h,float xInit, float yInit, float zInit);
		//NxActor* CreateBox(NxVec3 dimensions, NxVec3 pos);
		//NxActor* CreateSphere(float r, float xInit, float yInit, float zInit);
		//NxActor* CreateSphere(float r, NxVec3 pos);
		//void CreateTumblingRobot(const NxVec3 pos);
		//void CreateSpringRobot(const NxVec3 pos);

		/*
		 * for OpenGL
		 */
		void InitGLUT(int argc, char ** argv);
		void MyGLInit();

		//Callback Functions must be 'static'
		static void KeyboardCallback(unsigned char key, int x, int y);
		static void ArrowKeyCallback(int key, int x, int y);
		static void MouseCallback(int button, int state, int x, int y);
		static void MotionCallback(int x, int y);
		static void RenderCallback();
		static void ReshapeCallback(int width, int height);
		static void IdleCallback();

		//Robots Object
		//struct TumblingRobots{
		//	NxActor *body;
		//	NxActor *leftArm;
		//	NxActor *rightArm;
		//};

		//struct SpringRobot{
		//	std::vector<NxActor *> vertices;
		//	NxVec3 centerOfMass;
		//};

		//OpenGL Utility Functions
		static void myGLBox(double x, double y, double z);
		static void myGLBox(NxVec3 dimensions);
		static void myGLCylinder(double radius, double height, int sides);

	//protected:
		//PhysX
		//To Handle these pointers at static Function (ClenUp), 
		//they need to be static members.
		static NxPhysicsSDK*		pPhysicsSDK;			///PhysX
		static NxScene*				pScene;					///Scene
		NxVec3						DefaultGravity;			///Gravity
		
		//OpenGL
		static NxVec3			gEye;//(50.0f, 50.0f, 50.0f);			///Camera Position
		static NxVec3			gDir;//(-1.0f,-1.0f,-1.0f);				///Camera Look At
		static NxVec3			gViewY;									//
		static int				gMouseX;	//=0						///X-position of Mouse Poiner
		static int				gMouseY;	//=0						///Y-Position of Mouse Pointer
		static unsigned char	gMouseButton[3];	//={0}					///Mouse Button State
		
		//Robots
		//std::vector<TumblingRobots> robots;					///Store Tumbling Robots
		//std::vector<SpringRobot>	spRobots;				///Store Spring Robots
		std::vector<SRE::Robot::Robot*>				robots;				///StoreRobots
		
		//Subsumption Architecture
		SRE::ExtendedSA::Server*	host;					///Server for Extended Subsumption Architecture
		
		//Flags
		static bool						isSimulate;				///Flag for Simulation
		//bool						isWalk;					///Flag for Walk
		//bool						isVibrate;				///Flag for Vibrate
		//bool						isShrink;				///Flag for Shrink

	};	//class World
}	//namespace World
}	//namespace SRE

#endif //SRE_World_World_H_