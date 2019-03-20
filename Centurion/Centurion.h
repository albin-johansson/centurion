#pragma once

namespace centurion
{
	class Centurion;
}

class centurion::Centurion final {

public:

	Centurion() = delete;

	~Centurion() = default;

	static void init();

	static void close();
};