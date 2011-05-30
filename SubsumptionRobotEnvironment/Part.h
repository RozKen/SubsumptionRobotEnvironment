#ifndef SRE_Robot_Part_H_
#define SRE_Robot_Part_H_

#include <vector>
#include <NxPhysics.h>			//Used for PhysX Variables

namespace SRE{
namespace Robot{
	/**
	  Interface Class of Parts of Robots.
	  @author Kenichi Yorozu
	  @date 30 May 2011
	 */
	class Part{
	public:
		Part();			///Constructor
		virtual ~Part();		///Destructor

		//Getters and Setters
		NxActor*	getActor();
		void		setActor(NxActor* actor);
		NxShape*	getShape();
		void		setShape(NxShape* shape);
		NxVec3		getLocalPosition();
		void		setLocalPosition(NxVec3 position);
		NxQuat		getLocalOrientation();
		void		setLocalPosition(NxQuat orientation);
	protected:
		NxActor*	pPhyxXActor;		///Actor Object
		NxShape*	pPhysXShape;		///Shape of Actor
		NxVec3		localPosition;		///Local Position in Robot
		NxQuat		localOrientation;	///Local Orientation in Robot
	};
}	//namespace Robot
}	//namespace SRE

#endif	//SRE_Robot_Part_H_