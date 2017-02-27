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

#define ASSERT_TRUE(condition) \
if(!(condition))				 \
{							 \
	assert(!#condition);     \
}							 \


int main(int argc, char** argv)
{
	//push one element
	{
		Stack s;

		StackContentType elementToPush = 5.0;

		s.push(elementToPush);
		StackContentType popedElement = s.pop();

		ASSERT_TRUE(elementToPush == popedElement);
	}

	//Can not push more
	{
		Stack s;
		size_t capacity = s.getCapacity();

		for (size_t i = 0; i < capacity; i++)
		{
			s.push(i);
		}

		StackContentType valueWillNotBePushed = 12.1;

		ASSERT_TRUE(s.push(valueWillNotBePushed) == false);
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

		ASSERT_TRUE(std::isnan<StackContentType>(s.pop()));

	}

	//Check equlity
	{
		size_t stackCap = 13U;

		Stack s(stackCap);

		StackContentType firstElementToPush = 12, secondElementToPush = 13, thirdElementToPush = 14;

		s.push(firstElementToPush);
		s.push(secondElementToPush);
		s.push(thirdElementToPush);

		size_t stackSize = s.getSize();

		Stack copy(s);//Copy constructor

		Stack anotherCopy = s;//overrided assignment operation

		bool areObjectsEqual = copy.getCapacity() == stackCap && anotherCopy.getCapacity() == stackCap
			&& copy.getSize() == stackSize && anotherCopy.getSize() == stackSize
			&& copy.pop() == thirdElementToPush && anotherCopy.pop() == thirdElementToPush
			&& copy.pop() == secondElementToPush && anotherCopy.pop() == secondElementToPush
			&& copy.pop() == firstElementToPush && anotherCopy.pop() == firstElementToPush;

		ASSERT_TRUE(areObjectsEqual == true);

		s.dump();
	}

	//top() test
	{
		Stack s;

		double toPush = 10;
		s.push(toPush);
		toPush = 11;
		s.push(toPush);

		double topElement = s.top();

		ASSERT_TRUE(topElement == toPush);
	}

	//Overflow memory test
	{
		Stack overflowMemory;

		try
		{
			overflowMemory = Stack(SIZE_MAX);
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "There are not memory for such big stack. Stack with default capacity will create\n" << ba.what() << std::endl;
			overflowMemory = Stack();
		}
	}




	std::cout << "All tests done. No errors\n";



	return 0;
}