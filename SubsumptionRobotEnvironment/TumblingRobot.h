#ifndef TumblingRobot_H_
#define TumblingRobot_H_

#include "Robot.h"

/**
 @class Tumbling Robot
 @brief Tumbling Robot Class subclass of Robot.
 Parts and Actors
 	TumblingBody*	body;
	TumblingArm*	leftArm;
	TumblingArm*	rightArm;
 Joints
 	NxJoint*		leftJoint;
	NxJoint*		rightJoint;
 Clients
	
 @author Kenichi Yorozu
 @date 2nd June 2011
 */
class TumblingRobot : public SRE::Robot::Robot {
public:
	TumblingRobot(NxScene* scene, SRE::ExtendedSA::Server* host, const NxVec3 position);
	~TumblingRobot();
protected:
	void Create();		//Override Robot::Create()

};

inline TumblingRobot::~TumblingRobot(){
	SRE::Robot::Robot::~Robot();
	return;
}
#endif	//TumblingRobot_H_