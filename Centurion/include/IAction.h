#pragma once
#include "Centurion.h"

class centurion::IAction {

protected:
	IAction() = default;

public:
	virtual ~IAction() = 0;

	/**
	\brief Executes the action represented by this IAction.
	*/
	virtual void execute() = 0;
};