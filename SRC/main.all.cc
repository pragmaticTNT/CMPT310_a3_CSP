
#include "global.h"
#include <time.h>

int main()
{

  const TIME_LIMIT = 300;     // program execution terminates after 
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
  //  M.print();

  cout << endl << "  " << VARS << "-Queens Problem" << endl << endl;
  
  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.BT, S, 2, &found);
  cout << "BT" <<endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;

  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.BJ, S, 2, &found);
  cout << "BJ" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;
  
  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.BM, S, 2, &found);
  cout << "BM" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;

  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.FC, S, 2, &found);
  cout << "FC" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;

  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.BM_BJ, S, 2, &found);
  cout << "BM-BJ" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl; 
  
  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.FC_BJ, S, 2, &found);
  cout << "FC-BJ" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;
  
  // Start and initialize timer
  start_timers();
  set_limit( VIRTUAL, TIME_LIMIT );
  // Solve the given CSP problem
  M.solve(M.CBJ, S, 2, &found);
  cout << "CBJ" << endl;
  cout << "  Number of solutions found in " << TIME_LIMIT << " seconds: "
    << count << endl << endl;

  // Test if solution verifies and output the solution found
  show_solution( M, SOL_1 );

  cout << endl;
  return(0);
}








