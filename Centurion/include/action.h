#pragma once
#include "centurion.h"

/** 
\brief The Action class serves as an interface for objects that represent various actions.
*/
class centurion::events::Action {
	
protected:
	Action() = default;

public:
	virtual ~Action() = default;

	/**
	\brief Executes the action represented by this action object.
	*/
	virtual void Execute() = 0;
};