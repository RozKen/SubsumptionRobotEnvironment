/**
 @file Walk.hpp
 @brief This file containes Walk State Declaration and Definition.
 @author Kenichi Yorozu
 @date 23th April 2011
 */

#ifndef WalkControl_HPP_
#define WalkControl_HPP_

#include "Client.h"

/**
 @class WalkControl
 @brief WalkControl State Class. Derived from Client
 @author Kenichi Yorozu
 */
class WalkControl : public SRE::ExtendedSA::Client {
public:
	enum State{ null = 0, Stop = 1, Forward = 2 };
	//Constructors
	WalkControl();
	WalkControl(SRE::ExtendedSA::Server *host);
	//Functions
	int Execute();
	//int Reset();										//Use Default
	//void sendMessage(Client *to, int message);		//Use Default
	//void sendMessage(std::string to, int message);	//Use Default
	//Getters and Setters
	int getState() const;
	//void setHost(Server *host);						//Use Default
	void setState(State state);
	void setState(int state);
private:
	State _currentState;
	//Server* _host;	//Not neccesary because Parent Class has it
};
 
/**
 @fn Walk::Walk
 @brief Default Constructor of class Walk
 */
inline WalkControl::WalkControl() : _currentState(WalkControl::null), Client(){
}

/**
 @fn Walk::Walk
 @brief Constructor of class Walk.
 @param Server *host
 */
inline WalkControl::WalkControl(SRE::ExtendedSA::Server *host) : _currentState(WalkControl::null), Client(host){
}
/**
 @fn Walk::getState
 @brief Acquire current State as int
 @return int _currentState
 */
inline int WalkControl::getState() const{
	return (int)_currentState;
}
/**
 @fn Walk::setState
 @brief Set current State of Walk State Machine
 @param Walk::State state
 */
inline void WalkControl::setState(WalkControl::State state){
	_currentState = state;
	return;
}
/**
 @fn Walk::setState
 @brief Set current State of Walk State Machine
 @param int state
 */
inline void WalkControl::setState(int state){
	_currentState = (WalkControl::State)state;
	return;
}

#endif //WalkControl_HPP_