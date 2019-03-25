#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::CTN_BooleanConverter;

namespace CenturionTest
{
	TEST_CLASS(BooleanConverterTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			Centurion::Init();
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Centurion::Close();
		}

		TEST_METHOD(convert1)
		{
			SDL_bool t = SDL_bool::SDL_TRUE;
			SDL_bool f = SDL_bool::SDL_FALSE;

			bool tConverted = CTN_BooleanConverter::convert(t);
			bool fConverted = CTN_BooleanConverter::convert(f);

			Assert::IsTrue(tConverted);
			Assert::IsFalse(fConverted);
		}

		TEST_METHOD(convert2)
		{
			bool t = true;
			bool f = false;

			SDL_bool tConverted = CTN_BooleanConverter::convert(t);
			SDL_bool fConverted = CTN_BooleanConverter::convert(f);

			Assert::IsTrue(tConverted);
			Assert::IsFalse(fConverted);
		}
	};
}