#include "stdafx.h"
#include "CppUnitTest.h"

/*
Due to the limitation of unit testing, tests of commands (classes) which require task index to be inputed are not available.
It is because unit testing will skip the UI and directly test the code, as such, the runtime task index generated in UI will
not be available. And since Coded UI testing is only vailable in VS2013 Ultimate Version, therefore, mannual testing is required.

Classes affected are: DELETE, EDIT, MARK, UNDO(For valid undo).
*/

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
//@author A0108375A
//Unit test for UNDO.
			TEST_METHOD(UNDOwithnothing)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "undo\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

//@author A0093863U
//Unit test for ADD.

			TEST_METHOD(ADDvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann today 8pm -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(ADDvaliddeadline1)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add swim today by 4pm -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(ADDvaliddeadline2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add do homework today before 10pm -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(ADDinvaliddate1)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 43/5 -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDinvaliddate2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann may 43 -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDinvaliddate3)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 43 may -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDexceptiondate)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 99/99 -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

//Unit test for ADD.
			TEST_METHOD(ADDinvalidtime)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 25:00 -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDinvalidtime2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 25:00-23:00 -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDinvalidtime3)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add meet zann 6pm-5pm -high\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(ADDnoinfo)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "add\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

//@author A0108341R
//Unit test for HELP.		

			TEST_METHOD(HELPvalid1)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help add\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help delete\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid3)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help edit\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid4)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help display\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid5)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help mark\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid6)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help directory\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(HELPvalid9)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "help search\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}
//@author A0110748J-unused
//Unit test for SORT.
/*
			TEST_METHOD(SORTinvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "sort\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(SORTbydate)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "sort by date\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(SORTbypriority)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "sort by priority\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}
*/

//@author A0108375A
//Unit test for SEARCH.
			TEST_METHOD(SEARCHvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "search zann\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(SEARCHinvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "search derrick\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}
//@author A0108341R
//Unit test for DIRECTORY.
			TEST_METHOD(DIRECTORYvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "directory D:\\abc.txt\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(DIRECTORYinvalid)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "directory D:\\a\\abc.txt\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(false, successful);
			}

			TEST_METHOD(DIRECTORYvalid2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "directory D:\\Storage.txt\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}
//@author A0110748J
//Unit test for DISPLAY.
			TEST_METHOD(DISPLAYvalid1)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "display\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

			TEST_METHOD(DISPLAYvalid2)
			{
				bool edited = false;
				bool successful = false;
				Logic* logic = new Logic;
				string input = "display week\r\n";
				logic->handleInput(input, edited, successful);
				Assert::AreEqual(true, successful);
			}

	};
}