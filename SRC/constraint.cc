
// Implementation of binary constraints as a class
// CLASS CONSTRAINT


class CONSTRAINT {
public:
  // default constructor
  CONSTRAINT();
  // constructor defining the size of the constraint
  CONSTRAINT(int size);
  // destructor 
  ~CONSTRAINT();
  // return the size of the constraint (i.e. k)
  int size();
  // access the entry in the constraint matrix for value a and b
  char access(int a, int b);
  // print the whole contraint
  void print();
  // assign a value 0 or 1 to C[a][b]
  void assign(int a, int b, int value);


private:
  int **C;    // CONSTRAINT c as a 2D array structure
  int k;      // size of the CONSTRAINT
};


// default constructor
CONSTRAINT::CONSTRAINT(): k(DOMS)
{
  C = new int*[k];
  assert (C != 0);
  for(int i=0; i<k; i++)
    {
      C[i] = new int[k];
      assert(C[i] != 0);
    }
}

// constructor defining the size of the constraint 
CONSTRAINT::CONSTRAINT(int size): k(size)
{
  if (size < 1)
    {
      cerr << "Illegal CONSTRAINT size" << size << endl;
      exit(1);
    }
  C = new int*[k];
  assert (C != 0);
  for(int i=0; i<k; i++)
    {
      C[i] = new int[k];
      assert(C[i] != 0);
    }
}

// destructor
CONSTRAINT::~CONSTRAINT()
{
  for (int i=0; i<k; i++)
    delete [](C[i]);
  delete []C;
}
      
// access the entry in the constraint matrix for value a and b
char CONSTRAINT::access(int a, int b)
{
  if ( (a < 0) || (a > k-1) || (b < 0) || (b > k-1) )
    {
      cerr << "illegal index for constraint when calling CONSTRAINT::access" 
	<< endl;
      exit(1);
    }
  return(C[a][b]);
}

// print the whole constraint
void CONSTRAINT::print()
{
/*
  for(int a=0; a<k; a++)
    for(int b=0; b<k; b++)
      printf("\n C[%d][%d]= %d ", a, b, C[a][b]);
*/
	for(int a = 0; a<k; a++){
		printf("[ ");
		for(int b = 0; b<k; b++){
			printf("%d ", C[a][b]);
		}
		printf("]\n");
	}
}

// assign a value 0 or 1 to C[a][b]
void CONSTRAINT::assign(int a, int b, int value)
{
  if ( a < 0 || a > (k-1) || b < 0 || b > (k-1) )
    {
      cerr << "illegal index for constraint when calling CONSTRAINT::assign" 
	<< endl;
      exit(1);
    } 
  C[a][b] = value;
}

// return the size of the constraint (i.e. k)
int CONSTRAINT::size()
{
  return(k);
}


























