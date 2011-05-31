#include "ExtendedSA.h"

namespace SRE{
namespace ExtendedSA{
	/**
		@fn Client::Client
		@brief Set _currentState as null
		@return none
		*/
	Client::Client() : _currentState(null){
		//protected ‚É‚µ‚Ä‰B‚Ø‚¢
		_host = new Server();
		return;
	}
	/**
		@fn Client::Execute
		@brief Execute Client Original Tasks
		@return int _currentState
		*/
	int Client::Execute(){
		State current = _currentState;
		switch(_currentState){
		case null:
	#ifdef _DEBUG
			std::cout << "Current Status - Client::null" << std::endl;
	#endif	//_DEBUG
				_currentState = state1;
				break;
			case state1:
	#ifdef _DEBUG
				std::cout << "Current Status - Client::state1" << std::endl;
	#endif	//_DEBUG
				//sendMessage(LeftArm, Forward);
				_currentState = state2;
				break;
			case state2:
	#ifdef _DEBUG
				std::cout << "Current Status - Client::state2" << std::endl;
	#endif	//_DEBUG
				_currentState = state3;
				break;
			case state3:
	#ifdef _DEBUG
				std::cout << "Current Status - Client::state3" << std::endl;
	#endif	//_DEBUG
				//sendMessage(RightArm, Forward);
				break;
		}
		return (int)current;
	}
	/**
		@fn Client::sendMessage
		@brief Send Message to Host's Message Queue
		@param Message * message
		@return void
		*/
	void Client::sendMessage(Message *message){
		_host->queueMessage(message);
		return;
	}
	void Client::sendMessage(Client *to, int message){
		sendMessage( createMessage( to, message ) );
		return;
	}
	void Client::sendMessage(std::string to, int message){
		sendMessage( createMessage( to, message ) );
		return;
	}
	/**
		@fn Client::createMessage
		@brief Create Message
		@param Client* to
		@param int message
		@return Message*
		*/
	Message* Client::createMessage(Client *to, int message){
		return new Message(to, message, this);
	}
	/**
		@fn Client::createMessage
		@brief Create Message
		@param std::string to
		@param int message
		@return Message*
		*/
	Message* Client::createMessage(std::string to, int message){
		std::vector<Client*> clients = _host->getClients();
		Client *clTo;
		for (unsigned int i = 0; i < clients.size(); i++ ){
			if( clients[i]->getName() == to ){
				clTo = clients[i];
				break;
			}
		}
		return new Message( clTo, message, this);
	}
};	//namespace ExtendedSA
};	//namespace SRE