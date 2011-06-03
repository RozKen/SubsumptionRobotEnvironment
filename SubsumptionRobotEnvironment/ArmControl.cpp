/**
 @file ArmControl.cpp
 @brief This file containes ArmControl State Definition.
 @author Kenichi Yorozu
 @date 25th April 2011
 */

#include <iostream>
#include "ArmControl.hpp"

/**
 @fn ArmControl::Execute
 @brief Execute Task according to its State
 @return int _currentState
 */
int ArmControl::Execute(){
	State current = _currentState;
	std::cout << _name << ":" << _currentState << ", ";
	switch(_currentState){
		case null:
			_currentState = Stop;	//Move to 'Stop' State
			break;
		case Stop:
			if(_inbox == 2 ){
				_currentState = Forward;	//Move to 'Forward' State
			}
			break;
		case Forward:
			if(_inbox == 1 ){
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