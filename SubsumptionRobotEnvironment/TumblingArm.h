#ifndef TumblingArm_H_
#define TumblingArm_H_

#include "Part.h"

class TumblingArm : public SRE::Robot::Part{
public:
	TumblingArm(NxScene* scene, NxVec3 robotPosition, NxVec3 localPosition, NxQuat localOrientation);
protected:
	void Create();
};

#endif	//TumblingArm_H_
