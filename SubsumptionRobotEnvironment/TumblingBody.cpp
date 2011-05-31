#include "TumblingBody.h"
#include <iostream>

TumblingBody::TumblingBody(NxScene* scene, NxVec3 robotPosition): Part(scene, robotPosition){
	this->localPosition = NxVec3(0, 0, 0);
	Create();
}

void TumblingBody::Create(){
	if(pScene == NULL)	return;
#ifdef _DEBUG
	std::cout<< "pScene == NULL at TumblingBody::Create()" << std::endl;
#endif	//_DEBUG
	pPhysXActor = CreateBox(NxVec3(1.5f, 1.5f, 1.5f), robotPosition + localPosition);
	//NxBodyDesc	bodyDesc;
	//NxActorDesc	actorDesc;
	//NxBoxShapeDesc	boxDesc;

	//bodyDesc.setToDefault();
	//actorDesc.setToDefault();
	//boxDesc.setToDefault();

	//bodyDesc.linearDamping = 0.1f;
	//actorDesc.body = &bodyDesc;

	//boxDesc.dimensions = NxVec3( 1.5f, 1.5f, 1.5f );
	//actorDesc.shapes.pushBack( &boxDesc );
	//actorDesc.density = DENSITY;
	//actorDesc.globalPose.t = robotPosition + localPosition;

	//pPhysXActor = pScene->createActor( actorDesc );
	pPhysXShape = pPhysXActor->getShapes()[0];
	return;
}