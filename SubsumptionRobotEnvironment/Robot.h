#ifndef SRE_Robot_Robot_H_
#define SRE_Robot_Robot_H_

#include <vector>
#include "Part.h"

namespace SRE{
	namespace ExtendedSA{
		class Client;		//Prototype Declaration
	}
namespace Robot{
	class Part;				//Prototype Declaration
	class Robot{
	public:
		Robot();
		virtual ~Robot();

		//Getters
		std::vector<ExtendedSA::Client *>	getClients();
		std::vector<Part *>		getParts();
		//Getters and Setters
		NxVec3		getPosition();
		void		setPosition(NxVec3 position);
		NxQuat		getOrientation();
		void		setOrientation(NxQuat orientation);
	
	protected:
		//Control Systems
		std::vector<ExtendedSA::Client *> clients;	//"Client" Derivative Classes

		//Parts
		std::vector<Part *> parts;		//"Part" Derivative Classes

		//Joints
			//Joints are specific to each Robot Type

		//Other Robot-Specific Elements
		NxVec3	position;			///Robot's Global Position
		NxQuat	orientation;		///Robot's Global Orientation
	
	};
	inline std::vector<ExtendedSA::Client *>	Robot::getClients(){
		return clients;
	}
	inline std::vector<Part *>		Robot::getParts(){
		return parts;
	}
	inline NxVec3	Robot::getPosition(){
		return position;
	}
	inline void		Robot::setPosition(NxVec3 position){
		this->position = position;
	}
	inline NxQuat	Robot::getOrientation(){
		return orientation;
	}
	inline void		Robot::setOrientation(NxQuat orientation){
		this->orientation = orientation;
	}

}	//namespace Robot
}	//namespace SRE



#endif	//SRE_Robot_Robot_H_