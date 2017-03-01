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


Stack* functionReturninLocalStack()
{
	Stack localStack;

	localStack.push(10);

	return &localStack;
}

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

		try
		{
			StackContentType el = s.pop();
		}
		catch (Stack::EmptyStackException& ex)
		{
			std::cout << "\nEmptyStackException catched in Stack::pop()\n" << ex.what() << std::endl;
		}

	}

	//Check equlity of capacities of equal stacks
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

		size_t copyCapacity = copy.getCapacity();
		size_t anotherCopyCapacity = anotherCopy.getCapacity();

		bool isCopyCapacityEqualToOriginCapacity = (copyCapacity == stackCap);

		bool isAnotherCopyCapacityEqualToOriginCapacity = (anotherCopyCapacity == stackCap);

		ASSERT_TRUE(isCopyCapacityEqualToOriginCapacity == true);

		ASSERT_TRUE(isAnotherCopyCapacityEqualToOriginCapacity == true);
	}

	//Check equlity of sizes of equal stacks
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

		size_t copySize = copy.getSize(),
			anotherCopySize = anotherCopy.getSize();

		bool isCopySizeEqualToOriginSize = (copySize == stackSize);

		bool isAnotherCopySizeEqualToOriginSize = (anotherCopySize == stackSize);

		ASSERT_TRUE(isCopySizeEqualToOriginSize == true);

		ASSERT_TRUE(isAnotherCopySizeEqualToOriginSize == true);
	}

	//Check equlity of elements of equal stacks
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

		StackContentType thirdElementFromCopy = copy.pop(),
			secondElementFromCopy = copy.pop(),
			firstElementFromCopy = copy.pop(),
			thirdElementFromAnotherCopy = anotherCopy.pop(),
			secondElementFromAnmotherCopy = anotherCopy.pop(),
			firstElementFromAnotherCopy = anotherCopy.pop();

		bool isCopyEqualToOrigin = (firstElementFromCopy == firstElementToPush)
			&& (secondElementFromCopy == secondElementToPush)
			&& (thirdElementFromCopy == thirdElementToPush);

		bool isAnotherCopyEqualToOrigin = (firstElementFromAnotherCopy == firstElementToPush)
			&& (secondElementFromAnmotherCopy == secondElementToPush)
			&& (thirdElementFromAnotherCopy == thirdElementToPush);

		ASSERT_TRUE(isCopyEqualToOrigin == true);

		ASSERT_TRUE(isAnotherCopyEqualToOrigin == true);
	}

	//top() test
	{
		Stack s;

		StackContentType toPush = 10;
		s.push(toPush);
		toPush = 11;
		s.push(toPush);

		StackContentType topElement = s.top();

		ASSERT_TRUE(topElement == toPush);
	}

	//top() with empty stack test
	{
		Stack s;

		try
		{
			StackContentType element = s.top();
		}
		catch (Stack::EmptyStackException& ex)
		{
			std::cout << "\nEmptyStackException catched in Stack::top()\n" << ex.what() << std::endl;
		}
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

	//Using stack after its destroying
	{
		Stack* s = functionReturninLocalStack();//destructor set capacity_ = 0 and size_ = 1. Object was destroying

		StackContentType elementToPush = 15;

		s->push(elementToPush);//in push method both size and capacity = 3435973836. WTF!!??
	}

	std::cout << "All tests done. No errors\n";

	return 0;
}