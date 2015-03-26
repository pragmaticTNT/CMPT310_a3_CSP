
// ********************************
// Clear the setup data structures.
// ********************************

void NETWORK::clear_setup_bm_bj(int n, int k)
{
  int i, j;
  
  for (i = 1; i <= n; i++) 
    {
      jump_place[i] = 0;
      mbl[i] = 1;
      for (j = 0; j < k; j++)
	mcl[i][j] = 1;
    }
}


// ****************************************************************************
// Check if the current instantiation of the variables is consistent by
// looking at the edge between the current variable and all previous variables.
// However, this is not done if the algorithm has not backed up enough to
// prevent a previous conflict from occurring again.  If a check is done
// between two variables, this information is retained for later use. On the
// other hand if a conflict exists, the set of conflicts with the current
//  variable is updated to reflect this fact.
// ****************************************************************************

int NETWORK::consistent_bmbj(SOLUTION solution, int current)
{
  int i;
  
  if (mcl[current][solution[current]] < mbl[current])
    return(0);
  for (i = mbl[current]; i < current; i++) 
    {
      checks++;
      mcl[current][solution[current]] = i;
      if (N[current][i].access(solution[current],solution[i]) == 0) 
	{
	  if (i > jump_place[current])
	    jump_place[current] = i;
	  return(0);
	}
    }
  jump_place[current] = current - 1;
  return(1);
}


// ***************************************************************************
// Solve the constraint network using the BACKMARKING with BACKJUMPING (BM-BJ)
// method.  If this is the first variable then initialize the data structures.
// If a solution is found then update the "found" variable, call the function
// to process the solution, and return the value according to whether the first
// solution is desired or all solutions.  Then, check if the timer has expired,
// and if it has, return immediately.  Otherwise, begin checking each possible
// instantiation of the variable.  For each domain value, perform the following
// steps.  First, if preprocessing eliminated the value, disregard the rest of
// the loop.  Otherwise, instantiate the variable, check if the network is
// still consistent, and then call the backtracking routine recursively.  After
// checking all possible domain values, update the minimum backup level data
// structure and return the variable to which the algorithm should jump back.
// ***************************************************************************

int NETWORK::BM_BJ(SOLUTION solution, int current, int number, int *found)
{
  int i, jump, h;
  int k = N[1][1].size();
  
  
  jump_place[current] = 0;
  if (current == 1) 
    {
      clear_setup_bm_bj(n, k);
      *found = 0;
    } 
  else 
    if (current > n) 
      {
	process_solution( solution );
        *found = 1;
	if ( count == 0 )
	  // save first solution into sol_1
	  sfs( solution ); 
	count++;
        return(number == 1 ? 0 : n);
      }
  if (time_expired())
    return(0);
  for (i = 0; i < k; i++) 
    {
      if (N[current][current].access(i,i) == 0)
	continue;
      solution[current] = i;
      if (consistent_bmbj(solution, current)) 
	{
	  jump = BM_BJ(solution, current + 1, number, found);
	  if (jump != current)
	    return(jump);
	}
    }
  h = jump_place[current];
  mbl[current] = h;
  for (i = h+1; i <= n; i++)
    if (mbl[i] > h)
      mbl[i] = h;
	/*
     Replaced by 5 lines above
     mbl[current] = jump_place[current];
     for (i = current ; i <= n; i++)
     if (mbl[i] > (current - 1))
     mbl[i] = current - 1;
	*/
 
  return(jump_place[current]);
}
