#ifndef SRE_ExtendedSA_Message_H_
#define SRE_ExtendedSA_Message_H_

#include <vector>

namespace SRE{
	namespace ExtendedSA{
		class Client;			//Prototype Declaration
		/**
		 @class Message
		 @brief This is a Message Object. Message is Send from Client to Server (host). It containes
		 message(int).
		 @author Kenichi Yorozu
		 */
		class Message{
		public:
			Message(Client *to, int message, Client *from);
			//Message();	//Default Constructer‚ğ‰B‚Ø‚¢//‚µ‚Ä‚¢‚È‚¢c
			Client* getTo() const;
			Client* getFrom() const;
			int getMessage() const;
			Message& operator = (const Message &message);
		private:
			Client *_to;
			Client *_from;
			int _message;
		};
		/**
		 @fn Message::Message
		 @brief Constructor. set _to, _from, _message
		 @param to
		 @param message
		 @param from
		 @return void
		 */
		inline Message::Message(Client *to, int message, Client *from)
		: _to(to), _from(from), _message(message){
		}

		/**
		 @fn Message::getTo
		 @brief return _to
		 @return _to
		 */
		inline Client* Message::getTo() const{
			return _to;
		}
		/**
		 @fn Message::getFrom
		 @brief return _from
		 @return _from
		 */
		inline Client* Message::getFrom() const{
			return _from;
		}
		/**
		 @fn Message::getMessage
		 @brief return _message
		 @return _message
		 */
		inline int Message::getMessage() const{
			return _message;
		}
		/**
		 @fn Message::operator=
		 @brief Assign Message
		 @param const Message &message
		 @return *this Object of itself
		 */
		inline Message& Message::operator = (const Message &message){
			_to = message.getTo();
			_message = message.getMessage();
			_from = message.getFrom();
			return *this;
		}

		//inline Message::Message(){
		//	//private‚¾‚©‚çC‰B‚Ø‚¢‚µ‚Ä‚ ‚éI//public‚É‚µ‚½
		//	return;
		//}
	};	//namespace ExtendedSA
};	//namespace SRE
#endif //SRE_ExtendedSA_Message_H_