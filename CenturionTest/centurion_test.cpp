#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::Centurion;

namespace CenturionTest
{
	TEST_CLASS(CenturionTestClazz)
	{
		TEST_CLASS_CLEANUP(Cleanup)
		{
			Centurion::Close();
		}

		TEST_METHOD(InitAndClose)
		{
			Centurion::Init();
			Assert::IsTrue(Centurion::IsInitialized());

			Centurion::Close();
			Assert::IsFalse(Centurion::IsInitialized());

			Centurion::Close();
			Assert::IsFalse(Centurion::IsInitialized());

			Centurion::Init();
			Assert::IsTrue(Centurion::IsInitialized());
		}
	};
}
