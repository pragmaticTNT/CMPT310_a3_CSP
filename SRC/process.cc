
// ****************************************************************
//  Sample function to process a solution found by one of the
//  backtracking routines. 
//  Note that N has to be a reference.
//  Otherwise the standard constructor for NETWORK is invoked which
//  causes an error if the actual parameter for NETWORK is of non
//  standard size.
// *****************************************************************

void NETWORK::process_solution( SOLUTION S )
{
  int i, j;
  // int n = N.size();
  
  //  Verify the solution to the problem is correct.
  
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (N[i][j].access( S[i], S[j]) == 0) 	
	  {
	    fprintf(stderr, "ERROR: Solution does not verify.\n");
	    return;
	  }
  
}




