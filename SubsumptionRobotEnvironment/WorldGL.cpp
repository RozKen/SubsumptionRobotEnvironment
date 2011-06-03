/*************************************************************************
 @file WorldGL.cpp
 @author - Kenichi Yorozu
 @description - OpenGL Handling Code. 
  - Test on Implentation of PhysX to Parallel Mimic System
 ***********************************************************************/

#include <cstdlib>			//for Random
#include <time.h>			//for Random

#include "ExtendedSA.h"		//Using Server class
#include "World.h"			//Class Declaration
#include "TumblingRobot.h"	//Using TumblingRobot


namespace SRE{
namespace World{
	World::World(int argc, char **argv) : DefaultGravity(0, -9.8, 0){
		host = new SRE::ExtendedSA::Server();
		InitGLUT(argc, argv);
		InitNx();
		InitScene();
		CreateGroundPlane();
		//glutMainLoop();		//これやるとConstructorから抜け出せない…
	}

	/**
	 * InitGLUT(int argc, char ** argv) : Initialize GLUT
	 * @param argc : Number of Inputs to Main Function
	 * @param argv : Each Command of inputs to the Function
	 * @return
	 */
	void World::InitGLUT(int argc, char ** argv){
		glutInit(&argc, argv);
		glutInitWindowSize(640, 480);
		glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
		int mainHandle = glutCreateWindow("Subsumption Robot Environment");
		glutSetWindow(mainHandle);
		glutDisplayFunc(RenderCallback);
		glutReshapeFunc(SRE::World::World::ReshapeCallback);
		glutIdleFunc(SRE::World::World::IdleCallback);
		glutKeyboardFunc(SRE::World::World::KeyboardCallback);
		glutSpecialFunc(SRE::World::World::ArrowKeyCallback);
		glutMouseFunc(SRE::World::World::MouseCallback);
		glutMotionFunc(SRE::World::World::MotionCallback);
		MotionCallback(0,0);
		MyGLInit();
		atexit(SRE::World::World::CleanUpNx);
		return;
	}
	void World::MyGLInit(){
		// Setup default render states
		glClearColor(0.3f, 0.4f, 0.5f, 1.0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);

		// Setup lighting
		glEnable(GL_LIGHTING);
		float ambientColor[]	= { 0.1f, 0.1f, 0.1f, 0.0f };
		float diffuseColor[]	= { 1.0f, 1.0f, 1.0f, 0.0f };		
		float specularColor[]	= { 0.0f, 0.0f, 0.0f, 0.0f };		
		float position[]		= { 100.0f, 100.0f, 400.0f, 1.0f };		
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glEnable(GL_LIGHT0);
	
		glClearColor(0.3, 0.3, 0.3, 1.0);		//背景色を設定

		srand((unsigned) time (NULL));		//Random Seedを設定
	}


	void World::KeyboardCallback(unsigned char key, int x, int y)
	{
		//int n = robots.size();
		SRE::Robot::Robot* newRobot = NULL;
		switch(key)
		{
			case 27:			//ESCキーが押されたら
				exit(0);			//プログラムを終了する
				break;
			case 32:			//Spaceキーが押されたら
				isSimulate = !isSimulate;		//Simulate状態をON/OFFする
				break;
			case 's':
				//CreateSphere(2.5f, 0, 3, 2.5f);
				break;
			case 'b':
				//CreateBox(2.5f, 2.5f, 2.5f, 2.5f, 2.5f, -10);
				break;
			case 'f':
				//CreateGroundPlane();
				break;
			case 't':
				//CreateTumblingRobot(NxVec3(-20, 30, -20));
				//TumblingRobot* robot = new TumblingRobot(pScene, NxVec3(0, 0, 0));
				newRobot = new TumblingRobot(pScene, host, NxVec3(0, 10, 0));
				//TODO : register to World
				//robots->push_back(robot);
				break;
			case 'p':
				//CreateSpringRobot(NxVec3(0, 50, 0));
				break;
			//////////Parameter調整中///////////////////
			case '0':
				for(int i = 0; i < robots.size(); i++){
					robots[i]->getClients()[0]->setState(0);		//Set WalkControl to Null;
				}
				//walk->Reset();
				break;
			case '1':
				for(int i = 0; i < robots.size(); i++){
					robots[i]->getClients()[0]->setState(1);		//Set WalkControl to Sotp;
				}
				//walk->setMessage(1);
				break;
			case '2':
				for(int i = 0; i < robots.size(); i++){
					robots[i]->getClients()[0]->setState(2);		//Set WalkControl to Walk;
				}
				//walk->setMessage(2);
			case 'w':
				//isWalk = !isWalk;
				break;
			case 'v':
				//isVibrate = !isVibrate;
				break;
			case 'h':
				//isShrink = !isShrink;
				break;
		}
		if(newRobot != NULL){
			robots.push_back(newRobot);
		}
	}

