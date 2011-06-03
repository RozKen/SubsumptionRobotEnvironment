#include "Part.h"
#include "Client.h"

namespace SRE{
namespace Robot{
		/**
		 * CreateSphere(float r, float xInit, float yInit, float zInit)
		 * @param r: radius of the sphere
		 * @param xInit: Initial Position on X
		 * @param yInit: Initial Position on Y
		 * @param zInit: Initial Position on Z
		 * @return pActor: Pointer to Created Actor
		 */
	NxActor* Part::CreateSphere(float r, float xInit, float yInit, float zInit){
		NxActorDesc actorDesc;
		NxBodyDesc bodyDesc;
		NxSphereShapeDesc sphereDesc;

		//デフォルト値で初期化 (クリア)
		actorDesc.setToDefault();
		bodyDesc.setToDefault();
		sphereDesc.setToDefault();
		//bodyDesc.angularDamping = 0.5f;	//転がり摩擦係数

		sphereDesc.radius = r;									//球の半径を指定
		//sphereDesc.userData = (void *)(&sphereDesc);
		//sphereDesc.userData = (void *)(&sphereDesc.radius);
		actorDesc.shapes.pushBack(&sphereDesc);	//球をアクターに追加
		actorDesc.body = &bodyDesc;	//動的情報を指定
		actorDesc.density = DENSITY;//7874.0f;		//密度7874 kg/m^3 : 鉄の密度
		actorDesc.globalPose.t = NxVec3(xInit, yInit, zInit);	//Scene上の位置
		//Set userData to NULL if you are not doing anyting with it.
		NxActor* pActor = pScene->createActor( actorDesc );
		return pActor;
	}

	NxActor* Part::CreateSphere(float r, NxVec3 pos){
		return CreateSphere(r, pos.x, pos.y, pos.z);
	}
		/**
		 * CreateBox(float w, float d, float h,float xInit, float yInit, float zInit)
		 * @param w: width of the box
		 * @param d: depth of the box
		 * @param h: height of the box
		 * @param xInit: Initial Position on X
		 * @param yInit: Initial Position on Y
		 * @param zInit: Initial Position on Z
		 * @return pActor: Pointer to Created Actor
		 */
	NxActor* Part::CreateBox(float w, float d, float h,float xInit, float yInit, float zInit){
		/*
		 *	Create a Box Actor
		 * Dynamic Actor: Rigid Bodies
		 */
		//Create a Body Descriptor
		NxBodyDesc bodyDesc;					//Box用 Body Descriptor
	
		//The Actor Descriptor
		NxActorDesc actorDesc;
	
		//Box Shape Descriptor
		NxBoxShapeDesc boxDesc;

		//デフォルト値で初期化 (クリア)
		actorDesc.setToDefault();
		bodyDesc.setToDefault();
		boxDesc.setToDefault();

		//bodyDesc.angularDamping = 0.5f;	//回転減衰係数????
		//bodyDesc.linearVelocity = NxVec3 (-30, -10, -10); //初期速度はX軸方向に1
		bodyDesc.linearDamping = 0.1f;

		actorDesc.body = &bodyDesc;

		boxDesc.dimensions = NxVec3( w, d, h );	//20.0 x 20.0 x 20.0の直方体
		actorDesc.shapes.pushBack( &boxDesc );	//ActorにBodyを登録
		actorDesc.density = DENSITY;//7874.0f;	//密度7874 kg/m^3 　g/cm3 : 鉄の密度
		actorDesc.globalPose.t = NxVec3( xInit, yInit, zInit);		//初期位置(10.0, 10.0, 10.0)
	
		//Set userData to NULL if you are not doing anyting with it.
		NxActor* pActor = pScene->createActor( actorDesc );
		return pActor;
	}

	NxActor* Part::CreateBox(NxVec3 dimensions, NxVec3 pos){
		return CreateBox(dimensions.x, dimensions.y, dimensions.z,
			pos.x, pos.y, pos.z);
	}

	/**
	 @fn Part::update
	 @brief Partの力学的状態をコントロールする
	 */
	void Part::update(){
		if(client == NULL){	//clientが指定されていないPartの場合は，無視する
			return;
		}

		//Specify process according to the state.
		switch(client->getState()){
		case client->state1:
		case client->state2:
		case client->state3:
		default:
			break;
		}
		return;
	}
}
}