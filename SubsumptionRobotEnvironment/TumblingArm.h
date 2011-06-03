#ifndef TumblingArm_H_
#define TumblingArm_H_

#include "Part.h"

class TumblingArm : public SRE::Robot::Part{
public:
	TumblingArm(NxScene* scene, NxVec3 robotPosition, NxVec3 localPosition, NxQuat localOrientation);
	//@Override
	void update();		
protected:
	//@Override
	void Create();
	double maxTorque;
};

#endif	//TumblingArm_H_
