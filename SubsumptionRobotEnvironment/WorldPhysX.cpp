/**
 @file WorldPhysX.cpp
 @author - Kenichi Yorozu
 @description - PhysX Handling Code.
 - Test on Implentation of PhysX to Parallel Mimic System
 */

#include "World.h"
#include "ExtendedSA.h"

namespace SRE{
namespace World{
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
		 * CreateGroundPlane(): Create Ground Plane
		 * @return
		 */
	void World::CreateGroundPlane(){
		/*
		 *	Create Ground Plane
		 * Static Actor: has no 'NxBodyDesc'
		 */
		//actor Descriptor with Collection of Shapes.
		NxActorDesc	actorDesc;

		//Plane Shape Descriptor
		NxPlaneShapeDesc	planeDesc;
		//���ʕ�����: ax + by + cz + d = 0;
		planeDesc.normal = NxVec3(0, 1, 0);		//�ʂ̖@����Y��(��)����
		planeDesc.d = 0.0f;						//Y = 0.0f�ɖʂ����

		actorDesc.shapes.pushBack( &planeDesc );	//Actor��Plane��o�^
	
		//NxScene Creates Actor and Returns a Pointer.
		NxActor* pActor = pScene->createActor( actorDesc );
		pActor->userData = NULL;		//PhysX���Actor��(�Q�[���Ȃǂ�)�f�[�^���Actor�����т���
	
		//Set the parameters for the Default Material
		//Physics��"Material"�Ƃ͖ڂɌ�����\�ʍގ��ł͂Ȃ��C���̂̕����w�I������\��
		NxMaterial* defaultMaterial = pScene->getMaterialFromIndex( 0 );
		defaultMaterial->setRestitution( 0.3f );		//�����W��
		defaultMaterial->setStaticFriction( 0.5f );		//�Î~���C�W��
		defaultMaterial->setDynamicFriction( 0.5f );	//�����C�W��
	}
}	//namespace World
}	//namespace SRE