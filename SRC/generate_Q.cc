// Generate the CSP for the n-queens problem.
// n is the number of variables (rows) 
// k is the number of values    (columns)
// in a standard n-queens problem, n equals k

void NETWORK::generate_Q()
{
  int i, j, a, b;
  char k = N[1][1].size();
  // Initialize the (0-1) matrices.

  for( i=1; i<=n; i++ )
    for( j=1; j<=n; j++ ){
      if( i==j )
	{
	  // Diagonal means unary constraints, so initialize 
          // the CONSTRAINTS to 1, if a==b
	  
	  for( a=0; a<k; a++ )
	    for( b=0; b<k; b++ )
	      if( a==b )
		N[i][i].assign(a,b,1);
	      else
		N[i][i].assign(a,b,0);
	}
      else
	{
	  // Initialize the binary constraints
	  for( a=0; a<k; a++ )
	    for( b=0; b<k; b++ )
	      // column attack or diagonal attack
	      if( a==b || abs(a-b) == abs(i-j) )
		N[i][j].assign(a,b,0);
	      else
		N[i][j].assign(a,b,1);
	 }
	//printf("N[%d][%d]\n", i, j);
	//N[i][j].print();
  }
}