	void World::ArrowKeyCallback(int key, int x, int y)
	{
		KeyboardCallback(key,x,y);
	}

	void World::MouseCallback(int button, int state, int x, int y)
	{
		gMouseX = x;
		gMouseY = y;
		switch(button){
			case GLUT_LEFT_BUTTON:
				gMouseButton[0] = ((GLUT_DOWN==state)?1:0);
				break;
			case GLUT_MIDDLE_BUTTON:
				gMouseButton[1] = ((GLUT_DOWN==state)?1:0);
				break;
			case GLUT_RIGHT_BUTTON:
				gMouseButton[2] = ((GLUT_DOWN==state)?1:0);
				break;
			default:
				break;
		}
		glutPostRedisplay();
	}

	void World::MotionCallback(int x, int y)
	{
		int dx = gMouseX - x;
		int dy = gMouseY - y;
	
		gDir.normalize();		//カメラの視線ベクトルを正規化
		gViewY.cross(gDir, NxVec3(0,1,0));	//

		if( gMouseButton[0] && gMouseButton[1] ){
			//Zoom: Left + Center Buttons Drag
			gEye -= gDir * 0.5f * dy;
		}else{
			if( gMouseButton[0] ){
				//Rotate: Left Button Drag
				NxQuat qx(NxPiF32 * dx * 10/ 180.0f, NxVec3(0,1,0));
				qx.rotate(gDir);
				NxQuat qy(NxPiF32 * dy * 10/ 180.0f, gViewY);
				qy.rotate(gDir);
			}else if( gMouseButton[1] ){
				//Move: Center Button Drag
				gEye += 0.1f * (gViewY * dx - NxVec3(0, 1, 0) * dy);
			}
		}
		gMouseX = x;
		gMouseY = y;
		glutPostRedisplay();
	}
	//static time_t t = time(NULL);
	void World::RenderCallback()
	{
		if(pScene == NULL){
	#ifdef _DEBUG
			std::cout << "pScene == NULL" << std::endl;
	#endif //_DEBUG
			return;
		}
	
		// Start simulation
		if (isSimulate){
			pScene->simulate(1.0f/FPS);	//time(NULL) - t);
			host->Run();
			for(int i = 0; i < robots.size(); i++){
				SRE::Robot::Robot* robot = robots[i];
				for(int j = 0; j < robot->getParts().size(); j++){
					robot->getParts()[j]->update();
				}
			}
			//t = time(NULL);
		}
	
		// Clear buffers
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// Setup projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH)/(float)glutGet(GLUT_WINDOW_HEIGHT), 1.0f, 10000.0f);
		gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + gDir.x, gEye.y + gDir.y, gEye.z + gDir.z, 0.0f, 1.0f, 0.0f);

