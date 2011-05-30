#ifndef SRE_ExtendedSA_FSM_States_H_
#define SRE_ExtendedSA_FSM_States_H_
namespace SRE{
namespace ExtendedSA{
namespace FSM{
	/**
		@class States
		@brief This is a States Object, virtual Class. This object is inspired by Finite State Machine.
		@author Kenichi Yorozu
		*/
	class States{
	public:
		virtual enum State {null = 0};	/** @brief each States Object must have some State, including 'null' */
		//virtual States() = 0;
		virtual int Execute() = 0;		/** @brief each States Object must execute some task according to its current State */
		virtual int Reset() = 0;							/** @brief each States can be reset by some signal */
		virtual void setState(State state) {};	/** @brief each State must have Setter to some State by some signal */
		//I want to make setState(State state) Purely Virtual Function. But for State
		virtual int getState() = 0;						/** @brief each State must have Getter of Current State */
	protected:
		State _currentState;			/** @brief each State must have Current State as private variable. */
	};
}	//namespace FSM
}	//namespace ExtendedSA
}	//namepsace SRE

#endif //SRE_ExtendedSA_FSM_States_H_