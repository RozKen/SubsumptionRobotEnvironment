/*************************************************************************
 @file WorldPhysX.cpp
 @author - Kenichi Yorozu
 @description - PhysX Handling Code.
 - Test on Implentation of PhysX to Parallel Mimic System
 ***********************************************************************/

#include "World.h"
#include "ExtendedSA.h"

namespace SRE{
namespace World{
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
		/**
		 *	InitNx() : Initialize PhysX
		 *	@return bool - whether Physics SDK Initialization has done or not.
		 */
	bool World::InitNx()
	{
		bool initialized = false;
	#ifdef _DEBUG
		std::cout << "Physics SDK Loading Version: " << NX_PHYSICS_SDK_VERSION << std::endl;
	#endif //_DEBUG
		pPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
		if (pPhysicsSDK != NULL){
			pPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect("localhost", 5425);
	#ifdef _DEBUG
			std::cout << "PhysX Initialized" << std::endl;
	#endif //_DEBUG
			initialized = true;
		}else{
			std::cout<<"Initialize Error: Cannot Create Physics SDK"<<std::endl;
		}
		return initialized;
	}
		/**
		 *	InitScene() : Initialize Scene
		 * @return bool - whether Scene Initialization has done or not.
		 * @description - Initialize Scene.
		 */
	bool World::InitScene(){
		bool sceneInit = false;
		//Create Scene Descripter
		NxSceneDesc sceneDesc;
		sceneDesc.gravity = DefaultGravity;
		//Create Real Scene
		pScene = pPhysicsSDK->createScene(sceneDesc);
		if (pScene != NULL){
	#ifdef _DEBUG
			std::cout << "Scene Initialized" << std::endl;
	#endif //_DEBUG
			sceneInit = true;
		}
		return sceneInit;
	}
		/**
		 *	CleanUpNx() : Clean Up PhysX Objects
		 *	@description - Clean Up Memory.
		 */
	void World::CleanUpNx(){
		if(pPhysicsSDK != NULL){
			if( pScene != NULL ){
				pPhysicsSDK->releaseScene(*pScene);
				pScene = NULL;	//Release Scene Object
			}
			NxReleasePhysicsSDK( pPhysicsSDK );
			pPhysicsSDK = NULL;	//Release PhysicsSDK Object
		}
	#ifdef _DEBUG
			std::cout << "Clean Up Ended." << std::endl;
	#endif //_DEBUG
	}

		/**
		 * CreateSpringRobot(const NxVec3 pos)
		 * @param pos const NxVec3 Position Vector of this Robot
		 * @return void
		 */
	//void World::CreateSpringRobot(const NxVec3 pos){
	//	if(pScene == NULL) return;
	//	double size = 1.0;
	//	double x = size;
	//	double y = size;
	//	double z = size;
	//	int nbVertices = 8;
	//
	//	NxVec3 coord[] = {
	//		NxVec3( -x, -y, -z ),
	//		NxVec3(  x, -y, -z ),
	//		NxVec3(  x,  y, -z ),
	//		NxVec3( -x,  y, -z ),
	//		NxVec3( -x, -y,  z ),
	//		NxVec3(  x, -y,  z ),
	//		NxVec3(  x,  y,  z ),
	//		NxVec3( -x,  y,  z ),
	//		NxVec3( 0, 0, 0)
	//	};

	//	int adj[][4] = {
	//		{2, 4, 5, 7},
	//		{1, 6, 3, 8},
	//		{2, 7, 4, 5},
	//		{1, 3, 8, 6},
	//		{1, 8, 6, 3},
	//		{2, 5, 7, 4},
	//		{3, 6, 8, 1},
	//		{4, 7, 5, 2}
	//	};
	//	std::vector<NxActor*> vertices;
	//	NxActor * vertex;
	//	//各頂点に球を配置し，各頂点のNxActorをverticesに格納
	//	double size2 = size * 0.8f;
	//	for(int i = 0; i < nbVertices; i++){
	//		vertex = CreateBox(NxVec3(size2, size2, size2), coord[i] + pos);
	//		//CreateSphere(size*0.5f, pos.x + coord[i].x, pos.y + coord[i].y, pos.z + coord[i].z);
	//		vertex->setMass(1);
	//		vertices.push_back(vertex);
	//	}
	//	vertex = 	CreateSphere(size, pos.x, pos.y, pos.z);
	//	vertices.push_back(vertex);

