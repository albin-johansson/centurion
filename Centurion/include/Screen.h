#pragma once
#include "centurion.h"

class centurion::CTN_Screen final {

private:
	CTN_Screen() = delete;

public:
	~CTN_Screen() = default;

	static int getWidth();

	static int getHeight();
};