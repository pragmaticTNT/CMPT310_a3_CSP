int NETWORK::compose_and_intersect_path(int i, int k, int j, int d )
{
	register int	a, b, c, result;
	int		changes = 0;


	for( a = 0; a < d; a++ )
	for( b = 0; b < d; b++ ) {
		if( N[i][j].access(a,b) == 1 ) {
		 result = (N[i][k].access(a,0) & N[k][k].access(0,0) & N[k][j].access(0,b));

			for( c = 1; !result && c < d; c++ )
				result /*|*/= (N[i][k].access(a,c) &
					   N[k][k].access(c,c) &
					   N[k][j].access(c,b));

			if( result == 0 ) {
				changes++;
				N[i][j].assign(a,b,0);
				N[j][i].assign(b,a,0);	/* inverse */
			}
		}
	}

	return( changes );
}


void NETWORK::detUs_path(int U[VARS+1][VARS+1], int k )
{
	int	i, j, a, b, all_ones;

	for( i = 1; i <= n; i++ )
	for( j = 1; j <= n; j++ ) {

		all_ones = 1;
		for( a = 0; a < k; a++ )
		for( b = 0; b < k && all_ones; b++ )
			all_ones = all_ones & (N[i][j].access(a,b) == 1);

		U [i][j] = all_ones;
	}
}


/*
 *  Path consistency algorithm.
 */
int NETWORK::pre_path()
{
	int	i, j, k, a, U [VARS+1][VARS+1];
	int d = N[1][1].size();
	STACK2 s;	

	s.init_stack();

	detUs_path( U, d );

	/*
	 *  First apply Floyd-Warshall version of path consistency,
	 *  pushing any edges that have changed.
	 */
	for( k = 1; k <= n; k++ )
	for( i = 1; i <= n; i++ ) if( !U [i][k] )
	for( j = i; j <= n; j++ ) if( !U [k][j] ) {

		if( compose_and_intersect_path( i, k, j, d ) ) {
			s.push( i, j );
			U [i][j] = 0;
			U [j][i] = 0;
		}
	}

	/*
	 *  Now process the edges that were pushed.
	 */
	while( !s.stack_empty() ) {
		s.pop( i, j );
		for( k = 1; k <= n; k++ ) {
			if( !U [j][k] &&
			    compose_and_intersect_path( i, j, k, d ) ) {
				s.push (i, k);
				U [i][k] = 0;
				U [k][i] = 0;
			}

			if( !U [k][i] &&
			    compose_and_intersect_path( k, i, j, d ) ) {
				s.push( k, j );
				U [k][j] = 0;
				U [j][k] = 0;
			}
		}
	}

	for( k = 1; k <= n; k++ ) {
		count = 0;
		for (a = 0; a < d; a++)
			count += N[k][k].access(a,a);
		if (count == 0)
			return(0);
	}

	return( 1 );
}

