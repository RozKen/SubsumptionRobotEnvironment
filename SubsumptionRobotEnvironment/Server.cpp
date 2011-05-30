#include "ExtendedSA.h"

namespace SRE{
namespace ExtendedSA{
	/**
		@fn Server::Run
		@brief Process Messages send from Clients and dispatch Message to Clients
		@return void
		*/
	void Server::Run(){
		std::cout << "Number of Clients : " << _clients.size() << std::endl;
		for(unsigned int i = 0; i < _clients.size(); i++){
			//std::cout << "i : " << i << std::endl;
			_clients[i]->Execute();
		}
		std::cout << std::endl;

		processMessage();
		dispatchMessage();
	}
	/**
		@fn Server::processMessage
		@brief Process Messages. Acquire Message from _inbox and add to _outbox
		@return void
		*/
	void Server::processMessage(){
		//_outbox = std::vector<Message *>(_clients.size());
		Message *tmp;
		Client *to;
		while(_inbox.size() != 0){
			int index = -1;
			tmp = *(--_inbox.end());	//‚±‚±‚ÅƒGƒ‰[‚É‚È‚éD2011.05.26.
			_inbox.pop_back();
			to = tmp->getTo();
			for(unsigned int i = 0; i < _outbox.size(); i++){
				if(_outbox[i]->getTo() == to){
					index = i;
				}
			}
			if(index != -1){
				_outbox[index] = tmp;
			}else{
				_outbox.push_back(tmp);
			}
		}
	}

	/**
		@fn Server::dispatchMessage
		@brief According to _outbox, dispatch messages to each Client as 
		Client->setMessage(message);
		@return void
		*/
	void Server::dispatchMessage(){
		Message *tmp;
		while( ! _outbox.empty() ){
			//tmp = *&*_outbox.end();//_outbox[_outbox.end()-1];
			tmp = *(--_outbox.end());
			tmp->getTo()->setMessage(tmp->getMessage());
			_outbox.pop_back();
		}
	}
};	//namespace ExtendedSA
};	//namespace SRE