
// ****************************************************************
//  Sample function to process a solution found by one of the
//  backtracking routines. 
//  Note that N has to be a reference.
//  Otherwise the standard constructor for NETWORK is invoked which
//  causes an error if the actual parameter for NETWORK is of non
//  standard size.
// *****************************************************************

void show_solution( NETWORK &N, SOLUTION S )
{
  // Print the solution after it was verified

  N.process_solution( S );
  cout << "  Solution found: " << endl << "  ";
  for(int i = 1; i <= VARS; i++)
    {
      cout << (int) S[i]+1 << " ";
    }

  cout << endl;
   
  
}

