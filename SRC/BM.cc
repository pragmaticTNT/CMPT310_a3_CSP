
// *********************************************************************
// Clear the setup data structures (however, set them to the appropriate
// values).
// *********************************************************************

void NETWORK::clear_setup_bm(int n, int k)
{
  int i, j;
  
  for (i = 1; i <= n; i++) 
    {
      mbl[i] = 1;
      for (j = 0; j < k; j++)
	mcl[i][j] = 1;
    }
}


// ***************************************************************************
// Check if the current instantiation of the variables is consistent by
// looking at the edge between the current variable and all previous variables.
// However, this is not done if the algorithm has not backed up enough to
// prevent a previous conflict from occurring again.  If a check is done
// between two variables, this information is retained for later use.
// ***************************************************************************

int NETWORK::consistent_bm(SOLUTION solution, int current)
{
  int i;
  
  if (mcl[current][solution[current]] < mbl[current])
    return(0);
  for (i = mbl[current]; i < current; i++) 
    {
      checks++;
      mcl[current][solution[current]] = i;
      if (N[current][i].access(solution[current],solution[i]) == 0)
	return(0);
    }
  return(1);
}


// ***************************************************************************
// Solve the constraint network using the simple BACKMARKING (BM) method.  If
// this is the first variable then initialize the data structures.  If a
// solution is found then update the "found" variable, call the function to
// process the solution, and return the value according to whether the first
// solution is desired or all solutions.  Then, check if the timer has expired,
// and if it has, return immediately.  Otherwise, begin checking each possible
// instantiation of the variable.  For each domain value, perform the following
// steps.  First, if preprocessing eliminated the value, disregard the rest of
// the loop.  Otherwise, instantiate the variable, check if the network is
// still consistent, and then call the backtracking routine recursively.  After
// checking all possible domain values, update the minimum backup level data
// structure and return.
// ****************************************************************************

int NETWORK::BM(SOLUTION solution, int current, int number, int *found)
{
  int i;
  int k = N[1][1].size();
  
  if (current == 1) 
    {
      clear_setup_bm(n, k);
      *found = 0;
    } 
  else 
    if (current > n) 
      {
	process_solution( solution );
	*found = 1;
	if ( count == 0 )
	  // save first solution into SOL_1
	  sfs( solution ); 
	count++;
	return(number == 1 ? 1 : 0);
      }
  if (time_expired())
    return(1);
  for (i = 0; i < k; i++) 
    {
      if (N[current][current].access(i,i) == 0)
	continue;
      solution[current] = i;
      if (consistent_bm(solution, current))
	if (BM(solution, current + 1, number, found))
	  return(1);
    }
  mbl[current] = current - 1;
  current--;
  for (i = current; i <= n; i++)
    if (mbl[i] > current)
      mbl[i] = current;
  return(0);
}
