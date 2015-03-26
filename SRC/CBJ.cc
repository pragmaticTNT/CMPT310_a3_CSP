//****************************************************************************
// Clear the setup data structure.
//****************************************************************************
void NETWORK::clear_setup_cbj(int n)
{
  int i, j;

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      conflicts[i][j] = 0;
}


//****************************************************************************
// Create the union of two sets which hold where the conflicts took place.  As
// described by Prosser, this is necessary to be able to continue
// conflict-directed backjumping correctly to ensure the correct variable
// will not be missed. The maximum in the set for variable "i" is retained
// in position "conflicts[i][i]" for future reference.
//****************************************************************************
void NETWORK::union_conflicts(int i, int j)
{
  int n;

  for (n = 1; n < i; n++) {
    conflicts[i][n] = conflicts[i][n] || conflicts[j][n];
    if (conflicts[i][n] && conflicts[i][i] < n)
      conflicts[i][i] = n;
  }
}


//****************************************************************************
// Reset the sets between the given indexes to be empty.  This allows for new
// information to be stored in these sets without the old information
// misleading the algorithm.
//****************************************************************************
void NETWORK::empty_conflicts(int from, int to)
{
  int i, j;

  for (i = from + 1; i <= to; i++)
    for (j = 1; j <= i; j++)
      conflicts[i][j] = 0;
}


//****************************************************************************
// Check if the current instantiation of the variables is consistent by
// looking at the edge between the current variable and all previous variables.
// If a conflict exists, the set of conflicts with the current variable is
// updated to reflect this fact.
//****************************************************************************
int NETWORK::consistent_cbj(SOLUTION solution, int current)
{
  int i;

  for (i = 1; i < current; i++) {
    checks++;
    if (N[current][i].access(solution[current],solution[i]) == 0) {
      conflicts[current][i] = 1;
      if (conflicts[current][current] < i)
	conflicts[current][current] = i;
      return(0);
    }
  }
  return(1);
}


//****************************************************************************
// Solve the constraint network using the CONFLICT-DIRECTED BACKJUMPING (CBJ) method.
// If this is the first variable then initialize the data structures.  If a
// solution is found then update the "found" variable, call the function to
// process the solution, and return the value according to whether the first
// solution is desired or all solutions.  Then, check if the timer has expired,
// and if it has, return immediately.  Otherwise, begin checking each possible
// instantiation of the variable.  For each domain value, perform the following
// steps.  First, if preprocessing eliminated the value, disregard the rest of
// the loop.  Otherwise, instantiate the variable, check if the network is
// still consistent, and then call the backtracking routine recursively.  After
// checking all possible domain values, determine the variable to jump back to
// and return this value.
//****************************************************************************
int NETWORK::CBJ(SOLUTION solution, int current, int number, int *found)
{
  int i, jump, curr = count;
  int k = N[1][1].size();

  if (current == 1)
    {
      clear_setup_cbj(n);
      *found = 0;
    }
  else if (current > n)
    {
      process_solution( solution );
      *found = 1;
      if ( count == 1 )
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
      if (consistent_cbj(solution, current))
	{
	  jump = CBJ(solution, current + 1, number, found);
	  if (jump != current)
	    return(jump);
	}
    }
  jump = (curr == count) ? conflicts[current][current] : current - 1;
  union_conflicts(jump, current);
  empty_conflicts(jump, current);
  return(jump);
}

