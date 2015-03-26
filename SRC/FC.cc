
// ***************************************************************************
// Clear the setup data structures.
// ***************************************************************************
void NETWORK::clear_setup_fc(int n, int k)
{
  int i, j;
  
  for (i = 1; i <= n; i++) {
    for (j = 0; j < k; j++)
      domains[i][j] = 0;
    for (j = 1; j <= n; j++)
      checking[i][j] = 0;
  }
}


// ***************************************************************************
// This function checks the edge between variables "i" and "j" to see which
// values in the domain of "j" can be eliminated due to the current
// instantiation of "i" as "value".  Note that given a variable "i" and an
// instantiation "v", domains[i][v] is 0 if the value is still allowed,
// otherwise it contains the variable which caused it to be eliminated.  If any
// value in "j" is deleted, this is noted in the "checking" matrix.  The number
// of values in the domain of "j" after all deletions is returned.
// ***************************************************************************
int NETWORK::check_forward(int k, int i, int j, int value)
{
  int m, old_count = 0, delete_count = 0;
  return(old_count - delete_count);
}


// ***************************************************************************
// Function to restore the domain of variables which were eliminated due to the
// instantiation of variable "i".  A variable is known to have had a value
// deleted by looking at the "checking" matrix.
// ***************************************************************************
void NETWORK::restore(int i, int m, int k)
{
  int j, l;
  
  for (j = i + 1; j <= m; j++)
    if (checking[i][j]) 
      {
	checking[i][j] = 0;
	for (l = 0; l < k; l++)
	  if (domains[j][l] == i)
	    domains[j][l] = 0;
      }
}


// ***************************************************************************
// Check if the current instantiation of the variables is consistent by
// checking if the current instantiation of a variable will reduce some future
// variable's domain to the empty set, in which case the appropriate result is
// returned.
// ***************************************************************************
int NETWORK::consistent_fc(int k, int current, int value)
{
  int i;
  
  for (i = current + 1; i <= n; i++) 
    {
      if (check_forward(k, current, i, value) == 0)
	return(0);
    }
  return(1);
}


// ***************************************************************************
// Solve the constraint network using the simple FORWARD CHECKING (FC) method.
// If this is the first variable then initialize the data structures.  If a
// solution is found then update the "found" variable, call the function to
// process the solution, and return the value according to whether the first
// solution is desired or all solutions.  Then, check if the timer has expired,
// and if it has, return immediately.  Otherwise, begin checking each possible
// instantiation of the variable.  For each domain value, perform the following
// steps.  First, if preprocessing eliminated the value, disregard the rest of
// the loop.  Otherwise, instantiate the variable, check if the network is
// still consistent, and then call the backtracking routine recursively.  After
// checking each domain value, restore the domains which were eliminated by the
// instantiation.  After checking all possible domain values, return.
// ***************************************************************************
int NETWORK::FC(SOLUTION solution, int current, int number, int *found)
{
  int i;
  int k = N[1][1].size();
  return 0;
}
