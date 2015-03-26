
//
//  Generate a consistent random (n x n) adjacency matrix representation,
//  C, of a constraint satisfaction problem.  Each entry of C is a (k x k)
//  binary matrix.  The CSP has n variables with domains of size k.
//  An edge is labeled with a non-trivial constraint with independent
//  probability p/100 and is labeled with U with probability (1-p/100).
//  A non-trivial constraint is a random (0,1)-matrix where each entry
//  is a 1 with independent probability q/100, and a 0 with probability
//  (1-q/100).
//

void NETWORK::generate_S( int p, int q )

{
  int	i, j;
  int	soln[n];
  char k = N[1][1].size();
  
  //
  //  generate a (possibly) inconsistent csp
  //
  generate_R( p, q );
  
  //
  //  generate a random instantiation
  //
  for( i = 1; i <= n; i++ )
    soln[i] = (random() % k);
  
  //
  //  adjust the constraints so that the
  //  instantiation is a solution
  //
  for( i = 1;   i <  n; i++ )
    for( j = i+1; j <= n; j++ ) 
      {
	N[i][j].assign( soln[i], soln[j], 1);
	N[j][i].assign( soln[j], soln[i], 1);
      }
}

