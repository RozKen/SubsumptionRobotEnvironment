/******************************************************************************
@file main.cpp
@brief Declaration of Functions related to PhysX and OpenGL
- Test on Implentation of PhysX to Parallel Mimic System 
@author Kenichi Yorozu
@date 23th April 2011
******************************************************************************/

#ifndef SRE_World_World_H_
#define SRE_World_World_H_

//#include <vector>		//Used for TumblingRobot Array
#include <iostream>		//Used for Console Message I/O
#include <string>		//Used for Console Window Closing Stopper

#include "Robot.h"		//Robots

#include <GL/glut.h>	//Used for OpenGL (GLUT)

#ifdef _WIN64
#pragma comment(lib, "glut64.lib")
#pragma comment(lib, "PhysXLoader64.lib")
#else //WIN32
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "PhysXLoader.lib")
#endif //WIN32

#define FPS 20.0		///Frame Per Second

namespace SRE{
	namespace ExtendedSA{
		class Server;				//Prototype Declaration
	}
namespace World{
	class World{
	public:
		World(int argc, char **argv);	//Constructor
		void InitWorld();
		/*
		 * for PhysX
		 */
		bool InitNx();
		static void CleanUpNx();
		bool InitScene();

		void CreateGroundPlane();
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

		//Utility Functions for OpenGL
		static void myGLBox(double x, double y, double z);
		static void myGLBox(NxVec3 dimensions);
		static void myGLCylinder(double radius, double height, int sides);

		//Getters and Setters
		NxPhysicsSDK*	getPhysicsSDK();
		NxScene*		getScene();
		NxVec3			getGravity();

		void			addRobot(SRE::Robot::Robot* robot);

		bool			getIsSimulate();
		void			setIsSimulate(bool flag);
		void			switchIsSimulate();

	protected:
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
			
		//Flags
		static bool						isSimulate;				///Flag for Simulation
		//bool						isWalk;					///Flag for Walk
		//bool						isVibrate;				///Flag for Vibrate
		//bool						isShrink;				///Flag for Shrink

		//Robots
		//std::vector<TumblingRobots> robots;					///Store Tumbling Robots
		//std::vector<SpringRobot>	spRobots;				///Store Spring Robots
		std::vector<SRE::Robot::Robot*>				robots;				///StoreRobots
		
		//Subsumption Architecture
		SRE::ExtendedSA::Server*	host;					///Server for Extended Subsumption Architecture

	};	//class World

	inline NxPhysicsSDK*	World::getPhysicsSDK(){
		return pPhysicsSDK;
	}

	inline NxScene*		World::getScene(){
		return pScene;
	}
	inline NxVec3		World::getGravity(){
		return DefaultGravity;
	}

	inline void			World::addRobot(SRE::Robot::Robot* robot){
		robots.push_back(robot);
	}

	inline bool			World::getIsSimulate(){
		return isSimulate;
	}
	inline void			World::setIsSimulate(bool flag){
		isSimulate = flag;
		return;
	}
	inline void			World::switchIsSimulate(){
		isSimulate = !isSimulate;
		return;
	}

}	//namespace World
}	//namespace SRE

#endif //SRE_World_World_H_