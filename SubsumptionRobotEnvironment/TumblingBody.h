#ifndef TumblingBody_H_
#define TumblingBody_H_

#include "Part.h"

class TumblingBody : public SRE::Robot::Part{
public:
	///Constructor
	TumblingBody(NxScene* scene, NxVec3 robotPosition);
protected:
	void Create();
};

#endif	//TumblingBody_H_