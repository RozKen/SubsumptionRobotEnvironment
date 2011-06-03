#ifndef SRE_Robot_Part_H_
#define SRE_Robot_Part_H_

#include <vector>
#include <NxPhysics.h>			//Used for PhysX Variables

#define DENSITY 0.5f	///Density of Mass Objects
#define MASS 1.0f		///Default Mass

namespace SRE{
	namespace ExtendedSA{
		class Client;			//Prototype Declaration
	}
namespace Robot{
	/**
	  Interface Class of Parts of Robots.
	  @author Kenichi Yorozu
	  @date 30 May 2011
	 */
	class Part{
	public:
		Part(NxScene* scene, NxVec3 robotPosition);			///Constructor
		//virtual ~Part();		///Destructor
		virtual void update();

		//Utility Functions for PhysX
		NxActor* CreateBox(float w, float d, float h,float xInit, float yInit, float zInit);
		NxActor* CreateBox(NxVec3 dimensions, NxVec3 pos);
		NxActor* CreateSphere(float r, float xInit, float yInit, float zInit);
		NxActor* CreateSphere(float r, NxVec3 pos);

		//Getters and Setters
		NxActor*	getActor();
		void		setActor(NxActor* actor);
		NxShape*	getShape();
		void		setShape(NxShape* shape);
		NxVec3		getLocalPosition();
		void		setLocalPosition(NxVec3 position);
		NxQuat		getLocalOrientation();
		void		setLocalOrientation(NxQuat orientation);

		void		setClient(SRE::ExtendedSA::Client* controlClient);
	protected:
		virtual void Create() = 0;

		//Pointer to World
		NxScene*	pScene;				///Pointer to Scene (World)
		ExtendedSA::Client* client;		///Control Client of this Part

		NxActor*	pPhysXActor;		///Actor Object
		NxShape*	pPhysXShape;		///Shape of Actor
		NxVec3		localPosition;		///Local Position in Robot
		NxQuat		localOrientation;	///Local Orientation in Robot
		NxVec3		robotPosition;		///Position of Whole Robot
		NxQuat		robotOrientation;	///Position of Whole Robot
	};

	inline Part::Part(NxScene* scene, NxVec3 robotPosition) : pScene(scene), robotPosition(robotPosition), client(NULL){
	}

	inline NxActor* Part::getActor(){
		return pPhysXActor;
	}
	inline void Part::setActor(NxActor* actor){
		pPhysXActor = actor;
		return;
	}
	inline NxShape* Part::getShape(){
		return pPhysXShape;
	}
	inline void Part::setShape(NxShape* shape){
		pPhysXShape = shape;
		return;
	}
	inline NxVec3 Part::getLocalPosition(){
		return localPosition;
	}
	inline void Part::setLocalPosition(NxVec3 position){
		localPosition = position;
		return;
	}
	inline NxQuat Part::getLocalOrientation(){
		return localOrientation;
	}
	inline void Part::setLocalOrientation(NxQuat orientation){
		localOrientation = orientation;
		return;
	}
	/**
	 Partの制御を司るClientを指定する
	 @param controlClient このPartを操作するExtendedSAのClientへのポインタ
	 */
	inline void	Part::setClient(ExtendedSA::Client* controlClient){
		client = controlClient;
		return;
	}
}	//namespace Robot
}	//namespace SRE

#endif	//SRE_Robot_Part_H_