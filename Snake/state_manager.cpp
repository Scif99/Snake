#include "state_manager.h"



//Changes the state associated with a context by pushing the new state onto the stack.
//If the replace flag is set to true, remove the old state from the stack before pushing the new one.
void StateManager::AddState(std::unique_ptr<GameState> new_state, bool replace)
{
	//ASSERT: stack should not be empty is replace is flagged true
	if (replace && !state_stack.empty())
	{
		state_stack.pop();
	}

	state_stack.push(std::move(new_state));

}