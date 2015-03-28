// ********************************
// Clear the setup data structure.
// ********************************

void NETWORK::clear_setup(int n)
{
  int i;

  for (i = 1; i <= n; i++)
    jump_place[i] = 0;
}


// ****************************************************************************
// Check if the current instantiation of the variables is consistent and update
// the jump back place array appropriately.  If a conflict is found and it is
// closer to the current variable, store that value.  Otherwise, if no conflict
// is found, the "conflict value" is the previous variable, by default.
// ****************************************************************************

int NETWORK::consistent_bj(SOLUTION solution, int current)
{
  int i;

  for (i = 1; i < current; i++)
    {
      checks++;
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


// ****************************************************************************
// Solve the constraint network using the BACKJUMPING (BJ) method.  If this is
// the first variable then initialize the data structures.  If a solution is
// found then update the "found" variable, call the function to process the
// solution, and return the value according to whether the first solution is
// desired or all solutions.  Then, check if the timer has expired, and if it
// has, return immediately.  Otherwise, begin checking each possible
// instantiation of the variable.  For each domain value, perform the following
// steps.  First, if preprocessing eliminated the value, disregard the rest of
// the loop.  Otherwise, instantiate the variable, check if the network is
// still consistent, and then call the backjumping routine recursively.  After
// checking all possible domain values, use jump_place to return the variable
// to which the algorithm should jump back.
// ****************************************************************************

int NETWORK::BJ(SOLUTION solution, int current, int number, int *found)
{
  int i, jump;
  int k = N[1][1].size();
	//for (i = 0; i<n; i++)
	//	printf("%d ", solution[i]);
	//printf("\n");
	printf("current: %d\n", current);

  jump_place[current] = 0;
  if (current == 1)
    {
      clear_setup(n);
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
	return(number == 1 ? 0 : n);
      }
  if (time_expired())
    return(0);
  for (i = 0; i < k; i++)
    {
      if (N[current][current].access(i,i) == 0)
	continue;
      solution[current] = i;
      if (consistent_bj(solution, current))
	{
	  jump = BJ(solution, current + 1, number, found);
	  if (jump != current)
	    return(jump);
	}
    }
  return(jump_place[current]);
}