	//	//ロボットを登録
	//	SpringRobot spRobot;
	//	spRobot.vertices = vertices;
	//	spRobot.centerOfMass = pos;
	//	spRobots.push_back(spRobot);
	//	//バネと距離ジョイントを定義
	//	NxSpringDesc spring;
	//	NxDistanceJointDesc distanceDesc;
	//	//バネの特性定義
	//	spring.spring = size *500;		//Young's Modulus
	//	spring.damper = 0.5;		//Damper Modulus

	//	//頂点間をばねで結ぶ(距離ジョイントで結ぶ)
	//	//全頂点間を結んでしまえ!!!!
	//	for(int i = 0; i < nbVertices+1; i++){
	//		for(int j = i + 1; j < nbVertices+1; j++){
	//			if(i != j){
	//				distanceDesc.setToDefault();

	//				distanceDesc.actor[0] = vertices[i];
	//				distanceDesc.actor[1] = vertices[j];

	//				//Set Orientation Vector for Elastic Force	//World Coordinates
	//				distanceDesc.setGlobalAxis( coord[i] - coord[j] );
	//				float distance = (coord[i] - coord[j]).magnitude();
	//				float multiply = 2.0f;
	//				distanceDesc.maxDistance =distance*multiply;
	//				distanceDesc.minDistance = distance*multiply;
	//				if( i == nbVertices || j == nbVertices ){
	//					distanceDesc.maxDistance =distance*multiply;//0.2f;
	//					distanceDesc.minDistance = distance*multiply;//0.2f;
	//				}
	//				distanceDesc.spring = spring;
	//				distanceDesc.flags = (NX_DJF_MIN_DISTANCE_ENABLED | NX_DJF_MAX_DISTANCE_ENABLED);
	//				//距離ジョイントの最大値制限と最小値制限を有効にする
	//				distanceDesc.flags |= NX_DJF_SPRING_ENABLED;		//ばね係数とダンパー係数による制限を有効にする
	//				distanceDesc.jointFlags |= NX_JF_COLLISION_ENABLED;	// 連結したアクター同士での衝突判定を有効にする

	//				pScene->createJoint(distanceDesc);
	//			}
	//		}
	//	}
	//	//ここ以下は，隣接頂点とだけ距離ジョイントで結ぶ場合
	//	//for(int i = 0; i < nbVertices; i++){
	//	//	for(int j = 0; j < 4; j++){
	//	//		distanceDesc.setToDefault();

	//	//		distanceDesc.actor[0] = vertices[i];
	//	//		distanceDesc.actor[1] = vertices[adj[i][j]-1];

	//	//		//Set Orientation Vector for Elastic Force	//World Coordinates
	//	//		distanceDesc.setGlobalAxis( coord[i] - coord[adj[i][j]-1] );

	//	//		distanceDesc.maxDistance = size * 2.0f*2.0f;
	//	//		distanceDesc.minDistance = size * 2.0f * 2.0f;
	//	//		if(j == 4){
	//	//			distanceDesc.maxDistance = size * 2.0f*2.0f;//1.7320508f;
	//	//			distanceDesc.minDistance = size * 2.0f*2.0f;//1.7320508f;
	//	//		}
	//	//		distanceDesc.spring = spring;
	//	//		distanceDesc.flags = (NX_DJF_MIN_DISTANCE_ENABLED | NX_DJF_MAX_DISTANCE_ENABLED);
	//	//		//距離ジョイントの最大値制限と最小値制限を有効にする
	//	//		distanceDesc.flags |= NX_DJF_SPRING_ENABLED;		//ばね係数とダンパー係数による制限を有効にする
	//	//		distanceDesc.jointFlags |= NX_JF_COLLISION_ENABLED;	// 連結したアクター同士での衝突判定を有効にする

	//	//		pScene->createJoint(distanceDesc);
	//	//	}
	//	//}

	//}

