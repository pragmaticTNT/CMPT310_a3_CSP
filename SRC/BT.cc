
// Simple chronological backtracking

// **********************************************************************
// Check if the current instantiation of the variables is consistent
// by looking at the edge between the current variable and all previours
// variables.
// **********************************************************************
 

int NETWORK::consistent_bt( SOLUTION solution, int current )
{
  int i;

  for( i=1; i<current; i++ )
    {
      checks++;
      if ( N[current][i].access(solution[current], solution[i]) == 0)
	return(0);
    }
  return(1);
}


// ************************************************************************
// Solve the constraint network using the simple chronological backtracking
// method (BT).
// ************************************************************************

int NETWORK::BT( SOLUTION solution, int current, int number, int *found )
{
  int i;
  int k = N[1][1].size();
  return(0);
}

