#include<iostream>
#include<cassert>
#include<cmath>
#include"Stack.h"

using namespace AhmedStack;
using namespace std;


//----------------------------------------------------------
//! Macros to orgonize test code in the main function
//! @param what - an object to test
//! @param caseToTest  - what test to run
//---------------------------------------------------------

//#define TEST( what, caseToTest ) 

#define ASSERT_EQ(condition) \
if(!condition)				 \
{							 \
	assert(!#condition);     \
}							 \


int main(int argc, char** argv)
{
	//push one element
	{
		Stack s;

		s.push(5.0);

		ASSERT_EQ((s.pop()) == (5.0));
	}

	//Can not push more
	{
		Stack s;
		size_t capacity = s.getCapacity();

		for (size_t i = 0; i < capacity; i++)
		{
			s.push(i);
		}

		double valueWillNotBePushed = 12.1;

		ASSERT_EQ(s.push(valueWillNotBePushed) == false);
	}

	//Over poping
	{
		Stack s;

		for (size_t i = 0; i < 5; i++)
		{
			s.push(i);
		}

		for (size_t i = 0; i < 5; i++)
		{
			s.pop();
		}

		ASSERT_EQ(std::isnan<StackContentType>(s.pop()));

	}

	//Check equlity
	{
		size_t stackCap = 13U;

		Stack s(stackCap);

		double firstElementToPush = 12, secondElementToPush = 13, thirdElementToPush = 14;

		s.push(firstElementToPush);
		s.push(secondElementToPush);
		s.push(thirdElementToPush);

		size_t stackSize = s.getSize();

		Stack copy(s);//Copy constructor

		Stack anotherCopy = s;

		bool areObjectsEqual = copy.getCapacity() == stackCap && anotherCopy.getCapacity() == stackCap
			&& copy.getSize() == stackSize && anotherCopy.getSize() == stackSize
			&& copy.pop() == thirdElementToPush && anotherCopy.pop() == thirdElementToPush
			&& copy.pop() == secondElementToPush && anotherCopy.pop() == secondElementToPush
			&& copy.pop() == firstElementToPush && anotherCopy.pop() == firstElementToPush;

		ASSERT_EQ(areObjectsEqual == true);

		s.dump();
	}



	std::cout << "All tests done. No errors\n";



	return 0;
}