#pragma once
#include <stack>
#include <memory>
#include "game_state.h"
class StateManager
{
public:
	StateManager() {};
	~StateManager() {};


	void AddState(std::unique_ptr<GameState> state, bool replace);
	void RemoveState() { if(!state_stack.empty()) state_stack.pop(); }


	const std::unique_ptr<GameState>& CurrentState() const { return state_stack.top(); } //top() is UB if stack is empty...

private:
	std::stack<std::unique_ptr<GameState>> state_stack;
};

/*
TODO
- Add a 	void ProcessStateChanges() function.
	- We can then move modifications of the stack into this function.
	- AddState() will then set flags to tell the  ProcessStateChanges() function what to do.
*/