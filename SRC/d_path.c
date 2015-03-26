
#include "global.h"


/*
 *  Directional path consistency algorithm.
 */
int
path( C, n, d )
	NETWORK	C;
	int	n, d;
{
	int	i, j, k;
	int	a, b, c, result;


	for( k = n; k >= 1; k-- )
	for( i = 1; i <= k; i++ )
	for( j = i; j <= k; j++ ) {

		for( a = 0; a < d; a++ )
		for( b = 0; b < d; b++ ) {
			if( C [i][j][a][b] == 1 ) {

				result = 0;
				for( c = 0; !result && c < d; c++ )
					result = (C [i][k][a][c] &
						  C [k][k][c][c] &
						  C [j][k][b][c]);

				if( result == 0 ) {
					C [i][j][a][b] = 0;
					C [j][i][b][a] = 0;	/* inverse */
				}
			}
		}

	}

}

