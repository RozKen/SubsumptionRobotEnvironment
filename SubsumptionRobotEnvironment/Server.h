#ifndef SRE_ExtendedSA_Server_H_
#define SRE_ExtendedSA_Server_H_

#include <vector>

namespace SRE{
namespace ExtendedSA{

	class Client;		//Prototype Declaration
	class Message;		//Prototype Declaration
	/**
	 @class Server
	 @brief This is a Server Object. Host Clients and process Messages.
	 @sa Client, Message
	 @author Kenichi Yorozu
	 */
	class Server{
	public:
		//Server();	
		//in case LNK2001:既定のコンストラクタがない on any files, then
		//add #include "Server.h" to specified cpp File.
		void Run();

		int addClient(Client *client);
		void queueMessage(Message *message);
		std::vector<Client*> getClients() const;
		std::vector<Message *> getInbox() const;
		std::vector<Message *> getOutbox() const;
		Server& operator = (const Server &server);
	private:
		std::vector<Client*> _clients;
		std::vector<Message *> _inbox;
		std::vector<Message *> _outbox;

		void processMessage();
		void dispatchMessage();
	};

	//inline Server::Server(){
	//	return;
	//}
	/**
	 @fn Server::addClient
	 @brief addClient to Server
	 @param Client* client
	 @return int _clients.size()
	 */
	inline int Server::addClient(Client *client){
		_clients.push_back(client);
		return _clients.size();
	}
	/**
	 @fn Server::queueMessage
	 @brief Store Messages send from Clients to Queue
	 @param Message* message
	 @return void
	 */
	inline void Server::queueMessage(Message *message){
		_inbox.push_back(message);
	}
	/**
	 @fn Server::getClients
	 @brief Return registered Clients
	 @return _clients Array of Registered Clients
	 */
	inline std::vector<Client*> Server::getClients() const{
		return _clients;
	}
	/**
	 @fn Server::getInbox
	 @brief Return current Inbox Message Array
	 @return _inbox Message Array of Inbox
	 */
	inline std::vector<Message *> Server::getInbox() const{
		return _inbox;
	}
	/**
	 @fn Server::getOutbox
	 @brief Return current Outbox Message Array
	 @return _outbox Message Array of Outbox
	 */
	inline std::vector<Message *> Server::getOutbox() const{
		return _outbox;
	}
	/**
	 @fn Server::operator=
	 @brief Assign Operator
	 @return *this Object of itself
	 */
	inline Server& Server::operator = (const Server &server){
		_clients = std::vector<Client *>(server.getClients());
		_inbox = std::vector<Message *>(server.getInbox());
		_outbox = std::vector<Message *>(server.getOutbox());
		return *this;
	}
};	//namespace ExtendedSA
};	//namespace SRE
#endif //SRE_ExtendedSA_Server_H_