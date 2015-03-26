// Class STACK for the path consistency algorithms


class STACK
{
public:
	// default constructor
	STACK();
	// constructor defining the size of the stack
	STACK(int size);
	// destructor 
	~STACK();	
	// Pushes a value onto the stack
	void push(int a);
	// Pops a value from the stack (reference argument)
	void pop(int& a);
	// returns true if the stack is empty
	int stack_empty();
	// initializes the stack to an empty state
	void init_stack();

private:
	int n; 				// size of stack	
	int top;			// top of stack
	int *stack;		// the stack itself
	int *on_stack;	// The markers for the stack

};

// Constructor (default)
STACK::STACK(): n(VARS+1)
{
	stack = (int *)new int[n];
	assert(stack != 0);
	on_stack = (int *)new int[n];
	assert(on_stack != 0);
	top = 0;
}

// Constructor with size specified
STACK::STACK(int size): n(size)
{
	if (size < 1)
	{
		cerr << "Illegal STACK size " << n << endl;
		exit(1);
	}
	stack = (int *)new int[n];
	assert(stack != 0);
	on_stack = (int *)new int[n];
	assert(on_stack != 0);
	top = 0;
}	

// destructor
STACK::~STACK()
{
	delete []stack;
	delete []on_stack;
}

int STACK::stack_empty()
{
	return(top == 0);
}	

void STACK::init_stack()
{
	top = 0;
	for (int i=1 ; i <= n ;i++)
		on_stack[i] = 0;
	return;
}

void STACK::push(int a)
{
	if (!on_stack[a])
	{
		top++;
		stack[top] = a;
		on_stack[a] = 1;
	}
	return;
}

void STACK::pop(int& a)
{
	a = stack[top];
	on_stack[a] = 0;
	top--;
	return;
}