		// Setup modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Render all actors
		int nbActor = pScene->getNbActors();
		NxActor** actors = pScene->getActors();
		for(int nbActors = 0; nbActors < nbActor; nbActors++)
		{
			NxActor* actor = *actors++;
			if(actor->userData == NULL){
				// draw grid
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glDisable(GL_LIGHTING);
				glBegin(GL_LINES);
					int y = 0;
					for(int i=-10;i<=10;++i) {
						glVertex3f(i*10,y,-100);
						glVertex3f(i*10,y,100);

						glVertex3f(100,y,i*10);
						glVertex3f(-100,y,i*10);
					}
				glEnd();
				glEnable(GL_LIGHTING);
			}
			int nbShapes = actor->getNbShapes();
			NxShape* const* shapes = actor->getShapes();
			while(nbShapes--){
				NxShape* shape = shapes[nbShapes];
				switch(shape->getType()){
					float glMat[16];
					float glMat2[16];
					case NX_SHAPE_BOX:
						// Render actor
						glPushMatrix();
						{				
							actor->getGlobalPose().getColumnMajor44(glMat);
							glMultMatrixf(glMat);
							shape->getLocalPose().getColumnMajor44(glMat2);
							glMultMatrixf(glMat2);
							glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
							if(shape->isBox()->getDimensions()[0] == 0.8f){
								glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
							}else if(shape->isBox()->getDimensions()[0] == 2.5f){
								switch((nbActors)%9){
								case 0:
									glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
									break;
								case 1:
									glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 2:
									glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
									break;
								case 3:
									glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 4:
									glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
									break;
								case 5:
									glColor4f(0.5f, 0.0f, 1.0f, 1.0f);
									break;
								case 6:
									glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
									break;
								case 7:
									glColor4f(0.5f, 1.0f, 0.5f, 1.0f);
									break;
								case 8:
									glColor4f(1.0f, 0.5f, 1.0f, 1.0f);
									break;

								default:
									glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
									break;
								}
							}else if(shape->isBox()->getDimensions()[0] == 1.5f){
								switch(((nbActors)/3%9)/3){
									case 0:
										glColor4f(1.0f, 0.25f, 0.0f, 1.0f);
										break;
									case 1:
										glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
										break;
									case 2:
										glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
										break;
									case 3:
										glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
										break;
									case 4:
										glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
										break;
									case 5:
										glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
										break;
									default:
										glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
										break;
								}
							}
							myGLBox(shape->isBox()->getDimensions());
						}
						glPopMatrix();

						// Render shadow
						glPushMatrix();
						{
							const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
							glMultMatrixf(shadowMat);
							glMultMatrixf(glMat);
							glMultMatrixf(glMat2);
							glDisable(GL_LIGHTING);
							glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
							myGLBox(shape->isBox()->getDimensions());
							glEnable(GL_LIGHTING);
						}
						glPopMatrix();
						break;
					case NX_SHAPE_SPHERE:
						// Render actor
						glPushMatrix();
						{
							actor->getGlobalPose().getColumnMajor44(glMat);
							glMultMatrixf(glMat);
							shape->getLocalPose().getColumnMajor44(glMat2);
							glMultMatrixf(glMat2);
							glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
							if((GLdouble)((shape->isSphere())->getRadius()) == 1.0f){
								glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
							}else if((GLdouble)((shape->isSphere())->getRadius()) == 2.5f){
								switch((nbActors)%9){
								case 0:
									glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
									break;
								case 1:
									glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 2:
									glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
									break;
								case 3:
									glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 4:
									glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
									break;
								case 5:
									glColor4f(0.5f, 0.0f, 1.0f, 1.0f);
									break;
								case 6:
									glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
									break;
								case 7:
									glColor4f(0.5f, 1.0f, 0.5f, 1.0f);
									break;
								case 8:
									glColor4f(1.0f, 0.5f, 1.0f, 1.0f);
									break;

								default:
									glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
									break;
								}
							}else if((GLdouble)((shape->isSphere())->getRadius()) == 1.5f){
									switch(((nbActors)/3%9)/3){
									case 0:
										glColor4f(0.2f, 0.7f, 0.5f, 1.0f);
										break;
									case 1:
										glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
										break;
									case 2:
										glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
										break;
									case 3:
										glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
										break;
									case 4:
										glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
										break;
									case 5:
										glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
										break;
									default:
										glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
										break;
								}
							}
							/*switch(((nbActors)/3%9)/3){
								case 0:
									glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
									break;
								case 1:
									glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 2:
									glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
									break;
								case 3:
									glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
									break;
								case 4:
									glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
									break;
								case 5:
									glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
									break;
								default:
									glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
									break;
							}*/
							glutSolidSphere((GLdouble)((shape->isSphere())->getRadius()),16, 16);
						}
						glPopMatrix();

						// Render shadow
						glPushMatrix();
						{
							const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
							glMultMatrixf(shadowMat);
							glMultMatrixf(glMat);
							glMultMatrixf(glMat2);
							glDisable(GL_LIGHTING);
							glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
							glutSolidSphere((GLdouble)((shape->isSphere())->getRadius()),16, 16);
							glEnable(GL_LIGHTING);
						}
						glPopMatrix();
						break;
					default:
						break;
				}
			}
		}

