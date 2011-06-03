#include "TumblingRobot.h"
#include "TumblingBody.h"
#include "TumblingArm.h"
#include "WalkControl.hpp"
#include "ArmControl.hpp"
#include "Server.h"
#include <iostream>

TumblingRobot::TumblingRobot(NxScene* scene, SRE::ExtendedSA::Server* host, const NxVec3 position)
	: Robot(scene, host, position){
	Create();
}

void TumblingRobot::Create(){
	if(this->pScene == NULL){
#ifdef _DEBUG
		std::cout<< "pScene == NULL at TumblingRobot::Create()" << std::endl;
#endif	//_DEBUG
		return;
	}
	TumblingBody*	body = new TumblingBody(pScene, position);
	TumblingArm*	leftArm = new TumblingArm(pScene, position, NxVec3(-2, 0, 0), NxQuat(-10, NxVec3(0, 1, 0)) );
	TumblingArm*	rightArm = new TumblingArm(pScene, position, NxVec3(2, 0, 0),	NxQuat(10, NxVec3(0, 1, 0)) );

	NxRevoluteJointDesc leftJointDesc;
	leftJointDesc.setToDefault();
	leftJointDesc.actor[0] = body->getActor();
	leftJointDesc.actor[1] = leftArm->getActor();
	leftJointDesc.setGlobalAnchor(position + NxVec3(2, 0, 0));
	leftJointDesc.setGlobalAxis(NxMat33(leftArm->getLocalOrientation()) * NxVec3(1, 0, 0));
	NxJoint* leftJoint = pScene->createJoint( leftJointDesc );

	NxRevoluteJointDesc rightJointDesc;
	rightJointDesc.setToDefault();
	rightJointDesc.actor[0] = body->getActor();
	rightJointDesc.actor[1] = rightArm->getActor();
	rightJointDesc.setGlobalAnchor(position + NxVec3(2, 0, 0));
	rightArm->getLocalOrientation();
	rightJointDesc.setGlobalAxis(NxMat33(rightArm->getLocalOrientation()) * NxVec3(1, 0, 0));
	NxJoint* rightJoint = pScene->createJoint( rightJointDesc );

	//Register Parts
	this->parts.push_back(body);
	this->parts.push_back(leftArm);
	this->parts.push_back(rightArm);

	//Register Joints
	this->joints.push_back(leftJoint);
	this->joints.push_back(rightJoint);

	WalkControl*		cWalk = new WalkControl(pHost);
	ArmControl*			cLeftArm = new ArmControl(pHost);
	ArmControl*			cRightArm = new ArmControl(pHost);

	cWalk->addTarget(cLeftArm);
	cWalk->addTarget(cRightArm);

	clients.push_back(cWalk);
	clients.push_back(cLeftArm);
	clients.push_back(cRightArm);

	pHost->addClient(cWalk);
	pHost->addClient(cLeftArm);
	pHost->addClient(cRightArm);
	
	return;
}