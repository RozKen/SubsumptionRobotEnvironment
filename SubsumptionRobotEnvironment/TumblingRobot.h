#ifndef TumblingRobot_H_
#define TumblingRobot_H_

#include "Robot.h"

//class TumblingBody;		//Prototype Declaration
//class TumblingArm;		//Prototype Declaration

class TumblingRobot : public SRE::Robot::Robot {
public:
	TumblingRobot(NxScene* scene, const NxVec3 position);
	~TumblingRobot();
protected:
	void Create();		//Override Robot::Create()

	//Actors
	//TumblingBody*	body;
	//TumblingArm*	leftArm;
	//TumblingArm*	rightArm;

	//Joints
	//NxJoint*		leftJoint;
	//NxJoint*		rightJoint;
};

inline TumblingRobot::~TumblingRobot(){
	//TODO: implement 
	//delete body;
	//delete leftArm;
	//delete rightArm;
	//delete leftJoint;
	//delete rightJoint;
	return;
}
#endif	//TumblingRobot_H_