#include <iostream>
#include "TumblingArm.h"
#include "ArmControl.hpp"
#include "Client.h"
TumblingArm::TumblingArm(NxScene* scene, NxVec3 robotPosition, NxVec3 localPosition,
	NxQuat localOrientation) : Part(scene, robotPosition), maxTorque(10000000000){
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

void TumblingArm::update(){
	if(client == NULL){	//client‚ªŽw’è‚³‚ê‚Ä‚¢‚È‚¢Part‚Ìê‡‚ÍC–³Ž‹‚·‚é
			return;
	}

	//Specify process according to the state.
	switch(((ArmControl*)client)->getState()){
	case ArmControl::null:
		break;
	case ArmControl::Stop:
		this->pPhysXActor->setAngularVelocity(NxVec3(0, 0, 0));
		this->pPhysXActor->setLinearVelocity(NxVec3(0, 0, 0));
		break;
	case ArmControl::Forward:
		this->pPhysXActor->addLocalTorque(NxVec3((double(rand())/RAND_MAX) * maxTorque * 2 - maxTorque/2, 0, 0));
		break;
	default:
		break;
	}

	return;
}