	//	/**
	//	 * CreateTumblingRobot(NxVec3 pos);
	//	 * @param pos const NxVec3 Position Vector of this Robot
	//	 * @return
	//	 */
	//void World::CreateTumblingRobot(const NxVec3 pos){
	//	if(pScene == NULL) return;
	//	//NxActor* body = CreateSphere(1.5f, pos);
	//	NxActor* body = CreateBox(NxVec3(1.5f, 1.5f, 1.5f), pos);
	//	//body->setMass(MASS * 2.0f);
	//	//body->setMass(15);
	//	NxVec3 armDim = NxVec3(0.5f, 3.0f, 0.15f);
	//	NxVec3 leftArmLocalPos = NxVec3(-2, 0, 0);
	//	NxVec3 rightArmLocalPos = NxVec3(2, 0, 0);
	//	NxQuat leftArmOrientation = NxQuat(-10, NxVec3(0, 1, 0));
	//	NxQuat rightArmOrientation = NxQuat(10, NxVec3(0, 1, 0));
	//	NxActor* leftArm = CreateBox(armDim, pos + leftArmLocalPos);
	//	NxActor* rightArm = CreateBox(armDim, pos + rightArmLocalPos);
	//	leftArm->setGlobalOrientationQuat(leftArmOrientation);
	//	//rightArm->setGlobalOrientationQuat(rightArmOrientation);
	//	//leftArm->setMass(MASS);
	//	rightArm->setMass(MASS);
	//	//Describe Revolute Joint
	//	NxRevoluteJointDesc revoluteDesc1;
	//	revoluteDesc1.setToDefault();
	//	revoluteDesc1.actor[0] = body;
	//	revoluteDesc1.actor[1] = leftArm;
	//	revoluteDesc1.setGlobalAnchor(pos + NxVec3(-2, 0, 0));
	//	revoluteDesc1.setGlobalAxis(NxMat33(leftArmOrientation) * NxVec3(1, 0, 0));
	//	NxJoint *joint1 = pScene->createJoint(revoluteDesc1);

	//	NxRevoluteJointDesc revoluteDesc2;
	//	revoluteDesc2.setToDefault();
	//	revoluteDesc2.actor[0] = body;
	//	revoluteDesc2.actor[1] = rightArm;
	//	revoluteDesc2.setGlobalAnchor(pos + NxVec3(2, 0, 0));
	//	revoluteDesc2.setGlobalAxis(NxMat33(rightArmOrientation) * NxVec3(1, 0, 0));
	//	NxJoint *join2 = pScene->createJoint(revoluteDesc2);
	//
	//	TumblingRobots robot;
	//	robot.body = body;
	//	robot.leftArm = leftArm;
	//	robot.rightArm = rightArm;
	//	robots.push_back(robot);
	//	return;
	//}
	//	/**
	//	 * CreateSphere(float r, float xInit, float yInit, float zInit)
	//	 * @param r: radius of the sphere
	//	 * @param xInit: Initial Position on X
	//	 * @param yInit: Initial Position on Y
	//	 * @param zInit: Initial Position on Z
	//	 * @return pActor: Pointer to Created Actor
	//	 */
	//NxActor* World::CreateSphere(float r, float xInit, float yInit, float zInit){
	//	NxActorDesc actorDesc;
	//	NxBodyDesc bodyDesc;
	//	NxSphereShapeDesc sphereDesc;

	//	//デフォルト値で初期化 (クリア)
	//	actorDesc.setToDefault();
	//	bodyDesc.setToDefault();
	//	sphereDesc.setToDefault();
	//	//bodyDesc.angularDamping = 0.5f;	//転がり摩擦係数

	//	sphereDesc.radius = r;									//球の半径を指定
	//	//sphereDesc.userData = (void *)(&sphereDesc);
	//	//sphereDesc.userData = (void *)(&sphereDesc.radius);
	//	actorDesc.shapes.pushBack(&sphereDesc);	//球をアクターに追加
	//	actorDesc.body = &bodyDesc;	//動的情報を指定
	//	actorDesc.density = DENSITY;//7874.0f;		//密度7874 kg/m^3 : 鉄の密度
	//	actorDesc.globalPose.t = NxVec3(xInit, yInit, zInit);	//Scene上の位置
	//	//Set userData to NULL if you are not doing anyting with it.
	//	NxActor*pActor = pScene->createActor( actorDesc );
	//	return pActor;
	//}

