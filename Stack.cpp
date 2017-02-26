#include<string>
#include<cassert>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include"Stack.h"

using namespace AhmedStack;

#define ASSERT_OK()					\
if (!isStackOk())					\
{									\
	dump();							\
	assert(!"Stack object is OK");	\
}									\

Stack::Stack() : capacity_(Stack::STACK_DEFAULT_CAPASITY), size_(0)
{
	data_ = new StackContentType[capacity_];
}


Stack::Stack(size_t capacity) : capacity_(capacity), size_(0)
{
	data_ = new StackContentType[capacity_];
}


Stack::Stack(Stack& other) : size_(0)
{
	deepCopy(other);
}


Stack Stack::operator=(Stack& other)
{
	deepCopy(other);
	return (*this);
}


Stack::~Stack()
{
	size_ = ++capacity_; //Специально портим объект, чтобы им не пользовались после удаления
	delete[] data_;
}


void Stack::deepCopy(Stack& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;

	data_ = new StackContentType[capacity_];

	for (size_t i = 0; i < size_; i++)
	{
		data_[i] = other.data_[i];
	}
}



bool Stack::push(StackContentType elementToPush)
{
	ASSERT_OK(); //Entry verification

	if (size_ >= capacity_)
	{
		return false;
	}
	else
	{
		ASSERT_OK();
		data_[size_++] = elementToPush;
		return true;
	}
}


StackContentType Stack::pop()
{

	if (size_ > 0)
	{
		ASSERT_OK();
		return data_[--size_];
	}
	else
	{
		ASSERT_OK();
		return NAN;
	}
}


bool Stack::isEmpty() const
{
	ASSERT_OK();
	return size_ == 0;
}


size_t Stack::getSize() const
{
	ASSERT_OK();
	return size_;
}


size_t Stack::getCapacity() const
{
	ASSERT_OK();
	return capacity_;
}


bool Stack::isStackOk() const
{
	return size_ <= capacity_;
}

void Stack::dump() const
{
	
	std::string dumpContent = (size_ <= capacity_) ? "Stack (OK)\n\t{\n" : "Stack (ERROR)\n\t{\n";

	dumpContent += "\tCapacity = " + std::to_string(capacity_) + "\n" + "\tSize = " + std::to_string(size_) + "\n\n\t\tdata[" + std::to_string(capacity_) + "]:\n\t\t{\n";

	for (size_t i = 0; i < capacity_; i++)
	{
		if (i < size_)
		{
			dumpContent += "   \t*\tElement № " + std::to_string(i) + ")\t" + std::to_string(data_[i]) + "\n";
		}
		else
		{
			dumpContent += "\t\tElement № " + std::to_string(i) + ")\t" + std::to_string(data_[i]) + " (TRASH)\n";
		}
	}

	dumpContent += "\t\t}\n\t}\n";

	std::ofstream fout;

	fout.open("Stack_Dump.txt");//open file Stack_Dump.txt if it exist or create new file

	fout << __DATE__ << std::endl << __TIME__ << "\n\n\n" << dumpContent;

	fout.close();

	std::cout << "Stack dump file was saved in current directory. See Stack_Dump.txt\n";
}
