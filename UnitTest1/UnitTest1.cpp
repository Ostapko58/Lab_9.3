#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_9.3/Lab_9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
			Electr* stud = new Electr[5];
			stud[0].prizn = "арнест";
			stud[0].poznach = Pozn::casual;
			stud[0].time[0] = 1;
			stud[0].time[1] = 21;

			stud[1].prizn = "дарт";
			stud[1].poznach = Pozn::casual;
			stud[1].time[0] = 5;
			stud[1].time[1] = 21;

			stud[2].prizn = "борд";
			stud[2].poznach = Pozn::casual;
			stud[2].time[0] = 2;
			stud[2].time[1] = 21;

			stud[3].prizn = "грушів";
			stud[3].poznach = Pozn::casual;
			stud[3].time[0] = 4;
			stud[3].time[1] = 21;

			stud[4].prizn = "врін";
			stud[4].poznach = Pozn::casual;
			stud[4].time[0] = 3;
			stud[4].time[1] = 21;

			SortPrizn(stud, 5);

			Assert::AreEqual(stud[0].time[0], 1);
			Assert::AreEqual(stud[1].time[0], 2);
			Assert::AreEqual(stud[2].time[0], 3);
			Assert::AreEqual(stud[3].time[0], 4);
			Assert::AreEqual(stud[4].time[0], 5);

			

		}
	};
}
