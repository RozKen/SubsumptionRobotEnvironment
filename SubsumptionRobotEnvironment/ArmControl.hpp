/**
 @file ArmControl.hpp
 @brief This file containes ArmControl State Declaration and Definition.
 @author Kenichi Yorozu
 @date 23th April 2011
 */

#ifndef ArmControl_hpp_
#define ArmControl_hpp_

#include "Client.h"

/**
 @class ArmControl
 @brief ArmControl State Class. Derived from Client
 @author Kenichi Yorozu
 */
class ArmControl : public SRE::ExtendedSA::Client {
public:
	enum State{ null = 0, Stop = 1, Forward = 2 };
	//Constructors
	ArmControl();
	ArmControl(SRE::ExtendedSA::Server *host);
	//Functions
	int Execute();
	//int Reset();		//Use Default
	//void sendMessage(Client *to, int message);		//Use Default
	//Getters and Setters
	int getState();
	//void setHost(Server *host);							//use Default
	void setState(State state);
	void setState(int state);
private:
	State _currentState;
	//Server* _host;		//Not neccesary because Parent Class has it
};
 
/**
 @fn ArmControl::ArmControl
 @brief Default Constructor of class ArmControl
 */
inline ArmControl::ArmControl() : _currentState(null), Client(){
}

/**
 @fn ArmControl::ArmControl
 @brief Constructor of class ArmControl.
 @param Server *host
 */
inline ArmControl::ArmControl(SRE::ExtendedSA::Server *host) : _currentState(null), Client(host){
}
/**
 @fn ArmControl::getState
 @brief Acquire current State as int
 @return int _currentState
 */
inline int ArmControl::getState(){
	return (int)_currentState;
}
/**
 @fn ArmControl::setState
 @brief Set current State of ArmControl State Machine
 @param ArmControl::State state
 */
inline void ArmControl::setState(ArmControl::State state){
	_currentState = state;
	return;
}
/**
 @fn ArmControl::setState
 @brief Set current State of ArmControl State Machine
 @param int state
 */
inline void ArmControl::setState(int state){
	_currentState = (ArmControl::State)state;
	return;
}

#endif //ArmControl_hpp_