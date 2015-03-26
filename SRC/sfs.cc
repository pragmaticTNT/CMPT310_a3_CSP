
// save the first solution that is found by any of 
// the search strategies

void sfs( SOLUTION solution )
{
  for( int i = 1; i <= VARS; i++)
    SOL_1[i] = solution[i];
}
