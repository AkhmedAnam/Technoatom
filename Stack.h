
namespace AhmedStack
{

	typedef double StackContentType;

	class Stack
	{
	public:
		Stack();

		Stack(size_t capacity);

		//copy-constructor
		Stack(Stack& otherStack);

		~Stack();

		static const size_t STACK_DEFAULT_CAPASITY = 10U;

		Stack operator=(Stack& other);

		//put an element to the stack
		bool push(StackContentType elementToPush);


		//pop an element from the stack
		StackContentType pop();

		//check whether the stack is empty
		bool isEmpty() const;

		//return current size of the stack
		size_t getSize() const;

		//return an object capacity
		size_t getCapacity() const;

		//scilent verefier
		bool isStackOk() const;

		//dump current object
		void dump() const;

	private:

		void deepCopy(Stack& other);

		StackContentType* data_;
		size_t size_, capacity_;
		
	};

}
