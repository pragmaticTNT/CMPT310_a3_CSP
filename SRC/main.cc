
#include "global.h"
#include <time.h>

int main()
{

  const int TIME_LIMIT = 1000000;     // program execution terminates after 
                             // TIME_LIMIT seconds

  //  CONSTRAINT A(10);      // invoke the constructor for CONSTRAINT
  //  CONSTRAINT B[10][10];  // invoke the default constructor for CONSTRAINT
  //  CONSTRAINT C(7)[10][10];

  //  NETWORK M(3);
  NETWORK M(VARS);

  TIME_KEEPER T;

  SOLUTION S;
  int found;
  
  // Initialize solution S to 0
  for(int i=1; i<=VARS; i++)
    {
      S[i] = 0;
    }

  // generate an N-queens problem
  M.generate_Q();
  //M.print();

  cout << endl << "  " << VARS << "-Queens Problem" << endl << endl;
  
  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
/*
  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::BT, S, 1, &found);
  cout << "BT" <<endl;
  T.print_time();
//	M.printBoard(S);
  
  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::BJ, S, 1, &found);
  cout << "BJ" << endl;
  T.print_time();

*/
  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::BM, S, 1, &found);
  cout << "BM" << endl;
  T.print_time();

/*
  //T.start_time();
  // Solve the given CSP problem
  //M.solve(&NETWORK::FC, S, 1, &found);
  //cout << "FC" << endl;
  //T.print_time();

  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::BM_BJ, S, 1, &found);
  cout << "BM-BJ" << endl;
  T.print_time();

  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::FC_BJ, S, 1, &found);
  cout << "FC-BJ" << endl;
  T.print_time();

  T.start_time();
  // Solve the given CSP problem
  M.solve(&NETWORK::CBJ, S, 1, &found);
  cout << "CBJ" << endl;
  T.print_time();
*/
  cout << "\n  Number of solutions found so far: " << count << endl << endl;

  // Test if solution verifies and output the solution found
  show_solution( M, SOL_1 );

  cout << endl;
  return(0);
}





