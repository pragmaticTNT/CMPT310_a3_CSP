
//
//  Generate a random (n x n) adjacency matrix representation, C, of
//  a constraint satisfaction problem.  Each entry of C is a (k x k)
//  binary matrix.  The CSP has n variables with domains of size k.
//  An edge is labeled with a non-trivial constraint with independent
//  probability p/100 and is labeled with U with probability (1-p/100).
//  A non-trivial constraint is a random (0,1)-matrix where each entry
//  is a 1 with independent probability q/100, and a 0 with probability
//  (1-q/100).
///

void NETWORK::generate_R( int p, int q )

{
  int	i, j, a, b;
  char k = N[1][1].size();
  
  //
  //  Initialize the (0,1)-matrices.
  //
  for( i = 1; i <= n; i++ )
    for( j = 1; j <= n; j++ )
      if( i == j ) 
	{
	  //
	  // Diagonal: Initialize to I.
	  //
	  for( a = 0; a < k; a++ )
	    for( b = 0; b < k; b++ )
	      if( a == b )
		N[i][i].assign( a, b, 1);
	      else
		N[i][i].assign( a, b, 0);
	}
      else 
	{
	  //
	  //  Off Diagonal: Initialize to U.
	  //
	  for( a = 0; a < k; a++ )
	    for( b = 0; b < k; b++ )
	      N[i][j].assign( a, b, 1);
	}
  
  //
  //  Fill-in the (0,1)-matrices.
  //
  for( i = 1;   i <= n; i++ )
    for( j = i+1; j <= n; j++ ) {
      if( ( random() % 100 ) >= p )	// (100-p)% are labeled U 
	; // leave it as a U 
      else 
	{
	  for( a = 0; a < k; a++ )
	    for( b = 0; b < k; b++ ) 
	      {
		if( ( random() % 100 ) < q )	//  q% ones  
		  ; // leave it as a one 
		else 
		  {
		    N[i][j].assign( a, b, 0);
		    N[j][i].assign( b, a, 0);
		  }
	      }
	}
    }
}

