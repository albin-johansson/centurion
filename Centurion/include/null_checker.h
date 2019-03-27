#pragma once
#include "centurion.h"
#include <stdlib.h>

class centurion::tools::NullChecker {

public:
	template<class T>
	static bool IsNull(T* arg)
	{
		return arg == nullptr || arg == NULL;
	}
};