		// Acquire simulation results
		if(isSimulate){
			pScene->flushStream();
			pScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}

		glutSwapBuffers();
	}

	void World::ReshapeCallback(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void World::IdleCallback()
	{
		glutPostRedisplay();
	}

	/**
	 * My Primitive Shapes for Open GL Presentation
	 */

	/**
	 * myGLBox : Draw Box (not only cube)
	 * @param x : Box Size (x-Axis)
	 * @param y : Box Size (y-Axis)
	 * @param z : Box Size (z-Axis)
	 * @return void
	 */
	void World::myGLBox(double x, double y, double z){
		GLdouble vertex[][3] = {
			{ -x, -y, -z },
			{  x, -y, -z },
			{  x,  y, -z },
			{ -x,  y, -z },
			{ -x, -y,  z },
			{  x, -y,  z },
			{  x,  y,  z },
			{ -x,  y,  z }
		};

		const static int face[][4] = {
			{ 0, 1, 2, 3 },
			{ 1, 5, 6, 2 },
			{ 5, 4, 7, 6 },
			{ 4, 0, 3, 7 },
			{ 4, 5, 1, 0 },
			{ 3, 2, 6, 7 }
		};

		const static GLdouble normal[][3] = {
			{ 0.0, 0.0,-1.0 },
			{ 1.0, 0.0, 0.0 },
			{ 0.0, 0.0, 1.0 },
			{-1.0, 0.0, 0.0 },
			{ 0.0,-1.0, 0.0 },
			{ 0.0, 1.0, 0.0 }
		};
		int i, j;
		glBegin(GL_QUADS);
			for (j = 0; j < 6; ++j) {
				glNormal3dv(normal[j]);
				for (i = 4; --i >= 0;) {
					glVertex3dv(vertex[face[j][i]]);
				}
			}
		glEnd();
	}
	//void myGLBox(myDimension3* dimensions){
	//	myGLBox((double)dimensions->x, (double)dimensions->y, (double)dimensions->z);
	//	return;
	//}
	void World::myGLBox(NxVec3 dimensions){
		myGLBox((double)dimensions.x, (double)dimensions.y, (double) dimensions.z);
		return;
	}
	/**
	 * myGLCylinder : Draw Cylinder
	 * @param radius : Cylinder Radius
	 * @param height : Cylinder Height
	 * @param sides : Number of Divisions of Sides
	 * @return void
	 */
	void World::myGLCylinder(double radius, double height, int sides){
		double step = 6.28318530717958647692 / (double)sides;
		int i = 0;
		/* 上面 */
		glNormal3d(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
			while (i < sides) {
				double t = step * (double)i++;
				glVertex3d(radius * sin(t), height, radius * cos(t));
			}
		glEnd();

		/* 底面 */
		glNormal3d(0.0, -1.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
			while (--i >= 0) {
				double t = step * (double)i;
				glVertex3d(radius * sin(t), -height, radius * cos(t));
			}
		glEnd();

		/* 側面 */
		glBegin(GL_QUAD_STRIP);
			while (i <= sides) {
				double t = step * (double)i++;
				double x = sin(t);
				double z = cos(t);

				glNormal3d(x, 0.0, z);
				glVertex3f(radius * x, height, radius * z);
				glVertex3f(radius * x, -height, radius * z);
			}
		glEnd();
	}

}	//namespace World
}	//namespace SRE