	//NxActor* World::CreateSphere(float r, NxVec3 pos){
	//	return CreateSphere(r, pos.x, pos.y, pos.z);
	//}
	//	/**
	//	 * CreateBox(float w, float d, float h,float xInit, float yInit, float zInit)
	//	 * @param w: width of the box
	//	 * @param d: depth of the box
	//	 * @param h: height of the box
	//	 * @param xInit: Initial Position on X
	//	 * @param yInit: Initial Position on Y
	//	 * @param zInit: Initial Position on Z
	//	 * @return pActor: Pointer to Created Actor
	//	 */
	//NxActor* World::CreateBox(float w, float d, float h,float xInit, float yInit, float zInit){
	//	/*
	//	 *	Create a Box Actor
	//	 * Dynamic Actor: Rigid Bodies
	//	 */
	//	//Create a Body Descriptor
	//	NxBodyDesc bodyDesc;					//Box用 Body Descriptor
	//
	//	//The Actor Descriptor
	//	NxActorDesc actorDesc;
	//
	//	//Box Shape Descriptor
	//	NxBoxShapeDesc boxDesc;

	//	//デフォルト値で初期化 (クリア)
	//	actorDesc.setToDefault();
	//	bodyDesc.setToDefault();
	//	boxDesc.setToDefault();

	//	//bodyDesc.angularDamping = 0.5f;	//回転減衰係数????
	//	//bodyDesc.linearVelocity = NxVec3 (-30, -10, -10); //初期速度はX軸方向に1
	//	bodyDesc.linearDamping = 0.1f;

	//	actorDesc.body = &bodyDesc;

	//	boxDesc.dimensions = NxVec3( w, d, h );	//20.0 x 20.0 x 20.0の直方体
	//	actorDesc.shapes.pushBack( &boxDesc );	//ActorにBodyを登録
	//	actorDesc.density = DENSITY;//7874.0f;	//密度7874 kg/m^3 　g/cm3 : 鉄の密度
	//	actorDesc.globalPose.t = NxVec3( xInit, yInit, zInit);		//初期位置(10.0, 10.0, 10.0)
	//
	//	//Set userData to NULL if you are not doing anyting with it.
	//	NxActor* pActor = pScene->createActor( actorDesc );
	//	return pActor;
	//}

	//NxActor* World::CreateBox(NxVec3 dimensions, NxVec3 pos){
	//	return CreateBox(dimensions.x, dimensions.y, dimensions.z,
	//		pos.x, pos.y, pos.z);
	//}
	//	/**
	//	 * CreateGroundPlane(): Create Ground Plane
	//	 * @return
	//	 */
	void World::CreateGroundPlane(){
		/*
		 *	Create Ground Plane
		 * Static Actor: has no 'NxBodyDesc'
		 */
		//actor Descriptor with Collection of Shapes.
		NxActorDesc	actorDesc;

		//Plane Shape Descriptor
		NxPlaneShapeDesc	planeDesc;
		//平面方程式: ax + by + cz + d = 0;
		planeDesc.normal = NxVec3(0, 1, 0);		//面の法線はY軸(↑)方向
		planeDesc.d = 0.0f;								//Y = 0.0fに面を作る

		actorDesc.shapes.pushBack( &planeDesc );	//ActorにPlaneを登録
	
		//NxScene Creates Actor and Returns a Pointer.
		NxActor* pActor = pScene->createActor( actorDesc);
		pActor->userData = NULL;		//PhysX上のActorと(ゲームなどの)データ上のActorを結びつける
	
		//Set the parameters for the Default Material
		//Physicsの"Material"とは目に見える表面材質ではなく，物体の物理学的特徴を表す
		NxMaterial* defaultMaterial = pScene->getMaterialFromIndex( 0 );
		defaultMaterial->setRestitution( 0.3f );		//反発係数
		defaultMaterial->setStaticFriction( 0.5f );		//静止摩擦係数
		defaultMaterial->setDynamicFriction( 0.5f );	//動摩擦係数
	}

}	//namespace World
}	//namespace SRE