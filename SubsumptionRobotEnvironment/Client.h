#ifndef SRE_ExtendedSA_Client_H_
#define SRE_ExtendedSA_Client_H_

#include <string>
#include <vector>

#include "States.h"
namespace SRE{
	namespace ExtendedSA{
		class Server;			//Prototype Declaration
		class Message;			//Prototype Declaration
		/**
		 @class Client
		 @brief This is a Client Object derived from States Object of Finite State 
			Machine. This Object  has Communication Functions. Each Client is 
			registered 	to Server (host) and send Message to Other Client through
			Server.
		 @sa Server, Message
		 @author Kenichi Yorozu
		 */
		class Client : public FSM::States{
		public:
			enum State {null, state1, state2, state3};
			//Constructors
			Client(Server *host);
			//Destructor
			//~Client();
			//Functions
			virtual int Execute() = 0;
			virtual int Reset();
			virtual Message* createMessage(Client *to, int message);
			virtual Message* createMessage(std::string to, int message);
			virtual void sendMessage(Message * message);
			virtual void sendMessage(Client *to, int message);
			virtual void sendMessage(std::string to, int message);
			//Getter and Setters
			virtual int getState() const = 0;
			virtual void setState(State state);
			virtual void setState(int state);
			virtual Server* getHost() const;
			virtual void setHost(Server *host);
			virtual std::string getName() const;
			virtual void setName(std::string name);
			virtual std::vector<Client *> getTarget() const;
			virtual void addTarget(Client *target);
			virtual void setMessage(int message);
			virtual int getInbox() const;

			virtual Client& operator = (const Client &client);
		protected:
			State _currentState;		/** Store Current State */
			Server* _host;
			std::string _name;			/** Store Unique Name of Object */
			std::vector<Client *> _target;		/** Store Target Clients to which
													send Messages
												*/
			int _inbox;					/** Store Message send from Server (host) */
			Client();		//protected ‚É‚µ‚Ä‰B‚Ø‚¢
		};

		/**
		 @fn Client::Client
		 @brief Set _currentState as null and _host as host
		 @param Server *host
		 @return none
		 */
		inline Client::Client(Server *host) : _currentState(null), _host(host){
			return;
		}
		//Execute is defined on Client.cpp
		/**
		 @fn Client::Reset
		 @brief Set _currentState as null
		 @return int _currentState
		 */
		inline int Client::Reset(){
			_currentState = null;
			return (int) _currentState;
		}
		/**
		 @fn Client::getState
		 @brief return _currentState
		 @return int _currentState
		 */
		inline int Client::getState() const{
			return (int) _currentState;
		}
		/**
		 @fn Client::setState
		 @brief Set _currentState
		 @param Client::State state
		 @return void
		 */
		inline void Client::setState(Client::State state){
			_currentState = state;
			return;
		}
		/**
		 @fn Client::setState
		 @brief Set _currentState
		 @param int state
		 @return void
		 */
		inline void Client::setState(int state){
			_currentState = (Client::State)state;
			return;
		}
		/**
		 @fn Client::getHost
		 @brief get Host (Server *)
		 @return Server*
		 */
		inline Server* Client::getHost() const{
			return this->_host;
		}
		/**
		 @fn Client::setHost
		 @brief Set _host
		 @return void
		 */
		inline void Client::setHost(Server *host){
			this->_host = host;
			return;
		}
		/**
		 @fn Client::getName
		 @brief Get _name
		 @return std::string _name
		 */
		inline std::string Client::getName() const{
			return _name;
		}
		/**
		 @fn Client::setName
		 @brief Set _name
		 @param std::string name
		 @return void
		 */
		inline void Client::setName(std::string name){
			this->_name = name;
			return;
		}
		/**
		 @fn Client::getTarget
		 @brief get _target for signal output
		 @return std::vector<Client *> _target
		 */
		inline std::vector<Client *> Client::getTarget() const{
			return _target;
		}
		/**
		 @fn Client::addTarget
		 @brief Add Target Client to _target
		 @param Client* target
		 @return void
		 */
		inline void Client::addTarget(Client *target){
			_target.push_back(target);
			return;
		}
		/**
		 @fn Client::setMessage
		 @brief Store message from Server to _inbox
		 @param int message
		 @return void
		 */
		inline void Client::setMessage(int message){
			_inbox = message;
		}
		/**
		 @fn Client::getInbox
		 @brief get Inbox
		 @return int _inbox
		 */
		inline int Client::getInbox() const{
			return _inbox;
		}
		/**
		 @fn Client::operator=
		 @brief Assign Client
		 @param const Client & client
		 @return Client
		 */
		inline Client& Client::operator = (const Client &client){
			_currentState = (Client::State)client.getState();
			_host = client.getHost();
			_inbox = client.getInbox();
			_name = client.getName();
			_target = std::vector<Client *>(client.getTarget());
			return *this;
		}
	};	//namespace ExtendedSA
};	//namespace SRE
#endif //SRE_ExtendedSA_Client_H_
