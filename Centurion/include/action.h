#pragma once
#include "centurion.h"

class centurion::Action {

protected:
	Action() = default;

public:
	virtual ~Action() = 0;

	/**
	\brief Executes the action represented by this IAction.
	*/
	virtual void Execute() = 0;
};