// Class STACK2 for the path consistency algorithms


class STACK2
{
public:
	// default constructor
	STACK2();
	// constructor defining the size of the stack
	STACK2(int size);
    // destructor 
	~STACK2();	
	// Pushes an edge onto the stack
	void push(int a, int b);
	// Pops an edge from the stack (reference arguments)
	void pop(int& a, int& b);
	// returns true if the stack is empty
	int stack_empty();
	// initializes the stack to an empty state
	void init_stack();

private:
	int n; 				// size of stack	
	int top;			// top of stack
	int **stack2;		// the stack itself
	int **on_stack2;	// The markers for the stack

};

// Constructor (default)
STACK2::STACK2(): n(VARS+1)
{
	int k;
	k = n*(n+1)/2;
	stack2 = new int *[k];
	assert(stack2 != 0);
	for (int i=0; i < k ; i++)
	{
		stack2[i] = (int *)new int[2];
		assert(stack2[i] != 0);
	}
	on_stack2 = (int **)new int*[n];
	assert(on_stack2 != 0);
	for (int i=0; i < n ; i++)
	{
		on_stack2[i] = (int *)new int[n];
		assert(on_stack2[i] != 0);
	}
	top = 0;
}

// Constructor with size specified
STACK2::STACK2(int size): n(size)
{
	int k;
	if (size < 1)
	{
		cerr << "Illegal STACK size " << n << endl;
		exit(1);
	}
	k = n*(n+1)/2;
	stack2 = (int **)new int*[k];
	assert(stack2 != 0);
	for (int i=0; i < k ; i++)
	{
		stack2[i] = (int *)new int[2];
		assert(stack2[i] != 0);
	}
	on_stack2 = (int **)new int*[n];
	assert(on_stack2 != 0);
	for (int i=0; i < n ; i++)
	{
		on_stack2[i] = (int *)new int[n];
		assert(on_stack2[i] != 0);
	}
	top = 0;
}	

// destructor
STACK2::~STACK2()
{
	int k;
	k = n*(n+1)/2;
	for (int i=0 ; i < k ; i++)
		delete [](stack2[i]);
	delete []stack2;
	for (int i=0 ; i < n ; i++)
		delete [](on_stack2[i]);
	delete []on_stack2;
}

int STACK2::stack_empty()
{
	return(top == 0);
}	

void STACK2::init_stack()
{
	top = 0;
	for (int i=1 ; i < n ;i++)
		for (int j=1 ; j < n ;j++)
			on_stack2[i][j] = 0;
	return;
}

void STACK2::push(int a, int b)
{
	if (!on_stack2[a][b])
	{
		top++;
		stack2[top][0] = a;
		stack2[top][1] = b;
		on_stack2[a][b] = 1;
		on_stack2[b][a] = 1;
	}
	return;
}

void STACK2::pop(int& a, int& b)
{
	a = stack2[top][0];
	b = stack2[top][1];
	on_stack2[a][b] = 0;
	on_stack2[b][a] = 0;
	top--;
	return;
}
