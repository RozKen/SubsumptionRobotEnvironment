/**
 @file Walk.cpp
 @brief This file containes Walk State and Definition. Declaration is done by "Walk.hpp"
 @sa Walk.hpp
 @author Kenichi Yorozu
 @date 23th April 2011
 */

#include "WalkControl.hpp"
#include <iostream>

/**
 @fn Walk::Execute
 @brief Execute Task according to its State
 @return int _currentState
 */
int WalkControl::Execute(){
	State current = _currentState;
	std::cout << _name << ":" << _currentState << ", ";
	switch(_currentState){
		case null:
			_currentState = Stop;	//Move to 'Stop' State
			break;
		case Stop:
			//sendMessage((std::string)"leftArm", 1);
			sendMessage(_target[0], 1);
			sendMessage(_target[1], 1);
			///TODO どうやってArm::State::Stop == 1であることを知るか？
			///いっそのこと，messageもstringにしてしまって，受け渡すか？
			if(_inbox == 2){
				_currentState = Forward;	//Move to 'Forward' State
			}
			break;
		case Forward:
			//sendMessage((std::string)"leftArm", 2);
			sendMessage(_target[0], 2);
			sendMessage(_target[1], 2);
			if(_inbox == 1){
				_currentState = Stop;	//Move to 'Stop' State
			}
			break;
		default:
#ifdef _DEBUG
			std::cout << "ERROR:_currentState is undefined : " << _currentState << std::endl;
#endif //_DEBUG
			break;
	}
	return (int)current;
}
