#pragma once
#include "Centurion.h"

class centurion::CTN_Action {

protected:
	CTN_Action() = default;

public:
	virtual ~CTN_Action() = 0;

	/**
	\brief Executes the action represented by this IAction.
	*/
	virtual void execute() = 0;
};