#ifndef SRE_Robot_Robot_H_
#define SRE_Robot_Robot_H_

#include <vector>
#include "Part.h"

namespace SRE{
	namespace ExtendedSA{
		class Client;		//Prototype Declaration
		class Server;		//Prototype Declaration
	}
namespace Robot{
	class Part;				//Prototype Declaration
	class Robot;
	class Robot{
	public:
		Robot(NxScene* scene,SRE::ExtendedSA::Server* host, NxVec3 position);
		virtual ~Robot();

		//Getters
		std::vector<ExtendedSA::Client *>	getClients() const;
		std::vector<Part *>		getParts() const;
		//Getters and Setters
		NxVec3		getPosition() const;
		void		setPosition(NxVec3 position);
		NxQuat		getOrientation() const;
		void		setOrientation(NxQuat orientation);

		void setClientToParts(ExtendedSA::Client* controlClient, Part* part);

	protected:
		virtual void Create() = 0;
		//Pointer to World
		NxScene*		pScene;
		SRE::ExtendedSA::Server* pHost;
		std::vector<SRE::Robot::Robot*> pRobots;

		//Control Systems
		std::vector<ExtendedSA::Client *> clients;	//"Client" Derivative Classes

		//Parts
		std::vector<Part *> parts;			//"Part" Derivative Classes

		//Joints
		std::vector<NxJoint *> joints;		//NxJoint Classes
			//Joints are specific to each Robot Type

		//Other Robot-Specific Elements
		NxVec3	position;			///Robot's Global Position
		NxQuat	orientation;		///Robot's Global Orientation
	
	};
	inline Robot::Robot(NxScene* scene, SRE::ExtendedSA::Server* host, NxVec3 position) : pScene(scene), pHost(host), position(position){
		///Existence of Copy Constructor of NxPhysicsSDK and NxScene should be confirmed
		return;
	}

	inline Robot::~Robot(){
		//delete pScene;
		clients.clear();
		parts.clear();
		joints.clear();
		return;
	}

	inline std::vector<ExtendedSA::Client *>	Robot::getClients() const{
		return clients;
	}
	inline std::vector<Part *>		Robot::getParts() const{
		return parts;
	}
	inline NxVec3	Robot::getPosition() const{
		return position;
	}
	inline void		Robot::setPosition(NxVec3 position){
		this->position = position;
	}
	inline NxQuat	Robot::getOrientation() const{
		return orientation;
	}
	inline void		Robot::setOrientation(NxQuat orientation){
		this->orientation = orientation;
	}

	inline void Robot::setClientToParts(ExtendedSA::Client* controlClient, Part* part){
		
	}

}	//namespace Robot
}	//namespace SRE



#endif	//SRE_Robot_Robot_H_