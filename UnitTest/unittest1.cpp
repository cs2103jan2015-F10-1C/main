#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethodADD)
		{
			bool edited = false;
			bool edited2 = false;
			bool successful = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input = "add meet zann today 8pm -high\r\n";
			logic->handleInput(input, edited, successful);
			string input2 = "display today\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "Displaying 27/3 task(s)\n\r\n1. meet zann [20:00-21:00] [high]\r\n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodDELETE)
		{
			bool edited2 = false;
			bool edited3 = false;
			bool successful2 = false;
			bool successful3 = false;
			Logic* logic = new Logic;
			string input2 = "delete 270300\r\n";
			logic->handleInput(input2, edited2, successful2);
			string input3 = "display today\r\n";
			string result = logic->handleInput(input3, edited3, successful3);

			string expectedResult = "No task found. \n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodEDIT)
		{
			bool edited = false;
			bool edited2 = false;
			bool edited3 = false;
			bool successful = false;
			bool successful2 = false;
			bool successful3 = false;
			Logic* logic = new Logic;
			string input = "add meet zann today 8pm -high\r\n";
			logic->handleInput(input, edited, successful);
			string input2 = "edit 270300 meet ruyan tomorrow 7pm -mid\r\n";
			logic->handleInput(input2, edited2, successful2);
			string input3 = "display all\r\n";
			string result = logic->handleInput(input3, edited3, successful3);

			string expectedResult = "[280301] [normal]\r\nDetails: meet ruyan\r\nDate: 28/3\r\nTime: 19:00-20:00\r\nPriority: mid\r\n\r\n";

			//error in the edit class
			//code suppose to be displaying meet ruyan instead of meet zann meet ruyan

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodSEARCH)
		{
			bool edited2 = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input2 = "search ruyan\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "1.Index: 280300\r\nDetails: meet ruyan\r\nDate: 28/3\r\nTime: 19:00-20:00\r\nPriority: mid\r\n\r\n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodADDWRONGINPUT)/* This is a boundary case for the ¡®wrong command type¡¯ partition */
		{
			bool edited2 = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input2 = "addtask\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "Command not recognised. Please re-input. \n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodDELETEWRONGINPUT)/* This is a boundary case for the ¡®not existing task index¡¯ partition */
		{
			bool edited2 = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input2 = "delete 000000\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "The Task have not been deleted. Please Check your inputs. \n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodEDITWRONGINPUT)/* This is a boundary case for the ¡®not existing task index¡¯ partition */
		{
			bool edited2 = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input2 = "edit 000000 meet ruyan tomorrow 7pm -mid\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "This index is not found. \n";

			Assert::AreEqual(expectedResult, result);
		}

		TEST_METHOD(TestMethodSEARCHWRONGINPUT)/* This is a boundary case for the ¡®not existing key word¡¯ partition */
		{
			bool edited2 = false;
			bool successful2 = false;
			Logic* logic = new Logic;
			string input2 = "search zann\r\n";
			string result = logic->handleInput(input2, edited2, successful2);

			string expectedResult = "This keyword is not found. \n";

			Assert::AreEqual(expectedResult, result);
		}
	};
}