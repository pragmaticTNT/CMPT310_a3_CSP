
// Implementation of a network to represent the constraint graph 
// in a binary constraint satisfaction problem.
// CLASS NETWORK


class NETWORK {
public:
  // default constructor
  NETWORK();
  // constructor defining the size of the constraint
  NETWORK(int size);
  // destructor 
  ~NETWORK();
  // Return the size of the network
  int size() { return(n); }
  // Access the constraint on variables i and j for values a and b
  char access(char i, char j, char a, char b);
  // print the whole constraint network
  void print();
  	//print the chess board with pieces in place
	void printBoard(SOLUTION s);
  // generate the n-queens problem
  void generate_Q();
  // generate a random CSP
  void generate_R( int p, int q );
  // generate a random CSP that is guaranteed to have a solution
  void generate_S( int p, int q );
  
  // interface to the solving (search) strategies
  void solve(int (NETWORK::*)(SOLUTION,int,int,int *),SOLUTION solution, int number, int *found );
  
  // process and verify a found solution
  void process_solution( SOLUTION S );

  // consistent() checks if the currently labeled variable is consistent
  // with the previous labels
  int consistent_bt(SOLUTION, int);   // for backtracking
  int consistent_bj(SOLUTION, int);   // for backjumping
  int consistent_bm(SOLUTION, int);   // for backmarking
  int consistent_bmbj(SOLUTION, int); // for backmarking with backjumping
  int consistent_fc(int, int, int);   // forward checking
  int consistent_cbj(SOLUTION, int);  // conflict directed back jumping
  int consistent_fc_bj(int, int, int, int);

  // simple backtracking routine
  int BT( SOLUTION, int, int, int *); 
  // simple back jumping
  int BJ(SOLUTION, int, int, int *);
  // simple back marking
  int BM(SOLUTION, int, int, int *);
  // backmarking with backjumping
  int BM_BJ(SOLUTION, int, int, int *);
  // forward checking
  int FC(SOLUTION, int, int, int *);
  // conflict directed back jumping
  int CBJ(SOLUTION, int, int, int *);
  // forward checking with back jumping
  int FC_BJ(SOLUTION, int, int, int *);

  // some functions needed
  void clear_setup(int);
  void clear_setup_bm_bj(int, int);
  void clear_setup_bm(int, int);
  void clear_setup_fc(int, int);
  void restore(int, int, int);
  int check_forward(int, int, int, int);
  int check_forward_fc_bj(int, int, int, int);
  void empty_conflicts(int, int);
  void union_conflicts(int, int);
  void clear_setup_cbj(int);

 	// arc consistency functions
	int value_arc(int k, int x, int y, int i);
	int revise_arc(int k, int x, int y);
	int pre_arc();
	int dom_empty(int x, int k);

	// path consistency algorithms
	int compose_and_intersect_path(int i, int k, int j, int d );
	void detUs_path(int U[VARS+1][VARS+1], int k );
	int pre_path();
  
  // domain.c functions for heuristic ordering of values in the domains

private:
  CONSTRAINT **N;    // NETWORK N as a 2D array structure, 
                     // elements are CONSTRAINTS
  int n;             // size of the NETWORK, we start labeling at 
                     // index 1
};


// default constructor
NETWORK::NETWORK(): n(50)   
{
  //  CONSTRAINT N[n][n];
  N = (CONSTRAINT **)new CONSTRAINT*[n+1];
  assert (N != 0);
  for(int i=1; i<=n; i++)
    {
      N[i] = (CONSTRAINT *)new CONSTRAINT[n+1]; 
      assert (N[i] != 0);
    }
}

// constructor defining the size of the NETWORK 
NETWORK::NETWORK(int size): n(size)
{
  if (size < 1)
    {
      cerr << "Illegal NETWORK size " << size << endl;
      exit(1);
    }
  N = new CONSTRAINT*[n+1];
  assert (N != 0);
  for(int i=1; i<=n; i++)
    {
      N[i] = new CONSTRAINT[n+1];
      assert (N[i] != 0);
    }
}

// destructor
NETWORK::~NETWORK()
{
  for (int i=1; i<=n; i++)
    {
      delete [](N[i]);
    }
  delete []N;
}
      
// Access the constraint on variables i and j for values a and b
char NETWORK::access(char i, char j, char a, char b)
{
  if ( i < 1 || i > n || j < 1 || j > n )
    {
      cerr << " illegal index for network when calling NETWORK::access" 
	<< endl;
      exit(1);
    }
  return(N[i][j].access(a, b));
}

// print the whole constraint network
void NETWORK::print()
{
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      N[i][j].print();
}

void NETWORK::printBoard(SOLUTION s){
	for(int i=1; i<=n; i++){
		printf("[ ");
		for(int j=0; j<n; j++){
			if (s[i] != j)
				printf(". ");
			else
				printf("Q ");
		}
		printf("]\n");
	}
}
