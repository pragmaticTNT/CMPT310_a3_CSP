
// ********************************
// Clear the setup data structures.
// ********************************
void clear_setup_fc_bj(int n, int k)
{
  int i, j;
  
  for (i = 1; i <= n; i++) {
    jump_place[i] = 0;
    for (j = 0; j < k; j++)
      domains[i][j] = 0;
    for (j = 1; j <= n; j++)
      checking[i][j] = 0;
  }
}

//*****************************************************************************
// This function checks the edge between variables "i" and "j" to see which
// values in the domain of "j" can be eliminated due to the current
// instantiation of "i" as "value".  Note that given a variable "i" and an
// instantiation "v", domains[i][v] is 0 if the value is still allowed,
// otherwise it contains the variable which caused it to be eliminated.  If any
// value in "j" is deleted, this is noted in the "checking" matrix.  The number
// of values in the domain of "j" after all deletions is returned.
//*****************************************************************************
int NETWORK::check_forward_fc_bj( int k, int i, int j, int value)
{
  int l, old_count = 0, delete_count = 0;
  
  for (l = 0; l < k; l++)
    if (N[j][j].access(l, l) && (domains[j][l] == 0)) {
      old_count++;
      checks++;
      if (N[i][j].access(value, l) == 0) {
	domains[j][l] = i;
	delete_count++;
      }
    }
  if (delete_count)
    checking[i][j] = 1;
  return(old_count - delete_count);
}

// ****************************************************************************
// Function to restore the domain of variables which were eliminated due to the
// instantiation of variable "i".  A variable is known to have had a value
// deleted by looking at the "checking" matrix.
// ****************************************************************************
void restore_fc_bj(int i, int n, int k)
{
  int j, l;
  
  for (j = i + 1; j <= n; j++)
    if (checking[i][j])
      for (l = 0; l < k; l++) {
	checking[i][j] = 0;
	if (domains[j][l] == i)
	  domains[j][l] = 0;
      }
  checking[i][i] = 0;
}

//*****************************************************************************
// Check if the current instantiation of the variables is consistent by
// checking if the current instantiation of a variable will reduce some future
// variable's domain to the empty set, in which case the appropriate result is
// returned.
//*****************************************************************************
int NETWORK::consistent_fc_bj( int n, int k, int current, int value)
{
  int i;
  
  for (i = current + 1; i <= n; i++) {
    if (check_forward_fc_bj( k, current, i, value) == 0)
      return(i);
    }
  return(0);
}


// **************************************************************************
// Solve the CSP using the FORWARD CHECKING with BACKJUMPING (FC-BJ) method.
// Solve the constraint network using the FORWARD CHECKING with BACKJUMPING
// (FC-BJ) method.  If this is the first variable then initialize the data
// structures.  If a solution is found then update the "found" variable, call
// the function to process the solution, and return the value according to
// whether the first solution is desired or all solutions.  Then, check if the
// timer has expired, and if it has, return immediately.  Otherwise, begin
// checking each possible instantiation of the variable.  For each domain
// value, perform the following steps.  First, if preprocessing eliminated the
// value, disregard the rest of the loop.  Otherwise, instantiate the variable,
// check if the network is still consistent, and then call the backtracking
// routine recursively.  After checking each domain value, restore the domains
// which were eliminated by the instantiation.  After checking all possible
// domain values, determine the variable to jump back to, update the data
// structures, and return.
// ***************************************************************************

int NETWORK::FC_BJ(SOLUTION solution, int current, int number, int *found)
{
  int i, j, jump, fail;
  int k = N[1][1].size();
  
  jump_place[current] = 0;
  if (current == 1) 
    {
      clear_setup_fc_bj(n, k);
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
      if (N[current][current].access(i,i) == 0 || domains[current][i])
	continue;
      solution[current] = i;
      fail = consistent_fc_bj( n, k, current, solution[current] );
      if (!fail) 
	{
	  jump_place[current] = current - 1;
	  jump = FC_BJ(solution, current + 1, number, found);
	  if (jump != current)
	    return(jump);
        }
      restore_fc_bj(current, n, k);
      if (fail)
	for (j = 1; j < fail; j++)
	  if (checking[j][fail] && jump_place[current] < j)
	    jump_place[current] = j;
    }
  jump = jump_place[current];
  for (j = 1; j < current; j++)
    if (checking[j][current] && jump < j)
      jump = j;
  /*
     Replaced by three lines above.
     for (i = 1; i <= current; i++)
     if (jump < checking[i][current])
     jump = checking[i][current];
     */
  
  for (i = current; i >= jump; i--)
    restore_fc_bj(i, n, k);
  return(jump);
}
