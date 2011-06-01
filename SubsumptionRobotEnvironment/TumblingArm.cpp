#include <iostream>
#include "TumblingArm.h"
TumblingArm::TumblingArm(NxScene* scene, NxVec3 robotPosition, NxVec3 localPosition,
	NxQuat localOrientation) : Part(scene, robotPosition){
	this->localPosition = localPosition;
	this->localOrientation = localOrientation;
	Create();
}

void TumblingArm::Create(){
	if(pScene == NULL){
#ifdef _DEBUG
		std::cout<< "pScene == NULL at TumblingArm::Create()" << std::endl;
#endif	//_DEBUG
		return;
	}
	pPhysXActor = CreateBox(NxVec3(0.5f, 3.0f, 0.15f), robotPosition + localPosition);
	pPhysXActor->setGlobalOrientationQuat(localOrientation);
	pPhysXShape = pPhysXActor->getShapes()[0];
	return;
}