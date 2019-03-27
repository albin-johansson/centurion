#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;
using centurion::tools::NullChecker;

namespace CenturionTest
{
	TEST_CLASS(NullCheckerTest)
	{
		TEST_CLASS_INITIALIZE(Init)
		{
			Centurion::Init();
		}

		TEST_CLASS_CLEANUP(Cleanup)
		{
			Centurion::Close();
		}

		TEST_METHOD(IsNull)
		{
			int i = 5;
			long a = 120;

			int* badPtr1 = nullptr;
			short* badPtr2 = NULL;

			int* goodPtr1 = &i;
			long* goodPtr2 = &a;

			Assert::IsFalse(NullChecker::IsNull(goodPtr1));
			Assert::IsFalse(NullChecker::IsNull(goodPtr2));

			Assert::IsTrue(NullChecker::IsNull(badPtr1));
			Assert::IsTrue(NullChecker::IsNull(badPtr2));
		}
	};
}